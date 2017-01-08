/*
 * This file is released under the MIT license.
 * Copyright (c) 2016, 2017 Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict";

import { TerminalNode } from 'antlr4ts/tree';

import { ANTLRv4ParserListener } from '../parser/ANTLRv4ParserListener';
import { LexerRuleSpecContext, ParserRuleSpecContext, TokensSpecContext, ChannelsSpecContext,
    ModeSpecContext, DelegateGrammarContext, OptionContext } from '../parser/ANTLRv4Parser';

import { SymbolKind } from '../index';
import { SymbolTable, definitionForContext } from './SymbolTable';

export class DetailsListener implements ANTLRv4ParserListener {
    constructor(private symbolTable: SymbolTable, private imports: string[]) {}

    exitLexerRuleSpec(ctx: LexerRuleSpecContext) {
        let tokenRef;
        try { tokenRef = ctx.TOKEN_REF() } catch (e) {}
        if (tokenRef) {
            let symbol: string = tokenRef.text;
            let fragment;
            try { fragment = ctx.FRAGMENT() } catch (e) {}
            if (fragment) {
                this.symbolTable.addSymbol(SymbolKind.FragmentLexerToken, symbol, ctx);
            } else {
                this.symbolTable.addSymbol(SymbolKind.LexerToken, symbol, ctx);
            }
        }
    }

    exitParserRuleSpec(ctx: ParserRuleSpecContext) {
        let symbol = ctx.RULE_REF().text;
        this.symbolTable.addSymbol(SymbolKind.ParserRule, symbol, ctx);
    }

    exitTokensSpec(ctx: TokensSpecContext) {
        if (ctx.idList() != null) {
            for (let identifier of ctx.idList()!.identifier()) {
                let symbol = identifier.text;
                this.symbolTable.addSymbol(SymbolKind.VirtualLexerToken, symbol, ctx);
            }
        }
    }

    exitChannelsSpec(ctx: ChannelsSpecContext) {
        if (ctx.idList() != null) {
            for (let identifier of ctx.idList()!.identifier()) {
                let symbol = identifier.text;
                this.symbolTable.addSymbol(SymbolKind.TokenChannel, symbol, ctx);
            }
        }
    }

    exitModeSpec(ctx: ModeSpecContext) {
        let symbol = ctx.identifier().text;
        this.symbolTable.addSymbol(SymbolKind.LexerMode, symbol, ctx);
    }

    exitDelegateGrammar(ctx: DelegateGrammarContext) {
        let context = ctx.identifier()[ctx.identifier().length - 1];
        let name = definitionForContext(context, false)!.text;
        this.imports.push(name);
        this.symbolTable.addSymbol(SymbolKind.Import, name, ctx);
    }

    exitOption(ctx: OptionContext) {
        let option = ctx.identifier().text;
        if (option.toLocaleLowerCase() == "tokenvocab") {
            let name = ctx.optionValue().text;
            this.imports.push(name);
            this.symbolTable.addSymbol(SymbolKind.TokenVocab, name, ctx);
        }
    }

};
