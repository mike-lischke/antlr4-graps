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

namespace antlr4 {

class LexerAdaptor : public Lexer {
public:

  LexerAdaptor(CharStream *input);

  virtual Token* emit() override;

protected:
  void handleBeginArgument();
  void handleEndArgument();
  void handleEndAction();

private:
	/**
	 * Track whether we are inside of a rule and whether it is lexical parser. _currentRuleType==Token.INVALID_TYPE
	 * means that we are outside of a rule. At the first sign of a rule name reference and _currentRuleType==invalid, we
	 * can assume that we are starting a parser rule. Similarly, seeing a token reference when not already in rule means
	 * starting a token rule. The terminating ';' of a rule, flips this back to invalid type.
	 *
	 * This is not perfect logic but works. For example, "grammar T;" means that we start and stop a lexical rule for
	 * the "T;". Dangerous but works.
	 *
	 * The whole point of this state information is to distinguish between [..arg actions..] and [charsets]. Char sets
	 * can only occur in lexical rules and arg actions cannot occur.
	 */
  ssize_t _currentRuleType = Token::INVALID_TYPE;

  ssize_t getCurrentRuleType();
  void setCurrentRuleType(ssize_t ruleType);
  bool inLexerRule();
};

} // namespace antlr4
