/*
 * This file is released under the MIT license.
 * Copyright (c) 2016 Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict";

import { ANTLRv4ParserListener } from '../parser/ANTLRv4ParserListener';
import { LexerRuleSpecContext, ParserRuleSpecContext, TokensSpecContext, ChannelsSpecContext,
    ModeSpecContext, DelegateGrammarContext, OptionContext } from '../parser/ANTLRv4Parser';

import { SymbolKind } from './index';
import { SymbolTable, definitionForContext } from './SymbolTable';

export class DetailsListener implements ANTLRv4ParserListener {
    public tokenVocab: string;

    constructor(private symbolTable: SymbolTable, private imports: string[]) {}

    exitLexerRuleSpec(ctx: LexerRuleSpecContext) {
        if (ctx.TOKEN_REF() != null) {
            let symbol: string = ctx.TOKEN_REF().getText();
            if (ctx.FRAGMENT() != null) {
                this.symbolTable.addSymbol(SymbolKind.FragmentLexerToken, symbol, ctx);
            } else {
                this.symbolTable.addSymbol(SymbolKind.LexerToken, symbol, ctx);
            }
        }
    }

    exitParserRuleSpec(ctx: ParserRuleSpecContext) {
        let symbol = ctx.RULE_REF().getText();
        this.symbolTable.addSymbol(SymbolKind.ParserRule, symbol, ctx);
    }

    exitTokensSpec(ctx: TokensSpecContext) {
        if (ctx.idList() != null) {
            for (let identifier of ctx.idList().identifier()) {
                let symbol = identifier.getText();
                this.symbolTable.addSymbol(SymbolKind.VirtualLexerToken, symbol, ctx);
            }
        }
    }

    exitChannelsSpec(ctx: ChannelsSpecContext) {
        if (ctx.idList() != null) {
            for (let identifier of ctx.idList().identifier()) {
                let symbol = identifier.getText();
                this.symbolTable.addSymbol(SymbolKind.TokenChannel, symbol, ctx);
            }
        }
    }

    exitModeSpec(ctx: ModeSpecContext) {
        let symbol = ctx.identifier().getText();
        this.symbolTable.addSymbol(SymbolKind.LexerMode, symbol, ctx);
    }

    exitDelegateGrammar(ctx: DelegateGrammarContext) {
        let context = ctx.identifier()[ctx.identifier().length - 1];
        let name = definitionForContext(context, false).text;
        this.imports.push(name);
        this.symbolTable.addSymbol(SymbolKind.Import, name, ctx);
    }

    exitOption(ctx: OptionContext) {
        let option = ctx.identifier().getText();
        if (option.toLocaleLowerCase() == "tokenvocab") {
            this.tokenVocab = ctx.optionValue().getText();
            this.symbolTable.addSymbol(SymbolKind.TokenVocab, this.tokenVocab, ctx);
        }
    }

};
