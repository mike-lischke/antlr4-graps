'use strict';

var logger = require("./logger");
var fs = require("fs");
var path = require("path");
var backend = require("./build/Release/antlr4-graps");

var sourceContexts = new Map(); // Mapping file names to SourceContext instances.

var AntlrLanguageSupport = (function () {
    function AntlrLanguageSupport() {
    }

    AntlrLanguageSupport.prototype.loadDependency = function(contextEntry, baseFile, depName) {
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
        return null;
    }

    AntlrLanguageSupport.prototype.loadGrammar = function(file, source) {
        var contextEntry = sourceContexts.get(file);
        if (contextEntry == undefined) {
            if (source == undefined) {
                logger.log("debug", "Loading source: " + file);
                source = fs.readFileSync(file, 'utf8');
            }
            var context = new backend.SourceContext();
            contextEntry = { "context": context, "refCount": 0, "dependencies": [] };
            sourceContexts.set(file, contextEntry);

            // Do an initial parse run and load all dependencies of this context
            // and pass their references to this context.
            var dependencies = context.parse(source);
            for (let dep of dependencies) {
                let depContext = this.loadDependency(contextEntry, file, dep);
                if (depContext != null)
                    context.addDependency(depContext);
            }
        }
        contextEntry.refCount++;
        return contextEntry.context;
    }

    AntlrLanguageSupport.prototype.releaseGrammar = function(file) {
        var contextEntry = sourceContexts.get(file);
        if (contextEntry != undefined) {
            contextEntry.refCount--;
            if (contextEntry.refCount == 0) {
                sourceContexts.delete(file);
                logger.log("debug", "Unloaded " + file);

                // Release also all dependencies.
                for (let dep of contextEntry.dependencies)
                    this.releaseGrammar(dep);
            }
        }
    }

    AntlrLanguageSupport.prototype.getContext = function(file, source) {
        var contextEntry = sourceContexts.get(file);
        if (contextEntry == undefined) {
            return loadGrammar(file, source);
        }
        return contextEntry.context;
    }

    AntlrLanguageSupport.prototype.reparse = function(file, source) {
        logger.log("debug", "Reparsing " + file);
        var context = this.getContext(file, source); // Should only do the context lookup at this point.
        context.parse(source);
    }

    AntlrLanguageSupport.prototype.infoForSymbol = function (file, source, position) {
        var context = this.getContext(file, source);
        return context.infoForSymbolAtPosition(position.line + 1, position.character);
    };

    return AntlrLanguageSupport;
})();

exports.AntlrLanguageSupport = AntlrLanguageSupport;
