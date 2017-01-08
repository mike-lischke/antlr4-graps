/*
 * This file is released under the MIT license.
 * Copyright (c) 2016, 2017 Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict";

import fs = require("fs");

import { expect, should, assert } from 'chai';

import { AntlrLanguageSupport, SymbolKind } from "../index";
import { SourceContext } from '../src/SourceContext';

var backend: AntlrLanguageSupport;

describe('antlr4-graps', function () {

  describe('Base Handling', function () {
    it("Create Backend", function () {
      backend = new AntlrLanguageSupport();
      expect(backend).to.be.a("object");

      expect(backend).to.have.property("loadGrammar");
      expect(backend).to.have.property("releaseGrammar");
      expect(backend).to.have.property("reparse");
      expect(backend).to.have.property("infoForSymbol");
      expect(backend).to.have.property("listSymbols");
      expect(backend).to.have.property("getDiagnostics");
    });

    var c1: SourceContext;
    it('Load Grammar', function () {
      c1 = backend.loadGrammar("test/t.g4");
      expect(c1).to.be.an.instanceOf(SourceContext);
    });

    it("Unload grammar", function () {
      backend.releaseGrammar("test/t.g4");
      var context = backend.loadGrammar("test/t.g"); // Non-existing grammar.
      expect(context).to.be.an.instanceOf(SourceContext);
      expect(context).to.not.equal(c1);

      backend.releaseGrammar("test/t.g");
      c1 = backend.loadGrammar("test/t.g4");
      context = backend.loadGrammar("test/t.g4");
      expect(context).to.equal(c1);
      backend.releaseGrammar("test/t.g4");
    });
  });

  describe('Symbol Info Retrieval (t.g4)', function () {
    it('infoForSymbol', function () {
      var info = backend.infoForSymbol("test/t.g4", 7, 2);
      assert(info);
      expect(info!.name).to.equal("B");
      expect(info!.source).to.equal("t.g4");
      expect(info!.kind).to.equal(SymbolKind.LexerToken);
      assert(info!.definition);
      expect(info!.definition!.text).to.equal("B: 'B';");
      expect(info!.definition!.start.column).to.equal(0);
      expect(info!.definition!.start.row).to.equal(7);
      expect(info!.definition!.end.column).to.equal(6);
      expect(info!.definition!.end.row).to.equal(7);
    });

    it('listSymbols', function () {
      let symbols = backend.listSymbols("test/t.g4", true);
      expect(symbols.length).to.equal(6);

      let info = symbols[4];
      expect(info.name).to.equal("x");
      expect(info.source).to.equal("t.g4");
      expect(info.kind).to.equal(SymbolKind.ParserRule);
      expect(info.definition!.text).to.equal("x: A | B | C;");
      expect(info.definition!.start.column).to.equal(0);
      expect(info.definition!.start.row).to.equal(2);
      expect(info.definition!.end.column).to.equal(12);
      expect(info.definition!.end.row).to.equal(2);
    });

    it('getDiagnostics', function () {
      let diagnostics = backend.getDiagnostics("test/t.g4");
      expect(diagnostics.length).to.equal(2);

      expect(diagnostics[0].message).to.equal("Unknown token reference \'ZZ\'");
      expect(diagnostics[0].length).to.equal(2);
      expect(diagnostics[0].column).to.equal(3);
      expect(diagnostics[0].row).to.equal(3);

      expect(diagnostics[1].message).to.equal("Unknown channel \'BLAH\'");
      expect(diagnostics[1].length).to.equal(4);
      expect(diagnostics[1].column).to.equal(18);
      expect(diagnostics[1].row).to.equal(8);

    });

    it('reparse', function () {
      backend.reparse("test/t.g4", "grammar A; a:: b \n| c; c: b+;");
      let diagnostics = backend.getDiagnostics("test/t.g4");

      expect(diagnostics.length).to.equal(4);

      expect(diagnostics[0].message).to.equal("mismatched input '::' expecting {BEGIN_ARGUMENT, 'options', 'returns', 'locals', 'throws', COLON, AT}");
      expect(diagnostics[0].length).to.equal(2);
      expect(diagnostics[0].column).to.equal(12);
      expect(diagnostics[0].row).to.equal(1);

      expect(diagnostics[1].message).to.equal("mismatched input '|' expecting {BEGIN_ARGUMENT, 'options', 'returns', 'locals', 'throws', COLON, AT}");
      expect(diagnostics[1].length).to.equal(1);
      expect(diagnostics[1].column).to.equal(0);
      expect(diagnostics[1].row).to.equal(2);

      backend.reparse("test/t.g4", "grammar A; a: b \n| c; c: b+;");
      diagnostics = backend.getDiagnostics("test/t.g4");

      expect(diagnostics.length).to.equal(2);

      expect(diagnostics[0].message).to.equal("Unknown parser rule \'b\'");
      expect(diagnostics[0].length).to.equal(1);
      expect(diagnostics[0].column).to.equal(14);
      expect(diagnostics[0].row).to.equal(1);

      expect(diagnostics[1].message).to.equal("Unknown parser rule \'b\'");
      expect(diagnostics[1].length).to.equal(1);
      expect(diagnostics[1].column).to.equal(8);
      expect(diagnostics[1].row).to.equal(2);
    });
  });

  describe('Symbol Info Retrieval (TParser.g4)', function () {
    it('Symbol Listing', function () {
      backend.loadGrammar("test/TParser.g4");
      let symbols = backend.listSymbols("test/TParser.g4", true);
      expect(symbols.length).to.equal(51);

      let info = symbols[48];
      expect(info.name).to.equal("Mode2");
      expect(info.source).to.equal("TLexer.g4");
      expect(info.kind).to.equal(SymbolKind.LexerMode);
      assert(info.definition);
      expect(info.definition!.text).to.equal("mode Mode2;");
      expect(info.definition!.start.column).to.equal(0);
      expect(info.definition!.start.row).to.equal(85);
      expect(info.definition!.end.column).to.equal(10);
      expect(info.definition!.end.row).to.equal(85);
    });

    it('Editing', function () {
      // "Edit" the source. This will release the lexer reference and reload it.
      // If that doesn't work we'll get a lot of unknown-symbol errors (for all lexer symbols).
      let source = fs.readFileSync("test/TParser.g4", 'utf8');
      backend.reparse("test/TParser.g4", source + "\nblah: any idarray;");

      let parserDiags = backend.getDiagnostics("test/TParser.g4"); // This also updates the symbol reference counts.
      expect(parserDiags.length).to.be.equal(0);
    });

    it('Diagnostics', function () {
      let lexerDiags = backend.getDiagnostics("test/TLexer.g4");
      expect(lexerDiags.length).to.be.equal(0);

      let refCount = backend.countReferences("test/TLexer.g4", "Semicolon");
      expect(refCount).to.equal(4);

      refCount = backend.countReferences("test/TLexer.g4", "Bar");
      expect(refCount).to.equal(2);
      backend.releaseGrammar("test/TParser.g4");
    });
  });

  describe('Bugs', function () {
    it("Lexer token in a set-element context", function () {
      var info = backend.infoForSymbol("test/TParser.g4", 48, 93);
      assert(info);
      expect(info!.name).to.equal("Semicolon");
      expect(info!.source).to.equal("TLexer.g4");
      expect(info!.kind).to.equal(SymbolKind.LexerToken);
      assert(info!.definition);
      expect(info!.definition!.text).to.equal("Semicolon: \';\';");
      expect(info!.definition!.start.column).to.equal(0);
      expect(info!.definition!.start.row).to.equal(59);
      expect(info!.definition!.end.column).to.equal(14);
      expect(info!.definition!.end.row).to.equal(59);

      backend.releaseGrammar("test/TParser.g4");
      var selfDiags = backend.getSelfDiagnostics();
      expect(selfDiags.contextCount).to.equal(0);
    });
  });

});
