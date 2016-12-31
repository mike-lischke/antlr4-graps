/*
 * This file is released under the MIT license.
 * Copyright (c) 2016 Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict";

import { expect, should } from 'chai';

import { AntlrLanguageSupport, SymbolKind } from "../src/index";
import { SourceContext } from '../src/SourceContext';

var backend: AntlrLanguageSupport;

describe('antlr4-graps', function () {

  describe('Create backend', function () {
    it("", function () {
      backend = new AntlrLanguageSupport();
      expect(backend).to.be.a("object");

      expect(backend).to.have.property("loadGrammar");
      expect(backend).to.have.property("releaseGrammar");
      expect(backend).to.have.property("reparse");
      expect(backend).to.have.property("infoForSymbol");
      expect(backend).to.have.property("listSymbols");
      expect(backend).to.have.property("getDiagnostics");
    });
  });

  var c1: SourceContext;
  describe('loadGrammar()', function () {
    it('', function () {
      c1 = backend.loadGrammar("test/t.g4");
      expect(c1).to.be.an.instanceOf(SourceContext);
    });
  });

  describe('unloadGrammar()', function () {
    it("", function () {
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

  describe('infoForSymbol()', function () {
    it('', function () {
      var info = backend.infoForSymbol("test/t.g4", 7, 2);
      expect(info.name).to.equal("B");
      expect(info.source).to.equal("t.g4");
      expect(info.kind).to.equal(SymbolKind.LexerToken);
      expect(info.definition.text).to.equal("B: 'B';");
      expect(info.definition.start.column).to.equal(0);
      expect(info.definition.start.row).to.equal(7);
      expect(info.definition.end.column).to.equal(6);
      expect(info.definition.end.row).to.equal(7);
    });
  });

  describe('listSymbols()', function () {
    it('', function () {
      let symbols = backend.listSymbols("test/t.g4", true);
      expect(symbols.length).to.equal(6);

      let info = symbols[4];
      expect(info.name).to.equal("x");
      expect(info.source).to.equal("t.g4");
      expect(info.kind).to.equal(SymbolKind.ParserRule);
      expect(info.definition.text).to.equal("x: A | B | C;");
      expect(info.definition.start.column).to.equal(0);
      expect(info.definition.start.row).to.equal(2);
      expect(info.definition.end.column).to.equal(12);
      expect(info.definition.end.row).to.equal(2);
    });
  });

  describe('getDiagnostics()', function () {
    it('', function () {
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
  });

  describe('reparse()', function () {
    it('', function () {
      backend.reparse("test/t.g4", "grammar A; a:: b \n| c; c: b+;");
      let diagnostics = backend.getDiagnostics("test/t.g4");

      expect(diagnostics.length).to.equal(4);

      expect(diagnostics[0].message).to.equal("mismatched input \'::\' expecting {\'options\', COLON, AT}");
      expect(diagnostics[0].length).to.equal(2);
      expect(diagnostics[0].column).to.equal(12);
      expect(diagnostics[0].row).to.equal(1);

      expect(diagnostics[1].message).to.equal("mismatched input \'|\' expecting {\'options\', COLON, AT}");
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

});
