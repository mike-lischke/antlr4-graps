# antlr4-graps API reference

## Usage

In order to start using antlr4-graps you have to import it as usual and create an instance of the `AntlrLanguageSupport` class, which then provides all the functionality.

```javascript
let graps = require("antlr4-graps");
let backend = new graps.AntlrLanguageSupport("")
```

The constructor takes a path which is used as a search path for grammars. The backend takes care to load additional dependencies when you load a grammar (token vocabularies and imports) and also not to load a grammar multiple times. Instead an internal reference counter is maintained. That also means that every call to `loadGrammar` must be paired with a call to `releaseGrammar` to avoid leaking grammar instances. Note that `loadGrammar` is also called implicitely if you call any of the information functions without having loaded the given grammar first. So, better do an explicit `loadGrammar` call to ensure memory is not held longer than necessary.

The file name you pass to all API functions is mostly used to identify a source context, not so much to get the source code from that file, hence you could use any unique identifier there. However, when you call a function for a file that has not been loaded the given string is interpreted as file name and the library tries to load content from that file. The file name is also used to resolve dependencies (if a grammar cannot be found in the library/search folder), by using its base path to locate the other grammar files. So better stick with file names there.

## Available APIs

> `function AntlrLanguageSupport.loadGrammar(fileName[, source])`
>
> Loads a grammar source from either the given file (a string) or, if specified, from the source parameter (also a string). If an explicit source is given then the file content will be ignored. The file name however is used to identify the internally managed source context and dependency references. A call to this function will not load any additional source, if there was a previous call to loadGrammar with the same file name (e.g. via dependency resolution). It will then only increase the internal ref counter. Calls to `loadGrammar()` must always be paired by a `releaseGrammar()` or the source context will stay in memory until the module is unloaded.
>

-----

> `function AntlrLanguageSupport.releaseGrammar(fileName)`
>
> Decreases the ref counter for the given file and if that reaches zero unloads the source context and releases all it's dependencies (which might lead to unloading them too if they are no longer referenced anywhere else). You should call this function also when you want to unload a grammar after you called any of the other functions without a `loadGrammar()` call first, because grammars are loaded implicitly if not done explicitly by this function.

-----

> `function AntlrLanguageSupport.reparse(fileName, source)`
>
> Used to update symbol information for a given file (e.g. after an edit action). It is not necessary that the file already has all the changes. Only `source` is used as source for the grammar code. This function will also update all dependencies, by releasing no longer used ones and loading new ones, if required.

-----

> `function AntlrLanguageSupport.infoForSymbol(fileName, column, row, limitToChildren)`
>
> Returns informations about the symbol at the given position or `undefined` if no symbol could be found. The column and row params are numbers, while `limitToChildren` is a boolean (default is `true`) that indicates to consider only child symbols in specific contexts (rules, options, sets, lexer modes), which is important to limit lookup to symbols usage, not definition. If set to `false` any symbol found at that position is returned.

-----

> `function AntlrLanguageSupport.enclosingRangeForSymbol(fileName, column, row, ruleScope)`
>
> Returns a lexical range (start row/column, end row/column) of the scoped symbol that contains the given position. A scoped symbol is a symbol that can contain other symbols (e.g. a rule block, rule parameter blocks, options or token blocks). Setting `ruleScope` to `true` (default is `false`) causes the parse tree walker to stop not on the most inner block but always on a rule (or semantically equivalent) block (semantically equivalent are for instance token + option blocks). If no symbol could be found the result is undefined.

-----

> `function AntlrLanguageSupport.listSymbols(fileName)`
>
> Returns a list of all symbols defined in the given file (or grammar if parsed from a string). The result is an array of symbol objects (like the one returned by `infoForSymbol()`).

-----

> `function AntlrLanguageSupport.getCodeCompletionCandidates(fileName, column, row)`
>
> Returns an array of `SymbolInfo` objects which represent symbols that are possible input at the given input position.
>
> Note: the code completion implementation is still in experimental status, so expect problems there. Use it with small grammars only.

-----

> `function AntlrLanguageSupport.getDiagnostics(fileName: string)`
>
> Returns a list of diagnostic records (e.g. syntax errors) for the given file as an array of `DiagnosticEntry` objects. The diagnostics are produced by 2 sources. One is the backend itself, which can check for syntax errors, duplicate or missing symbols and simimlar problems. Once a generation run was triggered the internal diagnostics list is dismissed and instead all issues reported by the ANTLR jar are collected. This allows for basic issue reporting while editing (which shouldn't constantly generate parser files) and full info after generation (e.g. on save of a document). Should there be a problem with running generation (or the user doesn't want that) there is at least some diagnostic info.

-----

> `function AntlrLanguageSupport.ruleFromPosition(fileName,  column, row)`
>
> Returns the name of the rule at the given position. Useful when you plan to get further informations about a specific rule (e.g. railroad diagrams). If there is no rule the result is undefined.

-----

> `function AntlrLanguageSupport.countReferences(fileName, symbol)`
>
> Returns the number of references for a given symbol (a string). Following conditions apply:
>
> * The symbol must be defined in the file passed to this function.
> * The return value only includes reference counts from those contexts which are currently loaded.

-----

> `function AntlrLanguageSupport.getReferenceGraph(fileName)`
>
> Returns a map with rule relationships, that is mappings of rule name (lexer + parser rules) to an `ReferenceNode` object with referenced rules, tokens and string literals. This can be used e.g. for call graphs.

-----

> `function AntlrLanguageSupport.getRRDScript(fileName, rule): string`
>
> Returns a text snippet that can be processed by the [railroad-diagrams.js](http://github.com/tabatkins/railroad-diagrams) script to generate rail road diagrams. The rule name passed in can be a lexer or parser rule in the given file or any of its dependencies.

-----

> `function AntlrLanguageSupport.generate(fileName, options: GenerationOptions)`
>
> This function generates parsers and associated files using one of the ANTLR jars shipped with this module. There are 2 jars, one just for the typescript target and one for all other supported target languages. Both jars are custom built snapshots, not the official downloads, but you can specify a different jar in the generation options. The jar for non-typescript targets not only generates parser files but also interpreter data. This data is used to setup parser + lexer interpreters for testing/debugging (done transparently as part of the `generate()` call, but only if the target language is not Typescript).
>
> The `options` parameter is an object with various optional parameters, like a dedicated library dir, an output dir and other settings for the ANTLR tool.
>
> The function returns a promise carrying a string array. The strings contain names of all affected files in the generation process. You can then directly iterate over that array to request diagnostic informations for each file.

-----

> `function AntlrLanguageSupport.getATNGraph(fileName, rule): ATNGraphData | undefined`
>
> This is a special purpose function, not so frequently used. It returns an `ATNGraphData` object which describes nodes and links of a graph that represents the ATN structure of a given rule. This is another set of data to allow a visual presentation of the rules (beside the railroad diagrams and the rule graph), but is mostly useful for ANTLR developers only.

-----
