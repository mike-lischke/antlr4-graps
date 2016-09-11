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

class SourceContextImpl
{
public:
  std::vector<std::string> imports; // Updated on each parse run.

  SourceContextImpl();

  std::string infoForSymbolAtPosition(size_t row, size_t column);
  void parse(std::string const& source);
  void addDependency(SourceContextImpl *context);

protected:
  std::string getTextForSymbol(std::string const& symbol);

private:
  antlr4::ANTLRInputStream _input;
  ANTLRv4Lexer _lexer;
  antlr4::CommonTokenStream _tokens;
  ANTLRv4Parser _parser;

  Ref<antlr4::tree::ParseTree> _tree;
  std::map<std::string, antlr4::ParserRuleContext *> _symbolTable;
  std::vector<SourceContextImpl *> _dependencies;
};

} // namespace graps
