/*
 * This file is released under the MIT license.
 * Copyright (c) 2016, 2017 Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict";

import { EventEmitter } from "events";

import {
    LexerInterpreter, ParserInterpreter, Vocabulary, TokenStream, ANTLRInputStream, CommonTokenStream, CommonToken,
    ParserRuleContext, RecognitionException, ANTLRErrorListener, Recognizer, Token
} from "antlr4ts";
import { ATN, RuleStartState, ATNState, ATNStateType } from "antlr4ts/atn";
import { ParseTree, ErrorNode, TerminalNode } from "antlr4ts/tree";

import { InterpreterData } from "./InterpreterDataReader";
import { LexerToken, ParseTreeNode, ParseTreeNodeType } from "../index";
import { Override } from "antlr4ts/Decorators";
import { EOF } from "dns";

/**
 * This class provides debugging support for a grammar.
 */
export class GrapsDebugger extends EventEmitter {
    constructor(
        public mainGrammarName: string,
        private lexerData: InterpreterData,
        private parserData: InterpreterData | undefined,
        private input: string
    ) {
        super();

        let stream = new ANTLRInputStream(input);
        this.lexer = new LexerInterpreter(mainGrammarName, lexerData.vocabulary, lexerData.modes, lexerData.ruleNames,
            lexerData.atn, stream);
        this.lexer.removeErrorListeners();
        this.lexer.addErrorListener(new DebuggerLexerErrorListener(this));
        this.tokenStream = new CommonTokenStream(this.lexer);
        if (parserData) {
            this.parser = new GrapsParserInterpreter(mainGrammarName, parserData.vocabulary, parserData.ruleNames,
                parserData.atn, this.tokenStream);
            this.parser.buildParseTree = true;
            this.parser.removeErrorListeners();
            this.parser.addErrorListener(new DebuggerErrorListener(this));
        }
    }

    public start(stopOnEntry: boolean) {
        if (!this.parser) {
            this.emit("end");
            return;
        }

        this.parseTree = undefined;
        if (false && stopOnEntry) {
            this.step();
        } else {
            this.parser.start(0);
            this.continue();
        }
    }

    public continue() {
        if (this.parser) {
            this.parseTree = this.parser.continue();
        }
        this.emit("end");
    }

    public step() {
    }

    public stop() {
    }

    public get tokenList(): LexerToken[] {
        this.tokenStream.fill();
        let result: LexerToken[] = [];
        for (let token of this.tokenStream.getTokens()) {
            result.push(this.convertToken(<CommonToken>token));
        }
        return result;
    }

    public get lexerSymbols(): [string | undefined, string | undefined][] {
        let result: [string | undefined, string | undefined][] = [];
        let vocab = this.lexer.vocabulary;
        for (let i = 0; i <= vocab.maxTokenType; ++i) {
            result.push([vocab.getLiteralName(i), vocab.getSymbolicName(i)]);
        }

        return result;
    }

    public get parserSymbols(): string[] {
        if (!this.parser) {
            return [];
        }
        return this.parser.ruleNames;
    }

    public get channels(): string[] {
        return this.lexerData.channels;
    }

    public get modes(): string[] {
        return this.lexerData.modes;
    }

    public ruleName(ruleIndex: number): string | undefined {
        if (!this.parser) {
            return;
        }
        if (ruleIndex < 0 || ruleIndex >= this.parser.ruleNames.length) {
            return;
        }
        return this.parser.ruleNames[ruleIndex];
    }

    public get currentParseTree(): ParseTreeNode | undefined {
        if (!this.parseTree) {
            return undefined;
        }

        return this.parseContextToNode(this.parseTree);
    }

    private parseContextToNode(tree: ParseTree) : ParseTreeNode {
        let result = new ParseTreeNode();
        result.children = [];
        if (tree instanceof ParserRuleContext) {
            result.type = ParseTreeNodeType.Rule;
            result.ruleIndex = tree.ruleIndex;
            result.name = this.parser!.ruleNames[tree.ruleIndex];
            result.start = this.convertToken(tree.start as CommonToken);
            result.stop = this.convertToken(tree.stop as CommonToken);
            if (tree.children) {
                for (let child of tree.children) {
                    if ((child instanceof TerminalNode) && (child.symbol.type == Token.EOF)) {
                        continue;
                    }
                    result.children.push(this.parseContextToNode(child));
                }
            }
        } else if (tree instanceof ErrorNode) {
            result.type = ParseTreeNodeType.Error;
            result.symbol = this.convertToken(tree.symbol as CommonToken);
            result.name = result.symbol.name;
        } else {
            // Must be a terminal node then.
            result.type = ParseTreeNodeType.Terminal;
            result.symbol = this.convertToken((<TerminalNode>tree).symbol as CommonToken);
            result.name = result.symbol.name;
        }

        return result;
    }

    private convertToken(token: CommonToken): LexerToken {
        return {
            text: token.text ? token.text : "",
            type: token.type,
            name: this.lexer.vocabulary.getSymbolicName(token.type) || token.type.toString(),
            line: token.line,
            offset: token.charPositionInLine,
            channel: token.channel,
            tokenIndex: token.tokenIndex
        }
    }

    private lexer: LexerInterpreter;
    private tokenStream: CommonTokenStream;
    private parser: GrapsParserInterpreter | undefined;
    private parseTree: ParserRuleContext | undefined;
}

class GrapsParserInterpreter extends ParserInterpreter {
    constructor(grammarFileName: string, vocabulary: Vocabulary, ruleNames: string[], atn: ATN, input: TokenStream) {
        super(grammarFileName, vocabulary, ruleNames, atn, input);
    }

    start(startRuleIndex: number) {
        this.reset();

        let startRuleStartState: RuleStartState = this._atn.ruleToStartState[startRuleIndex];

        this._rootContext = this.createInterpreterRuleContext(undefined, ATNState.INVALID_STATE_NUMBER, startRuleIndex);
        if (startRuleStartState.isPrecedenceRule) {
            this.enterRecursionRule(this._rootContext, startRuleStartState.stateNumber, startRuleIndex, 0);
        }
        else {
            this.enterRule(this._rootContext, startRuleStartState.stateNumber, startRuleIndex);
        }

        this.startIsPrecedenceRule = startRuleStartState.isPrecedenceRule;
    }

    /**
     * Resume parsing from the current ATN state until the end or we hit a breakpoint.
     */
    continue(): ParserRuleContext {
        while (true) {
            let p: ATNState = this.atnState;
            switch (p.stateType) {
                case ATNStateType.RULE_STOP:
                    // End of start rule.
                    if (this._ctx.isEmpty) {
                        if (this.startIsPrecedenceRule) {
                            let result: ParserRuleContext = this._ctx;
                            let parentContext: [ParserRuleContext, number] = this._parentContextStack.pop()!;
                            this.unrollRecursionContexts(parentContext[0]);
                            return result;
                        } else {
                            this.exitRule();
                            return this._rootContext;
                        }
                    }

                    this.visitRuleStopState(p);
                    break;

                default:
                    try {
                        this.visitState(p);
                    }
                    catch (e) {
                        if (e instanceof RecognitionException) {
                            this.state = this._atn.ruleToStopState[p.ruleIndex].stateNumber;
                            this.context.exception = e;
                            this.errorHandler.reportError(this, e);
                            this.recover(e);
                        } else {
                            throw e;
                        }
                    }

                    break;
            }
        }
    }

    private startIsPrecedenceRule: boolean;
}

class DebuggerLexerErrorListener implements ANTLRErrorListener<number> {
    constructor(private _debugger: GrapsDebugger) {
    }

    syntaxError<T extends number>(recognizer: Recognizer<T, any>, offendingSymbol: T | undefined, line: number,
        charPositionInLine: number, msg: string, e: RecognitionException | undefined): void {
            this._debugger.emit("output", "Lexer error (" + line + ", " + (charPositionInLine + 1) + "): " + msg,
                this._debugger.mainGrammarName, line, charPositionInLine, true);
    }
};

class DebuggerErrorListener implements ANTLRErrorListener<CommonToken> {
    constructor(private _debugger: GrapsDebugger) {
    }

    syntaxError<T extends Token>(recognizer: Recognizer<T, any>, offendingSymbol: T | undefined, line: number,
        charPositionInLine: number, msg: string, e: RecognitionException | undefined): void {
            this._debugger.emit("output", "Parser error (" + line + ", " + (charPositionInLine + 1) + "): " + msg,
                this._debugger.mainGrammarName, line, charPositionInLine, true);
    }
};
