/*
 * This file is released under the MIT license.
 * Copyright (c) 2016 Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict";

import { ParserRuleContext, CharStream } from 'antlr4ts';
import { Interval } from 'antlr4ts/misc';

import { SymbolKind, SymbolScope, SymbolGroupKind, SymbolInfo, Definition } from './index';
import { SourceContext } from './SourceContext';
import { ANTLRv4Parser, ModeSpecContext, GrammarSpecContext } from '../parser/ANTLRv4Parser';

type SymbolStore = Map<SymbolKind, Map<string, ParserRuleContext>>;

export class SymbolTable {
    public tree: ParserRuleContext; // Set by the owning source context after each parse run.

    constructor(private owner: SourceContext) { };

    clear() {
        this.dependencies = [];
        this.localSymbols.clear();
    }

    addDependency(context: SymbolTable) {
        this.dependencies.push(context);
    }

    addSymbol(kind: SymbolKind, name: string, ctx: ParserRuleContext) {
        let symbolsForKind = this.localSymbols.get(kind);
        if (!symbolsForKind) {
            symbolsForKind = new Map();
            this.localSymbols.set(kind, symbolsForKind);
        }
        symbolsForKind.set(name, ctx);
    }

    symbolExists(symbol: string, kind: SymbolKind, scope: SymbolScope): boolean {
        // Single kind lookup.
        if (SymbolTable.globalSymbols.has(<SymbolKind>kind) && SymbolTable.globalSymbols.get(<SymbolKind>kind).has(symbol))
            return true;

        if (scope == SymbolScope.LocalOnly || scope == SymbolScope.Full) {
            if (this.localSymbols.has(<SymbolKind>kind) && this.localSymbols.get(<SymbolKind>kind).has(symbol))
                return true;
        }

        if (scope == SymbolScope.DependencyOnly || scope == SymbolScope.Full) {
            for (let dep of this.dependencies) {
                if (dep.localSymbols.has(<SymbolKind>kind) && dep.localSymbols.get(<SymbolKind>kind).has(symbol))
                    return true;
            }
        }
        return false;
    }

    symbolExistsInGroup(symbol: string, kind: SymbolGroupKind, scope: SymbolScope): boolean {
        // Group of lookups.
        switch (kind) {
            case SymbolGroupKind.TokenRef:
                if (this.symbolExists(symbol, SymbolKind.BuiltInLexerToken, scope))
                    return true;
                if (this.symbolExists(symbol, SymbolKind.VirtualLexerToken, scope))
                    return true;
                if (this.symbolExists(symbol, SymbolKind.FragmentLexerToken, scope))
                    return true;
                if (this.symbolExists(symbol, SymbolKind.LexerToken, scope))
                    return true;
                break;

            case SymbolGroupKind.LexerMode:
                if (this.symbolExists(symbol, SymbolKind.BuiltInMode, scope))
                    return true;
                if (this.symbolExists(symbol, SymbolKind.LexerMode, scope))
                    return true;
                break;

            case SymbolGroupKind.TokenChannel:
                if (this.symbolExists(symbol, SymbolKind.BuiltInChannel, scope))
                    return true;
                if (this.symbolExists(symbol, SymbolKind.TokenChannel, scope))
                    return true;
                break;

            case SymbolGroupKind.RuleRef:
                if (this.symbolExists(symbol, SymbolKind.ParserRule, scope))
                    return true;
                break;
        }
        return false;
    }

    contextForSymbol(symbol: string, kind: SymbolKind, scope: SymbolScope): ParserRuleContext {
        if (!SymbolTable.globalSymbols.has(kind) || !SymbolTable.globalSymbols.get(kind).has(symbol))
            return null; // No context available for global symbols.

        if (scope == SymbolScope.LocalOnly || scope == SymbolScope.Full) {
            let entry = this.localSymbols.get(kind);
            if (entry != undefined && entry.has(symbol))
                return entry.get(symbol);
        }

        if (scope == SymbolScope.DependencyOnly || scope == SymbolScope.Full) {
            for (let dep of this.dependencies) {
                let entry = dep.localSymbols.get(kind);
                if (entry != undefined && entry.has(symbol))
                    return entry.get(symbol);
            }
        }

        return null;
    }

    getSymbolInfo(symbol: string): SymbolInfo {
        for (let pair of SymbolTable.globalSymbols)
            if (pair[1].has(symbol))
                return {
                    kind: pair[0],
                    name: symbol,
                    source: "ANTLR runtime",
                    definition: definitionForContext(null, true)
                };

        for (let pair of this.localSymbols) {
            if (pair[1].has(symbol)) {
                let context = pair[1].get(symbol);

                // Special handling for imports.
                if (pair[0] == SymbolKind.TokenVocab || pair[0] == SymbolKind.Import) {
                    // Get the source id from a dependent module.
                    for (let dep of this.dependencies) {
                        if (dep.owner.sourceId.includes(symbol)) {
                            return { // TODO: implement a best match search.
                                kind: pair[0],
                                name: symbol,
                                source: dep.owner.sourceId,
                                definition: definitionForContext(dep.tree, true)
                            };
                        }
                    }
                }

                return {
                    kind: pair[0],
                    name: symbol,
                    source: this.owner.sourceId,
                    definition: definitionForContext(context, true)
                };
            }
        }

        // Nothing in our table, so try the dependencies in order of appearance (effectively implementing rule overrides this way).
        for (let dep of this.dependencies) {
            let result: SymbolInfo = dep.getSymbolInfo(symbol);
            if (result != null)
                return result;
        }

        return null;
    }

    public listSymbols(includeDependencies: boolean): SymbolInfo[] {
        var result: SymbolInfo[] = [];

        // First enumerate entries for all our local symbols.
        for (let kind of [SymbolKind.TokenVocab, SymbolKind.Import, SymbolKind.BuiltInLexerToken, SymbolKind.VirtualLexerToken,
        SymbolKind.FragmentLexerToken, SymbolKind.LexerToken, SymbolKind.BuiltInMode, SymbolKind.LexerMode, SymbolKind.BuiltInChannel,
        SymbolKind.TokenChannel, SymbolKind.ParserRule]) {
            if (this.localSymbols.has(kind)) {
                for (let pair of this.localSymbols.get(kind)) {
                    result.push({ kind: kind, name: pair[0], source: this.owner.sourceId, definition: definitionForContext(pair[1], true) });
                }
            }
        }

        // If told so do the same for all our dependencies.
        if (includeDependencies) {
            for (let dep of this.dependencies) {
                let depSymbols = dep.listSymbols(includeDependencies);
                result = result.concat(depSymbols);
            }
        }
        return result;
    }

    private dependencies: SymbolTable[] = [];
    private localSymbols: SymbolStore = new Map();

    private static globalSymbols: SymbolStore = new Map([
        [SymbolKind.BuiltInChannel, new Map([['DEFAULT_TOKEN_CHANNEL', null], ["HIDDEN", null]])],
        [SymbolKind.BuiltInLexerToken, new Map([['EOF', null]])],
        [SymbolKind.BuiltInMode, new Map([['DEFAULT_MODE', null]])]
    ]);
};

export function definitionForContext(ctx: ParserRuleContext, keepQuotes: boolean): Definition {
    if (ctx == null)
        return null;

    let cs: CharStream = ctx.start.getTokenSource().getInputStream();

    var result: Definition = {
        text: "",
        start: { column: ctx.start.getCharPositionInLine(), row: ctx.start.getLine() },
        end: { column: ctx.stop.getCharPositionInLine(), row: ctx.stop.getLine() }
    };

    let start = ctx.start.getStartIndex();
    let stop = ctx.stop.getStopIndex();

    // For mode definitions we only need the init line, not all the lexer rules following it.
    if (ctx.getRuleIndex() == ANTLRv4Parser.RULE_modeSpec) {
        let modeSpec: ModeSpecContext = <ModeSpecContext>ctx;
        stop = modeSpec.SEMI().getSymbol().getStopIndex();
        result.end.column = modeSpec.SEMI().getSymbol().getCharPositionInLine();
        result.end.row = modeSpec.SEMI().getSymbol().getLine();
    } else if (ctx.getRuleIndex() == ANTLRv4Parser.RULE_grammarSpec) {
        // Similar for entire grammars. We only need the introducer line here.
        let grammarSpec: GrammarSpecContext = <GrammarSpecContext>ctx;
        stop = grammarSpec.SEMI().getSymbol().getStopIndex();
        result.end.column = grammarSpec.SEMI().getSymbol().getCharPositionInLine();
        result.end.row = grammarSpec.SEMI().getSymbol().getLine();

        start = grammarSpec.grammarType().start.getStartIndex();
        result.start.column = grammarSpec.grammarType().start.getCharPositionInLine();
        result.start.row = grammarSpec.grammarType().start.getLine();
    }

    result.text = cs.getText(new Interval(start, stop));
    if (keepQuotes || result.text.length < 2)
        return result;

    let quoteChar = result.text[0];
    if ((quoteChar == '"' || quoteChar == '`' || quoteChar == '\'') && quoteChar == result.text[result.text.length - 1])
        result.text = result.text.substr(1, result.text.length - 2);

    return result;
}
