/*
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *  Created by Mike Lischke on 03.09.16.
 *  Copyright © 2016 Mike Lischke. All rights reserved.
 *
 */

#include "SourceContextImpl.h"

#include "ANTLRv4Lexer.h"
#include "ANTLRv4Parser.h"

using namespace graps;

using namespace antlr4;
using namespace antlr4::atn;

//----------------------------------------------------------------------------------------------------------------------

SourceContextImpl::SourceContextImpl(std::string const& source)
{
  parse(source);
}

//----------------------------------------------------------------------------------------------------------------------

void SourceContextImpl::parse(std::string const& source)
{
  ANTLRInputStream input(source);
  ANTLRv4Lexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  ANTLRv4Parser parser(&tokens);

  parser.setBuildParseTree(true);

  // First parse with the bail error strategy to get quick feedback for correct queries.
  parser.setErrorHandler(std::make_shared<BailErrorStrategy>());
  parser.getInterpreter<ParserATNSimulator>()->setPredictionMode(PredictionMode::SLL);
  parser.removeErrorListeners();

  try {
    _tree = parser.grammarSpec();
  } catch (ParseCancellationException &pce) {
    // If parsing was cancelled we either really have a syntax error or we need to do a second step,
    // now with the default strategy and LL parsing.
    tokens.reset();
    parser.reset();
    parser.setErrorHandler(std::make_shared<DefaultErrorStrategy>());
    parser.getInterpreter<ParserATNSimulator>()->setPredictionMode(PredictionMode::LL);
    parser.addErrorListener(&ConsoleErrorListener::INSTANCE);
    _tree = parser.grammarSpec();
  }
}

//----------------------------------------------------------------------------------------------------------------------

