/*
 * This file is released under the MIT license.
 * Copyright (c) 2016, 2017 Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict";

import { SymbolGroupKind, SymbolScope, SymbolKind, DiagnosticEntry, DiagnosticType } from '../index';
import { SymbolTable } from './SymbolTable';
import { ANTLRv4ParserListener } from '../parser/ANTLRv4ParserListener';
import {
    TerminalRuleContext, RulerefContext, SetElementContext, LexerCommandContext, LexerRuleSpecContext,
    ParserRuleSpecContext
} from '../parser/ANTLRv4Parser';

import { Token } from 'antlr4ts';
import { TerminalNode } from 'antlr4ts/tree';

export class SemanticListener implements ANTLRv4ParserListener {
    constructor(private diagnostics: DiagnosticEntry[], private symbolTable: SymbolTable) { }

    exitTerminalRule(ctx: TerminalRuleContext) {
        let tokenRef = ctx.TOKEN_REF();
        if (tokenRef) {
            let symbol = tokenRef.text;
            this.checkSymbolExistance(true, SymbolGroupKind.TokenRef, symbol, "Unknown token reference", tokenRef.symbol);
            this.symbolTable.countReference(symbol);
        }
    }

    exitRuleref(ctx: RulerefContext) {
        let ruleRef = ctx.RULE_REF()
        let symbol = ruleRef.text;
        this.checkSymbolExistance(true, SymbolGroupKind.RuleRef, symbol, "Unknown parser rule", ruleRef.symbol);
        this.symbolTable.countReference(symbol);
    }

    exitSetElement(ctx: SetElementContext) {
        let tokenRef = ctx.TOKEN_REF();
        if (tokenRef) {
            let symbol = tokenRef.text;
            this.checkSymbolExistance(true, SymbolGroupKind.TokenRef, symbol, "Unknown token reference", tokenRef.symbol);
            this.symbolTable.countReference(symbol);
        }
    }

    exitLexerCommand(ctx: LexerCommandContext) {
        let lexerCommandExpr = ctx.lexerCommandExpr();
        let lexerCommandExprId = lexerCommandExpr ? lexerCommandExpr.identifier() : undefined;
        if (lexerCommandExprId) {
            let name = ctx.lexerCommandName().text;
            let kind = SymbolGroupKind.TokenRef;

            let value = name.toLowerCase();
            if (value == "pushmode" || value == "mode") {
                name = "mode";
                kind = SymbolGroupKind.LexerMode;
            } else if (value == "channel") {
                kind = SymbolGroupKind.TokenChannel;
            }
            let symbol = lexerCommandExprId.text;
            this.checkSymbolExistance(true, kind, symbol, "Unknown " + name, lexerCommandExprId.start);
            this.symbolTable.countReference(symbol);
        }
    }

    exitLexerRuleSpec(ctx: LexerRuleSpecContext) {
        let tokenRef = ctx.TOKEN_REF();
        if (tokenRef) {
            let symbol = tokenRef.text;
            let seenSymbol = this.seenSymbols.get(symbol);
            if (seenSymbol) {
                this.reportDuplicateSymbol(symbol, tokenRef.symbol, seenSymbol);
            } else if (this.symbolTable.symbolExists(symbol, SymbolKind.LexerToken, SymbolScope.DependencyOnly)) {
                let symbolContext = this.symbolTable.contextForSymbol(symbol, SymbolKind.LexerToken, SymbolScope.DependencyOnly);
                this.reportDuplicateSymbol(symbol, tokenRef.symbol, symbolContext ? symbolContext.start : undefined);
            } else {
                this.seenSymbols.set(symbol, tokenRef.symbol);
            }
        }
    }

    exitParserRuleSpec(ctx: ParserRuleSpecContext) {
        let symbol = ctx.RULE_REF().text;
        let seenSymbol = this.seenSymbols.get(symbol);
        if (seenSymbol) {
            this.reportDuplicateSymbol(symbol, ctx.RULE_REF().symbol, seenSymbol);
        } else if (this.symbolTable.symbolExists(symbol, SymbolKind.ParserRule, SymbolScope.DependencyOnly)) {
            let symbolContext = this.symbolTable.contextForSymbol(symbol, SymbolKind.ParserRule, SymbolScope.DependencyOnly);
            this.reportDuplicateSymbol(symbol, ctx.RULE_REF().symbol, symbolContext ? symbolContext.start : undefined);
        } else {
            this.seenSymbols.set(symbol, ctx.RULE_REF().symbol);
        }
    }

    protected checkSymbolExistance(mustExist: boolean, kind: SymbolGroupKind, symbol: string, message: string, offendingToken: Token) {
        if (this.symbolTable.symbolExistsInGroup(symbol, kind, SymbolScope.Full) != mustExist) {
            let entry: DiagnosticEntry = {
                type: DiagnosticType.Error,
                message: message + " '" + symbol + "'",
                column: offendingToken.charPositionInLine,
                row: offendingToken.line,
                length: offendingToken.stopIndex - offendingToken.startIndex + 1
            }
            this.diagnostics.push(entry);
        }
    }

    protected reportDuplicateSymbol(symbol: string, offendingToken: Token, previousToken: Token | undefined) {
        let entry: DiagnosticEntry = {
            type: DiagnosticType.Error,
            message: "Duplicate symbol '" + symbol + "'",
            column: offendingToken.charPositionInLine,
            row: offendingToken.line,
            length: offendingToken.stopIndex - offendingToken.startIndex + 1
        }
        this.diagnostics.push(entry);
    }

    private seenSymbols: Map<string, Token> = new Map();
}
