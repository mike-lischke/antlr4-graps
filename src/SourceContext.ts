/*
 * This file is released under the MIT license.
 * Copyright (c) 2016, 2017, Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict"

// This file contains the handling for a single source file. It provides syntactic and semantic
// informations, symbol lookups and more.

import { ANTLRInputStream, CommonTokenStream, BailErrorStrategy, ParserRuleContext, DefaultErrorStrategy, Token } from 'antlr4ts';
import { PredictionMode } from 'antlr4ts/atn';
import { ParseCancellationException } from 'antlr4ts/misc';
import { ParseTreeWalker, TerminalNode, ParseTree } from 'antlr4ts/tree';

import { CodeCompletionCore } from "antlr4-c3";

import { ANTLRv4Parser } from '../parser/ANTLRv4Parser';
import { ANTLRv4Lexer } from '../parser/ANTLRv4Lexer';

import { SymbolKind, SymbolInfo, DiagnosticEntry, DiagnosticType, DependencyNode } from '../index';

import { ContextErrorListener } from './ContextErrorListener';
import { GrapsSymbolTable, BuiltInChannelSymbol, BuiltInLexerTokenSymbol, BuiltInModeSymbol } from './GrapsSymbolTable';
import { DetailsListener } from './DetailsListener';
import { SemanticListener } from './SemanticListener';
import { RuleVisitor } from './RuleVisitor';

// One source context per file. Source contexts can reference each other (e.g. for symbol lookups).
export class SourceContext {
    public symbolTable: GrapsSymbolTable = new GrapsSymbolTable("Context", this);
    public references: SourceContext[] = []; // Contexts referencing us.

    constructor(public sourceId: string) {
        // Initialize static global symbol table, if not yet done.
        if (!SourceContext.globalSymbols.resolve("EOF")) {
            SourceContext.globalSymbols.addNewSymbolOfType(BuiltInChannelSymbol, undefined, "DEFAULT_TOKEN_CHANNEL");
            SourceContext.globalSymbols.addNewSymbolOfType(BuiltInChannelSymbol, undefined, "HIDDEN");
            SourceContext.globalSymbols.addNewSymbolOfType(BuiltInLexerTokenSymbol, undefined, "EOF");
            SourceContext.globalSymbols.addNewSymbolOfType(BuiltInModeSymbol, undefined, "DEFAULT_MODE");
        }
    }

    public infoForSymbolAtPosition(column: number, row: number): SymbolInfo | undefined {
        let terminal = terminalFromPosition(this.tree!, column, row);
        if (!terminal) {
            return undefined;
        }

        // We only want to show info for symbols in specific contexts.
        let parent = (terminal.parent as ParserRuleContext);
        if (parent.ruleIndex == ANTLRv4Parser.RULE_identifier) {
            parent = (parent.parent as ParserRuleContext);
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

    public listSymbols(includeDependencies: boolean): SymbolInfo[] {
        return this.symbolTable.listSymbols(includeDependencies);
    }

    public getCodeCompletionCandidates(column: number, row: number): SymbolInfo[] {
        let core = new CodeCompletionCore(this.parser);
        core.showResult = false;

        // Search the token index which covers our caret position.
        let index: number;
        for (index = 0; ; ++index) {
            let token = this.parser.inputStream.get(index);
            if (token.type == Token.EOF) {
                break;
            }
            if (token.line > row
                || (token.line === row && token.charPositionInLine >= column)) {
                break;
            }
        }

        let candidates = core.collectCandidates(index);
        let result: SymbolInfo[] = [];
        candidates.tokens.forEach((following: number[], type: number) => {
            switch (type) {
                case ANTLRv4Lexer.TOKEN_REF:
                //break;

                default:
                    result.push({
                        kind: SymbolKind.LexerToken,
                        name: this.parser.vocabulary.getDisplayName(type),
                        source: "",
                        definition: undefined
                    });
                    break;
            }
        });
        return result;
    }

    public parse(source: string): string[] {
        let inputStream = new ANTLRInputStream(source);
        let lexer = new ANTLRv4Lexer(inputStream);
        lexer.removeErrorListeners();
        lexer.addErrorListener(this.errorListener);
        let tokenStream = new CommonTokenStream(lexer);

        // Keep the current parser instance for code completion.
        this.parser = new ANTLRv4Parser(tokenStream);
        this.parser.removeErrorListeners();
        this.parser.addErrorListener(this.errorListener);
        this.parser.errorHandler = new BailErrorStrategy();
        this.parser.interpreter.setPredictionMode(PredictionMode.SLL);

        this.tree = undefined;
        this.semanticAnalysisDone = false;
        this.diagnostics.length = 0;
        this.imports.length = 0;

        this.symbolTable.clear();
        this.symbolTable.addDependencies(SourceContext.globalSymbols);
        try {
            this.tree = this.parser.grammarSpec();
        } catch (e) {
            if (e instanceof ParseCancellationException) {
                tokenStream.reset();
                this.parser.reset();
                this.parser.errorHandler = new DefaultErrorStrategy();
                this.parser.interpreter.setPredictionMode(PredictionMode.LL);
                this.tree = this.parser.grammarSpec();
            } else {
                throw e;
            }
        }

        this.symbolTable.tree = this.tree;
        let listener: DetailsListener = new DetailsListener(this.symbolTable, this.imports);
        ParseTreeWalker.DEFAULT.walk(listener, this.tree);

        return this.imports;
    }

    public getDiagnostics(): DiagnosticEntry[] {
        this.runSemanticAnalysisIfNeeded();

        return this.diagnostics;
    }

    public getDependencyGraph(): Map<number, DependencyNode> {
        this.runSemanticAnalysisIfNeeded();

        return this.dependencyGraph;
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

    protected getSymbolInfo(symbol: string): SymbolInfo | undefined {
        return this.symbolTable.getSymbolInfo(symbol);
    }

    private runSemanticAnalysisIfNeeded() {
        if (!this.semanticAnalysisDone) {
            this.semanticAnalysisDone = true;
            //this.diagnostics.length = 0; We would lose our syntax error from last parse run.
            this.dependencyGraph = new Map();
            this.rrdScripts = new Map();
            let semanticListener = new SemanticListener(this.diagnostics, this.symbolTable);
            ParseTreeWalker.DEFAULT.walk(semanticListener, this.tree!);

            let visitor = new RuleVisitor(this.rrdScripts);
            let t = visitor.visit(this.tree!);
        }
    }

    private static globalSymbols = new GrapsSymbolTable("Global Symbols");

    private parser: ANTLRv4Parser;

    private tree: ParserRuleContext | undefined; // The root context from the last parse run.
    private imports: string[] = []; // Updated on each parse run.

    private diagnostics: DiagnosticEntry[] = [];
    private dependencyGraph: Map<number, DependencyNode>;
    private rrdScripts: Map<string, string>;
    private semanticAnalysisDone: boolean = false; // Includes determining reference counts.

    private errorListener: ContextErrorListener = new ContextErrorListener(this.diagnostics);
};

/**
 * Returns the terminal node at the given position, or null if there is no terminal at that position.
 */
function terminalFromPosition(root: ParseTree, column: number, row: number): TerminalNode | undefined {
    // Does the root node actually contain the position? If not we don't need to look further.
    if (root instanceof TerminalNode) {
        let terminal: TerminalNode = <TerminalNode>root;
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

        for (var i = 0; i < context.childCount; ++i) {
            let result = terminalFromPosition(context.getChild(i), column, row);
            if (result) {
                return result;
            }
        }

    }

    return undefined;
}
