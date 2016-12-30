/*
 * This file is released under the MIT license.
 * Copyright (c) 2016 Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict";

import { BaseErrorListener, Token, Recognizer, RecognitionException } from 'antlr4ts';

import { DiagnosticEntry, DiagnosticType } from './index';

export class ContextErrorListener extends BaseErrorListener {
    constructor(errorList: DiagnosticEntry[]) {
        super();
        this._errorList = errorList;
    }

    syntaxError<T extends Token>(recognizer: Recognizer<T, any>, offendingSymbol: T | undefined, line: number,
        charPositionInLine: number, msg: string, e: RecognitionException | undefined) {

        var error: DiagnosticEntry = new DiagnosticEntry();
        error.type = DiagnosticType.Error;
        error.message = msg;
        error.column = charPositionInLine;
        error.row = line;
        error.length = 1;
        if (offendingSymbol != undefined) {
            error.length = offendingSymbol.getStopIndex() - offendingSymbol.getStartIndex() + 1;
        }
        this._errorList.push(error);
    }

    private _errorList: DiagnosticEntry[]; // A reference to the actual list, filled by us.
};
