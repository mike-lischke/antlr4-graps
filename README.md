# antlr4-graps

[![NPM](https://nodei.co/npm/antlr4-graps.png?downloads=true&downloadRank=true)](https://nodei.co/npm/antlr4-graps/)

[![Build Status](https://travis-ci.org/mike-lischke/antlr4-graps.svg?branch=master)](https://travis-ci.org/mike-lischke/antlr4-graps)

ANTLR4 graps (Grammar Parsing Service) is a TypeScript node module using the [TypeScript ANTLR runtime](https://github.com/tunnelvisionlabs/antlr4ts) (antlr4ts) created by Sam Harwell. At the time being this runtime is still considered alpha, while it works already quite well.

# Note
**This will be the last release of antlr4-graps as a standalone module. It looks like there's no general interest in such a special module. Instead it will continue its existance in the only application that uses it so far: [ANTLR4 for Visual Studio Code](https://github.com/mike-lischke/vscode-antlr4).**

Speak up as soon as you can if you think antlr4-graps should stay as own node module.

## Features

At its core this module manages source contexts for each ANTLR4 grammar source an application provides (usually files, but can also be strings in memory). It manages grammar dependencies and automatically loads them as required (either from the same folder as the requesting grammar or from a common lib folder).

A context is identfied by a unique string, which is usually the absolute file name, but can be any unique string (e.g. a UUID). Using a file name has the advantage that the module can load file content transparently, if no grammar code is given as string (especially important for dependencies).

The module comes with jars for parser generation (the main ANTLR jar and a derived one only for typescript) and can so generate all parser and lexer files for you (targets: Java, C++, C#, JS, Python, Typescript, Swift, Go). It will then parse all error messages and provide diagnostic informations, if problems were reported. Additionally the module does its own syntactic and semantic checks and can so provide a subset of the diagnostics available from ANTLR. These are provided on each reparse call, while ANTLR diagnostics are only available after a generation call (in this case the interal diagnostics are replaced by the external ones).

Here's a feature summary of the module:

* Semi-automatic grammar management (manual loading/unloading of a main grammar, automatic loading of dependencies).
* (Re)parsing of a grammar (and its dependencies), which collects internal diagnostics.
* Symbol lookup at a given position, rule name from position, enclosing range (the outer rule or the block containing a symbol).
* Listing of all found symbols.
* Syntactic and semantic diagnostics (e.g. duplicate symbols, unknown symbols).
* Symbol reference counts (usage counts), unreferenced rules.
* A reference graph for all symbols.
* Code completion candidates (fairly stable now, might be a bit slow for large grammars).
* Railroad diagrams for rules.
* Parser generation, including interpreter data generation, with flexible configuration (listeners, visitors, search/lib folder etc.).
* Full semantic checks and reports by code generation (e.g. left-recursive rule detection etc.).
* ATN graph (nodes and links describing the ATN structure for a given rule)
* Sentence generation (random or all-path generation of sentences that are valid for a given grammar), mostly used for testing and grammar review.
* Grammar formatting, controlled by large set of (dynamically switchable) options.
* Grammar debugging support, with the usual features (run through, run w/o debugging, step-in, step-over, step-out, breakpoints at rule enter and exit points).

## Usage

You can find details about use and all available public functions and structures in the [api reference file](api.md). See the ANTLR4 for vscode extension for using the debugger.

## Testing

The GIT repository contains a test setup, which allows to run unit tests (via `mocha`). Simply execute:

```bash
npm test
```

Additionally, there is a `mocha` setup for Visual Studio Code, which even allows to debug the tests. Tests are however not shipped in the published node module.

## Known Issues
see [bug tracker](https://github.com/mike-lischke/antlr-graps/issues)

## What's next?

* Convert the module to a subfolder in the [ANTLR4 for vscode](https://github.com/mike-lischke/vscode-antlr4) extension
* Grammar profiling
* Improve code completion
* Refactoring: extract rule, rename items, comment selected lines, remove left recursion
* Templates (for frequently used rules like whitespace, ID etc.)

I'd love to see code contributions, to make the module evolve quicker.

## Release Notes

### 1.4.0
- Added a grammar debugger.

### 1.3.16
- Return full paths for symbols to remove doubt from which file a symbol comes from.

### 1.3.13

- New API `getDependencies` for a list of sub grammars a grammar depends on.
- The reference graph now contains qualified symbols (the grammar from which it was read).

### 1.3.11
- Added support for grammar formatting
- Updated docs for that and sentence generation

### 1.3.9
- Return also the rule index from `ruleFromPosition`

### 1.3.7
- Added support for sentence generation

### 1.3.6
- Travis build fixes
- Code completion improvements which now make this feature actually usable.

### 1.3.3
- Improvements for RRD scripts.
- Improvements for ATN graph scripts.

### 1.3.2
- antlr4-graps now ships with a custom build of antlr4, to be able to generate code.
- Added code generation support for grammars.
- Typscript code is no longer published.
- Added special ATN deserializer class for the typescript runtime that allows to load standard ATN data (antlr4ts uses an extended version).
- Added parser for antlr4 error message, which allows to integrate them into the module's diagnostics.
- Added ATN graph generation support.
- Doc updated to describe JS code, not TS code.

### 1.3.0
- Added support for symbol references (e.g. for references graphs).
- Updated doc and added unit tests for that.

### 1.2.15
- Now using antlr4-c3 for code completion + symbol tables.
- Added support for railroad diagrams.

### 1.2.10
- Updates for new antlr4ts version.

### 1.2.6
- Improved documenation
- Added token reference count support.
- New unit tests added for that.
- Enabled strict null checks for TS code.

### 1.2.1
- Radical change: switched from C++ to TypeScript backend (antlr4ts).
- Added more unit tests
- Better organization of exported types.
- Improved readme.md.
- `npm test` works now.

### 1.1.10
- Improved symbol information, introduced SymbolKind enum.

### 1.0.9
- Visual Studio build fixes (C++).

### 1.0.6 Initial Release
This was the first public release (yet with a C++ backend). Implements the base project structure (source contexts).
