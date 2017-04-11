/*
 * This file is released under the MIT license.
 * Copyright (c) 2016, 2017, Mike Lischke
 *
 * See LICENSE file for more info.
 */

'use strict';

import fs = require('fs');
import path = require('path');

export enum SymbolGroupKind { // Multiple symbol kinds can be involved in a symbol lookup.
    TokenRef,
    RuleRef,
    LexerMode,
    TokenChannel,
};

export enum SymbolKind {
    TokenVocab,
    Import,
    BuiltInLexerToken,
    VirtualLexerToken,
    FragmentLexerToken,
    LexerToken,
    BuiltInMode,
    LexerMode,
    BuiltInChannel,
    TokenChannel,
    ParserRule
};

// The definition of a single symbol.
export class Definition {
    text: string;
    start: { column: number, row: number };
    end: { column: number, row: number };
};

export class SymbolInfo {
    kind: SymbolKind;
    name: string;
    source: string;
    definition: Definition | undefined;
};

export enum DiagnosticType {
    Hint,
    Info,
    Warning,
    Error
}

export class DiagnosticEntry {
    type: DiagnosticType;
    message: string;
    column: number;
    row: number;
    length: number;
};

/**
 * All references of a rule (both lexer and parser) to other rules and string literals.
 * Lexer rules obviously cannot have any parser rule reference. String literals are mostly interesting
 * for parser rules to check for implicit lexer tokens.
 */
export class ReferenceNode {
    rules: string[];
    tokens: string[];
    literals: string[];
};

class ContextEntry {
    context: SourceContext;
    refCount: number;
    dependencies: string[] = [];
};

import { SourceContext } from './src/SourceContext'; // Import *after* the type declarations, especially the enums or static init fails.

export class AntlrLanguageSupport {
    // Mapping file names to SourceContext instances.
    private sourceContexts: Map<string, ContextEntry> = new Map<string, ContextEntry>();

    constructor() {
    }

    /**
     * Info for unit tests.
     */
    public getSelfDiagnostics() {
        return {
            "contextCount": this.sourceContexts.keys.length
        }
    }

    private loadDependency(contextEntry: ContextEntry, baseFile: string, depName: string): SourceContext | undefined {
        // The dependency file must be located in the same folder as the base file.
        var basePath = path.dirname(baseFile);
        try {
            let depPath = basePath + "/" + depName + ".g4";
            fs.statSync(depPath);
            contextEntry.dependencies.push(depPath);
            return this.loadGrammar(depPath);
        } catch (e) {
        };

        // No such file. Try the .g extension instead.
        try {
            let depPath = basePath + "/" + depName + ".g";
            fs.statSync(depPath);
            contextEntry.dependencies.push(depPath);
            return this.loadGrammar(depPath);
        } catch (e) {
        };

        // Ignore the dependency if we cannot find the source file for it.
        return undefined;
    }

    private parseGrammar(contextEntry: ContextEntry, file: string, source: string) {
        let oldDependencies = contextEntry.dependencies.slice();
        contextEntry.dependencies.length = 0;
        let newDependencies = contextEntry.context.parse(source);

        for (let dep of newDependencies) {
            let depContext = this.loadDependency(contextEntry, file, dep);
            if (depContext)
                contextEntry.context.addDependency(depContext);
        }

        // Release all old dependencies. This will only unload grammars which have
        // not been ref-counted by the above dep loading (or which are not used by other
        // grammars).
        for (let dep of oldDependencies)
            this.releaseGrammar(dep);
    }

    private getContext(file: string, source?: string | undefined): SourceContext {
        let contextEntry = this.sourceContexts.get(file);
        if (!contextEntry) {
            return this.loadGrammar(file, source);
        }
        return contextEntry.context;
    }

    public reparse(file: string, source: string) {
        var contextEntry = this.sourceContexts.get(file);
        if (!contextEntry) // Not yet loaded?
            this.loadGrammar(file, source);
        else
            this.parseGrammar(contextEntry, file, source);
    }

    public loadGrammar(file: string, source?: string | undefined): SourceContext {
        var contextEntry = this.sourceContexts.get(file);
        if (!contextEntry) {
            if (!source) {
                try {
                    fs.statSync(file);
                    source = fs.readFileSync(file, 'utf8');
                } catch (e) {
                    source = "";
                };
            }

            var context = new SourceContext(path.basename(file));
            contextEntry = { context: context, refCount: 0, dependencies: [] };
            this.sourceContexts.set(file, contextEntry);

            // Do an initial parse run and load all dependencies of this context
            // and pass their references to this context.
            this.parseGrammar(contextEntry, file, source);
        }
        contextEntry.refCount++;
        return contextEntry.context;
    }

    private internalReleaseGrammar(file: string, referencing?: ContextEntry) {
        var contextEntry = this.sourceContexts.get(file);
        if (contextEntry) {
            if (referencing) {
                // If a referencing context is given remove this one from the reference's dependencies list,
                // which in turn will remove the referencing context from the dependency's referencing list.
                referencing.context.removeDependency(contextEntry.context);
            }

            contextEntry.refCount--;
            if (contextEntry.refCount == 0) {
                this.sourceContexts.delete(file);

                // Release also all dependencies.
                for (let dep of contextEntry.dependencies)
                    this.internalReleaseGrammar(dep, contextEntry);
            }
        }
    }

    public releaseGrammar(file: string) {
        this.internalReleaseGrammar(file);
    }

    public infoForSymbol(file: string, column: number, row: number): SymbolInfo | undefined {
        var context = this.getContext(file);
        return context.infoForSymbolAtPosition(column, row);
    };

    public listSymbols(file: string, fullList: boolean): SymbolInfo[] {
        var context = this.getContext(file);
        return context.listSymbols(!fullList);
    };

    public getCodeCompletionCandidates(file: string, column: number, row: number): SymbolInfo[] {
        var context = this.getContext(file);
        return context.getCodeCompletionCandidates(column, row);
    };

    public getDiagnostics(file: string): DiagnosticEntry[] {
        var context = this.getContext(file);
        return context.getDiagnostics();
    };

    public ruleFromPosition(file: string,  column: number, row: number): string {
        var context = this.getContext(file);
        return context.ruleFromPosition(column, row);
    }

    /**
     * Count how many times a symbol has been referenced. The given file must contain the definition of this symbol.
     */
    public countReferences(file: string, symbol: string): number {
        var context = this.getContext(file);
        var result: number = context.getReferenceCount(symbol);
        for (let reference of context.references) {
            result += reference.getReferenceCount(symbol);
        }
        return result;
    }

    public getReferenceGraph(file: string): Map<string, ReferenceNode> {
        var context = this.getContext(file);
        return context.getReferenceGraph();
    }

    public getRRDScript(file: string, rule: string): string {
        var context = this.getContext(file);

        let result = context.getRRDScript(rule);
        if (!result) {
            for (let reference of context.references) {
                result = reference.getRRDScript(rule);
                if (result) {
                    return result;
                }
            }
            return "";
        }
        return result!;
    };

}
