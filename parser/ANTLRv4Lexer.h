
// Generated from ANTLRv4Lexer.g4 by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"
#include "LexerAdaptor.h"

using namespace antlr4;

namespace parsers {


class ANTLRv4Lexer : public LexerAdaptor {
public:
  enum {
    TOKEN_REF = 1, RULE_REF = 2, LEXER_CHAR_SET = 3, DOC_COMMENT = 4, BLOCK_COMMENT = 5, 
    LINE_COMMENT = 6, INT = 7, STRING_LITERAL = 8, UNTERMINATED_STRING_LITERAL = 9, 
    BEGIN_ARGUMENT = 10, BEGIN_ACTION = 11, OPTIONS = 12, TOKENS = 13, CHANNELS = 14, 
    IMPORT = 15, FRAGMENT = 16, LEXER = 17, PARSER = 18, GRAMMAR = 19, PROTECTED = 20, 
    PUBLIC = 21, PRIVATE = 22, RETURNS = 23, LOCALS = 24, THROWS = 25, CATCH = 26, 
    FINALLY = 27, MODE = 28, COLON = 29, COLONCOLON = 30, COMMA = 31, SEMI = 32, 
    LPAREN = 33, RPAREN = 34, LBRACE = 35, RBRACE = 36, RARROW = 37, LT = 38, 
    GT = 39, ASSIGN = 40, QUESTION = 41, STAR = 42, PLUS_ASSIGN = 43, PLUS = 44, 
    OR = 45, DOLLAR = 46, RANGE = 47, DOT = 48, AT = 49, POUND = 50, NOT = 51, 
    ID = 52, WS = 53, ERRCHAR = 54, END_ARGUMENT = 55, UNTERMINATED_ARGUMENT = 56, 
    ARGUMENT_CONTENT = 57, END_ACTION = 58, UNTERMINATED_ACTION = 59, ACTION_CONTENT = 60, 
    UNTERMINATED_CHAR_SET = 61
  };

  enum {
    OFF_CHANNEL = 2
  };

  enum {
    Argument = 1,
    Action = 2,
    Options = 3,
    Tokens = 4,
    Channels = 5,
    LexerCharSet = 6,
  };

  ANTLRv4Lexer(CharStream *input);
  ~ANTLRv4Lexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const atn::ATN& getATN() const override;

  virtual void action(Ref<RuleContext> const& context, int ruleIndex, int actionIndex) override;

private:
  static std::vector<dfa::DFA> _decisionToDFA;
  static atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static dfa::Vocabulary _vocabulary;
  static atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.
  void BEGIN_ARGUMENTAction(Ref<RuleContext> const& context, int actionIndex);
  void END_ARGUMENTAction(Ref<RuleContext> const& context, int actionIndex);
  void END_ACTIONAction(Ref<RuleContext> const& context, int actionIndex);

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace parsers
