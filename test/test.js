"use strict";

const chai = require('chai'),
  expect = chai.expect,
  should = chai.should();
const graps = require("../");

var backend;

describe('antlr4-graps', function() {

  describe('Create backend', function() {
    it("", function() {
      backend = new graps.AntlrLanguageSupport();
      expect(backend).to.be.a("object");

      expect(backend).to.have.property("loadGrammar");
      expect(backend).to.have.property("releaseGrammar");
      expect(backend).to.have.property("reparse");
      expect(backend).to.have.property("infoForSymbol");
      expect(backend).to.have.property("listSymbols");
      expect(backend).to.have.property("getDiagnostics");
    });
  });

  var c1;
  describe('loadGrammar()', function() {
    it('', function() {
      var context = backend.loadGrammar("test/t.g4");
      expect(context).to.be.a("SourceContext");
      c1 = context;
    });
  });

  describe('unloadGrammar()', function() {
    it("", function() {
      backend.releaseGrammar("test/t.g4");
      var context = backend.loadGrammar("test/t.g");
      expect(context).to.be.a("SourceContext");
      expect(context).to.not.equal(c1);

      backend.releaseGrammar("test/t.g");
      c1 = backend.loadGrammar("test/t.g4");
      context = backend.loadGrammar("test/t.g4");
      expect(context).to.equal(c1);
      backend.releaseGrammar("test/t.g4");
    });
  });

  describe('infoForSymbol()', function() {
    it('', function() {
      var info = backend.infoForSymbol("test/t.g4", { "line": 2, "character": 7});
      expect(info.name).to.equal("B");
      expect(info.source).to.equal("t.g4");
      expect(info.kind).to.equal(backend.SymbolKind.LexerToken);
      expect(info.text).to.equal("B: 'B';");
      //expect(info.start).to.equal({ character: 0, line: 6 });
      expect(info.start.character).to.equal(0);
      expect(info.start.line).to.equal(7);
      //expect(info.stop).to.equal({ character: 6, line: 6 });
      expect(info.stop.character).to.equal(6);
      expect(info.stop.line).to.equal(7);
    });
  });

  describe('listSymbols()', function() {
    it('', function() {
      let symbols = backend.listSymbols("test/t.g4");
      expect(symbols.length).to.equal(6);

      let info = symbols[5];
      expect(info.name).to.equal("x");
      expect(info.source).to.equal("t.g4");
      expect(info.kind).to.equal(backend.SymbolKind.ParserRule);
      expect(info.text).to.equal("x: A | B | C;");
      expect(info.start.character).to.equal(0);
      expect(info.start.line).to.equal(2);
      expect(info.stop.character).to.equal(12);
      expect(info.stop.line).to.equal(2);
    });
  });

  describe('getDiagnostics()', function() {
    it('', function() {
      let diagnostics = backend.getDiagnostics("test/t.g4");
      expect(diagnostics.length).to.equal(2);

      expect(diagnostics[0].message).to.equal("Unknown token reference \'ZZ\'");
      expect(diagnostics[0].length).to.equal(2);
      expect(diagnostics[0].position.character).to.equal(3);
      expect(diagnostics[0].position.line).to.equal(3);

      expect(diagnostics[1].message).to.equal("Unknown channel \'BLAH\'");
      expect(diagnostics[1].length).to.equal(4);
      expect(diagnostics[1].position.character).to.equal(18);
      expect(diagnostics[1].position.line).to.equal(8);

    });
  });

});
