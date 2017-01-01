/*
 * This file is released under the MIT license.
 * Copyright (c) 2016, 2017 Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict";

import { BaseErrorListener, Token, Recognizer, RecognitionException } from 'antlr4ts';

import { DiagnosticEntry, DiagnosticType } from '../index';

export class ContextErrorListener extends BaseErrorListener {
    constructor(private errorList: DiagnosticEntry[]) {
        super();
    }

    syntaxError<T extends Token>(recognizer: Recognizer<T, any>, offendingSymbol: T | undefined, line: number,
        charPositionInLine: number, msg: string, e: RecognitionException | undefined) {

        var error: DiagnosticEntry = {
            type: DiagnosticType.Error,
            message: msg,
            column: charPositionInLine,
            row: line,
            length: 1
        }
        if (offendingSymbol != undefined) {
            error.length = offendingSymbol.getStopIndex() - offendingSymbol.getStartIndex() + 1;
        }
        this.errorList.push(error);
    }
};
