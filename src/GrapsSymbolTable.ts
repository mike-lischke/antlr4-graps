/*
 * This file is released under the MIT license.
 * Copyright (c) 2016, 2017 Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict";

import { ParserRuleContext, CharStream } from 'antlr4ts';
import { Interval } from 'antlr4ts/misc';
import { SymbolTable, Symbol } from "antlr4-c3";

import { SymbolKind, SymbolGroupKind, SymbolInfo, Definition, DependencyNode } from '../index';
import { SourceContext } from './SourceContext';
import { ANTLRv4Parser, ModeSpecContext, GrammarSpecContext } from '../parser/ANTLRv4Parser';

type SymbolStore = Map<SymbolKind, Map<string, ParserRuleContext | undefined>>;

export class GrapsSymbolTable extends SymbolTable {
    public tree: ParserRuleContext; // Set by the owning source context after each parse run.

    private symbolDependencyGraph: Map<number, DependencyNode>;

    constructor(name: string, private owner?: SourceContext) {
        super(name);
    };

    public clear() {
        // Before clearing the dependencies make sure the owners are updated.
        if (this.owner) {
            for (let dep of this.dependencies) {
                if ((dep as GrapsSymbolTable).owner) {
                    this.owner.removeDependency((dep as GrapsSymbolTable).owner!);
                }
            }
        }
        this.symbolReferences.clear();
        super.clear();
    }

    public addNewSymbol(kind: SymbolKind, name: string, ctx: ParserRuleContext) {
        let symbol: Symbol;
        switch (kind) {
            case SymbolKind.TokenVocab:
                symbol = this.addNewSymbolOfType(TokenVocabSymbol, undefined, name);
                break;
            case SymbolKind.Import:
                symbol = this.addNewSymbolOfType(ImportSymbol, undefined, name);
                break;
            case SymbolKind.BuiltInLexerToken:
                symbol = this.addNewSymbolOfType(BuiltInLexerTokenSymbol, undefined, name);
                break;
            case SymbolKind.VirtualLexerToken:
                symbol = this.addNewSymbolOfType(VirtualLexerTokenSymbol, undefined, name);
                break;
            case SymbolKind.FragmentLexerToken:
                symbol = this.addNewSymbolOfType(FragmentLexerTokenSymbol, undefined, name);
                break;
            case SymbolKind.LexerToken:
                symbol = this.addNewSymbolOfType(LexerTokenSymbol, undefined, name);
                break;
            case SymbolKind.BuiltInMode:
                symbol = this.addNewSymbolOfType(BuiltInModeSymbol, undefined, name);
                break;
            case SymbolKind.LexerMode:
                symbol = this.addNewSymbolOfType(LexerModeSymbol, undefined, name);
                break;
            case SymbolKind.BuiltInChannel:
                symbol = this.addNewSymbolOfType(BuiltInChannelSymbol, undefined, name);
                break;
            case SymbolKind.TokenChannel:
                symbol = this.addNewSymbolOfType(TokenChannelSymbol, undefined, name);
                break;
            default: // SymbolKind.ParserRule
                symbol = this.addNewSymbolOfType(ParserRuleSymbol, undefined, name);
                break;
        }
        symbol.context = ctx;
    }

    public symbolExists(name: string, kind: SymbolKind, localOnly: boolean): boolean {
        return this.getSymbolOfType(name, kind, localOnly) != undefined;
    }

    public symbolExistsInGroup(symbol: string, kind: SymbolGroupKind, localOnly: boolean): boolean {
        // Group of lookups.
        switch (kind) {
            case SymbolGroupKind.TokenRef:
                if (this.symbolExists(symbol, SymbolKind.BuiltInLexerToken, localOnly))
                    return true;
                if (this.symbolExists(symbol, SymbolKind.VirtualLexerToken, localOnly))
                    return true;
                if (this.symbolExists(symbol, SymbolKind.FragmentLexerToken, localOnly))
                    return true;
                if (this.symbolExists(symbol, SymbolKind.LexerToken, localOnly))
                    return true;
                break;

            case SymbolGroupKind.LexerMode:
                if (this.symbolExists(symbol, SymbolKind.BuiltInMode, localOnly))
                    return true;
                if (this.symbolExists(symbol, SymbolKind.LexerMode, localOnly))
                    return true;
                break;

            case SymbolGroupKind.TokenChannel:
                if (this.symbolExists(symbol, SymbolKind.BuiltInChannel, localOnly))
                    return true;
                if (this.symbolExists(symbol, SymbolKind.TokenChannel, localOnly))
                    return true;
                break;

            case SymbolGroupKind.RuleRef:
                if (this.symbolExists(symbol, SymbolKind.ParserRule, localOnly))
                    return true;
                break;
        }
        return false;
    }

    public contextForSymbol(name: string, kind: SymbolKind, localOnly: boolean): ParserRuleContext | undefined {
        let symbol = this.getSymbolOfType(name, kind, localOnly);
        if (!symbol) {
            return undefined;
        }
        return symbol.context;
    }

    public getSymbolInfo(name: string): SymbolInfo | undefined {
        let symbol = this.resolve(name);
        if (!symbol) {
            return undefined;
        }

        let kind = this.getKindFromSymbol(symbol);

        // Special handling for imports.
        if (kind == SymbolKind.TokenVocab || kind == SymbolKind.Import) {
            // Get the source id from a dependent module.
            this.dependencies.forEach((table: GrapsSymbolTable) => {
                if (table.owner && table.owner.sourceId.includes(name)) {
                    return { // TODO: implement a best match search.
                        kind: kind,
                        name: symbol!.name,
                        source: table.owner.sourceId,
                        definition: definitionForContext(table.tree, true)
                    };
                }
            });
        }

        let root = symbol.getRoot() as GrapsSymbolTable;
        return {
            kind: kind,
            name: symbol.name,
            source: (symbol.context && root.owner) ? root.owner.sourceId : "ANTLR runtime",
            definition: definitionForContext(symbol.context, true)
        };

    }

    private symbolsOfType<T extends Symbol>(t: new (...args: any[]) => T, localOnly: boolean = false): SymbolInfo[] {
        var result: SymbolInfo[] = [];

        let symbols = this.getAllSymbols(t, localOnly);
        for (let symbol of symbols) {
            let root = symbol.getRoot() as GrapsSymbolTable;
            result.push({
                kind: this.getKindFromSymbol(symbol),
                name: symbol.name,
                source: root.owner ? root.owner.sourceId : "ANTLR runtime",
                definition: definitionForContext(symbol.context, true)
            });
        }
        return result;
    }

    public listSymbols(localOnly: boolean): SymbolInfo[] {
        var result: SymbolInfo[] = [];

        result.push(...this.symbolsOfType(TokenVocabSymbol, localOnly));
        result.push(...this.symbolsOfType(ImportSymbol, localOnly));
        result.push(...this.symbolsOfType(BuiltInLexerTokenSymbol, localOnly));
        result.push(...this.symbolsOfType(VirtualLexerTokenSymbol, localOnly));
        result.push(...this.symbolsOfType(FragmentLexerTokenSymbol, localOnly));
        result.push(...this.symbolsOfType(LexerTokenSymbol, localOnly));
        result.push(...this.symbolsOfType(BuiltInModeSymbol, localOnly));
        result.push(...this.symbolsOfType(LexerModeSymbol, localOnly));
        result.push(...this.symbolsOfType(BuiltInChannelSymbol, localOnly));
        result.push(...this.symbolsOfType(TokenChannelSymbol, localOnly));
        result.push(...this.symbolsOfType(ParserRuleSymbol, localOnly));

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

    private getSymbolOfType(name: string, kind: SymbolKind, localOnly: boolean): Symbol | undefined {
        switch (kind) {
            case SymbolKind.TokenVocab:
                return this.resolve(name, localOnly) as TokenVocabSymbol;
            case SymbolKind.Import:
                return this.resolve(name, localOnly) as ImportSymbol;
            case SymbolKind.BuiltInLexerToken:
                return this.resolve(name, localOnly) as BuiltInLexerTokenSymbol;
            case SymbolKind.VirtualLexerToken:
                return this.resolve(name, localOnly) as VirtualLexerTokenSymbol;
            case SymbolKind.FragmentLexerToken:
                return this.resolve(name, localOnly) as FragmentLexerTokenSymbol;
            case SymbolKind.LexerToken:
                return this.resolve(name, localOnly) as LexerTokenSymbol;
            case SymbolKind.BuiltInMode:
                return this.resolve(name, localOnly) as BuiltInModeSymbol;
            case SymbolKind.LexerMode:
                return this.resolve(name, localOnly) as LexerModeSymbol;
            case SymbolKind.BuiltInChannel:
                return this.resolve(name, localOnly) as BuiltInChannelSymbol;
            case SymbolKind.TokenChannel:
                return this.resolve(name, localOnly) as TokenChannelSymbol;
            case SymbolKind.ParserRule:
                return this.resolve(name, localOnly) as ParserRuleSymbol;
        }

        return undefined;
    }

    private getKindFromSymbol(symbol: Symbol): SymbolKind {
        if (symbol instanceof TokenVocabSymbol) {
            return SymbolKind.TokenVocab;
        }
        if (symbol instanceof ImportSymbol) {
            return SymbolKind.Import;
        }
        if (symbol instanceof BuiltInLexerTokenSymbol) {
            return SymbolKind.BuiltInLexerToken;
        }
        if (symbol instanceof VirtualLexerTokenSymbol) {
            return SymbolKind.VirtualLexerToken;
        }
        if (symbol instanceof FragmentLexerTokenSymbol) {
            return SymbolKind.FragmentLexerToken;
        }
        if (symbol instanceof LexerTokenSymbol) {
            return SymbolKind.LexerToken;
        }
        if (symbol instanceof BuiltInModeSymbol) {
            return SymbolKind.BuiltInMode;
        }
        if (symbol instanceof LexerModeSymbol) {
            return SymbolKind.LexerMode;
        }
        if (symbol instanceof BuiltInChannelSymbol) {
            return SymbolKind.BuiltInChannel;
        }
        if (symbol instanceof TokenChannelSymbol) {
            return SymbolKind.TokenChannel;
        }
        return SymbolKind.ParserRule;
    }

    private symbolReferences: Map<string, number> = new Map();
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

export class TokenVocabSymbol extends Symbol { }
export class ImportSymbol extends Symbol { }
export class BuiltInLexerTokenSymbol extends Symbol { }
export class VirtualLexerTokenSymbol extends Symbol { }
export class FragmentLexerTokenSymbol extends Symbol { }
export class LexerTokenSymbol extends Symbol { }
export class BuiltInModeSymbol extends Symbol { }
export class LexerModeSymbol extends Symbol { }
export class BuiltInChannelSymbol extends Symbol { }
export class TokenChannelSymbol extends Symbol { }
export class ParserRuleSymbol extends Symbol { }
