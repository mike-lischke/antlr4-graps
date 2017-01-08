/*
 * This file is released under the MIT license.
 * Copyright (c) 2016, 2017 Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict";

import { ParserRuleContext, CharStream } from 'antlr4ts';
import { Interval } from 'antlr4ts/misc';

import { SymbolKind, SymbolScope, SymbolGroupKind, SymbolInfo, Definition } from '../index';
import { SourceContext } from './SourceContext';
import { ANTLRv4Parser, ModeSpecContext, GrammarSpecContext } from '../parser/ANTLRv4Parser';

type SymbolStore = Map<SymbolKind, Map<string, ParserRuleContext | undefined>>;

export class SymbolTable {
    public tree: ParserRuleContext; // Set by the owning source context after each parse run.

    constructor(private owner: SourceContext) { };

    public clear() {
        // Before clearing the dependencies make sure the owners are updated.
        for (let pair of this.dependencies) {
            this.owner.removeDependency(pair[0].owner);
        }

        this.dependencies.clear();
        this.localSymbols.clear();
        this.symbolReferences.clear();
    }

    public addDependency(context: SymbolTable) {
        this.dependencies.set(context, 0);
    }

    public removeDependency(context: SymbolTable) {
        if (this.dependencies.has(context)) {
            this.dependencies.delete(context);
        }
    }

    public addSymbol(kind: SymbolKind, name: string, ctx: ParserRuleContext) {
        let symbolsForKind = this.localSymbols.get(kind);
        if (!symbolsForKind) {
            symbolsForKind = new Map();
            this.localSymbols.set(kind, symbolsForKind);
        }
        symbolsForKind.set(name, ctx);
    }

    public symbolExists(symbol: string, kind: SymbolKind, scope: SymbolScope): boolean {
        // Single kind lookup.
        let globalSymbol = SymbolTable.globalSymbols.get(kind);
        if (globalSymbol && globalSymbol.has(symbol))
            return true;

        if (scope == SymbolScope.LocalOnly || scope == SymbolScope.Full) {
            let localSymbol = this.localSymbols.get(kind);
            if (localSymbol && localSymbol.has(symbol))
                return true;
        }

        if (scope == SymbolScope.DependencyOnly || scope == SymbolScope.Full) {
            for (let pair of this.dependencies) {
                let dependencySymbol = pair[0].localSymbols.get(kind);
                if (dependencySymbol && dependencySymbol.has(symbol)) {
                    return true;
                }
            }
        }
        return false;
    }

    public symbolExistsInGroup(symbol: string, kind: SymbolGroupKind, scope: SymbolScope): boolean {
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

    public contextForSymbol(symbol: string, kind: SymbolKind, scope: SymbolScope): ParserRuleContext | undefined {
        let globalSymbol = SymbolTable.globalSymbols.get(kind);
        if (!globalSymbol || !globalSymbol.has(symbol))
            return undefined; // No context available for global symbols.

        if (scope == SymbolScope.LocalOnly || scope == SymbolScope.Full) {
            let entry = this.localSymbols.get(kind);
            if (entry && entry.has(symbol))
                return entry.get(symbol);
        }

        if (scope == SymbolScope.DependencyOnly || scope == SymbolScope.Full) {
            this.dependencies.forEach((value: number, key: SymbolTable) => {
                let entry = key.localSymbols.get(kind);
                if (entry && entry.has(symbol))
                    return entry.get(symbol);
            });
        }

        return undefined;
    }

    public getSymbolInfo(symbol: string): SymbolInfo | undefined {
        for (let pair of SymbolTable.globalSymbols)
            if (pair[1].has(symbol))
                return {
                    kind: pair[0],
                    name: symbol,
                    source: "ANTLR runtime",
                    definition: definitionForContext(undefined, true)
                };

        for (let pair of this.localSymbols) {
            if (pair[1].has(symbol)) {
                let context = pair[1].get(symbol);

                // Special handling for imports.
                if (pair[0] == SymbolKind.TokenVocab || pair[0] == SymbolKind.Import) {
                    // Get the source id from a dependent module.
                    this.dependencies.forEach((value: number, key: SymbolTable) => {
                        if (key.owner.sourceId.includes(symbol)) {
                            return { // TODO: implement a best match search.
                                kind: pair[0],
                                name: symbol,
                                source: key.owner.sourceId,
                                definition: definitionForContext(key.tree, true)
                            };
                        }
                    });
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
        for (let pair of this.dependencies) {
            let result = pair[0].getSymbolInfo(symbol);
            if (result)
                return result;
        }

        return undefined;
    }

    public listSymbols(includeDependencies: boolean): SymbolInfo[] {
        var result: SymbolInfo[] = [];

        // First enumerate entries for all our local symbols.
        for (let kind of [
            SymbolKind.TokenVocab, SymbolKind.Import, SymbolKind.BuiltInLexerToken, SymbolKind.VirtualLexerToken,
            SymbolKind.FragmentLexerToken, SymbolKind.LexerToken, SymbolKind.BuiltInMode, SymbolKind.LexerMode,
            SymbolKind.BuiltInChannel, SymbolKind.TokenChannel, SymbolKind.ParserRule
        ]) {
            let symbols = this.localSymbols.get(kind);
            if (symbols) {
                for (let pair of symbols) {
                    result.push({ kind: kind, name: pair[0], source: this.owner.sourceId, definition: definitionForContext(pair[1], true) });
                }
            }
        }

        // If told so do the same for all our dependencies.
        if (includeDependencies) {
            this.dependencies.forEach((value: number, key: SymbolTable) => {
                let depSymbols = key.listSymbols(includeDependencies);
                result.push(...depSymbols);
            });
        }
        return result;
    }

    public getReferenceCount(symbol: string): number {
        let reference = this.symbolReferences.get(symbol);
        if (reference) {
            return reference;
        } else {
            return 0;
        }
    }

    public countReference(symbol: string) {
        let reference = this.symbolReferences.get(symbol);
        if (reference) {
            this.symbolReferences.set(symbol, reference + 1);
        } else {
            this.symbolReferences.set(symbol, 1);
        }
    }

    private dependencies: Map<SymbolTable, number> = new Map(); // Used like a set.
    private localSymbols: SymbolStore = new Map();
    private symbolReferences: Map<string, number> = new Map();

    private static globalSymbols: SymbolStore = new Map([
        [SymbolKind.BuiltInChannel, new Map([['DEFAULT_TOKEN_CHANNEL', undefined], ["HIDDEN", undefined]])],
        [SymbolKind.BuiltInLexerToken, new Map([['EOF', undefined]])],
        [SymbolKind.BuiltInMode, new Map([['DEFAULT_MODE', undefined]])]
    ]);
};

/**
 * Returns the definition info for the given rule context. Exported as required by listeners.
 */
export function definitionForContext(ctx: ParserRuleContext | undefined, keepQuotes: boolean): Definition | undefined {
    if (!ctx)
        return undefined;

    let cs: CharStream = ctx.start.tokenSource!.inputStream!;

    var result: Definition = {
        text: "",
        start: { column: ctx.start.charPositionInLine, row: ctx.start.line },
        end: { column: ctx.stop!.charPositionInLine, row: ctx.stop!.line }
    };

    let start = ctx.start.startIndex;
    let stop = ctx.stop!.stopIndex;

    // For mode definitions we only need the init line, not all the lexer rules following it.
    if (ctx.ruleIndex == ANTLRv4Parser.RULE_modeSpec) {
        let modeSpec: ModeSpecContext = <ModeSpecContext>ctx;
        stop = modeSpec.SEMI().symbol.stopIndex;
        result.end.column = modeSpec.SEMI().symbol.charPositionInLine;
        result.end.row = modeSpec.SEMI().symbol.line;
    } else if (ctx.ruleIndex == ANTLRv4Parser.RULE_grammarSpec) {
        // Similar for entire grammars. We only need the introducer line here.
        let grammarSpec: GrammarSpecContext = <GrammarSpecContext>ctx;
        stop = grammarSpec.SEMI().symbol.stopIndex;
        result.end.column = grammarSpec.SEMI().symbol.charPositionInLine;
        result.end.row = grammarSpec.SEMI().symbol.line;

        start = grammarSpec.grammarType().start.startIndex;
        result.start.column = grammarSpec.grammarType().start.charPositionInLine;
        result.start.row = grammarSpec.grammarType().start.line;
    }

    result.text = cs.getText(new Interval(start, stop));
    if (keepQuotes || result.text.length < 2)
        return result;

    let quoteChar = result.text[0];
    if ((quoteChar == '"' || quoteChar == '`' || quoteChar == '\'') && quoteChar == result.text[result.text.length - 1])
        result.text = result.text.substr(1, result.text.length - 2);

    return result;
}
