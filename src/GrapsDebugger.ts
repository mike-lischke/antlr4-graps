/*
 * This file is released under the MIT license.
 * Copyright (c) 2016, 2017 Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict";

import { EventEmitter } from "events";

import { LexerInterpreter, ParserInterpreter, Vocabulary, TokenStream, ANTLRInputStream, CommonTokenStream, CommonToken } from "antlr4ts";
import { ATN } from "antlr4ts/atn";

import { InterpreterData } from "./InterpreterDataReader";

/**
 * This class provides debugging support for a grammar.
 */
export class GrapsDebugger extends EventEmitter {
    constructor(lexerGrammarName: string, parserGrammarName: string, private lexerData: InterpreterData,
         private parserData: InterpreterData, private input: string) {
        super();

        let stream =  new ANTLRInputStream(input);
        this.lexer = new LexerInterpreter(lexerGrammarName, lexerData.vocabulary, lexerData.modes, lexerData.ruleNames, lexerData.atn, stream);
        let tokenStream = new CommonTokenStream(this.lexer);
        this.parser = new GrapsParserInterpreter(parserGrammarName, parserData.vocabulary, parserData.ruleNames, parserData.atn, tokenStream);
        this.parser.buildParseTree = true;
    }

    public start(stopOnEntry: boolean) {
    }

    public continue() {
    }

    public step() {
    }

    public stop() {
    }

    public get tokenList(): string[] {
        let stream = this.parser.inputStream as CommonTokenStream;
        stream.fill();
        let result: string[] = [];
        for (let token of stream.getTokens()) {
            result.push((<CommonToken>token).toString(this.parser));
        }
        return result;
    }

    private lexer: LexerInterpreter;
    private parser: GrapsParserInterpreter;
}

class GrapsParserInterpreter extends ParserInterpreter {
    constructor(grammarFileName: string, vocabulary: Vocabulary, ruleNames: string[], atn: ATN, input: TokenStream) {
        super(grammarFileName, vocabulary, ruleNames, atn, input);
    }
}
