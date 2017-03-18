# antlr4-graps

[![NPM](https://nodei.co/npm/antlr4-graps.png?downloads=true&downloadRank=true)](https://nodei.co/npm/antlr4-graps/)

[![Build Status](https://travis-ci.org/mike-lischke/antlr-graps.svg?branch=master)](https://travis-ci.org/mike-lischke/antlr-graps)

ANTLR4 graps (Grammar Parsing Service) is a TypeScript node module using the [TypeScript ANTLR runtime](https://github.com/tunnelvisionlabs/antlr4ts) (antlr4ts) created by Sam Harwell. At the time being this runtime is still considered alpha, while it works already quite well.

## Usage

After installation (e.g. via `npm install antlr4-graps`) you can do a first test using `ts-node` (which you also have to install). Here's such a session to demonstrate the use of the module (run from the root folder of the antlr4-graps module):

```bash
antlr4-graps Mike$ ts-node
```
```typescript
> var graps = require(".");
'use strict'
>
> console.log(graps);
{ SymbolKind:
   { TokenVocab: 0,
     Import: 1,
     BuiltInLexerToken: 2,
     VirtualLexerToken: 3,
     FragmentLexerToken: 4,
     LexerToken: 5,
     BuiltInMode: 6,
     LexerMode: 7,
     BuiltInChannel: 8,
     TokenChannel: 9,
     ParserRule: 10 },
  DiagnosticType:
   { '0': 'Hint',
     '1': 'Info',
     '2': 'Warning',
     '3': 'Error',
     Hint: 0,
     Info: 1,
     Warning: 2,
     Error: 3 },
  DiagnosticEntry: [Function: DiagnosticEntry],
  AntlrLanguageSupport: [Function: AntlrLanguageSupport] }
undefined
>
> import { AntlrLanguageSupport } from "./src/index";
undefined
> var backend = new AntlrLanguageSupport();
undefined
>
> console.log(backend.listSymbols("test/t.g4", true));
[ { kind: 5,
    name: 'D',
    source: 't.g4',
    definition: { text: 'D: \'D\';', start: [Object], end: [Object] } },
  { kind: 5,
    name: 'A',
    source: 't.g4',
    definition: { text: 'A: \'A\';', start: [Object], end: [Object] } },
  { kind: 5,
    name: 'B',
    source: 't.g4',
    definition: { text: 'B: \'B\';', start: [Object], end: [Object] } },
  { kind: 5,
    name: 'C',
    source: 't.g4',
    definition:
     { text: 'C: \'C\' -> channel(BLAH);',
       start: [Object],
       end: [Object] } },
  { kind: 10,
    name: 'x',
    source: 't.g4',
    definition: { text: 'x: A | B | C;', start: [Object], end: [Object] } },
  { kind: 10,
    name: 'y',
    source: 't.g4',
    definition: { text: 'y: ZZ;', start: [Object], end: [Object] } } ]
undefined
> backend.releaseGrammar("test/t.g4");
undefined
>
> backend.reparse("test/t.g4", "grammar A; a:: b \n| c; c: b+;");
undefined
>
> console.log(backend.getDiagnostics("test/t.g4"));
[ DiagnosticEntry {
    type: 3,
    message: 'mismatched input \'::\' expecting {\'options\', COLON, AT}',
    column: 12,
    row: 1,
    length: 2 },
  DiagnosticEntry {
    type: 3,
    message: 'mismatched input \'|\' expecting {\'options\', COLON, AT}',
    column: 0,
    row: 2,
    length: 1 },
  DiagnosticEntry {
    type: 3,
    message: 'mismatched input \';\' expecting {\'options\', COLON, AT}',
    column: 3,
    row: 2,
    length: 1 },
  { type: 3,
    message: 'Duplicate symbol \'c\'',
    column: 5,
    row: 2,
    length: 1 } ]
undefined
>
> backend.reparse("test/t.g4", "grammar A; a: b \n| c; c: b+;");
> undefined
>
> console.log(backend.getDiagnostics("test/t.g4"));
[ { type: 3,
    message: 'Unknown parser rule \'b\'',
    position: { character: 14, line: 1 },
    length: 1 },
  { type: 3,
    message: 'Unknown parser rule \'b\'',
    position: { character: 8, line: 2 },
    length: 1 } ]
```

The module exports a central class (**AntlrLanguageSupport**), which provides all the main functionality. It takes care to load additional dependencies when you load a grammar (token vocabularies and imports) and it takes care not to load a grammar multiple times. Instead an internal reference counter is maintained. That also means that every call to `loadGrammar` must be paired with a call to `releaseGrammar` to avoid leaking grammar instances. Note that `loadGrammar` is also called implicitely if you call any of the information functions without having loaded the given grammar first. So, better do an explicit `loadGrammar` call to ensure memory is not held longer than necessary.

The module uses the given file name mostly to identify a source context, not so much to get the source from that file. Only if you call `loadGrammar()` without the source parameter the file name is used to open that file and load its content. However, the file name is also used to resolve dependencies, by using its base path to locate the other grammar files (they all have to be in the same folder).

In the node session above you can see how to call the available APIs and what their output is. The diagnostic report is executed for 2 different scenarios, one with a syntax error (and partially dubious follow up errors) and one returning results from the semantic check when syntactically everything is correct (e.g. missing symbols).

## Symbol Kinds

The module uses an enum to denote the kind of a symbol. Use this to check what type of symbol has been returned by the symbol retrieval functions.

```typescript
enum SymbolKind {
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
```

## Diagnostic Types

The module also uses an enum to denote the type of diagnostic entries (returned by `getDiagnostics`):

```typescript
enum DiagnosticType {
    Hint,
    Info,
    Warning,
    Error
}
```

## Available APIs

> `function AntlrLanguageSupport.loadGrammar(file: string[, source: string])`
>
> Loads a grammar source from either the given file or, if specified, from the source parameter. If an explicit source is given then the file content will be ignored. The file name however is used to identify the internally managed source context and dependency references. A call to this function will not load any additional source, if there was a previous call to loadGrammar with the same file name (e.g. via dependency resolution). It will then only increase the internal ref counter. Calls to `loadGrammar()` must always be paired by a `releaseGrammar()` or the source context will stay in memory until the module is unloaded.
>

-----

> `function AntlrLanguageSupport.releaseGrammar(file: string)`
>
> Decreases the ref counter for the given file and if that reaches zero unloads the source context and releases all it's dependencies (which might lead to unloading them too if they are no longer referenced anywhere else).

-----

> `function AntlrLanguageSupport.reparse(file: string, source: string)`
>
> Used to update symbol information for a given file (e.g. after an edit action). It is not necessary that the file already has all the changes. Only `source` is used as source for the grammar code. This function will also update all dependencies, by releasing no longer used ones and loading new ones, if required.

-----

> `function AntlrLanguageSupport.infoForSymbol(file: string, column: number, row: number): SymbolInfo | undefined`
>
> Returns informations about the symbol at the given position.
>
> The result is an object with these members:
>
>```typescript
>class Definition {
>    text: string;
>    start: { column: number, row: number };
>    end: { column: number, row: number };
>};
>class SymbolInfo {
>    kind: SymbolKind;
>    name: string;
>    source: string;
>    definition: Definition;
>};
>```

-----

> `function AntlrLanguageSupport.listSymbols(file: string): SymbolInfo[]`
>
> Returns a list of all symbols defined in the given file (or grammar if parsed from a string). The result is an array of symbol objects (like the ones returned by `infoForSymbol()`).

-----

> `function AntlrLanguageSupport.getDiagnostics(file: string): DiagnosticEntry[]`
>
> Returns a list of diagnostic records (e.g. syntax errors). Syntax error messages are generated by ANTLR itself and passed on unchanged currently. Semantic errors are mostly about symbol validity. A lookup is done for each found symbol (parser rule, lexer token, channel + mode) in a parse unit in all symbols (including those from imported grammars).
>
>```typescript
>class DiagnosticEntry {
>    type: DiagnosticType;
>    message: string;
>    column: number;
>    row: number;
>    length: number;
>};
>```

This function is the starting point for all kind of semantic processing, including reference counting and symbol checks. It should usually be called after a `reparse` call, to update the internal informations.

-----

> `function AntlrLanguageSupport.countReferences(file: string, symbol: string): number`
>
> Returns the number of references for a given symbol. In order to speed up processing a few conditions must be met to make this work:
>
> * The symbol must be defined in the file passed to this function.
> * The return value only includes reference counts from those contexts which have actually been loaded.

-----

> `function AntlrLanguageSupport.getCodeCompletionCandidates(file: string, column: number, row: number): SymbolInfo[]`
>
> Returns a list of symbols that are possible input at the given input position.

-----

> `function AntlrLanguageSupport.getRRDScript(file: string, rule: string): string`
>
> Returns a text snippet that can be processed by the [railroad-diagrams.js](http://github.com/tabatkins/railroad-diagrams) script to generate rail road diagrams. The rule name passed in can be a lexer or parser rule in the given file or any of it's dependencies. As usual, dependencies must be loaded first for this kind of lookup. Typical output looks like this:
>
>```
>Diagram(Choice(0, Sequence(Terminal('Foo'), Terminal('Dot'), Optional(Terminal('Bar')), Terminal('DotDot'), Terminal('Baz'), Terminal('Bar')))).addTo()
>```

-----

## Testing

The module contains a simple test setup, which you can run from the module root folder by running mocha from a console. Since the module uses TypeScript you first have to transpile the code to JavaScript. You can do this with a call to `tsc`, but better is to launch the tests with additional parameters like this:

```bash
mocha --compilers ts:ts-node/register,tsx:ts-node/register
```

Additionally, there is a 'Mocha' setup for Visual Studio Code, which even allows to debug the tests. You have to install the node modules "mocha" and "chai" locally for this to work.

## Known Issues
When looking for dependencies a simple search for .g and .g4 files is applied to find the files. This can fail if the grammar extension is different or the files are not all in the same folder.

## What's next?
The module is in a pretty good shape now and fully functional, but there are ideas to add more functionality, like:

* Call tree visualization.
* More semantic checks (e.g. indirect left-recursion and other warning/error conditions as detected by ANTLR)
* Automatic code formatting.
* Linting support?
* Test rig?

I'd love to see code contributions, so that the module evolves faster.

## Release Notes

For release details see [Git commit history](https://github.com/mike-lischke/antlr-graps/commits/master).
