# antlr4-graps

[![NPM](https://nodei.co/npm/antlr4-graps.png?downloads=true&downloadRank=true)](https://nodei.co/npm/antlr4-graps/)

[![Build Status](https://travis-ci.org/mike-lischke/antlr-graps.svg?branch=master)](https://travis-ci.org/mike-lischke/antlr-graps)

ANTLR4 graps (Grammar Parsing Service) is a TypeScript node module using the [TypeScript ANTLR runtime](https://github.com/tunnelvisionlabs/antlr4ts) (antlr4ts) created by Sam Harwell. At the time being this runtime is still considered alpha, while it works already quite well.

## Usage

You can find details about (interactive) use and all available public functions and structures in the [api reference file](api.md).

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

* More semantic checks (e.g. indirect left-recursion and other warning/error conditions as detected by ANTLR)
* Automatic code formatting.
* Linting support?
* Test rig?

I'd love to see code contributions, to make the module evolve quicker.

## Release Notes

For release details see [Git commit history](https://github.com/mike-lischke/antlr-graps/commits/master).
