
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
