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
import { LexerToken, ParseTreeNode, ParseTreeNodeType, SymbolInfo } from "../index";
import { Override } from "antlr4ts/Decorators";
import { EOF } from "dns";
import { SourceContext } from "./SourceContext";

export interface GrapsBreakPoint {
    validated: boolean;
    line: number;
    id: number;
}

/**
 * This class provides debugging support for a grammar.
 */
export class GrapsDebugger extends EventEmitter {
    constructor(
        private context: SourceContext,
        public mainGrammarName: string,
        private lexerData: InterpreterData,
        private parserData: InterpreterData | undefined
    ) {
        super();

        // We set up all our structures with an empty input stream. On start we replaced that with the
        // actual input.
        let stream = new ANTLRInputStream("");
        this.lexer = new LexerInterpreter(this.mainGrammarName, this.lexerData.vocabulary, this.lexerData.modes,
            this.lexerData.ruleNames, this.lexerData.atn, stream);
        this.lexer.removeErrorListeners();
        this.lexer.addErrorListener(new DebuggerLexerErrorListener(this));
        this.tokenStream = new CommonTokenStream(this.lexer);
        if (this.parserData) {
            this.parser = new GrapsParserInterpreter(this, this.mainGrammarName, this.parserData.vocabulary,
                this.parserData.ruleNames, this.parserData.atn, this.tokenStream);
            this.parser.buildParseTree = true;
            this.parser.removeErrorListeners();
            this.parser.addErrorListener(new DebuggerErrorListener(this));
        }
    }

    public start(startRuleIndex: number, input: string) {
        let stream = new ANTLRInputStream(input);
        this.lexer.inputStream = stream;

        if (!this.parser) {
            this.sendEvent("end");
            return;
        }

        this.parser.breakPoints.clear();
        for (let bp of this.breakPoints) {
            this.validateBreakPoint(bp[1]);
        }

        this.parseTree = undefined;
        this.parser.start(startRuleIndex);
        this.continue();
    }

    public continue() {
        if (this.parser) {
            this.parseTree = this.parser.continue(RunMode.Normal);
        }
    }

    public stepIn() {
        if (this.parser) {
            this.parseTree = this.parser.continue(RunMode.StepIn);
        }
    }

    public stepOut() {
        if (this.parser) {
            this.parseTree = this.parser.continue(RunMode.StepOut);
        }
    }

    public stepOver() {
        if (this.parser) {
            this.parseTree = this.parser.continue(RunMode.StepOver);
        }
    }

    public stop() {
        // no-op
    }

    public pause() {
    }

    public clearBreakPoints(): void {
        this.breakPoints.clear();
        if (this.parser) {
            this.parser.breakPoints.clear();
        }
    }

    public addBreakPoint(path: string, line: number): GrapsBreakPoint {
        let breakPoint = <GrapsBreakPoint> { validated: false, line: line, id: this.nextBreakPointId++ };
        this.breakPoints.set(breakPoint.id, breakPoint);
        this.validateBreakPoint(breakPoint);

        return breakPoint;
    }

    public get tokenList(): LexerToken[] {
        this.tokenStream.fill();
        let result: LexerToken[] = [];
        for (let token of this.tokenStream.getTokens()) {
            let entry = this.convertToken(<CommonToken>token);
            if (entry) {
                result.push(entry);
            }
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

    public ruleNameFromIndex(ruleIndex: number): string | undefined {
        if (!this.parser) {
            return;
        }
        if (ruleIndex < 0 || ruleIndex >= this.parser.ruleNames.length) {
            return;
        }
        return this.parser.ruleNames[ruleIndex];
    }

    public ruleIndexFromName(ruleName: string): number {
        if (!this.parser) {
            return -1;
        }
        return this.parser.ruleNames.findIndex(entry => entry == ruleName);
    }

    public get currentParseTree(): ParseTreeNode | undefined {
        if (!this.parseTree) {
            return undefined;
        }

        return this.parseContextToNode(this.parseTree);
    }

    public get currentStackTrace(): SymbolInfo[] {
        let result = new Array<SymbolInfo>();
        if (this.parser) {
            let stack = this.parser.getRuleInvocationStack();
            for (let frame of stack) {
                result.push(this.context.getSymbolInfo(frame)!);
            }
        }
        return result;
    }

    public get currentTokenIndex(): number {
        return this.tokenStream.index;
    }

	public sendEvent(event: string, ... args: any[]) {
		setImmediate(_ => {
			this.emit(event, ...args);
		});
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
            if (result.symbol) {
                result.name = result.symbol.name;
            } else {
                result.name = "<no name>";
            }
        } else {
            // Must be a terminal node then.
            result.type = ParseTreeNodeType.Terminal;
            result.symbol = this.convertToken((<TerminalNode>tree).symbol as CommonToken);
            if (result.symbol) {
                result.name = result.symbol.name;
            } else {
                result.name = "<no name>";
            }
        }

        return result;
    }

    private convertToken(token: CommonToken): LexerToken | undefined {
        if (!token) {
            return;
        }

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

    /**
     * Validates the breakpoint's position.
     * When a breakpoint is within a rule, but not at the start line, it will be moved to that line.
     * Only breakpoints at rule start lines will be set to be valid and only valid breakpoints are
     * sent to the parser interpreter.
     * @param breakPoint The breakpoint to validate.
     */
    private validateBreakPoint(breakPoint: GrapsBreakPoint) {
        if (!this.parserData) {
            return;
        }

        let [name, index] = this.context.ruleFromPosition(0, breakPoint.line); // Assuming here a rule always starts in column 0.
        if (name != undefined && index != undefined) {
            breakPoint.validated = true;

            let start = this.parserData.atn.ruleToStartState[index];
            this.parser!.breakPoints.add(start);
            let range = this.context.enclosingRangeForSymbol(0, breakPoint.line, true);
            breakPoint.line = range!.start.row;
            this.sendEvent("breakpointValidated", breakPoint);
        }
    }

    private lexer: LexerInterpreter;
    private tokenStream: CommonTokenStream;
    private parser: GrapsParserInterpreter | undefined;
    private parseTree: ParserRuleContext | undefined;

    private breakPoints: Map<number, GrapsBreakPoint> = new Map();
    private nextBreakPointId = 0;
}

class GrapsParserInterpreter extends ParserInterpreter {
    breakPoints: Set<ATNState> = new Set<ATNState>();

    constructor(private _debugger: GrapsDebugger, grammarFileName: string, vocabulary: Vocabulary,
        ruleNames: string[], atn: ATN, input: TokenStream) {
        super(grammarFileName, vocabulary, ruleNames, atn, input);
    }

    start(startRuleIndex: number) {
        this.reset();

        let startRuleStartState: RuleStartState = this._atn.ruleToStartState[startRuleIndex];

        this._rootContext = this.createInterpreterRuleContext(undefined, ATNState.INVALID_STATE_NUMBER, startRuleIndex);
        if (startRuleStartState.isPrecedenceRule) {
            this.enterRecursionRule(this._rootContext, startRuleStartState.stateNumber, startRuleIndex, 0);
        } else {
            this.enterRule(this._rootContext, startRuleStartState.stateNumber, startRuleIndex);
        }

        this.startIsPrecedenceRule = startRuleStartState.isPrecedenceRule;
    }

    /**
     * Resume parsing from the current ATN state until the end or we hit a breakpoint.
     */
    continue(runMode: RunMode): ParserRuleContext {
        // Keep the index of the rule we are in currently, for step over/out.
        let currentRule = this.atnState.ruleIndex;

        // If we are not going to jump into a rule then make step over a step in.
        // This way we can use step over only for rule processing.
        if (this.atnState.stateType != ATNStateType.RULE_START && runMode == RunMode.StepOver) {
            runMode = RunMode.StepIn;
        }

        while (true) {
            let p = this.atnState;
            switch (p.stateType) {
                case ATNStateType.RULE_STOP: {
                    // End of start rule.
                    if (this._ctx.isEmpty) {
                        if (this.startIsPrecedenceRule) {
                            let result: ParserRuleContext = this._ctx;
                            let parentContext: [ParserRuleContext, number] = this._parentContextStack.pop()!;
                            this.unrollRecursionContexts(parentContext[0]);
                            this._debugger.sendEvent("end");
                            return result;
                        } else {
                            this.exitRule();
                            this._debugger.sendEvent("end");
                            return this._rootContext;
                        }
                    }

                    let endOfCurrentRule = currentRule == this.atnState.ruleIndex;
                    this.visitRuleStopState(p);

                    if ((endOfCurrentRule && runMode == RunMode.StepOut)
                        || (runMode == RunMode.StepOver && currentRule == this.atnState.ruleIndex)) {
                        this._debugger.sendEvent("stopOnStep");
                        return this._rootContext;
                    }
                    break;
                }

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

            if (this.breakPoints.has(p)) {
                this._debugger.sendEvent("stopOnBreakpoint");
                return this._rootContext;
            } else if (runMode == RunMode.StepIn) {
                // Stop here when we reached a state which represents work to do.
                if ((this.atnState.stateType == ATNStateType.RULE_START)
                    || (this.atnState.stateType == ATNStateType.BASIC && !this.atnState.onlyHasEpsilonTransitions)) {
                    this._debugger.sendEvent("stopOnStep");
                    return this._rootContext;
                }
            }
        }
    }

    private startIsPrecedenceRule: boolean;
}

enum RunMode { Normal, StepIn, StepOver, StepOut };

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
