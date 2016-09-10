'use strict';

var backend = require("./build/Release/antlr4-graps");
var sourceContexts = new Map(); // Mapping file names to SourceContext instances.

var AntlrLanguageSupport = (function () {
    function AntlrLanguageSupport() {
    }

    AntlrLanguageSupport.prototype.infoForSymbol = function (file, source, symbol) {
        var context = sourceContexts.get(file);
        if (context == undefined) {
            context = new backend.SourceContext(source);
            sourceContexts.set(file, context);
        }
        return context.infoForSymbol(symbol);
    };

    return AntlrLanguageSupport;
})();

exports.default = AntlrLanguageSupport;
