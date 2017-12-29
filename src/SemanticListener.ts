/*
 * This file is released under the MIT license.
 * Copyright (c) 2016, 2017 Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict";

import { SymbolGroupKind, SymbolKind, DiagnosticEntry, DiagnosticType } from '../index';
import { GrapsSymbolTable, LexerTokenSymbol, ParserRuleSymbol } from './GrapsSymbolTable';
import { ANTLRv4ParserListener } from '../parser/ANTLRv4ParserListener';
import {
    TerminalRuleContext, RulerefContext, SetElementContext, LexerCommandContext, LexerRuleSpecContext,
    ParserRuleSpecContext
} from '../parser/ANTLRv4Parser';

import { Token } from 'antlr4ts';
import { TerminalNode } from 'antlr4ts/tree';

export class SemanticListener implements ANTLRv4ParserListener {
    constructor(private diagnostics: DiagnosticEntry[], private symbolTable: GrapsSymbolTable) { }

    // Check references to other lexer tokens.
    exitTerminalRule(ctx: TerminalRuleContext) {
        let tokenRef = ctx.TOKEN_REF();
        if (tokenRef) {
            let symbol = tokenRef.text;
            this.checkSymbolExistance(true, SymbolGroupKind.TokenRef, symbol, "Unknown token reference", tokenRef.symbol);
            this.symbolTable.countReference(symbol);
        }
    }

    // Check references to other parser rules.
    exitRuleref(ctx: RulerefContext) {
        let ruleRef = ctx.RULE_REF();
        if (ruleRef) {
            let symbol = ruleRef.text;
            this.checkSymbolExistance(true, SymbolGroupKind.RuleRef, symbol, "Unknown parser rule", ruleRef.symbol);
            this.symbolTable.countReference(symbol);
        }
    }

    // Check references to other lexer tokens.
    exitSetElement(ctx: SetElementContext) {
        let tokenRef = ctx.TOKEN_REF();
        if (tokenRef) {
            let symbol = tokenRef.text;
            this.checkSymbolExistance(true, SymbolGroupKind.TokenRef, symbol, "Unknown token reference", tokenRef.symbol);
            this.symbolTable.countReference(symbol);
        }
    }

    // Check references to modes + channels in lexer actions.
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

    // Check definition of a lexer token.
    exitLexerRuleSpec(ctx: LexerRuleSpecContext) {
        let tokenRef = ctx.TOKEN_REF();
        let name = tokenRef.text;

        // The symbol table already contains an entry for this symbol. So we can only partially use that
        // for duplicate checks. `seenSymbols` tracks occurences for symbols in the main symbol table.
        let seenSymbol = this.seenSymbols.get(name);
        if (seenSymbol) {
            this.reportDuplicateSymbol(name, tokenRef.symbol, seenSymbol);
        } else {
            // Check if there are dependencies which already have this symbol, expressed by the fact
            // that the found symbol is not defined in the main symbol table.
            let symbol = this.symbolTable.resolve(name) as LexerTokenSymbol;
            if (symbol.getRoot() != this.symbolTable) {
                this.reportDuplicateSymbol(name, tokenRef.symbol, symbol.context ? symbol.context.start : undefined);
            } else {
                // Otherwise we haven't come accross this symbol yet.
                this.seenSymbols.set(name, tokenRef.symbol);
            }
        }
    }

    // Check definition of a parser rule.
    exitParserRuleSpec(ctx: ParserRuleSpecContext) {
        // Same processing here as for lexer rules.
        let ruleRef = ctx.RULE_REF();
        let name = ruleRef.text;
        let seenSymbol = this.seenSymbols.get(name);
        if (seenSymbol) {
            this.reportDuplicateSymbol(name, ruleRef.symbol, seenSymbol);
        } else {
            let symbol = this.symbolTable.resolve(name) as ParserRuleSymbol;
            if (symbol.getRoot() != this.symbolTable) {
                this.reportDuplicateSymbol(name, ruleRef.symbol, symbol.context ? symbol.context.start : undefined);
            } else {
                this.seenSymbols.set(name, ruleRef.symbol);
            }
        }
    }

    protected checkSymbolExistance(mustExist: boolean, kind: SymbolGroupKind, symbol: string, message: string, offendingToken: Token) {
        if (this.symbolTable.symbolExistsInGroup(symbol, kind, false) != mustExist) {
            let entry: DiagnosticEntry = {
                type: DiagnosticType.Error,
                message: message + " '" + symbol + "'",
                range: {
                    start: {
                        column: offendingToken.charPositionInLine,
                        row: offendingToken.line
                    },
                    end: {
                        column: offendingToken.charPositionInLine + offendingToken.stopIndex - offendingToken.startIndex + 1,
                        row: offendingToken.line
                    }
                }
            }
            this.diagnostics.push(entry);
        }
    }

    protected reportDuplicateSymbol(symbol: string, offendingToken: Token, previousToken: Token | undefined) {
        let entry: DiagnosticEntry = {
            type: DiagnosticType.Error,
            message: "Duplicate symbol '" + symbol + "'",
            range: {
                start: {
                    column: offendingToken.charPositionInLine,
                    row: offendingToken.line
                },
                end: {
                    column: offendingToken.charPositionInLine + offendingToken.stopIndex - offendingToken.startIndex + 1,
                    row: offendingToken.line
                }
            }
        }
        this.diagnostics.push(entry);
    }

    private seenSymbols: Map<string, Token> = new Map();
}
