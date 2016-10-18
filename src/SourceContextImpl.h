/*
 * MIT License
 *
 * Copyright (c) 2016 Mike Lischke
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include "antlr4-runtime.h"
#include "ANTLRv4Lexer.h"
#include "ANTLRv4Parser.h"

namespace graps {

  enum SymbolLookupKind { // Multiple symbol kinds can be involved in a symbol lookup.
    SLKTokenRef,
    SLKRuleRef,
    SLKLexerMode,
    SLKTokenChannel,
  };
  
  enum SymbolKind {
    SKTokenVocab = 0,
    SkImport = 1,
    SKBuiltInLexerToken = 2,
    SKVirtualLexerToken = 3,
    SKFragmentLexerToken = 4,
    SKLexerToken = 5,
    SKBuiltInMode = 6,
    SKLexerMode = 7,
    SKBuiltInChannel = 8,
    SKTokenChannel = 9,
    SKParserRule = 10
  };

  enum DiagnosticType {
    DTHint = 0,
    DTInfo = 1,
    DTWarning = 2,
    DTError = 3,
  };

  struct Definition {
    std::string text;
    int startColumn;
    int startRow;
    int endColumn;
    int endRow;
  };

  struct SymbolInfo {
    SymbolKind kind;
    std::string name;
    std::string source;
    Definition definition;
  };

  struct DiagnosticEntry {
    DiagnosticType type;
    std::string message;
    int column;
    int row;
    int length;
  };

  using SymbolStore = std::map<SymbolKind, std::unordered_map<std::string, antlr4::ParserRuleContext *>>;

  class SourceContextImpl;
  
  class SymbolTable {
  public:
    enum SymbolScope { LocalOnly, DependencyOnly, Full };

    SymbolTable(SourceContextImpl *owner);

    void clear();

    void addDependency(SourceContextImpl *context);
    void addSymbol(SymbolKind kind, std::string const& name, antlr4::ParserRuleContext *ctx);
    bool symbolExists(std::string const& symbol, SymbolKind kind, SymbolScope scope);
    bool symbolExists(std::string const& symbol, SymbolLookupKind kind, SymbolScope scope);
    antlr4::ParserRuleContext* contextForSymbol(std::string const& symbol, SymbolKind kind, SymbolScope scope);

    SymbolInfo getSymbolInfo(std::string const& symbol);
    std::vector<SymbolInfo> listSymbols(bool includeDependencies);

  private:
    SourceContextImpl *_owner;
    std::vector<SourceContextImpl *> _dependencies;
  };

  class ContextErrorListener : public BaseErrorListener {
  public:
    ContextErrorListener(std::vector<DiagnosticEntry> &errorList) : _errors(errorList) {}

    virtual void syntaxError(IRecognizer *recognizer, Token * offendingSymbol, size_t line, int charPositionInLine,
                             const std::string &msg, std::exception_ptr e) override;
  private:
    std::vector<DiagnosticEntry> &_errors;
  };

  class SourceContextImpl
  {
    friend class SymbolTable;

  public:
    std::vector<std::string> imports; // Updated on each parse run.

    SourceContextImpl(std::string const& sourceId);

    SymbolInfo infoForSymbolAtPosition(size_t row, size_t column);
    std::vector<SymbolInfo> listSymbols(bool includeDependencies);

    void parse(std::string const& source);
    std::vector<DiagnosticEntry> getDiagnostics();
    void addDependency(SourceContextImpl *context);

  protected:
    SymbolInfo getSymbolInfo(std::string const& symbol);

  private:
    antlr4::ANTLRInputStream _input;
    ANTLRv4Lexer _lexer;
    antlr4::CommonTokenStream _tokens;
    ANTLRv4Parser _parser;
    ContextErrorListener _errorListener;

    std::string _sourceId;
    Ref<antlr4::tree::ParseTree> _tree;

    SymbolStore _localSymbols;
    SymbolTable _symbolTable;

    std::vector<DiagnosticEntry> _diagnostics;
  };

} // namespace graps
