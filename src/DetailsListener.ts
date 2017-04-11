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
    ModeSpecContext, DelegateGrammarContext, OptionContext, TerminalRuleContext, RulerefContext
} from '../parser/ANTLRv4Parser';

import { SymbolKind } from '../index';
import {
    GrapsSymbolTable, FragmentLexerTokenSymbol, LexerTokenSymbol, ParserRuleSymbol, VirtualLexerTokenSymbol,
    TokenChannelSymbol, LexerModeSymbol, ImportSymbol, TokenVocabSymbol, definitionForContext
} from './GrapsSymbolTable';

import { ScopedSymbol, LiteralSymbol } from "antlr4-c3";

export class DetailsListener implements ANTLRv4ParserListener {
    constructor(private symbolTable: GrapsSymbolTable, private imports: string[]) { }

    enterLexerRuleSpec(ctx: LexerRuleSpecContext) {
        let tokenRef = ctx.TOKEN_REF();
        if (tokenRef) {
            if (ctx.FRAGMENT()) {
                this.currentRuleSymbol = this.symbolTable.addNewSymbolOfType(FragmentLexerTokenSymbol, undefined, tokenRef.text);
                this.currentRuleSymbol.context = ctx;
            } else {
                this.currentRuleSymbol = this.symbolTable.addNewSymbolOfType(LexerTokenSymbol, undefined, tokenRef.text);
                this.currentRuleSymbol.context = ctx;
            }
        }
    }

    enterParserRuleSpec(ctx: ParserRuleSpecContext) {
        let name = ctx.RULE_REF().text;
        if (this.symbolTable.resolve(name)) {
            return; // Duplicate symbols are handled in the semantic phase.
        }
        this.currentRuleSymbol = this.symbolTable.addNewSymbolOfType(ParserRuleSymbol, undefined, ctx.RULE_REF().text);
        this.currentRuleSymbol.context = ctx;
    }

    enterTokensSpec(ctx: TokensSpecContext) {
        let idList = ctx.idList();
        if (idList) {
            for (let identifier of idList.identifier()) {
                let symbol = this.symbolTable.addNewSymbolOfType(VirtualLexerTokenSymbol, undefined, identifier.text);
                symbol.context = ctx;
            }
        }
    }

    enterTerminalRule(ctx: TerminalRuleContext) {
        if (this.currentRuleSymbol) {
            if (ctx.TOKEN_REF()) {
                let refName = ctx.TOKEN_REF()!.text;
                if (!this.currentRuleSymbol.resolve(refName, true)) { // A rule can be referenced more than once.
                    let symbol = this.symbolTable.addNewSymbolOfType(LexerTokenSymbol, this.currentRuleSymbol, refName);
                }
            } else {
                // Must be a string literal then.
                let refName = ctx.STRING_LITERAL()!.text;
                refName = refName.substring(1, refName.length - 1);
                if (!this.currentRuleSymbol.resolve(refName, true)) {
                    let symbol = this.symbolTable.addNewSymbolOfType(LiteralSymbol, this.currentRuleSymbol, refName);
                }
            }
        }
    }

    enterRuleref(ctx: RulerefContext) {
        if (ctx.RULE_REF() && this.currentRuleSymbol) {
            let refName = ctx.RULE_REF()!.text;
            if (!this.currentRuleSymbol.resolve(refName, true)) {
                let symbol = this.symbolTable.addNewSymbolOfType(ParserRuleSymbol, this.currentRuleSymbol, refName);
            }
        }
    }

    enterChannelsSpec(ctx: ChannelsSpecContext) {
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
        let name = definitionForContext(context, false)!.text;
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

    private currentRuleSymbol: ScopedSymbol | undefined;
};
