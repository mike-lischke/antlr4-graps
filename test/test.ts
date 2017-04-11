/*
 * This file is released under the MIT license.
 * Copyright (c) 2016, 2017, Mike Lischke
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
      expect(backend, "Test ").to.be.a("object");

      expect(backend, "Test 1.1").to.have.property("loadGrammar");
      expect(backend, "Test 1.21").to.have.property("releaseGrammar");
      expect(backend, "Test 1.3").to.have.property("reparse");
      expect(backend, "Test 1.4").to.have.property("infoForSymbol");
      expect(backend, "Test 1.5").to.have.property("listSymbols");
      expect(backend, "Test 1.6").to.have.property("getDiagnostics");
    });

    var c1: SourceContext;
    it('Load Grammar', function () {
      c1 = backend.loadGrammar("test/t.g4");
      expect(c1, "Test 2.1").to.be.an.instanceOf(SourceContext);
    });

    it("Unload grammar", function () {
      backend.releaseGrammar("test/t.g4");
      var context = backend.loadGrammar("test/t.g"); // Non-existing grammar.
      expect(context, "Test 2.1").to.be.an.instanceOf(SourceContext);
      expect(context, "Test 2.2").to.not.equal(c1);

      backend.releaseGrammar("test/t.g");
      c1 = backend.loadGrammar("test/t.g4");
      context = backend.loadGrammar("test/t.g4");
      expect(context, "Test 2.3").to.equal(c1);
      backend.releaseGrammar("test/t.g4");
    });
  });

  describe('Symbol Info Retrieval (t.g4)', function () {
    it('infoForSymbol', function () {
      var info = backend.infoForSymbol("test/t.g4", 7, 2);
      assert(info);
      expect(info!.name, "Test 3.1").to.equal("B");
      expect(info!.source, "Test 3.2").to.equal("t.g4");
      expect(info!.kind, "Test 3.3").to.equal(SymbolKind.LexerToken);
      assert(info!.definition);
      expect(info!.definition!.text, "Test 3.4").to.equal("B: 'B';");
      expect(info!.definition!.start.column, "Test 3.5").to.equal(0);
      expect(info!.definition!.start.row, "Test 3.6").to.equal(7);
      expect(info!.definition!.end.column, "Test 3.7").to.equal(6);
      expect(info!.definition!.end.row, "Test 3.8").to.equal(7);
    });

    it('listSymbols', function () {
      let symbols = backend.listSymbols("test/t.g4", true);
      expect(symbols.length, "Test 4.1").to.equal(10);

      let info = symbols[8];
      expect(info.name, "Test 4.2").to.equal("x");
      expect(info.source, "Test 4.3").to.equal("t.g4");
      expect(info.kind, "Test 4.4").to.equal(SymbolKind.ParserRule);
      expect(info.definition!.text, "Test 4.5").to.equal("x: A | B | C;");
      expect(info.definition!.start.column, "Test 4.6").to.equal(0);
      expect(info.definition!.start.row, "Test 4.7").to.equal(2);
      expect(info.definition!.end.column, "Test 4.8").to.equal(12);
      expect(info.definition!.end.row, "Test 4.9").to.equal(2);
    });

    it('getDiagnostics', function () {
      let diagnostics = backend.getDiagnostics("test/t.g4");
      expect(diagnostics.length).to.equal(2);

      expect(diagnostics[0].message, "Test 5.1").to.equal("Unknown token reference \'ZZ\'");
      expect(diagnostics[0].length, "Test 5.2").to.equal(2);
      expect(diagnostics[0].column, "Test 5.3").to.equal(3);
      expect(diagnostics[0].row, "Test 5.4").to.equal(3);

      expect(diagnostics[1].message, "Test 5.5").to.equal("Unknown channel \'BLAH\'");
      expect(diagnostics[1].length, "Test 5.6").to.equal(4);
      expect(diagnostics[1].column, "Test 5.7").to.equal(18);
      expect(diagnostics[1].row, "Test 5.8").to.equal(8);

    });

    it('reparse', function () {
      backend.reparse("test/t.g4", "grammar A; a:: b \n| c; c: b+;");
      let diagnostics = backend.getDiagnostics("test/t.g4");

      expect(diagnostics.length, "Test 6.1").to.equal(4);

      expect(diagnostics[0].message, "Test 6.2").to.equal("mismatched input '::' expecting {BEGIN_ARGUMENT, 'options', 'returns', 'locals', 'throws', COLON, AT}");
      expect(diagnostics[0].length, "Test 6.3").to.equal(2);
      expect(diagnostics[0].column, "Test 6.4").to.equal(12);
      expect(diagnostics[0].row, "Test 6.5").to.equal(1);

      expect(diagnostics[1].message, "Test 6.6").to.equal("mismatched input '|' expecting {BEGIN_ARGUMENT, 'options', 'returns', 'locals', 'throws', COLON, AT}");
      expect(diagnostics[1].length, "Test 6.7").to.equal(1);
      expect(diagnostics[1].column, "Test 6.8").to.equal(0);
      expect(diagnostics[1].row, "Test 6.9").to.equal(2);

      backend.reparse("test/t.g4", "grammar A; a: b \n| c; c: b+;");
      diagnostics = backend.getDiagnostics("test/t.g4");

      expect(diagnostics.length, "Test 6.10").to.equal(2);

      expect(diagnostics[0].message, "Test 6.11").to.equal("Unknown parser rule \'b\'");
      expect(diagnostics[0].length, "Test 6.12").to.equal(1);
      expect(diagnostics[0].column, "Test 6.13").to.equal(14);
      expect(diagnostics[0].row, "Test 6.14").to.equal(1);

      expect(diagnostics[1].message, "Test 6.15").to.equal("Unknown parser rule \'b\'");
      expect(diagnostics[1].length, "Test 6.16").to.equal(1);
      expect(diagnostics[1].column, "Test 6.17").to.equal(8);
      expect(diagnostics[1].row, "Test 6.18").to.equal(2);
    });
  });

  describe('Symbol Info Retrieval (TParser.g4)', function () {
    it('Symbol Listing', function () {
      backend.loadGrammar("test/TParser.g4");
      let symbols = backend.listSymbols("test/TParser.g4", true);
      expect(symbols.length, "Test 7.1").to.equal(60);

      let info = symbols[40];
      expect(info.name, "Test 7.2").to.equal("Mode2");
      expect(info.source, "Test 7.3").to.equal("TLexer.g4");
      expect(info.kind, "Test 7.4").to.equal(SymbolKind.LexerMode);
      assert(info.definition, "Test 7.5");
      expect(info.definition!.text, "Test 7.6").to.equal("mode Mode2;");
      expect(info.definition!.start.column, "Test 7.7").to.equal(0);
      expect(info.definition!.start.row, "Test 7.8").to.equal(86);
      expect(info.definition!.end.column, "Test 7.9").to.equal(10);
      expect(info.definition!.end.row, "Test 7.10").to.equal(86);

      let ruleName = backend.ruleFromPosition("test/TParser.g4", 37, 103);
      expect(ruleName, "Test 7.11").to.equal("expr");
      ruleName = backend.ruleFromPosition("test/TParser.g4", 100, 123);
      expect(ruleName, "Test 7.12").to.equal("");
      ruleName = backend.ruleFromPosition("test/TParser.g4", 2, 119);
      expect(ruleName, "Test 7.13").to.equal("any");
      ruleName = backend.ruleFromPosition("test/TParser.g4", 103, 82);
      expect(ruleName, "Test 7.14").to.equal("unused");
      ruleName = backend.ruleFromPosition("test/TParser.g4", 64, 68);
      expect(ruleName, "Test 7.15").to.equal("");

      ruleName = backend.ruleFromPosition("test/TLexer.g4", 62, 77);
      expect(ruleName, "Test 7.16").to.equal("Comment");
      ruleName = backend.ruleFromPosition("test/TLexer.g4", 0, 50);
      expect(ruleName, "Test 7.16").to.equal("ID");
    });

    it('Editing', function () {
      // "Edit" the source. This will release the lexer reference and reload it.
      // If that doesn't work we'll get a lot of unknown-symbol errors (for all lexer symbols).
      let source = fs.readFileSync("test/TParser.g4", 'utf8');
      backend.reparse("test/TParser.g4", source + "\nblah: any idarray;");

      let parserDiags = backend.getDiagnostics("test/TParser.g4"); // This also updates the symbol reference counts.
      expect(parserDiags.length, "Test 8.1").to.be.equal(0);
    });

    it('Diagnostics', function () {
      let lexerDiags = backend.getDiagnostics("test/TLexer.g4");
      expect(lexerDiags.length, "Test 9.1").to.be.equal(0);

      let refCount = backend.countReferences("test/TParser.g4", "Semicolon");
      expect(refCount, "Test 9.2").to.equal(4);

      refCount = backend.countReferences("test/TLexer.g4", "Bar");
      expect(refCount, "Test 9.3").to.equal(2);
      backend.releaseGrammar("test/TParser.g4");
    });
  });

  describe('Advanced symbol informations', function () {

    it("RRD diagram", function () {
      let diagram = backend.getRRDScript("test/TParser.g4", "Any");
      expect(diagram, "Test 10.1").to.equal("Diagram(Choice(0, Sequence(Terminal('Foo'), Terminal('Dot'), " +
        "Optional(Terminal('Bar')), Terminal('DotDot'), Terminal('Baz'), Terminal('Bar')))).addTo()");

      diagram = backend.getRRDScript("test/TParser.g4", "idarray");
      expect(diagram, "Test 10.2").to.equal("ComplexDiagram(Choice(0, Sequence(Terminal('OpenCurly'), " +
        "NonTerminal('id'), ZeroOrMore(Choice(0, Sequence(Terminal('Comma'), NonTerminal('id')))), Terminal('CloseCurly')))).addTo()");

      diagram = backend.getRRDScript("test/TParser.g4", "expr");
      expect(diagram, "Test 10.2").to.equal("ComplexDiagram(Choice(0, Sequence(NonTerminal('expr'), Terminal('Star'), " +
        "NonTerminal('expr')), Sequence(NonTerminal('expr'), Terminal('Plus'), NonTerminal('expr')), Sequence(Terminal" +
        "('OpenPar'), NonTerminal('expr'), Terminal('ClosePar')), Sequence(NonTerminal('expr'), Terminal('QuestionMark'), " +
        "NonTerminal('expr'), Terminal('Colon'), NonTerminal('expr')), Sequence(NonTerminal('expr'), Terminal('Equal'), " +
        "NonTerminal('expr')), Sequence(NonTerminal('id')), Sequence(NonTerminal('flowControl')), Sequence(Terminal('INT')), " +
        "Sequence(Terminal('String')))).addTo()");
    });

    it("Reference Graph", function () {
      let graph = backend.getReferenceGraph("test/TParser.g4");
      expect(graph.size, "Test 11.1").to.equal(13);
      expect(graph.has("expr"), "Test 11.2");
      expect(graph.get("expr")!.tokens.length, "Test 11.3").to.equal(9);
      expect(graph.get("expr")!.tokens[4], "Test 11.4").to.equal("QuestionMark");

      expect(graph.has("flowControl"), "Test 11.5");
      expect(graph.get("flowControl")!.rules.length, "Test 11.6").to.equal(1);
      expect(graph.get("flowControl")!.tokens.length, "Test 11.7").to.equal(2);
      expect(graph.get("flowControl")!.literals.length, "Test 11.8").to.equal(1);
      expect(graph.get("flowControl")!.rules[0], "Test 11.9").to.equal("expr");
      expect(graph.get("flowControl")!.tokens[1], "Test 11.10").to.equal("Continue");
      expect(graph.get("flowControl")!.literals[0], "Test 11.11").to.equal("return");
    });

  });

  describe('Test for Bugs', function () {
    it("Lexer token in a set-element context", function () {
      var info = backend.infoForSymbol("test/TParser.g4", 48, 93);
      assert(info, "Test 20.1");
      expect(info!.name, "Test 20.2").to.equal("Semicolon");
      expect(info!.source, "Test 20.3").to.equal("TLexer.g4");
      expect(info!.kind, "Test 20.4").to.equal(SymbolKind.LexerToken);
      assert(info!.definition, "Test 20.5");
      expect(info!.definition!.text, "Test 20.6").to.equal("Semicolon: \';\';");
      expect(info!.definition!.start.column, "Test 20.7").to.equal(0);
      expect(info!.definition!.start.row, "Test 20.8").to.equal(59);
      expect(info!.definition!.end.column, "Test 20.9").to.equal(14);
      expect(info!.definition!.end.row, "Test 20.10").to.equal(59);

      backend.releaseGrammar("test/TParser.g4");
      var selfDiags = backend.getSelfDiagnostics();
      expect(selfDiags.contextCount, "Test 20.11").to.equal(0);
    });
  });

});
