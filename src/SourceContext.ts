/*
 * This file is released under the MIT license.
 * Copyright (c) 2016, 2017, Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict"

// This file contains the handling for a single source file. It provides syntactic and semantic
// informations, symbol lookups and more.

import * as child_process from 'child_process';
import * as path from 'path';
import * as fs from 'fs';

import {
    ANTLRInputStream, CommonTokenStream, BailErrorStrategy, DefaultErrorStrategy, Token, LexerInterpreter,
    ParserInterpreter, CharStream, RuleContext, ParserRuleContext, CommonToken
} from 'antlr4ts';
import {
    PredictionMode, ATNState, RuleTransition, TransitionType, ATNStateType, BlockStartState, DecisionState,
    RuleStopState, PlusBlockStartState, StarLoopEntryState, RuleStartState
} from 'antlr4ts/atn';
import { ParseCancellationException, IntervalSet } from 'antlr4ts/misc';
import { ParseTreeWalker, TerminalNode, ParseTree, ParseTreeListener } from 'antlr4ts/tree';

import { CodeCompletionCore, Symbol, ScopedSymbol, LiteralSymbol } from "antlr4-c3";

import {
    ANTLRv4Parser, ParserRuleSpecContext, LexerRuleSpecContext, GrammarSpecContext, RuleSpecContext, OptionsSpecContext,
    TokensSpecContext
} from '../parser/ANTLRv4Parser';
import { ANTLRv4Lexer } from '../parser/ANTLRv4Lexer';

import {
    SymbolKind, SymbolInfo, DiagnosticEntry, DiagnosticType, ReferenceNode, ATNGraphData, GenerationOptions,
    SentenceGenerationOptions, FormattingOptions
} from './AntlrLanguageSupport';

import { ContextErrorListener, ContextLexerErrorListener } from './ContextErrorListener';

import { DetailsListener } from './DetailsListener';
import { SemanticListener } from './SemanticListener';
import { RuleVisitor } from './RuleVisitor';
import { InterpreterDataReader } from "./InterpreterDataReader";
import { ErrorParser } from "./ErrorParser";

import {
    GrapsSymbolTable, BuiltInChannelSymbol, BuiltInLexerTokenSymbol, BuiltInModeSymbol, ParserRuleSymbol,
    VirtualLexerTokenSymbol, FragmentLexerTokenSymbol, LexerTokenSymbol
} from "./GrapsSymbolTable";

import { LexicalRange } from "../index";
import { SentenceGenerator } from "./SentenceGenerator";
import { GrammarFormatter } from "./Formatter";

enum GrammarType { Unknown, Parser, Lexer, Combined };

// One source context per file. Source contexts can reference each other (e.g. for symbol lookups).
export class SourceContext {
    public symbolTable: GrapsSymbolTable;
    public references: SourceContext[] = []; // Contexts referencing us.
    public sourceId: string;

    /* @internal */
    public diagnostics: DiagnosticEntry[] = [];

    constructor(public fileName: string) {
        this.sourceId = path.basename(fileName, path.extname(fileName));
        this.symbolTable =  new GrapsSymbolTable(this.sourceId, { allowDuplicateSymbols: true }, this);

        // Initialize static global symbol table, if not yet done.
        if (!SourceContext.globalSymbols.resolve("EOF")) {
            SourceContext.globalSymbols.addNewSymbolOfType(BuiltInChannelSymbol, undefined, "DEFAULT_TOKEN_CHANNEL");
            SourceContext.globalSymbols.addNewSymbolOfType(BuiltInChannelSymbol, undefined, "HIDDEN");
            SourceContext.globalSymbols.addNewSymbolOfType(BuiltInLexerTokenSymbol, undefined, "EOF");
            SourceContext.globalSymbols.addNewSymbolOfType(BuiltInModeSymbol, undefined, "DEFAULT_MODE");
        }
    }

    public infoForSymbolAtPosition(column: number, row: number, limitToChildren: boolean): SymbolInfo | undefined {
        let terminal = parseTreeFromPosition(this.tree!, column, row);
        if (!terminal || !(terminal instanceof TerminalNode)) {
            return undefined;
        }

        // If limitToChildren is set we only want to show info for symbols in specific contexts.
        // These are contexts which are used as subrules in rule definitions.
        if (!limitToChildren) {
            return this.getSymbolInfo(terminal.text);
        }

        let parent = (terminal.parent as RuleContext);
        if (parent.ruleIndex == ANTLRv4Parser.RULE_identifier) {
            parent = (parent.parent as RuleContext);
        }

        switch (parent.ruleIndex) {
            case ANTLRv4Parser.RULE_ruleref:
            case ANTLRv4Parser.RULE_terminalRule:
            case ANTLRv4Parser.RULE_lexerCommandExpr:
            case ANTLRv4Parser.RULE_optionValue:
            case ANTLRv4Parser.RULE_delegateGrammar:
            case ANTLRv4Parser.RULE_modeSpec:
            case ANTLRv4Parser.RULE_setElement:
                return this.getSymbolInfo(terminal.text);
        }

        return undefined;
    }

    /**
     * Returns the lexical range of the closest symbol scope that covers the given location.
     * @param ruleScope if true find the enclosing rule (if any) and return it's range, instead of the directly enclosing scope.
     */
    public enclosingRangeForSymbol(column: number, row: number, ruleScope: boolean): LexicalRange | undefined {
        let context = parseTreeFromPosition(this.tree!, column, row);
        if (!context) {
            return;
        }

        if (context instanceof TerminalNode) {
            context = context.parent;
        }

        if (ruleScope) {
            let run = context;
            while (run && !(run instanceof RuleSpecContext) && !(run instanceof OptionsSpecContext) && !(run instanceof TokensSpecContext)) {
                run = run.parent;
            }
            if (run) {
                context = run;
            }
        }

        if (context instanceof ParserRuleContext) {
            if (context.stop) {
                return {
                    start: { column: context.start.charPositionInLine, row: context.start.line },
                    end: { column: context.stop.charPositionInLine, row: context.stop.line }
                };
            }

            let length = context.start.inputStream!.size - context.start.startIndex + 1;
            return {
                start: { column: context.start.charPositionInLine, row: context.start.line },
                end: { column: context.start.charPositionInLine + length, row: context.start.line }
            };
        }
    }

    public listSymbols(includeDependencies: boolean): SymbolInfo[] {
        return this.symbolTable.listSymbols(includeDependencies);
    }

    public getCodeCompletionCandidates(column: number, row: number): SymbolInfo[] {
        if (!this.parser) {
            return [];
        }

        let core = new CodeCompletionCore(this.parser);
        core.showResult = false;
        core.ignoredTokens = new Set([
            ANTLRv4Lexer.TOKEN_REF,
            ANTLRv4Lexer.RULE_REF,
            ANTLRv4Lexer.LEXER_CHAR_SET,
            ANTLRv4Lexer.DOC_COMMENT,
            ANTLRv4Lexer.BLOCK_COMMENT,
            ANTLRv4Lexer.LINE_COMMENT,
            ANTLRv4Lexer.INT,
            ANTLRv4Lexer.STRING_LITERAL,
            ANTLRv4Lexer.UNTERMINATED_STRING_LITERAL,
            ANTLRv4Lexer.MODE,
            ANTLRv4Lexer.COLON,
            ANTLRv4Lexer.COLONCOLON,
            ANTLRv4Lexer.COMMA,
            ANTLRv4Lexer.SEMI,
            ANTLRv4Lexer.LPAREN,
            ANTLRv4Lexer.RPAREN,
            ANTLRv4Lexer.LBRACE,
            ANTLRv4Lexer.RBRACE,
            //ANTLRv4Lexer.RARROW,
            //ANTLRv4Lexer.LT,
            ANTLRv4Lexer.GT,
            //ANTLRv4Lexer.ASSIGN,
            //ANTLRv4Lexer.QUESTION,
            //ANTLRv4Lexer.STAR,
            //ANTLRv4Lexer.PLUS_ASSIGN,
            //ANTLRv4Lexer.PLUS,
            //ANTLRv4Lexer.OR,
            ANTLRv4Lexer.DOLLAR,
            ANTLRv4Lexer.RANGE,
            ANTLRv4Lexer.DOT,
            ANTLRv4Lexer.AT,
            ANTLRv4Lexer.POUND,
            ANTLRv4Lexer.NOT,
            ANTLRv4Lexer.ID,
            ANTLRv4Lexer.WS,
            ANTLRv4Lexer.END_ARGUMENT,
            ANTLRv4Lexer.UNTERMINATED_ARGUMENT,
            ANTLRv4Lexer.ARGUMENT_CONTENT,
            ANTLRv4Lexer.END_ACTION,
            ANTLRv4Lexer.UNTERMINATED_ACTION,
            ANTLRv4Lexer.ACTION_CONTENT,
            ANTLRv4Lexer.UNTERMINATED_CHAR_SET,
            ANTLRv4Lexer.EOF,
            -2, // Errorneously inserted. Needs fix in antlr4-c3.
        ]);

        core.preferredRules = new Set([
            ANTLRv4Parser.RULE_argActionBlock,
            ANTLRv4Parser.RULE_actionBlock,
            ANTLRv4Parser.RULE_terminalRule,
            ANTLRv4Parser.RULE_lexerCommandName,
            ANTLRv4Parser.RULE_identifier,
            ANTLRv4Parser.RULE_ruleref,
        ]);

        // Search the token index which covers our caret position.
        let index: number;
        this.tokenStream.fill();
        for (index = 0; ; ++index) {
            let token = this.tokenStream.get(index);
            //console.log(token.toString());
            if (token.type == Token.EOF || token.line > row) {
                break;
            }
            if (token.line < row) {
                continue;
            }
            let length = token.text ? token.text.length : 0;
            if ((token.charPositionInLine + length) >= column) {
                break;
            }
        }

        let candidates = core.collectCandidates(index);
        let result: SymbolInfo[] = [];

        candidates.tokens.forEach((following: number[], type: number) => {
            var info = new SymbolInfo();
            info.source = this.fileName; // TODO: need source info from c3.

            switch (type) {
                case ANTLRv4Lexer.RARROW:
                    info.kind = SymbolKind.Operator;
                    info.name = "->";
                    info.description = "Lexer action introducer";
                    break;

                case ANTLRv4Lexer.LT:
                    info.kind = SymbolKind.Operator;
                    info.name = "< key = value >";
                    info.description = "Rule element option";
                    break

                case ANTLRv4Lexer.ASSIGN:
                    info.kind = SymbolKind.Operator;
                    info.name = "=";
                    info.description = "Variable assignment";
                    break;

                case ANTLRv4Lexer.QUESTION:
                    info.kind = SymbolKind.Operator;
                    info.name = "?";
                    info.description = "Zero or one repetition operator";
                    break;

                case ANTLRv4Lexer.STAR:
                    info.kind = SymbolKind.Operator;
                    info.name = "*";
                    info.description = "Zero or more repetition operator";
                    break;

                case ANTLRv4Lexer.PLUS_ASSIGN:
                    info.kind = SymbolKind.Operator;
                    info.name = "+=";
                    info.description = "Variable list addition";
                    break;

                case ANTLRv4Lexer.PLUS:
                    info.kind = SymbolKind.Operator;
                    info.name = "+";
                    info.description = "One or more repetition operator";
                    break;

                case ANTLRv4Lexer.OR:
                    info.kind = SymbolKind.Operator;
                    info.name = "|";
                    info.description = "Rule alt separator";
                    break;

                default: {
                    let value = this.parser!.vocabulary.getDisplayName(type);
                    info.kind = SymbolKind.Keyword;
                    info.name = value[0] === "'" ? value.substr(1, value.length - 2) : value; // Remove quotes.
                    break;
                }
            }

            result.push(info);
        });

        candidates.rules.forEach((callStack, key) => {
            switch (key) {
                case ANTLRv4Parser.RULE_argActionBlock: {
                    result.push({ kind: SymbolKind.Action, name: "[ argument action code ]", source: this.fileName, definition: undefined, description: undefined });
                    break;
                }

                case ANTLRv4Parser.RULE_actionBlock: {
                    result.push({ kind: SymbolKind.Action, name: "{ action code }", source: this.fileName, definition: undefined, description: undefined });
                    // Include predicates only when we are in a lexer or parser element.
                    if (callStack[callStack.length - 1] === ANTLRv4Parser.RULE_lexerElement
                        || callStack[callStack.length - 1] === ANTLRv4Parser.RULE_element) {
                        result.push({ kind: SymbolKind.Predicate, name: "{ predicate }?", source: this.fileName, definition: undefined, description: undefined });
                    }
                    break;
                }

                case ANTLRv4Parser.RULE_terminalRule: { // Lexer rules.
                    this.symbolTable.getAllSymbols(BuiltInLexerTokenSymbol).forEach(symbol => {
                        if (symbol.name !== "EOF") {
                            result.push({ kind: SymbolKind.BuiltInLexerToken, name: symbol.name, source: this.fileName, definition: undefined, description: undefined });
                        }
                    });
                    this.symbolTable.getAllSymbols(VirtualLexerTokenSymbol).forEach(symbol => {
                        result.push({ kind: SymbolKind.VirtualLexerToken, name: symbol.name, source: this.fileName, definition: undefined, description: undefined });
                    });

                    // Include fragment rules only when referenced from a lexer rule.
                    if (callStack[callStack.length - 1] === ANTLRv4Parser.RULE_lexerAtom) {
                        this.symbolTable.getAllSymbols(FragmentLexerTokenSymbol).forEach(symbol => {
                            result.push({
                                kind: SymbolKind.FragmentLexerToken,
                                name: symbol.name,
                                source: this.fileName,
                                definition: undefined,
                                description: undefined
                            });
                        });
                    }

                    this.symbolTable.getAllSymbols(LexerTokenSymbol).forEach(symbol => {
                        result.push({
                            kind: SymbolKind.LexerToken,
                            name: symbol.name,
                            source: this.fileName,
                            definition: undefined,
                            description: undefined
                        });
                    });

                    break;
                }

                case ANTLRv4Parser.RULE_lexerCommandName: {
                    ["channel", "skip", "more", "mode", "push", "pop"].forEach(symbol => {
                        result.push({ kind: SymbolKind.Keyword, name: symbol, source: this.fileName, definition: undefined, description: undefined });
                    });
                    break;
                }

                case ANTLRv4Parser.RULE_ruleref: {
                    this.symbolTable.getAllSymbols(ParserRuleSymbol).forEach(symbol => {
                        result.push({ kind: SymbolKind.ParserRule, name: symbol.name, source: this.fileName, definition: undefined, description: undefined });
                    });
                    break;
                }

                case ANTLRv4Parser.RULE_identifier: {
                    // Identifiers can be a lot of things. We only handle special cases here.
                    // More concrete identifiers should be captured by rules further up in the call chain.
                    switch (callStack[callStack.length - 1]) {
                        case ANTLRv4Parser.RULE_option: {
                            ["superClass", "tokenVocab", "TokenLabelType", "contextSuperClass", "exportMacro"].forEach(symbol => {
                                result.push({ kind: SymbolKind.Option, name: symbol, source: this.fileName, definition: undefined, description: undefined });
                            });
                            break;
                        }

                        case ANTLRv4Parser.RULE_namedAction: {
                            ["header", "members", "preinclude", "postinclude", "context", "declarations", "definitions",
                                "listenerpreinclude", "listenerpostinclude", "listenerdeclarations", "listenermembers", "listenerdefinitions",
                                "baselistenerpreinclude", "baselistenerpostinclude", "baselistenerdeclarations", "baselistenermembers",
                                "baselistenerdefinitions", "visitorpreinclude", "visitorpostinclude", "visitordeclarations", "visitormembers",
                                "visitordefinitions", "basevisitorpreinclude", "basevisitorpostinclude", "basevisitordeclarations", "basevisitormembers",
                                "basevisitordefinitions"].forEach(symbol => {
                                    result.push({ kind: SymbolKind.Keyword, name: symbol, source: this.fileName, definition: undefined, description: undefined });
                                });

                            break;
                        }
                    }

                    break;
                }

            }
        });

        return result;
    }

    /**
     * Should be called on every change to keep the input stream up to date particularly for code completion.
     * This call doesn't do any expensive processing (parse() does).
     */
    public setText(source: string) {
        let input = new ANTLRInputStream(source);
        let lexer = new ANTLRv4Lexer(input);

        // There won't be lexer errors actually. They are silently bubbled up and will cause parser errors.
        lexer.removeErrorListeners();
        lexer.addErrorListener(this.lexerErrorListener);
        this.tokenStream = new CommonTokenStream(lexer);
        this.parser = undefined;
    }

    public parse(): string[] {
        // Rewind the input stream for a new parse run.
        // Might be unnecessary when we just created that via setText.
        this.tokenStream.seek(0);
        this.parser = new ANTLRv4Parser(this.tokenStream);
        this.parser.removeErrorListeners();
        this.parser.addErrorListener(this.errorListener);

        this.parser.errorHandler = new BailErrorStrategy();
        this.parser.interpreter.setPredictionMode(PredictionMode.SLL);

        this.tree = undefined;
        this.lexerInterpreter = undefined;
        this.parserInterpreter = undefined;
        this.semanticAnalysisDone = false;
        this.diagnostics.length = 0;
        this.imports.length = 0;
        this.grammarType = GrammarType.Unknown;

        this.symbolTable.clear();
        this.symbolTable.addDependencies(SourceContext.globalSymbols);
        try {
            this.tree = this.parser.grammarSpec();
        } catch (e) {
            if (e instanceof ParseCancellationException) {
                this.tokenStream.seek(0);
                this.parser.reset();
                this.parser.errorHandler = new DefaultErrorStrategy();
                this.parser.interpreter.setPredictionMode(PredictionMode.LL);
                this.tree = this.parser.grammarSpec();
            } else {
                throw e;
            }
        }

        if (this.tree && this.tree.childCount > 0) {
            try {
                let typeContext = this.tree.grammarType();
                if (typeContext.LEXER()) {
                    this.grammarType = GrammarType.Lexer;
                } else if (typeContext.PARSER()) {
                    this.grammarType = GrammarType.Parser;
                } else {
	                this.grammarType = GrammarType.Combined;
                }
		    } catch (e) {
            }
        }
        this.symbolTable.tree = this.tree;
        let listener: DetailsListener = new DetailsListener(this.symbolTable, this.imports);
        ParseTreeWalker.DEFAULT.walk(listener as ParseTreeListener, this.tree);

        return this.imports;
    }

    public getDiagnostics(): DiagnosticEntry[] {
        this.runSemanticAnalysisIfNeeded();

        return this.diagnostics;
    }

    // Returns all rules with a reference count of 0.
    public getUnreferencedRules(): string[] {
        return this.symbolTable.getUnreferencedSymbols();
    }

    public getReferenceGraph(): Map<string, ReferenceNode> {
        this.runSemanticAnalysisIfNeeded();

        let result = new Map();
        for (let symbol of this.symbolTable.getAllSymbols(Symbol, false)) {
            if (symbol instanceof ParserRuleSymbol
                || symbol instanceof LexerTokenSymbol
                || symbol instanceof FragmentLexerTokenSymbol) {
                let entry: ReferenceNode = {
                    kind: symbol instanceof ParserRuleSymbol ? SymbolKind.ParserRule : SymbolKind.LexerToken,
                    rules: [],
                    tokens: [],
                    literals: []
                };

                for (let child of symbol.getAllSymbols(ParserRuleSymbol, true)) {
                    let resolved = this.symbolTable.resolve(child.name, false);
                    if (resolved) {
                        entry.rules.push(resolved.qualifiedName());
                    } else {
                        entry.rules.push(child.name);
                    }
                }

                for (let child of symbol.getAllSymbols(LexerTokenSymbol, true)) {
                    let resolved = this.symbolTable.resolve(child.name, false);
                    if (resolved) {
                        entry.tokens.push(resolved.qualifiedName());
                    } else {
                        entry.tokens.push(child.name);
                    }
                }

                for (let child of symbol.getAllSymbols(LiteralSymbol, true)) {
                    let resolved = this.symbolTable.resolve(child.name, false);
                    if (resolved) {
                        entry.literals.push(resolved.qualifiedName());
                    } else {
                        entry.literals.push(child.name);
                    }
                }

                result.set(symbol.qualifiedName(), entry);
            } else if (symbol instanceof BuiltInLexerTokenSymbol) {
                result.set(symbol.qualifiedName(), { kind: SymbolKind.BuiltInLexerToken, rules: [], tokens: [], literals: [] });
            } else if (symbol instanceof VirtualLexerTokenSymbol) {
                result.set(symbol.qualifiedName(), { kind: SymbolKind.VirtualLexerToken, rules: [], tokens: [], literals: [] });
            }
        }
        return result;
    }

    public getRRDScript(ruleName: string): string | undefined {
        this.runSemanticAnalysisIfNeeded();

        return this.rrdScripts.get(ruleName)!;
    }

    public addDependency(context: SourceContext) {
        // Check for mutual inclusion. Since dependencies are organized like a mesh
        // we use a work pipeline to check all relevant referencing contexts.
        var pipeline: SourceContext[] = [context];
        while (pipeline.length > 0) {
            let current = pipeline.shift();
            if (!current) {
                continue;
            }

            if (current.references.indexOf(this) > -1) {
                return; // Already in the list.
                // TODO: add diagnostic entry for this case.
            }

            pipeline.push(...current.references);
        }
        this.references.push(context);
        this.symbolTable.addDependencies(context.symbolTable);
    }

    /**
     * Remove the given context from our list of dependencies.
     */
    public removeDependency(context: SourceContext) {
        let index = context.references.indexOf(this);
        if (index > -1) {
            context.references.splice(index, 1);
        }
        this.symbolTable.removeDependency(context.symbolTable);
    }

    public getReferenceCount(symbol: string): number {
        return this.symbolTable.getReferenceCount(symbol);
    }

    public ruleFromPosition(column: number, row: number): [string | undefined, number | undefined] {
        let terminal = parseTreeFromPosition(this.tree!, column, row);
        if (!terminal) {
            return [undefined, undefined];
        }

        let context: RuleContext | undefined = (terminal as RuleContext);
        while (context && context.ruleIndex != ANTLRv4Parser.RULE_parserRuleSpec && context.ruleIndex != ANTLRv4Parser.RULE_lexerRuleSpec) {
            context = context.parent;
        }

        if (context) {
            if (context.ruleIndex == ANTLRv4Parser.RULE_parserRuleSpec) {
                const name = (context as ParserRuleSpecContext).RULE_REF().text;
                let index;
                if (this.parserInterpreter) {
                    index = this.parserInterpreter.getRuleIndexMap().get(name);
                }
                return [name, index];
            }

            const name = (context as LexerRuleSpecContext).TOKEN_REF().text;
            let index;
            if (this.lexerInterpreter) {
                index = this.lexerInterpreter.getRuleIndexMap().get(name);
            }
            return [name, index];
        }
        return [undefined, undefined];
    }

    /**
     * Use ANTLR4 jars to generate target files for the grammar managed in this context and all its dependencies.
     * @param dependencies A list of additional grammars which need generation too.
     * @param options Options to customize the generation process.
     * @returns List of names of all participating files.
     */
    public generate(dependencies: Set<SourceContext>, options: GenerationOptions): Promise<string[]> {
        if (options.loadOnly) {
            this.setupInterpreters(options.outputDir);
            return new Promise<string[]>((resolve, reject) => {
                resolve([]);
            });
        }

        let thisRef = this;
        return new Promise<string[]>((resolve, reject) => {
            let parameters = ["-jar"];
            if (options.alternativeJar) {
                parameters.push(options.alternativeJar);
            } else {
                if (options.language === "typescript") {
                    parameters.push(path.join(__dirname, '../../antlr/antlr4-typescript-4.6-SNAPSHOT-complete.jar'));
                } else {
                    parameters.push(path.join(__dirname, '../../antlr/antlr4-4.7.1-SNAPSHOT-complete.jar'));
                }
            }

            if (options.language) {
                parameters.push("-Dlanguage=" + options.language);
            }

            parameters.push("-message-format");
            parameters.push("antlr");
            if (options.libDir) {
                parameters.push("-lib");
                parameters.push(options.libDir);
            }

            if (options.outputDir) {
                parameters.push("-o");
                parameters.push(options.outputDir);
            }

            if (options.package) {
                parameters.push("-package");
                parameters.push(options.package);
            }

            let genListener = options.listeners == undefined || options.listeners === true;
            parameters.push(genListener ? "-listener" : "-no-listener");
            parameters.push(options.visitors === true ? "-visitor" : "-no-visitor");
            dependencies.add(thisRef); // Needs this also in the error parser.

            let fileList: string[] = [];
            for (let dependency of dependencies) {
                fileList.push(dependency.fileName);
            }
            parameters.push(...fileList);

            let spawnOptions = { cwd: options.baseDir ? options.baseDir : undefined };
            let java = child_process.spawn("java", parameters, spawnOptions);
            let exception = "";
            java.stderr.on("data", (data) => {
                let text = data.toString();
                if (text.startsWith("Picked up _JAVA_OPTIONS:")) {
                    let endOfInfo = text.indexOf("\n");
                    if (endOfInfo == -1) {
                        text = "";
                    } else {
                        text = text.substr(endOfInfo + 1, text.length);
                    }
                }

                if (text.length > 0) {
                    if (exception.length > 0) {
                        // We got a Java execution exception. Return it as is, so the caller can show that
                        // to the user, instead of interpreting it as a grammar error.
                        exception += text;
                    } else {
                        let parser = new ErrorParser(dependencies);
                        if (parser.convertErrorsToDiagnostics(text)) {
                            resolve(fileList);
                        } else {
                            exception += text;
                        }
                    }
                }
            });

            java.on("close", (code) => {
                if (exception.length > 0) {
                    // Report an execution exception as is, if there's any.
                    reject(exception);
                }

                thisRef.setupInterpreters(options.outputDir);
                resolve(fileList);
            });
        });
    }

    public getATNGraph(rule: string): ATNGraphData | undefined {
        let isLexerRule = rule[0] == rule[0].toUpperCase();
        if ((isLexerRule && !this.lexerInterpreter) || (!isLexerRule && !this.parserInterpreter)) {
            // Requires a generation run.
            return;
        }

        let ruleIndexMap = isLexerRule ? this.lexerInterpreter!.getRuleIndexMap() : this.parserInterpreter!.getRuleIndexMap();
        if (!ruleIndexMap.has(rule)) {
            return;
        }
        let ruleIndex: number = ruleIndexMap.get(rule)!;

        let atn = isLexerRule ? this.lexerInterpreter!.atn : this.parserInterpreter!.atn;
        let ruleNames = isLexerRule ? this.lexerInterpreter!.ruleNames : this.parserInterpreter!.ruleNames;
        let vocabulary = isLexerRule ? this.lexerInterpreter!.vocabulary : this.parserInterpreter!.vocabulary;

        let startState = atn.ruleToStartState[ruleIndex];
        let stopState = atn.ruleToStopState[ruleIndex];

        let seenStates: Set<ATNState> = new Set([startState]);
        let pipeline: ATNState[] = [startState];

        let result = new ATNGraphData();
        result.links = [];
        result.nodes = [];
        let stateToIndex = new Map<number, number>();
        let currentRuleIndex = -1;

        // First collect all ATN states that belong to this rule, so we can reference them in our links list.
        for (let state of atn.states) {
            if (state.ruleIndex == ruleIndex) {
                stateToIndex.set(state.stateNumber, result.nodes.length);
                result.nodes.push({ id: state.stateNumber, name: state.stateNumber.toString(), type: state.stateType });

                let transitions = state.getTransitions();
                // If this state transits to a new rule create also a fake node for that rule.
                if (transitions.length == 1 && transitions[0].target.stateType == ATNStateType.RULE_START) {
                    let marker = state.stateNumber * transitions[0].target.stateNumber;
                    stateToIndex.set(marker, result.nodes.length);
                    // Type 13 is a fake type denoting a rule. It's one beyond the highest ATNStateType values.
                    result.nodes.push({ id: currentRuleIndex--, name: ruleNames[transitions[0].target.ruleIndex], type: 13 });
                }
            }
        }

        while (pipeline.length > 0) {
            let state = pipeline.shift()!;

            let nodeIndex = stateToIndex.get(state.stateNumber)!; // Must exist.

            for (let transition of state.getTransitions()) {
                // Rule stop states usually point to the follow state in the calling rule, but can also
                // point to a state in itself if the rule is left recursive. In any case we don't need to follow
                // transitions going out from a stop state.
                if (state == stopState)
                    continue;

                let transitsToRule = transition.target.stateType == ATNStateType.RULE_START;
                let marker = transition.target.stateNumber * (transitsToRule ? state.stateNumber : 1);
                let link = {
                    source: nodeIndex, target: stateToIndex.get(marker)!, type: transition.serializationType,
                    labels: new Array<string>()
                };
                if (transition.isEpsilon) {
                    link.labels.push("ε");
                } else if (transition.label) {
                    if (isLexerRule) {
                        // Lexer rules can be defined for a large range of characters (even the full Unicode range).
                        // We hance return a compact form here instead of listing every character.
                        link.labels = this.intervalSetToStrings(transition.label);
                    } else {
                        for (let label of transition.label.toList()) {
                            link.labels.push(vocabulary.getDisplayName(label));
                        }
                    }
                }

                result.links.push(link);

                let nextState: ATNState;
                if (transitsToRule) {
                    // Target is a state in a different rule (or this rule if left recursive).
                    // Add a backlink from that subrule into ours.
                    nextState = (transition as RuleTransition).followState;
                    let link = {
                        source: stateToIndex.get(marker)!, target: stateToIndex.get(nextState.stateNumber)!,
                        type: TransitionType.RULE, labels: ["ε"]
                    };
                    result.links.push(link);
                } else {
                    nextState = transition.target;
                }

                if (seenStates.has(nextState))
                    continue;

                seenStates.add(nextState);
                pipeline.push(nextState);
            }
        }

        return result;
    }

    /**
     * Generates strings that are valid input for the managed grammar.
     *
     * @param options The settings controlling the generation.
     * @param defined A map of rule names and the output string to use for them (instead of walking the ATN).
     * @returns A list of strings with sentences that this grammar would successfully parse.
     */
    public generateSentences(options: SentenceGenerationOptions, definitions?: Map<string, string>): string[] {
        if (!this.lexerInterpreter || !this.parserInterpreter) {
            // Requires a generation run.
            return [];
        }
        let isLexerRule = options.startRule[0] == options.startRule[0].toUpperCase();

        let generator = new SentenceGenerator(this.lexerInterpreter.atn, this.lexerInterpreter.getRuleIndexMap(),
            this.lexerInterpreter.vocabulary, this.lexerInterpreter.ruleNames, this.parserInterpreter.ruleNames);

        let lexerRuleIndexMap = this.lexerInterpreter.getRuleIndexMap();
        let parserRuleIndexMap = this.parserInterpreter.getRuleIndexMap();
        let start: RuleStartState;
        if (isLexerRule) {
            let index = lexerRuleIndexMap.get(options.startRule);
            if (index == undefined) {
                return [];
            }
            start = this.lexerInterpreter.atn.ruleToStartState[index];
        } else {
            let index = parserRuleIndexMap.get(options.startRule);
            if (index == undefined) {
                return [];
            }
            start = this.parserInterpreter.atn.ruleToStartState[index];
        }

        return generator.generate(options, start, definitions);
    }

    public getSymbolInfo(symbol: string): SymbolInfo | undefined {
        return this.symbolTable.getSymbolInfo(symbol);
    }

    public formatGrammar(options: FormattingOptions, start: number, stop: number): [string, number, number] {
        this.tokenStream.fill();
        let tokens = this.tokenStream.getTokens();
        let formatter = new GrammarFormatter(tokens);
        return formatter.formatGrammar(options, start, stop);
    }

    private runSemanticAnalysisIfNeeded() {
        if (!this.semanticAnalysisDone) {
            this.semanticAnalysisDone = true;
            //this.diagnostics.length = 0; Don't, we would lose our syntax errors from last parse run.
            this.rrdScripts = new Map();
            let semanticListener = new SemanticListener(this.diagnostics, this.symbolTable);
            ParseTreeWalker.DEFAULT.walk(semanticListener as ParseTreeListener, this.tree!);

            let visitor = new RuleVisitor(this.rrdScripts);
            let t = visitor.visit(this.tree!);
        }
    }

    /**
     * Loads interpreter data if it exists and sets up the interpreters.
     */
    private setupInterpreters(outputDir?: string) {
        // Load interpreter data if the code generation was successfull.
        // For that we only need the final parser and lexer files, not any imported stuff.
        // The target path is either the output path (if one was given) or the grammar path.
        let lexerFile = "";
        let parserFile = "";
        let baseName = (this.fileName.endsWith(".g4") ? path.basename(this.fileName, ".g4") : path.basename(this.fileName, ".g"));
        let grammarPath = (outputDir) ? outputDir : path.dirname(this.fileName);
        switch (this.grammarType) {
            case GrammarType.Parser:
                if (baseName.endsWith("Parser")) {
                    baseName = baseName.substr(0, baseName.length - "Parser".length);
                }
                parserFile = path.join(grammarPath, baseName) + "Parser.interp"
                lexerFile = path.join(grammarPath, baseName) + "Lexer.interp"
                break;

            case GrammarType.Lexer:
                lexerFile = path.join(grammarPath, baseName) + ".interp"
                break;

            case GrammarType.Combined:
                if (baseName.endsWith("Parser")) {
                    baseName = baseName.substr(0, baseName.length - "Parser".length);
                }
                parserFile = path.join(grammarPath, baseName) + ".interp"
                lexerFile = path.join(grammarPath, baseName) + "Lexer.interp"
                break;

            default: // Unknown, no data is loaded.
                break;
        }

        if (fs.existsSync(lexerFile)) {
            let data = InterpreterDataReader.parseFile(lexerFile);
            this.interpreterInput = new ANTLRInputStream(""); // Will be overwritten on interpreter runs.
            this.lexerInterpreter = new LexerInterpreter(this.fileName, data.vocabulary, data.modes, data.ruleNames, data.atn, this.interpreterInput);
            this.tokens = new CommonTokenStream(this.lexerInterpreter);
        }

        if (this.lexerInterpreter && fs.existsSync(parserFile)) {
            let data = InterpreterDataReader.parseFile(parserFile);
            this.parserInterpreter = new ParserInterpreter(this.fileName, data.vocabulary, data.ruleNames, data.atn, this.tokens!)
        }

    }

    /**
     * Convert an interval set in a list of ranges, consumable by a human.
     * @param set The set to convert.
     * @return A list of strings, one for each defined interval.
     */
    private intervalSetToStrings(set: IntervalSet): string[] {
        let result: string[] = [];

        /**
         * Return a readable representation of a code point. The input can be anything from the
         * full Unicode range.
         * @param char The code point to convert.
         */
        function characterRepresentation(char: number): string {
            // Unfortunately JS/TS has no means to determine the Unicode class of a character,
            // so we are very limited here. For now we return a quoted character for a code point if
            // in the printable ANSI char range (but not latin extended A + B), otherwise a Unicode escape code.
            if (char < 0) {
                return "EOF";
            }

            if ((char >= 0x21 && char <= 0x7F) || (char >= 0xA1 && char <= 0xFF)) {
                return "'" + String.fromCharCode(char) + "'";
            }

            return "\\u" + char.toString(16).toUpperCase();
        }

        for (let interval of set.intervals) {
            let entry = characterRepresentation(interval.a);
            if (interval.a !== interval.b) {
                entry += " - " + characterRepresentation(interval.b);
            }
            result.push(entry);
        }

        return result;
    }

    private static globalSymbols = new GrapsSymbolTable("Global Symbols", { allowDuplicateSymbols: false });

    // Interpreter infrastructure.
    private interpreterInput: CharStream;
    private tokens: CommonTokenStream | undefined;
    private lexerInterpreter: LexerInterpreter | undefined;
    private parserInterpreter: ParserInterpreter | undefined;

    // Result related fields.
    //private diagnostics: DiagnosticEntry[] = [];
    private rrdScripts: Map<string, string>;
    private semanticAnalysisDone: boolean = false; // Includes determining reference counts.

    // Grammar parsing infrastructure.
    private grammarType: GrammarType;
    private tokenStream: CommonTokenStream;
    private parser: ANTLRv4Parser | undefined;
    private errorListener: ContextErrorListener = new ContextErrorListener(this.diagnostics);
    private lexerErrorListener: ContextLexerErrorListener = new ContextLexerErrorListener(this.diagnostics);

    private tree: GrammarSpecContext | undefined; // The root context from the last parse run.
    private imports: string[] = []; // Updated on each parse run.
};

/**
 * Returns the parse tree which covers the given position or undefined if none could be found.
 */
function parseTreeFromPosition(root: ParseTree, column: number, row: number): ParseTree | undefined {
    // Does the root node actually contain the position? If not we don't need to look further.
    if (root instanceof TerminalNode) {
        let terminal = (root as TerminalNode);
        let token = terminal.symbol;
        if (token.line != row)
            return undefined;

        let tokenStop = token.charPositionInLine + (token.stopIndex - token.startIndex + 1);
        if (token.charPositionInLine <= column && tokenStop >= column) {
            return terminal;
        }
        return undefined;
    } else {
        let context = (root as ParserRuleContext);
        if (!context.start || !context.stop) { // Invalid tree?
            return undefined;
        }

        if (context.start.line > row || (context.start.line == row && column < context.start.charPositionInLine)) {
            return undefined;
        }

        let tokenStop = context.stop.charPositionInLine + (context.stop.stopIndex - context.stop.startIndex + 1);
        if (context.stop.line < row || (context.stop.line == row && tokenStop < column)) {
            return undefined;
        }

        if (context.children) {
            for (let child of context.children) {
                let result = parseTreeFromPosition(child, column, row);
                if (result) {
                    return result;
                }
            }
        }
        return context;

    }
}
