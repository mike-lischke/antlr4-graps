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
        let tokenRef: TerminalNode;
        try { tokenRef = ctx.TOKEN_REF() } catch (e) {} // Temporary workaround for incomplete antlr4ts implementation.
        if (tokenRef) {
            let symbol = tokenRef.getText();
            this.checkSymbolExistance(true, SymbolGroupKind.TokenRef, symbol, "Unknown token reference", tokenRef.getSymbol());
        }
    }

    exitRuleref(ctx: RulerefContext) {
        let ruleRef = ctx.RULE_REF()
        let symbol = ruleRef.getText();
        this.checkSymbolExistance(true, SymbolGroupKind.RuleRef, symbol, "Unknown parser rule", ruleRef.getSymbol());

    }

    exitSetElement(ctx: SetElementContext) {
        let tokenRef: TerminalNode;
        try { tokenRef = ctx.TOKEN_REF() } catch (e) {}
        if (tokenRef) {
            let symbol = tokenRef.getText();
            this.checkSymbolExistance(true, SymbolGroupKind.TokenRef, symbol, "Unknown token reference", tokenRef.getSymbol());
        }
    }

    exitLexerCommand(ctx: LexerCommandContext) {
        if (ctx.lexerCommandExpr() && ctx.lexerCommandExpr().identifier()) {
            let name = ctx.lexerCommandName().getText();
            let kind = SymbolGroupKind.TokenRef;

            let value = name.toLowerCase();
            if (value == "pushmode" || value == "mode") {
                name = "mode";
                kind = SymbolGroupKind.LexerMode;
            } else if (value == "channel") {
                kind = SymbolGroupKind.TokenChannel;
            }
            let symbol = ctx.lexerCommandExpr().identifier().getText();
            this.checkSymbolExistance(true, kind, symbol, "Unknown " + name, ctx.lexerCommandExpr().identifier().start);
        }
    }

    exitLexerRuleSpec(ctx: LexerRuleSpecContext) {
        let tokenRef: TerminalNode;
        try { tokenRef = ctx.TOKEN_REF() } catch (e) {}
        if (tokenRef) {
            let symbol = tokenRef.getText();
            if (this.seenSymbols.has(symbol)) {
                this.reportDuplicateSymbol(symbol, tokenRef.getSymbol(), this.seenSymbols.get(symbol));
            } else if (this.symbolTable.symbolExists(symbol, SymbolKind.LexerToken, SymbolScope.DependencyOnly)) {
                let symbolContext = this.symbolTable.contextForSymbol(symbol, SymbolKind.LexerToken, SymbolScope.DependencyOnly);
                this.reportDuplicateSymbol(symbol, tokenRef.getSymbol(), symbolContext.start);
            } else {
                this.seenSymbols.set(symbol, tokenRef.getSymbol());
            }
        }
    }

    exitParserRuleSpec(ctx: ParserRuleSpecContext) {
        let symbol = ctx.RULE_REF().getText();
        if (this.seenSymbols.has(symbol)) {
            this.reportDuplicateSymbol(symbol, ctx.RULE_REF().getSymbol(), this.seenSymbols.get(symbol));
        } else if (this.symbolTable.symbolExists(symbol, SymbolKind.ParserRule, SymbolScope.DependencyOnly)) {
            let symbolContext = this.symbolTable.contextForSymbol(symbol, SymbolKind.ParserRule, SymbolScope.DependencyOnly);
            this.reportDuplicateSymbol(symbol, ctx.RULE_REF().getSymbol(), symbolContext.start);
        } else {
            this.seenSymbols.set(symbol, ctx.RULE_REF().getSymbol());
        }
    }

    protected checkSymbolExistance(mustExist: boolean, kind: SymbolGroupKind, symbol: string, message: string, offendingToken: Token) {
        if (this.symbolTable.symbolExistsInGroup(symbol, kind, SymbolScope.Full) != mustExist) {
            let entry: DiagnosticEntry = {
                type: DiagnosticType.Error,
                message: message + " '" + symbol + "'",
                column: offendingToken.getCharPositionInLine(),
                row: offendingToken.getLine(),
                length: offendingToken.getStopIndex() - offendingToken.getStartIndex() + 1
            }
            this.diagnostics.push(entry);
        }
    }

    reportDuplicateSymbol(symbol: string, offendingToken: Token, previousToken: Token) {
        let entry: DiagnosticEntry = {
            type: DiagnosticType.Error,
            message: "Duplicate symbol '" + symbol + "'",
            column: offendingToken.getCharPositionInLine(),
            row: offendingToken.getLine(),
            length: offendingToken.getStopIndex() - offendingToken.getStartIndex() + 1
        }
        this.diagnostics.push(entry);
    }

    private seenSymbols: Map<string, Token> = new Map();
}
