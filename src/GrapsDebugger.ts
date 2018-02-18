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
    ParserRuleContext, RecognitionException, ANTLRErrorListener, Recognizer, Token, Lexer
} from "antlr4ts";
import { ATN, RuleStartState, ATNState, ATNStateType, TransitionType, Transition, RuleTransition } from "antlr4ts/atn";
import { ParseTree, ErrorNode, TerminalNode } from "antlr4ts/tree";
import { Override } from "antlr4ts/Decorators";

import { Symbol, ScopedSymbol, BlockSymbol } from "antlr4-c3";

import { InterpreterData } from "./InterpreterDataReader";
import { LexerToken, ParseTreeNode, ParseTreeNodeType, SymbolInfo, LexicalRange } from "../index";
import { SourceContext } from "./SourceContext";
import { AlternativeSymbol, GrapsSymbolTable, RuleReferenceSymbol, EbnfSuffixSymbol, RuleSymbol } from "./GrapsSymbolTable";

export interface GrapsBreakPoint {
    validated: boolean;
    line: number;
    id: number;
}

export interface GrapsStackFrame {
    name: string;
    source: string;
    next: LexicalRange[];
}

/**
 * This class provides debugging support for a grammar.
 */
export class GrapsDebugger extends EventEmitter {
    constructor(
        private context: SourceContext,
        private symbolTable: GrapsSymbolTable,
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
            this.parser = new GrapsParserInterpreter(this, this.symbolTable, this.mainGrammarName,
                this.parserData.vocabulary, this.parserData.ruleNames, this.parserData.atn, this.tokenStream);
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
        let breakPoint = <GrapsBreakPoint>{ validated: false, line: line, id: this.nextBreakPointId++ };
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

    public tokenIndexFromName(tokenName: string): number {
        let vocab = this.lexer.vocabulary;
        for (let i = 0; i <= vocab.maxTokenType; ++i) {
            if (vocab.getSymbolicName(i) == tokenName) {
                return i;
            }
        }

        return -1;
    }

    public get currentParseTree(): ParseTreeNode | undefined {
        if (!this.parseTree) {
            return undefined;
        }

        return this.parseContextToNode(this.parseTree);
    }

    public get currentStackTrace(): GrapsStackFrame[] {
        let result: GrapsStackFrame[] = [];
        if (this.parser) {
            for (let frame of this.parser.callStack) {
                let externalFrame = <GrapsStackFrame>{
                    name: frame.name,
                    source: frame.source,
                    next: []
                }

                for (let next of frame.next) {
                    if (next.context instanceof ParserRuleContext) {
                        let start = next.context.start;
                        let stop = next.context.stop;
                        externalFrame.next.push({
                            start: { column: start.charPositionInLine, row: start.line },
                            end: { column: stop ? stop.charPositionInLine : 0, row: stop ? stop.line : start.line },
                        });
                    } else {
                        let terminal = (next.context as TerminalNode).symbol;
                        let length = terminal.stopIndex - terminal.startIndex + 1;
                        externalFrame.next.push({
                            start: { column: terminal.charPositionInLine, row: terminal.line },
                            end: { column: terminal.charPositionInLine + length, row: terminal.line },
                        });
                    }
                }
                result.push(externalFrame);
            }
        }
        return result.reverse();
    }

    public get currentTokenIndex(): number {
        return this.tokenStream.index;
    }

    public sendEvent(event: string, ...args: any[]) {
        setImmediate(_ => {
            this.emit(event, ...args);
        });
    }

    /**
     * Determines which symbols correspond to the target state we reach from the given transition.
     * Even though the prediction algorithm determines a single path through the ATN we may get
     * more than one result for ambiguities, since at the moment we only know a part of the path.
     *
     * @param frame The frame from which to compute the next symbol list.
     * @param transition The transition to the next ATN state for which we want the symbol.
     */
    public computeNextSymbols(frame: InternalStackFrame, transition: Transition) {
        frame.next = [];

        let targetRule = "";
        if (transition.target.stateType == ATNStateType.RULE_START) {
            targetRule = this.ruleNameFromIndex(transition.target.ruleIndex)!;
        }

        for (let source of frame.current) {
            let candidates = this.nextCandidates(source);
            for (let candidate of candidates) {
                if (candidate instanceof RuleReferenceSymbol) {
                    if (candidate.name == targetRule) {
                        frame.next.push(candidate);
                    }
                } else {
                    if (candidate.name == ";") { // Special case: end of rule.
                        frame.next.push(candidate);
                    } else if (candidate.context instanceof TerminalNode) {
                        let type = this.tokenIndexFromName(candidate.context.symbol.text!);
                        let currentType = this.tokenStream.LA(1);
                        if (type == currentType
                            && transition.matches(currentType, Lexer.MIN_CHAR_VALUE, Lexer.MAX_CHAR_VALUE)) {
                            frame.next.push(candidate);
                        }

                    }
                }
            }
        }
    }

    /**
     * Returns a list of reachable leaf symbols from the given symbol.
     */
    private nextCandidates(start: Symbol): Symbol[] {
        let result: Symbol[] = [];

        // We can get a rule symbol as start, which means we want to get the candidates
        // from the rule's block, instead its sibling (which is another rule).
        let next: Symbol | undefined;
        if (start instanceof RuleSymbol) {
            next = start.children[0]; // 2 children in a rule: the rule block and the semicolon.
        } else {
            // Any other case. Continue with the next directly following symbol.
            next = start.nextSibling;

            // Check EBNF suffixes first.
            if (next instanceof EbnfSuffixSymbol) {
                switch (next.name[0]) {
                    case '?': { // The previous symbol was optional. We are done with it.
                        next = next.nextSibling;
                        break;
                    }
                    case '+':
                    case '*': { // A loop - the previous symbol is again a candidate.
                        result.push(start);
                        next = next.nextSibling;
                        break;
                    }
                }
            }

            if (!next) {
                // Nothing more in the current alt. Walk up the parent chain until we find a block with content.
                let block = start;
                while (true) {
                    if (block.parent instanceof RuleSymbol) {
                        result.push(block.lastSibling); // The semicolon.
                        return result;
                    }

                    block = (block.parent as ScopedSymbol).parent;
                    next = block.nextSibling;
                    if (next) {
                        if (next instanceof EbnfSuffixSymbol) {
                            switch (next.name[0]) {
                                case '?': {
                                    next = next.nextSibling;
                                    break;
                                }
                                case '+':
                                case '*': {
                                    // Include the candidates from the previous block again.
                                    result.push(...this.candidatesFromBlock(block as ScopedSymbol));
                                    next = next.nextSibling;
                                    break;
                                }
                            }
                        }

                        if (next) {
                            break;
                        }
                    }
                }
            }
        }

        if (next instanceof BlockSymbol) {
            result.push(...this.candidatesFromBlock(next));
        } else {
            result.push(next);
        }

        // Check cardinality which allows optional elements.
        next = next.nextSibling;
        if (next instanceof EbnfSuffixSymbol) {
            if (next.name[0] == '?' || next.name[0] == '*') {
                let subResult = this.nextCandidates(next);
                result.push(...subResult);
            }
        }

        return result;
    }

    private candidatesFromBlock(block: ScopedSymbol): Symbol[] {
        let result: Symbol[] = [];
        for (let alt of block.children) {
            let next: Symbol | undefined = (alt as AlternativeSymbol).children[0];
            if (next instanceof BlockSymbol) {
                result.push(...this.candidatesFromBlock(next));
            } else {
                result.push(next);
            }

            // Check cardinality which allows optional elements.
            next = next.nextSibling;
            if (next instanceof EbnfSuffixSymbol) {
                if (next.name[0] == '?' || next.name[0] == '*') {
                    let subResult = this.nextCandidates(next);
                    result.push(...subResult);
                }
            }
        }

        return result;
    }

    private parseContextToNode(tree: ParseTree): ParseTreeNode {
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
    public breakPoints: Set<ATNState> = new Set<ATNState>();
    public callStack: InternalStackFrame[];

    constructor(
        private _debugger: GrapsDebugger,
        private symbolTable: GrapsSymbolTable,
        grammarFileName: string,
        vocabulary: Vocabulary,
        ruleNames: string[],
        atn: ATN,
        input: TokenStream
    ) {
        super(grammarFileName, vocabulary, ruleNames, atn, input);
    }

    start(startRuleIndex: number) {
        this.reset();

        this.callStack = [];
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
        // Need the current step depth for step over/out.
        let stackDepth = this.callStack.length;

        // If we are not going to jump into a rule then make step over a step in.
        // This way we can use step over exclusively for rule processing.
        let p = this.atnState;
        if (p.transition(0).serializationType != TransitionType.RULE && runMode == RunMode.StepOver) {
            runMode = RunMode.StepIn;
        }

        // We don't stop directly on the break point state but on the next rule/non-epsilon transition.
        let breakPointPending = false;

        while (true) {
            if (this.breakPoints.has(p)) {
                breakPointPending = true;
                runMode = RunMode.StepIn;
            }

            switch (p.stateType) {
                case ATNStateType.RULE_STOP: {
                    if (this._ctx.isEmpty) {
                        // End of start rule.
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

                    this.callStack.pop();
                    this.visitRuleStopState(p);

                    if ((runMode == RunMode.StepOut && stackDepth == this.callStack.length + 1)
                        || (runMode == RunMode.StepOver && stackDepth == this.callStack.length)) {
                        // Reached the rule end right before a step over/out.
                        // Continue with step-in to stop at the next work item.
                        runMode = RunMode.StepIn;
                    }

                    break;
                }

                case ATNStateType.RULE_START: {
                    let frame = new InternalStackFrame();
                    let ruleName = this._debugger.ruleNameFromIndex(this.atnState.ruleIndex);
                    if (ruleName) {
                        let ruleSymbol = this.symbolTable.resolve(ruleName, false);
                        if (ruleSymbol) {
                            // Get the source name from the symbol's symbol table (which doesn't
                            // necessarily correspond to the one we have set for the debugger).
                            let st = ruleSymbol.symbolTable as GrapsSymbolTable;
                            if (st.owner) {
                                frame.source = st.owner.fileName;
                            }
                            frame.name = ruleName;
                            frame.current = [ruleSymbol];
                            frame.next = [ruleSymbol];
                            this.callStack.push(frame);
                        }
                    }
                    // fall through
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

            // Update the list of next symbols if there's a label or rule ahead.
            p = this.atnState;
            if (p.numberOfTransitions == 1) {
                let transition = p.transition(0);
                switch (transition.serializationType) {
                    case TransitionType.RULE:
                    case TransitionType.ATOM:
                    case TransitionType.NOT_SET:
                    case TransitionType.RANGE:
                    case TransitionType.SET:
                    case TransitionType.WILDCARD: {
                        let lastStackFrame = this.callStack[this.callStack.length - 1];
                        lastStackFrame.current = lastStackFrame.next;
                        this._debugger.computeNextSymbols(lastStackFrame, transition);

                        if (runMode == RunMode.StepIn) {
                            if (breakPointPending) {
                                this._debugger.sendEvent("stopOnBreakpoint");
                            } else {
                                this._debugger.sendEvent("stopOnStep");
                            }
                            return this._rootContext;
                        }

                        break;
                    }

                    case TransitionType.EPSILON: { // Stop on the rule's semicolon.
                        if (transition.target.stateType == ATNStateType.RULE_STOP && runMode == RunMode.StepIn) {
                            let lastStackFrame = this.callStack[this.callStack.length - 1];
                            lastStackFrame.current = lastStackFrame.next;
                            this._debugger.computeNextSymbols(lastStackFrame, transition);
                            this._debugger.sendEvent("stopOnStep");

                            return this._rootContext;
                        }
                    }
                }
            }
        }
    }

    private startIsPrecedenceRule: boolean;
}

enum RunMode { Normal, StepIn, StepOver, StepOut };

export class InternalStackFrame {
    name: string;
    source: string;
    current: Symbol[];
    next: Symbol[];
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