# antlr4-graps API reference

## Usage

In order to start using antlr4-graps you have to import it as usual and create an instance of the `AntlrLanguageSupport` class, which then provides all the functionality.

```javascript
let graps = require("antlr4-graps");
let backend = new graps.AntlrLanguageSupport("")
```

The constructor takes a path which is used as a search path for grammars. The backend takes care to load additional dependencies when you load a grammar (token vocabularies and imports) and also not to load a grammar multiple times. Instead an internal reference counter is maintained. That also means that every call to `loadGrammar` must be paired with a call to `releaseGrammar` to avoid leaking grammar instances. Note that `loadGrammar` is also called implicitely if you call any of the information functions without having loaded the given grammar first. So, better do an explicit `loadGrammar` call to ensure memory is not held longer than necessary.

The file name you pass to all API functions is mostly used to identify a source context, not so much to get the source code from that file, hence you could use any unique identifier there. However, when you call a function for a file that has not been loaded the given string is interpreted as file name and the library tries to load content from that file. The file name is also used to resolve dependencies (if a grammar cannot be found in the library/search folder), by using its base path to locate the other grammar files. So better stick with file names there, but keep in mind that the content of the file and in the source context can differ.

## Available APIs
(in alphabetic order)

> `function AntlrLanguageSupport.countReferences(fileName, symbol)`
>
> Returns the number of references for a given symbol (a string). Following conditions apply:
>
> * The symbol must be defined in the file passed to this function.
> * The return value only includes reference counts from those contexts which are currently loaded.

-----

> `function AntlrLanguageSupport.enclosingRangeForSymbol(fileName, column, row, ruleScope)`
>
> Returns a lexical range (start row/column, end row/column) of the scoped symbol that contains the given position. A scoped symbol is a symbol that can contain other symbols (e.g. a rule block, rule parameter blocks, options or token blocks). Setting `ruleScope` to `true` (default is `false`) causes the parse tree walker to stop not on the most inner block but always on a rule (or semantically equivalent) block (semantically equivalent are for instance token + option blocks). If no symbol could be found the result is undefined.

-----

> `function AntlrLanguageSupport.formatGrammar(fileName, options, start, end)`
>
> Formats the source code of the source context addressed by the first parameter.
>
> * options: an object (`FormattingOptions`) containing settings for the formatting process. See below for details.
> * start, end: the character indices of the range [start, end) to format.
> 
> The function returns a tuple containing the formatted text and the range in the original text that must be replaced(`[string, number, number]`). This range might differ from that passed in, in cases where the formatter has to adjust it.
> 
> The `formatGrammar` function allows to change formatting options on the fly. This is also described in more detail below.

-----

> `function AntlrLanguageSupport.generate(fileName, options)`
>
> This function generates parsers and associated files using one of the ANTLR jars shipped with this module. There are 2 jars, one just for the typescript target and one for all other supported target languages. The main ANTLR4 jar is a custom built snapshots, not the official download. However, you can specify a different jar in the generation options. This custom jar not only generates parser files but also interpreter data. This data is used to setup parser + lexer interpreters for testing/debugging (done transparently as part of the `generate()` call, but only if the target language is not Typescript).
>
> The `options` parameter is an object (`GenerationOptions`) with various optional parameters, like a dedicated library dir, an output dir and other settings for the ANTLR tool. See the Antlr4LanguageSupport.ts file for details.
>
> The function returns a promise carrying a string array with names of all files taking part in the generation process. You can then directly iterate over that array to request diagnostic informations for each file.

-----

> `function AntlrLanguageSupport.generateSentences(fileName, options, definitions)`
>
> This function's purpose is to generate text based on the rules in the grammar. A sentence is a syntactic block of input symbols that can be parsed as a whole. Sentences can range from very simple expressions (in a calculator grammar) up to entire programs (in a Java grammar). See below for more informations about sentence generation.
> 
> The `options` parameter is an object (`SentenceGenerationOptions`) that controls the generation process. See the Antlr4LanguageSupport.ts file for details.
> The `definitions` parameter is a map that allows to specify values for rules, which will be used instead of generating sub sentences for such a rule. More about that below.

-----

> `function AntlrLanguageSupport.getATNGraph(fileName, rule): ATNGraphData | undefined`
>
> This is also a special purpose function, not so frequently used. It returns an `ATNGraphData` object which describes nodes and links of a graph that represents the ATN structure of a given rule. This is another set of data to allow a visual presentation of the rules (beside the railroad diagrams and the rule graph), but is mostly useful for ANTLR developers only.

-----

> `function AntlrLanguageSupport.getCodeCompletionCandidates(fileName, column, row)`
>
> Returns an array of `SymbolInfo` objects which represent symbols that are possible input at the given input position. You should have called `setText()` at least once before calling this method in order to have internal state set up properly.

-----

> `function AntlrLanguageSupport.getDependencies(fileName)`
>
> Returns a list of strings with names of grammars this grammar depends on.

-----

> `function AntlrLanguageSupport.getDiagnostics(fileName: string)`
>
> Returns a list of diagnostic records (e.g. syntax errors) for the given file as an array of `DiagnosticEntry` objects. The diagnostics are produced by 2 sources. One is the backend itself, which can check for syntax errors, duplicate or missing symbols and simimlar problems. Once a generation run was triggered the internal diagnostics list is dismissed and instead all issues reported by the ANTLR4 jar are collected. This allows for basic issue reporting while editing (which shouldn't constantly generate parser files) and full info after generation (e.g. on save of a document). Should there be a problem with running generation (or the user doesn't want that) there is at least some diagnostic info.

-----

> `function AntlrLanguageSupport.getReferenceGraph(fileName)`
>
> Returns a map with rule relationships, that is mappings of rule name (lexer + parser rules) to an `ReferenceNode` object with referenced rules, tokens and string literals. This can be used e.g. for call graphs.

-----

> `function AntlrLanguageSupport.getRRDScript(fileName, rule): string`
>
> Returns a text snippet that can be processed by the [railroad-diagrams.js](http://github.com/tabatkins/railroad-diagrams) script to generate rail road diagrams. The rule name passed in can be a lexer or parser rule in the given file or any of its dependencies.

-----

> `function AntlrLanguageSupport.infoForSymbol(fileName, column, row, limitToChildren)`
>
> Returns informations about the symbol at the given position or `undefined` if no symbol could be found. The column and row params are numbers, while `limitToChildren` is a boolean (default is `true`) that indicates to consider only child symbols in specific contexts (rules, options, sets, lexer modes), which is important to limit lookup to symbols usage, not definition. If set to `false` any symbol found at that position is returned.

-----

> `function AntlrLanguageSupport.listSymbols(fileName)`
>
> Returns a list of all symbols defined in the given file (or grammar if parsed from a string). The result is an array of symbol objects (like the one returned by `infoForSymbol()`).

-----

> `function AntlrLanguageSupport.loadGrammar(fileName[, source])`
>
> Loads a grammar source from either the given file (a string) or, if specified, from the source parameter (also a string). If an explicit source is given then the file content will be ignored. The file name however is used to identify the internally managed source context and dependency references. A call to this function will not load any additional source, if there was a previous call to loadGrammar with the same file name (e.g. via dependency resolution). It will then only increase the internal ref counter. Calls to `loadGrammar()` must always be paired by a `releaseGrammar()` or the source context will stay in memory until the module is unloaded.
>

-----

> `function AntlrLanguageSupport.releaseGrammar(fileName)`
>
> Decreases the ref counter for the given file and if that reaches zero unloads the source context and releases all it's dependencies (which might lead to unloading them too if they are no longer referenced anywhere else). You should call this function also when you want to unload a grammar after you called any of the other functions without a `loadGrammar()` call first, because grammars are loaded implicitly if not done explicitly by this function.

-----

> `function AntlrLanguageSupport.reparse(fileName)`
>
> Used to update symbol information for a given file (e.g. after an edit action). You should have called `setText()` at least once before calling this method in order to have internal state set up properly.
>
> Does nothing if the grammar with the given file name hasn't been loaded yet.

-----

> `function AntlrLanguageSupport.ruleFromPosition(fileName,  column, row)`
>
> Returns a tuple (name, index) of the rule at the given position. Useful when you plan to get further informations about a specific rule (e.g. railroad diagrams). If there is no rule the result is undefined.

-----

> `function AntlrLanguageSupport.setText(fileName, source)`
>
> Call this function when the text of the grammar has changed. This is fast enough to be called on every keypress (and should be called like that to keep the internal input stream up to date for code completion). No heavy processing happens here.
>
> Does nothing if the grammar with the given file name hasn't been loaded yet.

-----

## Grammar Formatting

The `formatGrammar` function allows to format grammar code in various ways, depending on a large set of settings. Some of them have been taken from [`clang-format`](http://clang.llvm.org/docs/ClangFormatStyleOptions.html) and you can read about their usage on this web page. Other options have been added to control grammar specific aspects and some have a slightly different meaning than their `clang-format` counterparts. See the `AntrlLanguageSupport.ts` file for what options are accepted and what their possible values are (including a short description of their purposes and the default values).

In order to adjust the output during formatting it's possible to direct the formatter with comments that contain an option introducer, followed by one or more options and their new values:

```
// $antlr-format option-name on, option-name: off, option-name: 100 ...
```

Instead of `on/off` you can also use `true/false`. The colon after an option name is optional.

This does not only work for line comments, but also block and doc comments (`/*  */` and `/**  */`), however you should avoid mixing normal comments with formatting commands in a single comment, as formatting commands prevent a comment from being included in comment text reflow operations (if that is enabled). See the antlr4-graps tests for usage examples (e.g. [raw.g4](test/formatting/raw.g4)).

In case of unrecognized options the formatter will insert an error message in the target text:

`<<Unexpected input or wrong formatter command>>`

## Sentence Generation

Sentence generation is the process of walking the parser's ATN and creating sequences of text elements that will successfully parse with the grammar that was used to generate the parser (and hence the ATN). This can be used as a test corpus and for inspection to recognize possible language anomalies/oddities.

It's very tricky to generate such text without getting into endless loops (even with very low repetition and recursion settings). Try first to generate sentences for an inner rule only to see where you end up and then go up in the rule caller chain for more complex variants. The ATN is full of loops and recursions and it's easy to generate a huge set of sentences or get stuck in endless loops.

### Token Definitions

Especially lexer tokens tend to generate a large set of possible sequences, because of the large set of possible values for identifiers and the like (the Unicode charset). Therefore it's very helpful to allow the definition of text for a given rule. The sentence generator will use this text then instead of trying to find all possible combinations. It's highly recommended to define such mappings at least for all those rules that work with a large part of the Unicode charset.

Rule mapping also works for parser rules. In fact it's a simple mapping of a rule name to text, which defines the outcome of this rule. This is extremely helpful for generating sentences for complex grammars, starting with some constant text that lowers the number of results at the beginning and later remove mapping by mapping to include more and more of the inner parts of a grammar. A good candidate for a useful mapping in the parser realm are expressions, which often can get endlessly complex, but are usually not that important for your grammar (unless it's an expression parser anway).

See the [test file](test/test.ts) for an example of mappings (this test is disabled however, see the comment there why).
