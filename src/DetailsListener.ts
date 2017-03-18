/*
 * This file is released under the MIT license.
 * Copyright (c) 2016, 2017, Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict";

import { ANTLRv4ParserListener } from '../parser/ANTLRv4ParserListener';
import {
    LexerRuleSpecContext, ParserRuleSpecContext, TokensSpecContext, ChannelsSpecContext,
    ModeSpecContext, DelegateGrammarContext, OptionContext
} from '../parser/ANTLRv4Parser';

import { SymbolKind } from '../index';
import {
    GrapsSymbolTable, FragmentLexerTokenSymbol, LexerTokenSymbol, ParserRuleSymbol, VirtualLexerTokenSymbol,
    TokenChannelSymbol, LexerModeSymbol, ImportSymbol, TokenVocabSymbol, definitionForContext
} from './GrapsSymbolTable';

export class DetailsListener implements ANTLRv4ParserListener {
    constructor(private symbolTable: GrapsSymbolTable, private imports: string[]) { }

    exitLexerRuleSpec(ctx: LexerRuleSpecContext) {
        let tokenRef = ctx.TOKEN_REF();
        if (tokenRef) {
            if (ctx.FRAGMENT()) {
                let symbol = this.symbolTable.addNewSymbolOfType(FragmentLexerTokenSymbol, undefined, tokenRef.text);
                symbol.context = ctx;
            } else {
                let symbol = this.symbolTable.addNewSymbolOfType(LexerTokenSymbol, undefined, tokenRef.text);
                symbol.context = ctx;
            }
        }
    }

    exitParserRuleSpec(ctx: ParserRuleSpecContext) {
        let name = ctx.RULE_REF().text;
        if (this.symbolTable.resolve(name)) {
            return; // Duplicate symbols are handled in the semantic phase.
        }
        let symbol = this.symbolTable.addNewSymbolOfType(ParserRuleSymbol, undefined, ctx.RULE_REF().text);
        symbol.context = ctx;
    }

    exitTokensSpec(ctx: TokensSpecContext) {
        let idList = ctx.idList();
        if (idList) {
            for (let identifier of idList.identifier()) {
                let symbol = this.symbolTable.addNewSymbolOfType(VirtualLexerTokenSymbol, undefined, identifier.text);
                symbol.context = ctx;
            }
        }
    }

    exitChannelsSpec(ctx: ChannelsSpecContext) {
        let idList = ctx.idList();
        if (idList) {
            for (let identifier of idList.identifier()) {
                let symbol = this.symbolTable.addNewSymbolOfType(TokenChannelSymbol, undefined, identifier.text);
                symbol.context = ctx;
            }
        }
    }

    exitModeSpec(ctx: ModeSpecContext) {
        let symbol = this.symbolTable.addNewSymbolOfType(LexerModeSymbol, undefined, ctx.identifier().text);
        symbol.context = ctx;
    }

    exitDelegateGrammar(ctx: DelegateGrammarContext) {
        let context = ctx.identifier()[ctx.identifier().length - 1];
        let name = definitionForContext(context, false) !.text;
        let symbol = this.symbolTable.addNewSymbolOfType(ImportSymbol, undefined, name);
        symbol.context = ctx;
        this.imports.push(name);
    }

    exitOption(ctx: OptionContext) {
        let option = ctx.identifier().text;
        if (option.toLocaleLowerCase() == "tokenvocab") {
            let name = ctx.optionValue().text;
            let symbol = this.symbolTable.addNewSymbolOfType(TokenVocabSymbol, undefined, name);
            symbol.context = ctx;
            this.imports.push(name);
        }
    }

};
