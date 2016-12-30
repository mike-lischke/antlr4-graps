/*
 * This file is released under the MIT license.
 * Copyright (c) 2016 Mike Lischke
 *
 * See LICENSE file for more info.
 */

'use strict';

import fs = require('fs');
import path = require('path');

import { SourceContext } from './SourceContext';
import { SymbolInfo } from './SymbolTable';

export const SymbolKind = {
    TokenVocab: 0,
    Import: 1,
    BuiltInLexerToken: 2,
    VirtualLexerToken: 3,
    FragmentLexerToken: 4,
    LexerToken: 5,
    BuiltInMode: 6,
    LexerMode: 7,
    BuiltInChannel: 8,
    TokenChannel: 9,
    ParserRule: 10
}

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

class ContextEntry {
    context: SourceContext;
    refCount: number;
    dependencies: string[] = [];
};

export class AntlrLanguageSupport {
    // Mapping file names to SourceContext instances.
    private _sourceContexts: Map<string, ContextEntry> = new Map<string, ContextEntry>();

    constructor() {
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
        var oldDependencies = contextEntry.dependencies;
        contextEntry.dependencies = [];
        var newDependencies = contextEntry.context.parse(source);

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
        var contextEntry = this._sourceContexts.get(file);
        if (!contextEntry) {
            return this.loadGrammar(file, source);
        }
        return contextEntry.context;
    }

    public reparse(file: string, source: string) {
        var contextEntry = this._sourceContexts.get(file);
        if (!contextEntry) // Not yet loaded?
            this.loadGrammar(file, source);
        else
            this.parseGrammar(contextEntry, file, source);
    }

    public loadGrammar(file: string, source?: string | undefined): SourceContext {
        var contextEntry: ContextEntry = this._sourceContexts.get(file);
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
            this._sourceContexts.set(file, contextEntry);

            // Do an initial parse run and load all dependencies of this context
            // and pass their references to this context.
            this.parseGrammar(contextEntry, file, source);
        }
        contextEntry.refCount++;
        return contextEntry.context;
    }

    public releaseGrammar(file: string) {
        var contextEntry = this._sourceContexts.get(file);
        if (contextEntry != undefined) {
            contextEntry.refCount--;
            if (contextEntry.refCount == 0) {
                this._sourceContexts.delete(file);

                // Release also all dependencies.
                for (let dep of contextEntry.dependencies)
                    this.releaseGrammar(dep);
            }
        }
    }

    public infoForSymbol(file: string, column: number, row: number): SymbolInfo {
        var context = this.getContext(file);
        return context.infoForSymbolAtPosition(column, row);
    };

    public listSymbols(file: string, fullList: boolean): SymbolInfo[] {
        var context = this.getContext(file);
        return context.listSymbols(fullList);
    };

    public getDiagnostics(file: string) {
        var context = this.getContext(file);
        return context.getDiagnostics();
    };

}

var backend = new AntlrLanguageSupport();
//console.log(backend.listSymbols("test/t.g4", true));
