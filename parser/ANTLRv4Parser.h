
// Generated from ANTLRv4Parser.g4 by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"


using namespace antlr4;

namespace graps {


class ANTLRv4Parser : public Parser {
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
    RuleGrammarSpec = 0, RuleGrammarType = 1, RulePrequelConstruct = 2, 
    RuleOptionsSpec = 3, RuleOption = 4, RuleOptionValue = 5, RuleDelegateGrammars = 6, 
    RuleDelegateGrammar = 7, RuleTokensSpec = 8, RuleChannelsSpec = 9, RuleIdList = 10, 
    RuleAction = 11, RuleActionScopeName = 12, RuleActionBlock = 13, RuleArgActionBlock = 14, 
    RuleModeSpec = 15, RuleRules = 16, RuleRuleSpec = 17, RuleParserRuleSpec = 18, 
    RuleExceptionGroup = 19, RuleExceptionHandler = 20, RuleFinallyClause = 21, 
    RuleRulePrequel = 22, RuleRuleReturns = 23, RuleThrowsSpec = 24, RuleLocalsSpec = 25, 
    RuleRuleAction = 26, RuleRuleModifiers = 27, RuleRuleModifier = 28, 
    RuleRuleBlock = 29, RuleRuleAltList = 30, RuleLabeledAlt = 31, RuleLexerRuleSpec = 32, 
    RuleLexerRuleBlock = 33, RuleLexerAltList = 34, RuleLexerAlt = 35, RuleLexerElements = 36, 
    RuleLexerElement = 37, RuleLabeledLexerElement = 38, RuleLexerBlock = 39, 
    RuleLexerCommands = 40, RuleLexerCommand = 41, RuleLexerCommandName = 42, 
    RuleLexerCommandExpr = 43, RuleAltList = 44, RuleAlternative = 45, RuleElement = 46, 
    RuleLabeledElement = 47, RuleEbnf = 48, RuleBlockSuffix = 49, RuleEbnfSuffix = 50, 
    RuleLexerAtom = 51, RuleAtom = 52, RuleNotSet = 53, RuleBlockSet = 54, 
    RuleSetElement = 55, RuleBlock = 56, RuleRuleref = 57, RuleCharacterRange = 58, 
    RuleTerminal = 59, RuleElementOptions = 60, RuleElementOption = 61, 
    RuleIdentifier = 62
  };

  ANTLRv4Parser(TokenStream *input);
  ~ANTLRv4Parser();

  virtual std::string getGrammarFileName() const override;
  virtual const atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual dfa::Vocabulary& getVocabulary() const override;


  class GrammarSpecContext;
  class GrammarTypeContext;
  class PrequelConstructContext;
  class OptionsSpecContext;
  class OptionContext;
  class OptionValueContext;
  class DelegateGrammarsContext;
  class DelegateGrammarContext;
  class TokensSpecContext;
  class ChannelsSpecContext;
  class IdListContext;
  class ActionContext;
  class ActionScopeNameContext;
  class ActionBlockContext;
  class ArgActionBlockContext;
  class ModeSpecContext;
  class RulesContext;
  class RuleSpecContext;
  class ParserRuleSpecContext;
  class ExceptionGroupContext;
  class ExceptionHandlerContext;
  class FinallyClauseContext;
  class RulePrequelContext;
  class RuleReturnsContext;
  class ThrowsSpecContext;
  class LocalsSpecContext;
  class RuleActionContext;
  class RuleModifiersContext;
  class RuleModifierContext;
  class RuleBlockContext;
  class RuleAltListContext;
  class LabeledAltContext;
  class LexerRuleSpecContext;
  class LexerRuleBlockContext;
  class LexerAltListContext;
  class LexerAltContext;
  class LexerElementsContext;
  class LexerElementContext;
  class LabeledLexerElementContext;
  class LexerBlockContext;
  class LexerCommandsContext;
  class LexerCommandContext;
  class LexerCommandNameContext;
  class LexerCommandExprContext;
  class AltListContext;
  class AlternativeContext;
  class ElementContext;
  class LabeledElementContext;
  class EbnfContext;
  class BlockSuffixContext;
  class EbnfSuffixContext;
  class LexerAtomContext;
  class AtomContext;
  class NotSetContext;
  class BlockSetContext;
  class SetElementContext;
  class BlockContext;
  class RulerefContext;
  class CharacterRangeContext;
  class TerminalContext;
  class ElementOptionsContext;
  class ElementOptionContext;
  class IdentifierContext; 

  class GrammarSpecContext : public ParserRuleContext {
  public:
    GrammarSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<GrammarTypeContext> grammarType();
    Ref<IdentifierContext> identifier();
    Ref<tree::TerminalNode> SEMI();
    Ref<RulesContext> rules();
    Ref<tree::TerminalNode> EOF();
    std::vector<Ref<tree::TerminalNode>> DOC_COMMENT();
    Ref<tree::TerminalNode> DOC_COMMENT(int i);
    std::vector<Ref<PrequelConstructContext>> prequelConstruct();
    Ref<PrequelConstructContext> prequelConstruct(int i);
    std::vector<Ref<ModeSpecContext>> modeSpec();
    Ref<ModeSpecContext> modeSpec(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<GrammarSpecContext> grammarSpec();

  class GrammarTypeContext : public ParserRuleContext {
  public:
    GrammarTypeContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> LEXER();
    Ref<tree::TerminalNode> GRAMMAR();
    Ref<tree::TerminalNode> PARSER();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<GrammarTypeContext> grammarType();

  class PrequelConstructContext : public ParserRuleContext {
  public:
    PrequelConstructContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<OptionsSpecContext> optionsSpec();
    Ref<DelegateGrammarsContext> delegateGrammars();
    Ref<TokensSpecContext> tokensSpec();
    Ref<ChannelsSpecContext> channelsSpec();
    Ref<ActionContext> action();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<PrequelConstructContext> prequelConstruct();

  class OptionsSpecContext : public ParserRuleContext {
  public:
    OptionsSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> OPTIONS();
    Ref<tree::TerminalNode> LBRACE();
    Ref<tree::TerminalNode> RBRACE();
    std::vector<Ref<OptionContext>> option();
    Ref<OptionContext> option(int i);
    std::vector<Ref<tree::TerminalNode>> SEMI();
    Ref<tree::TerminalNode> SEMI(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<OptionsSpecContext> optionsSpec();

  class OptionContext : public ParserRuleContext {
  public:
    OptionContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<IdentifierContext> identifier();
    Ref<tree::TerminalNode> ASSIGN();
    Ref<OptionValueContext> optionValue();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<OptionContext> option();

  class OptionValueContext : public ParserRuleContext {
  public:
    OptionValueContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    std::vector<Ref<IdentifierContext>> identifier();
    Ref<IdentifierContext> identifier(int i);
    std::vector<Ref<tree::TerminalNode>> DOT();
    Ref<tree::TerminalNode> DOT(int i);
    Ref<tree::TerminalNode> STRING_LITERAL();
    Ref<ActionBlockContext> actionBlock();
    Ref<tree::TerminalNode> INT();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<OptionValueContext> optionValue();

  class DelegateGrammarsContext : public ParserRuleContext {
  public:
    DelegateGrammarsContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> IMPORT();
    std::vector<Ref<DelegateGrammarContext>> delegateGrammar();
    Ref<DelegateGrammarContext> delegateGrammar(int i);
    Ref<tree::TerminalNode> SEMI();
    std::vector<Ref<tree::TerminalNode>> COMMA();
    Ref<tree::TerminalNode> COMMA(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<DelegateGrammarsContext> delegateGrammars();

  class DelegateGrammarContext : public ParserRuleContext {
  public:
    DelegateGrammarContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    std::vector<Ref<IdentifierContext>> identifier();
    Ref<IdentifierContext> identifier(int i);
    Ref<tree::TerminalNode> ASSIGN();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<DelegateGrammarContext> delegateGrammar();

  class TokensSpecContext : public ParserRuleContext {
  public:
    TokensSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> TOKENS();
    Ref<tree::TerminalNode> LBRACE();
    Ref<tree::TerminalNode> RBRACE();
    Ref<IdListContext> idList();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<TokensSpecContext> tokensSpec();

  class ChannelsSpecContext : public ParserRuleContext {
  public:
    ChannelsSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> CHANNELS();
    Ref<tree::TerminalNode> LBRACE();
    Ref<tree::TerminalNode> RBRACE();
    Ref<IdListContext> idList();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<ChannelsSpecContext> channelsSpec();

  class IdListContext : public ParserRuleContext {
  public:
    IdListContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    std::vector<Ref<IdentifierContext>> identifier();
    Ref<IdentifierContext> identifier(int i);
    std::vector<Ref<tree::TerminalNode>> COMMA();
    Ref<tree::TerminalNode> COMMA(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<IdListContext> idList();

  class ActionContext : public ParserRuleContext {
  public:
    ActionContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> AT();
    Ref<IdentifierContext> identifier();
    Ref<ActionBlockContext> actionBlock();
    Ref<ActionScopeNameContext> actionScopeName();
    Ref<tree::TerminalNode> COLONCOLON();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<ActionContext> action();

  class ActionScopeNameContext : public ParserRuleContext {
  public:
    ActionScopeNameContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<IdentifierContext> identifier();
    Ref<tree::TerminalNode> LEXER();
    Ref<tree::TerminalNode> PARSER();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<ActionScopeNameContext> actionScopeName();

  class ActionBlockContext : public ParserRuleContext {
  public:
    ActionBlockContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> BEGIN_ACTION();
    Ref<tree::TerminalNode> END_ACTION();
    std::vector<Ref<tree::TerminalNode>> ACTION_CONTENT();
    Ref<tree::TerminalNode> ACTION_CONTENT(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<ActionBlockContext> actionBlock();

  class ArgActionBlockContext : public ParserRuleContext {
  public:
    ArgActionBlockContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> BEGIN_ARGUMENT();
    Ref<tree::TerminalNode> END_ARGUMENT();
    std::vector<Ref<tree::TerminalNode>> ARGUMENT_CONTENT();
    Ref<tree::TerminalNode> ARGUMENT_CONTENT(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<ArgActionBlockContext> argActionBlock();

  class ModeSpecContext : public ParserRuleContext {
  public:
    ModeSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> MODE();
    Ref<IdentifierContext> identifier();
    Ref<tree::TerminalNode> SEMI();
    std::vector<Ref<LexerRuleSpecContext>> lexerRuleSpec();
    Ref<LexerRuleSpecContext> lexerRuleSpec(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<ModeSpecContext> modeSpec();

  class RulesContext : public ParserRuleContext {
  public:
    RulesContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    std::vector<Ref<RuleSpecContext>> ruleSpec();
    Ref<RuleSpecContext> ruleSpec(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<RulesContext> rules();

  class RuleSpecContext : public ParserRuleContext {
  public:
    RuleSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<ParserRuleSpecContext> parserRuleSpec();
    Ref<LexerRuleSpecContext> lexerRuleSpec();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<RuleSpecContext> ruleSpec();

  class ParserRuleSpecContext : public ParserRuleContext {
  public:
    ParserRuleSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> RULE_REF();
    Ref<tree::TerminalNode> COLON();
    Ref<RuleBlockContext> ruleBlock();
    Ref<tree::TerminalNode> SEMI();
    Ref<ExceptionGroupContext> exceptionGroup();
    std::vector<Ref<tree::TerminalNode>> DOC_COMMENT();
    Ref<tree::TerminalNode> DOC_COMMENT(int i);
    Ref<RuleModifiersContext> ruleModifiers();
    Ref<ArgActionBlockContext> argActionBlock();
    Ref<RuleReturnsContext> ruleReturns();
    Ref<ThrowsSpecContext> throwsSpec();
    Ref<LocalsSpecContext> localsSpec();
    std::vector<Ref<RulePrequelContext>> rulePrequel();
    Ref<RulePrequelContext> rulePrequel(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<ParserRuleSpecContext> parserRuleSpec();

  class ExceptionGroupContext : public ParserRuleContext {
  public:
    ExceptionGroupContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    std::vector<Ref<ExceptionHandlerContext>> exceptionHandler();
    Ref<ExceptionHandlerContext> exceptionHandler(int i);
    Ref<FinallyClauseContext> finallyClause();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<ExceptionGroupContext> exceptionGroup();

  class ExceptionHandlerContext : public ParserRuleContext {
  public:
    ExceptionHandlerContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> CATCH();
    Ref<ArgActionBlockContext> argActionBlock();
    Ref<ActionBlockContext> actionBlock();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<ExceptionHandlerContext> exceptionHandler();

  class FinallyClauseContext : public ParserRuleContext {
  public:
    FinallyClauseContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> FINALLY();
    Ref<ActionBlockContext> actionBlock();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<FinallyClauseContext> finallyClause();

  class RulePrequelContext : public ParserRuleContext {
  public:
    RulePrequelContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<OptionsSpecContext> optionsSpec();
    Ref<RuleActionContext> ruleAction();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<RulePrequelContext> rulePrequel();

  class RuleReturnsContext : public ParserRuleContext {
  public:
    RuleReturnsContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> RETURNS();
    Ref<ArgActionBlockContext> argActionBlock();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<RuleReturnsContext> ruleReturns();

  class ThrowsSpecContext : public ParserRuleContext {
  public:
    ThrowsSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> THROWS();
    std::vector<Ref<IdentifierContext>> identifier();
    Ref<IdentifierContext> identifier(int i);
    std::vector<Ref<tree::TerminalNode>> COMMA();
    Ref<tree::TerminalNode> COMMA(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<ThrowsSpecContext> throwsSpec();

  class LocalsSpecContext : public ParserRuleContext {
  public:
    LocalsSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> LOCALS();
    Ref<ArgActionBlockContext> argActionBlock();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<LocalsSpecContext> localsSpec();

  class RuleActionContext : public ParserRuleContext {
  public:
    RuleActionContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> AT();
    Ref<IdentifierContext> identifier();
    Ref<ActionBlockContext> actionBlock();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<RuleActionContext> ruleAction();

  class RuleModifiersContext : public ParserRuleContext {
  public:
    RuleModifiersContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    std::vector<Ref<RuleModifierContext>> ruleModifier();
    Ref<RuleModifierContext> ruleModifier(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<RuleModifiersContext> ruleModifiers();

  class RuleModifierContext : public ParserRuleContext {
  public:
    RuleModifierContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> PUBLIC();
    Ref<tree::TerminalNode> PRIVATE();
    Ref<tree::TerminalNode> PROTECTED();
    Ref<tree::TerminalNode> FRAGMENT();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<RuleModifierContext> ruleModifier();

  class RuleBlockContext : public ParserRuleContext {
  public:
    RuleBlockContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<RuleAltListContext> ruleAltList();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<RuleBlockContext> ruleBlock();

  class RuleAltListContext : public ParserRuleContext {
  public:
    RuleAltListContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    std::vector<Ref<LabeledAltContext>> labeledAlt();
    Ref<LabeledAltContext> labeledAlt(int i);
    std::vector<Ref<tree::TerminalNode>> OR();
    Ref<tree::TerminalNode> OR(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<RuleAltListContext> ruleAltList();

  class LabeledAltContext : public ParserRuleContext {
  public:
    LabeledAltContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<AlternativeContext> alternative();
    Ref<tree::TerminalNode> POUND();
    Ref<IdentifierContext> identifier();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<LabeledAltContext> labeledAlt();

  class LexerRuleSpecContext : public ParserRuleContext {
  public:
    LexerRuleSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> TOKEN_REF();
    Ref<tree::TerminalNode> COLON();
    Ref<LexerRuleBlockContext> lexerRuleBlock();
    Ref<tree::TerminalNode> SEMI();
    std::vector<Ref<tree::TerminalNode>> DOC_COMMENT();
    Ref<tree::TerminalNode> DOC_COMMENT(int i);
    Ref<tree::TerminalNode> FRAGMENT();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<LexerRuleSpecContext> lexerRuleSpec();

  class LexerRuleBlockContext : public ParserRuleContext {
  public:
    LexerRuleBlockContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<LexerAltListContext> lexerAltList();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<LexerRuleBlockContext> lexerRuleBlock();

  class LexerAltListContext : public ParserRuleContext {
  public:
    LexerAltListContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    std::vector<Ref<LexerAltContext>> lexerAlt();
    Ref<LexerAltContext> lexerAlt(int i);
    std::vector<Ref<tree::TerminalNode>> OR();
    Ref<tree::TerminalNode> OR(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<LexerAltListContext> lexerAltList();

  class LexerAltContext : public ParserRuleContext {
  public:
    LexerAltContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<LexerElementsContext> lexerElements();
    Ref<LexerCommandsContext> lexerCommands();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<LexerAltContext> lexerAlt();

  class LexerElementsContext : public ParserRuleContext {
  public:
    LexerElementsContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    std::vector<Ref<LexerElementContext>> lexerElement();
    Ref<LexerElementContext> lexerElement(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<LexerElementsContext> lexerElements();

  class LexerElementContext : public ParserRuleContext {
  public:
    LexerElementContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<LabeledLexerElementContext> labeledLexerElement();
    Ref<EbnfSuffixContext> ebnfSuffix();
    Ref<LexerAtomContext> lexerAtom();
    Ref<LexerBlockContext> lexerBlock();
    Ref<ActionBlockContext> actionBlock();
    Ref<tree::TerminalNode> QUESTION();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<LexerElementContext> lexerElement();

  class LabeledLexerElementContext : public ParserRuleContext {
  public:
    LabeledLexerElementContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<IdentifierContext> identifier();
    Ref<tree::TerminalNode> ASSIGN();
    Ref<tree::TerminalNode> PLUS_ASSIGN();
    Ref<LexerAtomContext> lexerAtom();
    Ref<BlockContext> block();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<LabeledLexerElementContext> labeledLexerElement();

  class LexerBlockContext : public ParserRuleContext {
  public:
    LexerBlockContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> LPAREN();
    Ref<LexerAltListContext> lexerAltList();
    Ref<tree::TerminalNode> RPAREN();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<LexerBlockContext> lexerBlock();

  class LexerCommandsContext : public ParserRuleContext {
  public:
    LexerCommandsContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> RARROW();
    std::vector<Ref<LexerCommandContext>> lexerCommand();
    Ref<LexerCommandContext> lexerCommand(int i);
    std::vector<Ref<tree::TerminalNode>> COMMA();
    Ref<tree::TerminalNode> COMMA(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<LexerCommandsContext> lexerCommands();

  class LexerCommandContext : public ParserRuleContext {
  public:
    LexerCommandContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<LexerCommandNameContext> lexerCommandName();
    Ref<tree::TerminalNode> LPAREN();
    Ref<LexerCommandExprContext> lexerCommandExpr();
    Ref<tree::TerminalNode> RPAREN();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<LexerCommandContext> lexerCommand();

  class LexerCommandNameContext : public ParserRuleContext {
  public:
    LexerCommandNameContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<IdentifierContext> identifier();
    Ref<tree::TerminalNode> MODE();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<LexerCommandNameContext> lexerCommandName();

  class LexerCommandExprContext : public ParserRuleContext {
  public:
    LexerCommandExprContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<IdentifierContext> identifier();
    Ref<tree::TerminalNode> INT();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<LexerCommandExprContext> lexerCommandExpr();

  class AltListContext : public ParserRuleContext {
  public:
    AltListContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    std::vector<Ref<AlternativeContext>> alternative();
    Ref<AlternativeContext> alternative(int i);
    std::vector<Ref<tree::TerminalNode>> OR();
    Ref<tree::TerminalNode> OR(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<AltListContext> altList();

  class AlternativeContext : public ParserRuleContext {
  public:
    AlternativeContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<ElementOptionsContext> elementOptions();
    std::vector<Ref<ElementContext>> element();
    Ref<ElementContext> element(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<AlternativeContext> alternative();

  class ElementContext : public ParserRuleContext {
  public:
    ElementContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<LabeledElementContext> labeledElement();
    Ref<EbnfSuffixContext> ebnfSuffix();
    Ref<AtomContext> atom();
    Ref<EbnfContext> ebnf();
    Ref<ActionBlockContext> actionBlock();
    Ref<tree::TerminalNode> QUESTION();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<ElementContext> element();

  class LabeledElementContext : public ParserRuleContext {
  public:
    LabeledElementContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<IdentifierContext> identifier();
    Ref<tree::TerminalNode> ASSIGN();
    Ref<tree::TerminalNode> PLUS_ASSIGN();
    Ref<AtomContext> atom();
    Ref<BlockContext> block();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<LabeledElementContext> labeledElement();

  class EbnfContext : public ParserRuleContext {
  public:
    EbnfContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<BlockContext> block();
    Ref<BlockSuffixContext> blockSuffix();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<EbnfContext> ebnf();

  class BlockSuffixContext : public ParserRuleContext {
  public:
    BlockSuffixContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<EbnfSuffixContext> ebnfSuffix();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<BlockSuffixContext> blockSuffix();

  class EbnfSuffixContext : public ParserRuleContext {
  public:
    EbnfSuffixContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    std::vector<Ref<tree::TerminalNode>> QUESTION();
    Ref<tree::TerminalNode> QUESTION(int i);
    Ref<tree::TerminalNode> STAR();
    Ref<tree::TerminalNode> PLUS();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<EbnfSuffixContext> ebnfSuffix();

  class LexerAtomContext : public ParserRuleContext {
  public:
    LexerAtomContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<CharacterRangeContext> characterRange();
    Ref<TerminalContext> terminal();
    Ref<NotSetContext> notSet();
    Ref<tree::TerminalNode> LEXER_CHAR_SET();
    Ref<tree::TerminalNode> DOT();
    Ref<ElementOptionsContext> elementOptions();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<LexerAtomContext> lexerAtom();

  class AtomContext : public ParserRuleContext {
  public:
    AtomContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<CharacterRangeContext> characterRange();
    Ref<TerminalContext> terminal();
    Ref<RulerefContext> ruleref();
    Ref<NotSetContext> notSet();
    Ref<tree::TerminalNode> DOT();
    Ref<ElementOptionsContext> elementOptions();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<AtomContext> atom();

  class NotSetContext : public ParserRuleContext {
  public:
    NotSetContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> NOT();
    Ref<SetElementContext> setElement();
    Ref<BlockSetContext> blockSet();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<NotSetContext> notSet();

  class BlockSetContext : public ParserRuleContext {
  public:
    BlockSetContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> LPAREN();
    std::vector<Ref<SetElementContext>> setElement();
    Ref<SetElementContext> setElement(int i);
    Ref<tree::TerminalNode> RPAREN();
    std::vector<Ref<tree::TerminalNode>> OR();
    Ref<tree::TerminalNode> OR(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<BlockSetContext> blockSet();

  class SetElementContext : public ParserRuleContext {
  public:
    SetElementContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> TOKEN_REF();
    Ref<ElementOptionsContext> elementOptions();
    Ref<tree::TerminalNode> STRING_LITERAL();
    Ref<CharacterRangeContext> characterRange();
    Ref<tree::TerminalNode> LEXER_CHAR_SET();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<SetElementContext> setElement();

  class BlockContext : public ParserRuleContext {
  public:
    BlockContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> LPAREN();
    Ref<AltListContext> altList();
    Ref<tree::TerminalNode> RPAREN();
    Ref<tree::TerminalNode> COLON();
    Ref<OptionsSpecContext> optionsSpec();
    std::vector<Ref<RuleActionContext>> ruleAction();
    Ref<RuleActionContext> ruleAction(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<BlockContext> block();

  class RulerefContext : public ParserRuleContext {
  public:
    RulerefContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> RULE_REF();
    Ref<ArgActionBlockContext> argActionBlock();
    Ref<ElementOptionsContext> elementOptions();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<RulerefContext> ruleref();

  class CharacterRangeContext : public ParserRuleContext {
  public:
    CharacterRangeContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    std::vector<Ref<tree::TerminalNode>> STRING_LITERAL();
    Ref<tree::TerminalNode> STRING_LITERAL(int i);
    Ref<tree::TerminalNode> RANGE();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<CharacterRangeContext> characterRange();

  class TerminalContext : public ParserRuleContext {
  public:
    TerminalContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> TOKEN_REF();
    Ref<ElementOptionsContext> elementOptions();
    Ref<tree::TerminalNode> STRING_LITERAL();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<TerminalContext> terminal();

  class ElementOptionsContext : public ParserRuleContext {
  public:
    ElementOptionsContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> LT();
    std::vector<Ref<ElementOptionContext>> elementOption();
    Ref<ElementOptionContext> elementOption(int i);
    Ref<tree::TerminalNode> GT();
    std::vector<Ref<tree::TerminalNode>> COMMA();
    Ref<tree::TerminalNode> COMMA(int i);

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<ElementOptionsContext> elementOptions();

  class ElementOptionContext : public ParserRuleContext {
  public:
    ElementOptionContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    std::vector<Ref<IdentifierContext>> identifier();
    Ref<IdentifierContext> identifier(int i);
    Ref<tree::TerminalNode> ASSIGN();
    Ref<tree::TerminalNode> STRING_LITERAL();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<ElementOptionContext> elementOption();

  class IdentifierContext : public ParserRuleContext {
  public:
    IdentifierContext(std::weak_ptr<ParserRuleContext> parent, int invokingState);
    virtual ssize_t getRuleIndex() const override;
    Ref<tree::TerminalNode> RULE_REF();
    Ref<tree::TerminalNode> TOKEN_REF();

    virtual void enterRule(tree::ParseTreeListener *listener) override;
    virtual void exitRule(tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(tree::ParseTreeVisitor *visitor) override;
   
  };

  Ref<IdentifierContext> identifier();


private:
  static std::vector<dfa::DFA> _decisionToDFA;
  static atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static dfa::Vocabulary _vocabulary;
  static atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace graps
