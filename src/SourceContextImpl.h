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

  enum SymbolKind {
    SKLexerToken = 0,
    SKVirtualLexerToken = 1,
    SKFragmentLexerToken = 2,
    SKBuiltInLexerToken = 3,
    SKParserRule = 4,
    SKLexerMode = 5,
    SKBuiltInMode = 6,
    SKTokenChannel = 7,
    SKBuiltInChannel = 8,
    SkImport = 9,
    SKTokenVocab = 10,
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

  struct ErrorEntry {
    std::string message;
    int column;
    int row;
    int length;
  };

  using SymbolTable = std::map<SymbolKind, std::map<std::string, antlr4::ParserRuleContext *>>;

  class ContextErrorListener : public BaseErrorListener {
  public:
    ContextErrorListener(std::vector<ErrorEntry> &errorList) : _errors(errorList) {}

    virtual void syntaxError(IRecognizer *recognizer, Token * offendingSymbol, size_t line, int charPositionInLine,
                             const std::string &msg, std::exception_ptr e) override;
  private:
    std::vector<ErrorEntry> &_errors;
  };

  class SourceContextImpl
  {
  public:
    std::vector<std::string> imports; // Updated on each parse run.

    SourceContextImpl(std::string const& sourceId);

    SymbolInfo infoForSymbolAtPosition(size_t row, size_t column);
    std::vector<SymbolInfo> listSymbols();

    void parse(std::string const& source);
    std::vector<ErrorEntry> getErrors();
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
    SymbolTable _symbolTable;
    std::vector<SourceContextImpl *> _dependencies;
    
    std::vector<ErrorEntry> _syntaxErrors;
  };

} // namespace graps
