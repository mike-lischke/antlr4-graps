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

#include <cctype>

#include "LexerAdaptor.h"
#include "ANTLRv4Lexer.h"

using namespace antlr4;
using namespace antlr4::misc;

using namespace graps;

LexerAdaptor::LexerAdaptor(CharStream *input) : Lexer(input)
{
}

Token* LexerAdaptor::emit()
{
  if (type == ANTLRv4Lexer::ID) {
    std::string firstChar = _input->getText(Interval(tokenStartCharIndex, tokenStartCharIndex));
    if (std::isupper(firstChar[0])) {
      type = ANTLRv4Lexer::TOKEN_REF;
    } else {
      type = ANTLRv4Lexer::RULE_REF;
    }

    if (_currentRuleType == Token::INVALID_TYPE) { // if outside of rule def
      _currentRuleType = type; // set to inside lexer or parser rule
    }
  }
  else if (type == ANTLRv4Lexer::SEMI) { // exit rule def
    _currentRuleType = Token::INVALID_TYPE;
  }

  return Lexer::emit();
}

ssize_t LexerAdaptor::getCurrentRuleType()
{
  return _currentRuleType;
}

void LexerAdaptor::setCurrentRuleType(ssize_t ruleType)
{
  _currentRuleType = ruleType;
}

void LexerAdaptor::handleBeginArgument()
{
  if (inLexerRule()) {
    pushMode(ANTLRv4Lexer::LexerCharSet);
    more();
  } else {
    pushMode(ANTLRv4Lexer::Argument);
  }
}

void LexerAdaptor::handleEndArgument()
{
  popMode();
  if (modeStack.size() > 0)
    setType(ANTLRv4Lexer::ARGUMENT_CONTENT);
}

void LexerAdaptor::handleEndAction()
{
  popMode();
  if (modeStack.size() > 0)
    setType(ANTLRv4Lexer::ACTION_CONTENT);
}

bool LexerAdaptor::inLexerRule()
{
  return _currentRuleType == ANTLRv4Lexer::TOKEN_REF;
}
