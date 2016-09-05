
// Generated from ANTLRv4Parser.g4 by ANTLR 4.5.3


#include "ANTLRv4ParserListener.h"
#include "ANTLRv4ParserVisitor.h"

#include "ANTLRv4Parser.h"


using namespace antlrcpp;
using namespace graps;
using namespace antlr4;

ANTLRv4Parser::ANTLRv4Parser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

ANTLRv4Parser::~ANTLRv4Parser() {
  delete _interpreter;
}

std::string ANTLRv4Parser::getGrammarFileName() const {
  return "ANTLRv4Parser.g4";
}

const std::vector<std::string>& ANTLRv4Parser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& ANTLRv4Parser::getVocabulary() const {
  return _vocabulary;
}


//----------------- GrammarSpecContext ------------------------------------------------------------------

ANTLRv4Parser::GrammarSpecContext::GrammarSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::GrammarTypeContext> ANTLRv4Parser::GrammarSpecContext::grammarType() {
  return getRuleContext<ANTLRv4Parser::GrammarTypeContext>(0);
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::GrammarSpecContext::identifier() {
  return getRuleContext<ANTLRv4Parser::IdentifierContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::GrammarSpecContext::SEMI() {
  return getToken(ANTLRv4Parser::SEMI, 0);
}

Ref<ANTLRv4Parser::RulesContext> ANTLRv4Parser::GrammarSpecContext::rules() {
  return getRuleContext<ANTLRv4Parser::RulesContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::GrammarSpecContext::EOF() {
  return getToken(ANTLRv4Parser::EOF, 0);
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::GrammarSpecContext::DOC_COMMENT() {
  return getTokens(ANTLRv4Parser::DOC_COMMENT);
}

Ref<tree::TerminalNode> ANTLRv4Parser::GrammarSpecContext::DOC_COMMENT(int i) {
  return getToken(ANTLRv4Parser::DOC_COMMENT, (size_t)i);
}

std::vector<Ref<ANTLRv4Parser::PrequelConstructContext>> ANTLRv4Parser::GrammarSpecContext::prequelConstruct() {
  return getRuleContexts<ANTLRv4Parser::PrequelConstructContext>();
}

Ref<ANTLRv4Parser::PrequelConstructContext> ANTLRv4Parser::GrammarSpecContext::prequelConstruct(int i) {
  return getRuleContext<ANTLRv4Parser::PrequelConstructContext>((size_t)i);
}

std::vector<Ref<ANTLRv4Parser::ModeSpecContext>> ANTLRv4Parser::GrammarSpecContext::modeSpec() {
  return getRuleContexts<ANTLRv4Parser::ModeSpecContext>();
}

Ref<ANTLRv4Parser::ModeSpecContext> ANTLRv4Parser::GrammarSpecContext::modeSpec(int i) {
  return getRuleContext<ANTLRv4Parser::ModeSpecContext>((size_t)i);
}


ssize_t ANTLRv4Parser::GrammarSpecContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleGrammarSpec;
}

void ANTLRv4Parser::GrammarSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGrammarSpec(this);
}

void ANTLRv4Parser::GrammarSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGrammarSpec(this);
}


antlrcpp::Any ANTLRv4Parser::GrammarSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitGrammarSpec(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::GrammarSpecContext> ANTLRv4Parser::grammarSpec() {
  Ref<GrammarSpecContext> _localctx = std::make_shared<GrammarSpecContext>(_ctx, getState());
  enterRule(_localctx, 0, ANTLRv4Parser::RuleGrammarSpec);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(129);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::DOC_COMMENT) {
      setState(126);
      match(ANTLRv4Parser::DOC_COMMENT);
      setState(131);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(132);
    grammarType();
    setState(133);
    identifier();
    setState(134);
    match(ANTLRv4Parser::SEMI);
    setState(138);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~(ssize_t)0x3f) == 0) &&
      ((1ULL << _la) & ((1ULL << ANTLRv4Parser::OPTIONS)
      | (1ULL << ANTLRv4Parser::TOKENS)
      | (1ULL << ANTLRv4Parser::CHANNELS)
      | (1ULL << ANTLRv4Parser::IMPORT)
      | (1ULL << ANTLRv4Parser::AT))) != 0)) {
      setState(135);
      prequelConstruct();
      setState(140);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(141);
    rules();
    setState(145);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::MODE) {
      setState(142);
      modeSpec();
      setState(147);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(148);
    match(ANTLRv4Parser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GrammarTypeContext ------------------------------------------------------------------

ANTLRv4Parser::GrammarTypeContext::GrammarTypeContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::GrammarTypeContext::LEXER() {
  return getToken(ANTLRv4Parser::LEXER, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::GrammarTypeContext::GRAMMAR() {
  return getToken(ANTLRv4Parser::GRAMMAR, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::GrammarTypeContext::PARSER() {
  return getToken(ANTLRv4Parser::PARSER, 0);
}


ssize_t ANTLRv4Parser::GrammarTypeContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleGrammarType;
}

void ANTLRv4Parser::GrammarTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGrammarType(this);
}

void ANTLRv4Parser::GrammarTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGrammarType(this);
}


antlrcpp::Any ANTLRv4Parser::GrammarTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitGrammarType(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::GrammarTypeContext> ANTLRv4Parser::grammarType() {
  Ref<GrammarTypeContext> _localctx = std::make_shared<GrammarTypeContext>(_ctx, getState());
  enterRule(_localctx, 2, ANTLRv4Parser::RuleGrammarType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ANTLRv4Parser::LEXER: {
        setState(150);
        match(ANTLRv4Parser::LEXER);
        setState(151);
        match(ANTLRv4Parser::GRAMMAR);
        break;
      }

      case ANTLRv4Parser::PARSER: {
        setState(152);
        match(ANTLRv4Parser::PARSER);
        setState(153);
        match(ANTLRv4Parser::GRAMMAR);
        break;
      }

      case ANTLRv4Parser::GRAMMAR: {
        setState(154);
        match(ANTLRv4Parser::GRAMMAR);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrequelConstructContext ------------------------------------------------------------------

ANTLRv4Parser::PrequelConstructContext::PrequelConstructContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::OptionsSpecContext> ANTLRv4Parser::PrequelConstructContext::optionsSpec() {
  return getRuleContext<ANTLRv4Parser::OptionsSpecContext>(0);
}

Ref<ANTLRv4Parser::DelegateGrammarsContext> ANTLRv4Parser::PrequelConstructContext::delegateGrammars() {
  return getRuleContext<ANTLRv4Parser::DelegateGrammarsContext>(0);
}

Ref<ANTLRv4Parser::TokensSpecContext> ANTLRv4Parser::PrequelConstructContext::tokensSpec() {
  return getRuleContext<ANTLRv4Parser::TokensSpecContext>(0);
}

Ref<ANTLRv4Parser::ChannelsSpecContext> ANTLRv4Parser::PrequelConstructContext::channelsSpec() {
  return getRuleContext<ANTLRv4Parser::ChannelsSpecContext>(0);
}

Ref<ANTLRv4Parser::ActionContext> ANTLRv4Parser::PrequelConstructContext::action() {
  return getRuleContext<ANTLRv4Parser::ActionContext>(0);
}


ssize_t ANTLRv4Parser::PrequelConstructContext::getRuleIndex() const {
  return ANTLRv4Parser::RulePrequelConstruct;
}

void ANTLRv4Parser::PrequelConstructContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrequelConstruct(this);
}

void ANTLRv4Parser::PrequelConstructContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrequelConstruct(this);
}


antlrcpp::Any ANTLRv4Parser::PrequelConstructContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitPrequelConstruct(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::PrequelConstructContext> ANTLRv4Parser::prequelConstruct() {
  Ref<PrequelConstructContext> _localctx = std::make_shared<PrequelConstructContext>(_ctx, getState());
  enterRule(_localctx, 4, ANTLRv4Parser::RulePrequelConstruct);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(162);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ANTLRv4Parser::OPTIONS: {
        enterOuterAlt(_localctx, 1);
        setState(157);
        optionsSpec();
        break;
      }

      case ANTLRv4Parser::IMPORT: {
        enterOuterAlt(_localctx, 2);
        setState(158);
        delegateGrammars();
        break;
      }

      case ANTLRv4Parser::TOKENS: {
        enterOuterAlt(_localctx, 3);
        setState(159);
        tokensSpec();
        break;
      }

      case ANTLRv4Parser::CHANNELS: {
        enterOuterAlt(_localctx, 4);
        setState(160);
        channelsSpec();
        break;
      }

      case ANTLRv4Parser::AT: {
        enterOuterAlt(_localctx, 5);
        setState(161);
        action();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OptionsSpecContext ------------------------------------------------------------------

ANTLRv4Parser::OptionsSpecContext::OptionsSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::OptionsSpecContext::OPTIONS() {
  return getToken(ANTLRv4Parser::OPTIONS, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::OptionsSpecContext::LBRACE() {
  return getToken(ANTLRv4Parser::LBRACE, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::OptionsSpecContext::RBRACE() {
  return getToken(ANTLRv4Parser::RBRACE, 0);
}

std::vector<Ref<ANTLRv4Parser::OptionContext>> ANTLRv4Parser::OptionsSpecContext::option() {
  return getRuleContexts<ANTLRv4Parser::OptionContext>();
}

Ref<ANTLRv4Parser::OptionContext> ANTLRv4Parser::OptionsSpecContext::option(int i) {
  return getRuleContext<ANTLRv4Parser::OptionContext>((size_t)i);
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::OptionsSpecContext::SEMI() {
  return getTokens(ANTLRv4Parser::SEMI);
}

Ref<tree::TerminalNode> ANTLRv4Parser::OptionsSpecContext::SEMI(int i) {
  return getToken(ANTLRv4Parser::SEMI, (size_t)i);
}


ssize_t ANTLRv4Parser::OptionsSpecContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleOptionsSpec;
}

void ANTLRv4Parser::OptionsSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOptionsSpec(this);
}

void ANTLRv4Parser::OptionsSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOptionsSpec(this);
}


antlrcpp::Any ANTLRv4Parser::OptionsSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitOptionsSpec(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::OptionsSpecContext> ANTLRv4Parser::optionsSpec() {
  Ref<OptionsSpecContext> _localctx = std::make_shared<OptionsSpecContext>(_ctx, getState());
  enterRule(_localctx, 6, ANTLRv4Parser::RuleOptionsSpec);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(164);
    match(ANTLRv4Parser::OPTIONS);
    setState(165);
    match(ANTLRv4Parser::LBRACE);
    setState(171);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::TOKEN_REF

    || _la == ANTLRv4Parser::RULE_REF) {
      setState(166);
      option();
      setState(167);
      match(ANTLRv4Parser::SEMI);
      setState(173);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(174);
    match(ANTLRv4Parser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OptionContext ------------------------------------------------------------------

ANTLRv4Parser::OptionContext::OptionContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::OptionContext::identifier() {
  return getRuleContext<ANTLRv4Parser::IdentifierContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::OptionContext::ASSIGN() {
  return getToken(ANTLRv4Parser::ASSIGN, 0);
}

Ref<ANTLRv4Parser::OptionValueContext> ANTLRv4Parser::OptionContext::optionValue() {
  return getRuleContext<ANTLRv4Parser::OptionValueContext>(0);
}


ssize_t ANTLRv4Parser::OptionContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleOption;
}

void ANTLRv4Parser::OptionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOption(this);
}

void ANTLRv4Parser::OptionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOption(this);
}


antlrcpp::Any ANTLRv4Parser::OptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitOption(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::OptionContext> ANTLRv4Parser::option() {
  Ref<OptionContext> _localctx = std::make_shared<OptionContext>(_ctx, getState());
  enterRule(_localctx, 8, ANTLRv4Parser::RuleOption);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    identifier();
    setState(177);
    match(ANTLRv4Parser::ASSIGN);
    setState(178);
    optionValue();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OptionValueContext ------------------------------------------------------------------

ANTLRv4Parser::OptionValueContext::OptionValueContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Ref<ANTLRv4Parser::IdentifierContext>> ANTLRv4Parser::OptionValueContext::identifier() {
  return getRuleContexts<ANTLRv4Parser::IdentifierContext>();
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::OptionValueContext::identifier(int i) {
  return getRuleContext<ANTLRv4Parser::IdentifierContext>((size_t)i);
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::OptionValueContext::DOT() {
  return getTokens(ANTLRv4Parser::DOT);
}

Ref<tree::TerminalNode> ANTLRv4Parser::OptionValueContext::DOT(int i) {
  return getToken(ANTLRv4Parser::DOT, (size_t)i);
}

Ref<tree::TerminalNode> ANTLRv4Parser::OptionValueContext::STRING_LITERAL() {
  return getToken(ANTLRv4Parser::STRING_LITERAL, 0);
}

Ref<ANTLRv4Parser::ActionBlockContext> ANTLRv4Parser::OptionValueContext::actionBlock() {
  return getRuleContext<ANTLRv4Parser::ActionBlockContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::OptionValueContext::INT() {
  return getToken(ANTLRv4Parser::INT, 0);
}


ssize_t ANTLRv4Parser::OptionValueContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleOptionValue;
}

void ANTLRv4Parser::OptionValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOptionValue(this);
}

void ANTLRv4Parser::OptionValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOptionValue(this);
}


antlrcpp::Any ANTLRv4Parser::OptionValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitOptionValue(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::OptionValueContext> ANTLRv4Parser::optionValue() {
  Ref<OptionValueContext> _localctx = std::make_shared<OptionValueContext>(_ctx, getState());
  enterRule(_localctx, 10, ANTLRv4Parser::RuleOptionValue);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(191);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ANTLRv4Parser::TOKEN_REF:
      case ANTLRv4Parser::RULE_REF: {
        enterOuterAlt(_localctx, 1);
        setState(180);
        identifier();
        setState(185);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ANTLRv4Parser::DOT) {
          setState(181);
          match(ANTLRv4Parser::DOT);
          setState(182);
          identifier();
          setState(187);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case ANTLRv4Parser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(188);
        match(ANTLRv4Parser::STRING_LITERAL);
        break;
      }

      case ANTLRv4Parser::BEGIN_ACTION: {
        enterOuterAlt(_localctx, 3);
        setState(189);
        actionBlock();
        break;
      }

      case ANTLRv4Parser::INT: {
        enterOuterAlt(_localctx, 4);
        setState(190);
        match(ANTLRv4Parser::INT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DelegateGrammarsContext ------------------------------------------------------------------

ANTLRv4Parser::DelegateGrammarsContext::DelegateGrammarsContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::DelegateGrammarsContext::IMPORT() {
  return getToken(ANTLRv4Parser::IMPORT, 0);
}

std::vector<Ref<ANTLRv4Parser::DelegateGrammarContext>> ANTLRv4Parser::DelegateGrammarsContext::delegateGrammar() {
  return getRuleContexts<ANTLRv4Parser::DelegateGrammarContext>();
}

Ref<ANTLRv4Parser::DelegateGrammarContext> ANTLRv4Parser::DelegateGrammarsContext::delegateGrammar(int i) {
  return getRuleContext<ANTLRv4Parser::DelegateGrammarContext>((size_t)i);
}

Ref<tree::TerminalNode> ANTLRv4Parser::DelegateGrammarsContext::SEMI() {
  return getToken(ANTLRv4Parser::SEMI, 0);
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::DelegateGrammarsContext::COMMA() {
  return getTokens(ANTLRv4Parser::COMMA);
}

Ref<tree::TerminalNode> ANTLRv4Parser::DelegateGrammarsContext::COMMA(int i) {
  return getToken(ANTLRv4Parser::COMMA, (size_t)i);
}


ssize_t ANTLRv4Parser::DelegateGrammarsContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleDelegateGrammars;
}

void ANTLRv4Parser::DelegateGrammarsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDelegateGrammars(this);
}

void ANTLRv4Parser::DelegateGrammarsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDelegateGrammars(this);
}


antlrcpp::Any ANTLRv4Parser::DelegateGrammarsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitDelegateGrammars(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::DelegateGrammarsContext> ANTLRv4Parser::delegateGrammars() {
  Ref<DelegateGrammarsContext> _localctx = std::make_shared<DelegateGrammarsContext>(_ctx, getState());
  enterRule(_localctx, 12, ANTLRv4Parser::RuleDelegateGrammars);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(193);
    match(ANTLRv4Parser::IMPORT);
    setState(194);
    delegateGrammar();
    setState(199);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::COMMA) {
      setState(195);
      match(ANTLRv4Parser::COMMA);
      setState(196);
      delegateGrammar();
      setState(201);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(202);
    match(ANTLRv4Parser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DelegateGrammarContext ------------------------------------------------------------------

ANTLRv4Parser::DelegateGrammarContext::DelegateGrammarContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Ref<ANTLRv4Parser::IdentifierContext>> ANTLRv4Parser::DelegateGrammarContext::identifier() {
  return getRuleContexts<ANTLRv4Parser::IdentifierContext>();
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::DelegateGrammarContext::identifier(int i) {
  return getRuleContext<ANTLRv4Parser::IdentifierContext>((size_t)i);
}

Ref<tree::TerminalNode> ANTLRv4Parser::DelegateGrammarContext::ASSIGN() {
  return getToken(ANTLRv4Parser::ASSIGN, 0);
}


ssize_t ANTLRv4Parser::DelegateGrammarContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleDelegateGrammar;
}

void ANTLRv4Parser::DelegateGrammarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDelegateGrammar(this);
}

void ANTLRv4Parser::DelegateGrammarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDelegateGrammar(this);
}


antlrcpp::Any ANTLRv4Parser::DelegateGrammarContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitDelegateGrammar(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::DelegateGrammarContext> ANTLRv4Parser::delegateGrammar() {
  Ref<DelegateGrammarContext> _localctx = std::make_shared<DelegateGrammarContext>(_ctx, getState());
  enterRule(_localctx, 14, ANTLRv4Parser::RuleDelegateGrammar);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(209);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(204);
      identifier();
      setState(205);
      match(ANTLRv4Parser::ASSIGN);
      setState(206);
      identifier();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(208);
      identifier();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TokensSpecContext ------------------------------------------------------------------

ANTLRv4Parser::TokensSpecContext::TokensSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::TokensSpecContext::TOKENS() {
  return getToken(ANTLRv4Parser::TOKENS, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::TokensSpecContext::LBRACE() {
  return getToken(ANTLRv4Parser::LBRACE, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::TokensSpecContext::RBRACE() {
  return getToken(ANTLRv4Parser::RBRACE, 0);
}

Ref<ANTLRv4Parser::IdListContext> ANTLRv4Parser::TokensSpecContext::idList() {
  return getRuleContext<ANTLRv4Parser::IdListContext>(0);
}


ssize_t ANTLRv4Parser::TokensSpecContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleTokensSpec;
}

void ANTLRv4Parser::TokensSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTokensSpec(this);
}

void ANTLRv4Parser::TokensSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTokensSpec(this);
}


antlrcpp::Any ANTLRv4Parser::TokensSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitTokensSpec(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::TokensSpecContext> ANTLRv4Parser::tokensSpec() {
  Ref<TokensSpecContext> _localctx = std::make_shared<TokensSpecContext>(_ctx, getState());
  enterRule(_localctx, 16, ANTLRv4Parser::RuleTokensSpec);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(211);
    match(ANTLRv4Parser::TOKENS);
    setState(212);
    match(ANTLRv4Parser::LBRACE);
    setState(214);

    _la = _input->LA(1);
    if (_la == ANTLRv4Parser::TOKEN_REF

    || _la == ANTLRv4Parser::RULE_REF) {
      setState(213);
      idList();
    }
    setState(216);
    match(ANTLRv4Parser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChannelsSpecContext ------------------------------------------------------------------

ANTLRv4Parser::ChannelsSpecContext::ChannelsSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::ChannelsSpecContext::CHANNELS() {
  return getToken(ANTLRv4Parser::CHANNELS, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ChannelsSpecContext::LBRACE() {
  return getToken(ANTLRv4Parser::LBRACE, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ChannelsSpecContext::RBRACE() {
  return getToken(ANTLRv4Parser::RBRACE, 0);
}

Ref<ANTLRv4Parser::IdListContext> ANTLRv4Parser::ChannelsSpecContext::idList() {
  return getRuleContext<ANTLRv4Parser::IdListContext>(0);
}


ssize_t ANTLRv4Parser::ChannelsSpecContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleChannelsSpec;
}

void ANTLRv4Parser::ChannelsSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChannelsSpec(this);
}

void ANTLRv4Parser::ChannelsSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChannelsSpec(this);
}


antlrcpp::Any ANTLRv4Parser::ChannelsSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitChannelsSpec(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::ChannelsSpecContext> ANTLRv4Parser::channelsSpec() {
  Ref<ChannelsSpecContext> _localctx = std::make_shared<ChannelsSpecContext>(_ctx, getState());
  enterRule(_localctx, 18, ANTLRv4Parser::RuleChannelsSpec);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(218);
    match(ANTLRv4Parser::CHANNELS);
    setState(219);
    match(ANTLRv4Parser::LBRACE);
    setState(221);

    _la = _input->LA(1);
    if (_la == ANTLRv4Parser::TOKEN_REF

    || _la == ANTLRv4Parser::RULE_REF) {
      setState(220);
      idList();
    }
    setState(223);
    match(ANTLRv4Parser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdListContext ------------------------------------------------------------------

ANTLRv4Parser::IdListContext::IdListContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Ref<ANTLRv4Parser::IdentifierContext>> ANTLRv4Parser::IdListContext::identifier() {
  return getRuleContexts<ANTLRv4Parser::IdentifierContext>();
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::IdListContext::identifier(int i) {
  return getRuleContext<ANTLRv4Parser::IdentifierContext>((size_t)i);
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::IdListContext::COMMA() {
  return getTokens(ANTLRv4Parser::COMMA);
}

Ref<tree::TerminalNode> ANTLRv4Parser::IdListContext::COMMA(int i) {
  return getToken(ANTLRv4Parser::COMMA, (size_t)i);
}


ssize_t ANTLRv4Parser::IdListContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleIdList;
}

void ANTLRv4Parser::IdListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdList(this);
}

void ANTLRv4Parser::IdListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdList(this);
}


antlrcpp::Any ANTLRv4Parser::IdListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitIdList(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::IdListContext> ANTLRv4Parser::idList() {
  Ref<IdListContext> _localctx = std::make_shared<IdListContext>(_ctx, getState());
  enterRule(_localctx, 20, ANTLRv4Parser::RuleIdList);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    int alt;
    enterOuterAlt(_localctx, 1);
    setState(225);
    identifier();
    setState(230);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(226);
        match(ANTLRv4Parser::COMMA);
        setState(227);
        identifier(); 
      }
      setState(232);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    }
    setState(234);

    _la = _input->LA(1);
    if (_la == ANTLRv4Parser::COMMA) {
      setState(233);
      match(ANTLRv4Parser::COMMA);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ActionContext ------------------------------------------------------------------

ANTLRv4Parser::ActionContext::ActionContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::ActionContext::AT() {
  return getToken(ANTLRv4Parser::AT, 0);
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::ActionContext::identifier() {
  return getRuleContext<ANTLRv4Parser::IdentifierContext>(0);
}

Ref<ANTLRv4Parser::ActionBlockContext> ANTLRv4Parser::ActionContext::actionBlock() {
  return getRuleContext<ANTLRv4Parser::ActionBlockContext>(0);
}

Ref<ANTLRv4Parser::ActionScopeNameContext> ANTLRv4Parser::ActionContext::actionScopeName() {
  return getRuleContext<ANTLRv4Parser::ActionScopeNameContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ActionContext::COLONCOLON() {
  return getToken(ANTLRv4Parser::COLONCOLON, 0);
}


ssize_t ANTLRv4Parser::ActionContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleAction;
}

void ANTLRv4Parser::ActionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAction(this);
}

void ANTLRv4Parser::ActionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAction(this);
}


antlrcpp::Any ANTLRv4Parser::ActionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitAction(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::ActionContext> ANTLRv4Parser::action() {
  Ref<ActionContext> _localctx = std::make_shared<ActionContext>(_ctx, getState());
  enterRule(_localctx, 22, ANTLRv4Parser::RuleAction);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(236);
    match(ANTLRv4Parser::AT);
    setState(240);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      setState(237);
      actionScopeName();
      setState(238);
      match(ANTLRv4Parser::COLONCOLON);
      break;
    }

    }
    setState(242);
    identifier();
    setState(243);
    actionBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ActionScopeNameContext ------------------------------------------------------------------

ANTLRv4Parser::ActionScopeNameContext::ActionScopeNameContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::ActionScopeNameContext::identifier() {
  return getRuleContext<ANTLRv4Parser::IdentifierContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ActionScopeNameContext::LEXER() {
  return getToken(ANTLRv4Parser::LEXER, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ActionScopeNameContext::PARSER() {
  return getToken(ANTLRv4Parser::PARSER, 0);
}


ssize_t ANTLRv4Parser::ActionScopeNameContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleActionScopeName;
}

void ANTLRv4Parser::ActionScopeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterActionScopeName(this);
}

void ANTLRv4Parser::ActionScopeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitActionScopeName(this);
}


antlrcpp::Any ANTLRv4Parser::ActionScopeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitActionScopeName(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::ActionScopeNameContext> ANTLRv4Parser::actionScopeName() {
  Ref<ActionScopeNameContext> _localctx = std::make_shared<ActionScopeNameContext>(_ctx, getState());
  enterRule(_localctx, 24, ANTLRv4Parser::RuleActionScopeName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(248);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ANTLRv4Parser::TOKEN_REF:
      case ANTLRv4Parser::RULE_REF: {
        enterOuterAlt(_localctx, 1);
        setState(245);
        identifier();
        break;
      }

      case ANTLRv4Parser::LEXER: {
        enterOuterAlt(_localctx, 2);
        setState(246);
        match(ANTLRv4Parser::LEXER);
        break;
      }

      case ANTLRv4Parser::PARSER: {
        enterOuterAlt(_localctx, 3);
        setState(247);
        match(ANTLRv4Parser::PARSER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ActionBlockContext ------------------------------------------------------------------

ANTLRv4Parser::ActionBlockContext::ActionBlockContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::ActionBlockContext::BEGIN_ACTION() {
  return getToken(ANTLRv4Parser::BEGIN_ACTION, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ActionBlockContext::END_ACTION() {
  return getToken(ANTLRv4Parser::END_ACTION, 0);
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::ActionBlockContext::ACTION_CONTENT() {
  return getTokens(ANTLRv4Parser::ACTION_CONTENT);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ActionBlockContext::ACTION_CONTENT(int i) {
  return getToken(ANTLRv4Parser::ACTION_CONTENT, (size_t)i);
}


ssize_t ANTLRv4Parser::ActionBlockContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleActionBlock;
}

void ANTLRv4Parser::ActionBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterActionBlock(this);
}

void ANTLRv4Parser::ActionBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitActionBlock(this);
}


antlrcpp::Any ANTLRv4Parser::ActionBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitActionBlock(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::ActionBlockContext> ANTLRv4Parser::actionBlock() {
  Ref<ActionBlockContext> _localctx = std::make_shared<ActionBlockContext>(_ctx, getState());
  enterRule(_localctx, 26, ANTLRv4Parser::RuleActionBlock);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(250);
    match(ANTLRv4Parser::BEGIN_ACTION);
    setState(254);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::ACTION_CONTENT) {
      setState(251);
      match(ANTLRv4Parser::ACTION_CONTENT);
      setState(256);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(257);
    match(ANTLRv4Parser::END_ACTION);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgActionBlockContext ------------------------------------------------------------------

ANTLRv4Parser::ArgActionBlockContext::ArgActionBlockContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::ArgActionBlockContext::BEGIN_ARGUMENT() {
  return getToken(ANTLRv4Parser::BEGIN_ARGUMENT, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ArgActionBlockContext::END_ARGUMENT() {
  return getToken(ANTLRv4Parser::END_ARGUMENT, 0);
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::ArgActionBlockContext::ARGUMENT_CONTENT() {
  return getTokens(ANTLRv4Parser::ARGUMENT_CONTENT);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ArgActionBlockContext::ARGUMENT_CONTENT(int i) {
  return getToken(ANTLRv4Parser::ARGUMENT_CONTENT, (size_t)i);
}


ssize_t ANTLRv4Parser::ArgActionBlockContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleArgActionBlock;
}

void ANTLRv4Parser::ArgActionBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgActionBlock(this);
}

void ANTLRv4Parser::ArgActionBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgActionBlock(this);
}


antlrcpp::Any ANTLRv4Parser::ArgActionBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitArgActionBlock(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::ArgActionBlockContext> ANTLRv4Parser::argActionBlock() {
  Ref<ArgActionBlockContext> _localctx = std::make_shared<ArgActionBlockContext>(_ctx, getState());
  enterRule(_localctx, 28, ANTLRv4Parser::RuleArgActionBlock);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(259);
    match(ANTLRv4Parser::BEGIN_ARGUMENT);
    setState(263);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::ARGUMENT_CONTENT) {
      setState(260);
      match(ANTLRv4Parser::ARGUMENT_CONTENT);
      setState(265);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(266);
    match(ANTLRv4Parser::END_ARGUMENT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ModeSpecContext ------------------------------------------------------------------

ANTLRv4Parser::ModeSpecContext::ModeSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::ModeSpecContext::MODE() {
  return getToken(ANTLRv4Parser::MODE, 0);
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::ModeSpecContext::identifier() {
  return getRuleContext<ANTLRv4Parser::IdentifierContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ModeSpecContext::SEMI() {
  return getToken(ANTLRv4Parser::SEMI, 0);
}

std::vector<Ref<ANTLRv4Parser::LexerRuleSpecContext>> ANTLRv4Parser::ModeSpecContext::lexerRuleSpec() {
  return getRuleContexts<ANTLRv4Parser::LexerRuleSpecContext>();
}

Ref<ANTLRv4Parser::LexerRuleSpecContext> ANTLRv4Parser::ModeSpecContext::lexerRuleSpec(int i) {
  return getRuleContext<ANTLRv4Parser::LexerRuleSpecContext>((size_t)i);
}


ssize_t ANTLRv4Parser::ModeSpecContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleModeSpec;
}

void ANTLRv4Parser::ModeSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterModeSpec(this);
}

void ANTLRv4Parser::ModeSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitModeSpec(this);
}


antlrcpp::Any ANTLRv4Parser::ModeSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitModeSpec(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::ModeSpecContext> ANTLRv4Parser::modeSpec() {
  Ref<ModeSpecContext> _localctx = std::make_shared<ModeSpecContext>(_ctx, getState());
  enterRule(_localctx, 30, ANTLRv4Parser::RuleModeSpec);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(268);
    match(ANTLRv4Parser::MODE);
    setState(269);
    identifier();
    setState(270);
    match(ANTLRv4Parser::SEMI);
    setState(274);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~(ssize_t)0x3f) == 0) &&
      ((1ULL << _la) & ((1ULL << ANTLRv4Parser::TOKEN_REF)
      | (1ULL << ANTLRv4Parser::DOC_COMMENT)
      | (1ULL << ANTLRv4Parser::FRAGMENT))) != 0)) {
      setState(271);
      lexerRuleSpec();
      setState(276);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RulesContext ------------------------------------------------------------------

ANTLRv4Parser::RulesContext::RulesContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Ref<ANTLRv4Parser::RuleSpecContext>> ANTLRv4Parser::RulesContext::ruleSpec() {
  return getRuleContexts<ANTLRv4Parser::RuleSpecContext>();
}

Ref<ANTLRv4Parser::RuleSpecContext> ANTLRv4Parser::RulesContext::ruleSpec(int i) {
  return getRuleContext<ANTLRv4Parser::RuleSpecContext>((size_t)i);
}


ssize_t ANTLRv4Parser::RulesContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleRules;
}

void ANTLRv4Parser::RulesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRules(this);
}

void ANTLRv4Parser::RulesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRules(this);
}


antlrcpp::Any ANTLRv4Parser::RulesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitRules(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::RulesContext> ANTLRv4Parser::rules() {
  Ref<RulesContext> _localctx = std::make_shared<RulesContext>(_ctx, getState());
  enterRule(_localctx, 32, ANTLRv4Parser::RuleRules);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(280);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~(ssize_t)0x3f) == 0) &&
      ((1ULL << _la) & ((1ULL << ANTLRv4Parser::TOKEN_REF)
      | (1ULL << ANTLRv4Parser::RULE_REF)
      | (1ULL << ANTLRv4Parser::DOC_COMMENT)
      | (1ULL << ANTLRv4Parser::FRAGMENT)
      | (1ULL << ANTLRv4Parser::PROTECTED)
      | (1ULL << ANTLRv4Parser::PUBLIC)
      | (1ULL << ANTLRv4Parser::PRIVATE))) != 0)) {
      setState(277);
      ruleSpec();
      setState(282);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RuleSpecContext ------------------------------------------------------------------

ANTLRv4Parser::RuleSpecContext::RuleSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::ParserRuleSpecContext> ANTLRv4Parser::RuleSpecContext::parserRuleSpec() {
  return getRuleContext<ANTLRv4Parser::ParserRuleSpecContext>(0);
}

Ref<ANTLRv4Parser::LexerRuleSpecContext> ANTLRv4Parser::RuleSpecContext::lexerRuleSpec() {
  return getRuleContext<ANTLRv4Parser::LexerRuleSpecContext>(0);
}


ssize_t ANTLRv4Parser::RuleSpecContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleRuleSpec;
}

void ANTLRv4Parser::RuleSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRuleSpec(this);
}

void ANTLRv4Parser::RuleSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRuleSpec(this);
}


antlrcpp::Any ANTLRv4Parser::RuleSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitRuleSpec(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::RuleSpecContext> ANTLRv4Parser::ruleSpec() {
  Ref<RuleSpecContext> _localctx = std::make_shared<RuleSpecContext>(_ctx, getState());
  enterRule(_localctx, 34, ANTLRv4Parser::RuleRuleSpec);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(285);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(283);
      parserRuleSpec();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(284);
      lexerRuleSpec();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParserRuleSpecContext ------------------------------------------------------------------

ANTLRv4Parser::ParserRuleSpecContext::ParserRuleSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::ParserRuleSpecContext::RULE_REF() {
  return getToken(ANTLRv4Parser::RULE_REF, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ParserRuleSpecContext::COLON() {
  return getToken(ANTLRv4Parser::COLON, 0);
}

Ref<ANTLRv4Parser::RuleBlockContext> ANTLRv4Parser::ParserRuleSpecContext::ruleBlock() {
  return getRuleContext<ANTLRv4Parser::RuleBlockContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ParserRuleSpecContext::SEMI() {
  return getToken(ANTLRv4Parser::SEMI, 0);
}

Ref<ANTLRv4Parser::ExceptionGroupContext> ANTLRv4Parser::ParserRuleSpecContext::exceptionGroup() {
  return getRuleContext<ANTLRv4Parser::ExceptionGroupContext>(0);
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::ParserRuleSpecContext::DOC_COMMENT() {
  return getTokens(ANTLRv4Parser::DOC_COMMENT);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ParserRuleSpecContext::DOC_COMMENT(int i) {
  return getToken(ANTLRv4Parser::DOC_COMMENT, (size_t)i);
}

Ref<ANTLRv4Parser::RuleModifiersContext> ANTLRv4Parser::ParserRuleSpecContext::ruleModifiers() {
  return getRuleContext<ANTLRv4Parser::RuleModifiersContext>(0);
}

Ref<ANTLRv4Parser::ArgActionBlockContext> ANTLRv4Parser::ParserRuleSpecContext::argActionBlock() {
  return getRuleContext<ANTLRv4Parser::ArgActionBlockContext>(0);
}

Ref<ANTLRv4Parser::RuleReturnsContext> ANTLRv4Parser::ParserRuleSpecContext::ruleReturns() {
  return getRuleContext<ANTLRv4Parser::RuleReturnsContext>(0);
}

Ref<ANTLRv4Parser::ThrowsSpecContext> ANTLRv4Parser::ParserRuleSpecContext::throwsSpec() {
  return getRuleContext<ANTLRv4Parser::ThrowsSpecContext>(0);
}

Ref<ANTLRv4Parser::LocalsSpecContext> ANTLRv4Parser::ParserRuleSpecContext::localsSpec() {
  return getRuleContext<ANTLRv4Parser::LocalsSpecContext>(0);
}

std::vector<Ref<ANTLRv4Parser::RulePrequelContext>> ANTLRv4Parser::ParserRuleSpecContext::rulePrequel() {
  return getRuleContexts<ANTLRv4Parser::RulePrequelContext>();
}

Ref<ANTLRv4Parser::RulePrequelContext> ANTLRv4Parser::ParserRuleSpecContext::rulePrequel(int i) {
  return getRuleContext<ANTLRv4Parser::RulePrequelContext>((size_t)i);
}


ssize_t ANTLRv4Parser::ParserRuleSpecContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleParserRuleSpec;
}

void ANTLRv4Parser::ParserRuleSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParserRuleSpec(this);
}

void ANTLRv4Parser::ParserRuleSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParserRuleSpec(this);
}


antlrcpp::Any ANTLRv4Parser::ParserRuleSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitParserRuleSpec(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::ParserRuleSpecContext> ANTLRv4Parser::parserRuleSpec() {
  Ref<ParserRuleSpecContext> _localctx = std::make_shared<ParserRuleSpecContext>(_ctx, getState());
  enterRule(_localctx, 36, ANTLRv4Parser::RuleParserRuleSpec);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(290);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::DOC_COMMENT) {
      setState(287);
      match(ANTLRv4Parser::DOC_COMMENT);
      setState(292);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(294);

    _la = _input->LA(1);
    if ((((_la & ~(ssize_t)0x3f) == 0) &&
      ((1ULL << _la) & ((1ULL << ANTLRv4Parser::FRAGMENT)
      | (1ULL << ANTLRv4Parser::PROTECTED)
      | (1ULL << ANTLRv4Parser::PUBLIC)
      | (1ULL << ANTLRv4Parser::PRIVATE))) != 0)) {
      setState(293);
      ruleModifiers();
    }
    setState(296);
    match(ANTLRv4Parser::RULE_REF);
    setState(298);

    _la = _input->LA(1);
    if (_la == ANTLRv4Parser::BEGIN_ARGUMENT) {
      setState(297);
      argActionBlock();
    }
    setState(301);

    _la = _input->LA(1);
    if (_la == ANTLRv4Parser::RETURNS) {
      setState(300);
      ruleReturns();
    }
    setState(304);

    _la = _input->LA(1);
    if (_la == ANTLRv4Parser::THROWS) {
      setState(303);
      throwsSpec();
    }
    setState(307);

    _la = _input->LA(1);
    if (_la == ANTLRv4Parser::LOCALS) {
      setState(306);
      localsSpec();
    }
    setState(312);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::OPTIONS

    || _la == ANTLRv4Parser::AT) {
      setState(309);
      rulePrequel();
      setState(314);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(315);
    match(ANTLRv4Parser::COLON);
    setState(316);
    ruleBlock();
    setState(317);
    match(ANTLRv4Parser::SEMI);
    setState(318);
    exceptionGroup();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExceptionGroupContext ------------------------------------------------------------------

ANTLRv4Parser::ExceptionGroupContext::ExceptionGroupContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Ref<ANTLRv4Parser::ExceptionHandlerContext>> ANTLRv4Parser::ExceptionGroupContext::exceptionHandler() {
  return getRuleContexts<ANTLRv4Parser::ExceptionHandlerContext>();
}

Ref<ANTLRv4Parser::ExceptionHandlerContext> ANTLRv4Parser::ExceptionGroupContext::exceptionHandler(int i) {
  return getRuleContext<ANTLRv4Parser::ExceptionHandlerContext>((size_t)i);
}

Ref<ANTLRv4Parser::FinallyClauseContext> ANTLRv4Parser::ExceptionGroupContext::finallyClause() {
  return getRuleContext<ANTLRv4Parser::FinallyClauseContext>(0);
}


ssize_t ANTLRv4Parser::ExceptionGroupContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleExceptionGroup;
}

void ANTLRv4Parser::ExceptionGroupContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExceptionGroup(this);
}

void ANTLRv4Parser::ExceptionGroupContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExceptionGroup(this);
}


antlrcpp::Any ANTLRv4Parser::ExceptionGroupContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitExceptionGroup(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::ExceptionGroupContext> ANTLRv4Parser::exceptionGroup() {
  Ref<ExceptionGroupContext> _localctx = std::make_shared<ExceptionGroupContext>(_ctx, getState());
  enterRule(_localctx, 38, ANTLRv4Parser::RuleExceptionGroup);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(323);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::CATCH) {
      setState(320);
      exceptionHandler();
      setState(325);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(327);

    _la = _input->LA(1);
    if (_la == ANTLRv4Parser::FINALLY) {
      setState(326);
      finallyClause();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExceptionHandlerContext ------------------------------------------------------------------

ANTLRv4Parser::ExceptionHandlerContext::ExceptionHandlerContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::ExceptionHandlerContext::CATCH() {
  return getToken(ANTLRv4Parser::CATCH, 0);
}

Ref<ANTLRv4Parser::ArgActionBlockContext> ANTLRv4Parser::ExceptionHandlerContext::argActionBlock() {
  return getRuleContext<ANTLRv4Parser::ArgActionBlockContext>(0);
}

Ref<ANTLRv4Parser::ActionBlockContext> ANTLRv4Parser::ExceptionHandlerContext::actionBlock() {
  return getRuleContext<ANTLRv4Parser::ActionBlockContext>(0);
}


ssize_t ANTLRv4Parser::ExceptionHandlerContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleExceptionHandler;
}

void ANTLRv4Parser::ExceptionHandlerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExceptionHandler(this);
}

void ANTLRv4Parser::ExceptionHandlerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExceptionHandler(this);
}


antlrcpp::Any ANTLRv4Parser::ExceptionHandlerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitExceptionHandler(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::ExceptionHandlerContext> ANTLRv4Parser::exceptionHandler() {
  Ref<ExceptionHandlerContext> _localctx = std::make_shared<ExceptionHandlerContext>(_ctx, getState());
  enterRule(_localctx, 40, ANTLRv4Parser::RuleExceptionHandler);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(329);
    match(ANTLRv4Parser::CATCH);
    setState(330);
    argActionBlock();
    setState(331);
    actionBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FinallyClauseContext ------------------------------------------------------------------

ANTLRv4Parser::FinallyClauseContext::FinallyClauseContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::FinallyClauseContext::FINALLY() {
  return getToken(ANTLRv4Parser::FINALLY, 0);
}

Ref<ANTLRv4Parser::ActionBlockContext> ANTLRv4Parser::FinallyClauseContext::actionBlock() {
  return getRuleContext<ANTLRv4Parser::ActionBlockContext>(0);
}


ssize_t ANTLRv4Parser::FinallyClauseContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleFinallyClause;
}

void ANTLRv4Parser::FinallyClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFinallyClause(this);
}

void ANTLRv4Parser::FinallyClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFinallyClause(this);
}


antlrcpp::Any ANTLRv4Parser::FinallyClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitFinallyClause(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::FinallyClauseContext> ANTLRv4Parser::finallyClause() {
  Ref<FinallyClauseContext> _localctx = std::make_shared<FinallyClauseContext>(_ctx, getState());
  enterRule(_localctx, 42, ANTLRv4Parser::RuleFinallyClause);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(333);
    match(ANTLRv4Parser::FINALLY);
    setState(334);
    actionBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RulePrequelContext ------------------------------------------------------------------

ANTLRv4Parser::RulePrequelContext::RulePrequelContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::OptionsSpecContext> ANTLRv4Parser::RulePrequelContext::optionsSpec() {
  return getRuleContext<ANTLRv4Parser::OptionsSpecContext>(0);
}

Ref<ANTLRv4Parser::RuleActionContext> ANTLRv4Parser::RulePrequelContext::ruleAction() {
  return getRuleContext<ANTLRv4Parser::RuleActionContext>(0);
}


ssize_t ANTLRv4Parser::RulePrequelContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleRulePrequel;
}

void ANTLRv4Parser::RulePrequelContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRulePrequel(this);
}

void ANTLRv4Parser::RulePrequelContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRulePrequel(this);
}


antlrcpp::Any ANTLRv4Parser::RulePrequelContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitRulePrequel(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::RulePrequelContext> ANTLRv4Parser::rulePrequel() {
  Ref<RulePrequelContext> _localctx = std::make_shared<RulePrequelContext>(_ctx, getState());
  enterRule(_localctx, 44, ANTLRv4Parser::RuleRulePrequel);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(338);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ANTLRv4Parser::OPTIONS: {
        enterOuterAlt(_localctx, 1);
        setState(336);
        optionsSpec();
        break;
      }

      case ANTLRv4Parser::AT: {
        enterOuterAlt(_localctx, 2);
        setState(337);
        ruleAction();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RuleReturnsContext ------------------------------------------------------------------

ANTLRv4Parser::RuleReturnsContext::RuleReturnsContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::RuleReturnsContext::RETURNS() {
  return getToken(ANTLRv4Parser::RETURNS, 0);
}

Ref<ANTLRv4Parser::ArgActionBlockContext> ANTLRv4Parser::RuleReturnsContext::argActionBlock() {
  return getRuleContext<ANTLRv4Parser::ArgActionBlockContext>(0);
}


ssize_t ANTLRv4Parser::RuleReturnsContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleRuleReturns;
}

void ANTLRv4Parser::RuleReturnsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRuleReturns(this);
}

void ANTLRv4Parser::RuleReturnsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRuleReturns(this);
}


antlrcpp::Any ANTLRv4Parser::RuleReturnsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitRuleReturns(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::RuleReturnsContext> ANTLRv4Parser::ruleReturns() {
  Ref<RuleReturnsContext> _localctx = std::make_shared<RuleReturnsContext>(_ctx, getState());
  enterRule(_localctx, 46, ANTLRv4Parser::RuleRuleReturns);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(340);
    match(ANTLRv4Parser::RETURNS);
    setState(341);
    argActionBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ThrowsSpecContext ------------------------------------------------------------------

ANTLRv4Parser::ThrowsSpecContext::ThrowsSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::ThrowsSpecContext::THROWS() {
  return getToken(ANTLRv4Parser::THROWS, 0);
}

std::vector<Ref<ANTLRv4Parser::IdentifierContext>> ANTLRv4Parser::ThrowsSpecContext::identifier() {
  return getRuleContexts<ANTLRv4Parser::IdentifierContext>();
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::ThrowsSpecContext::identifier(int i) {
  return getRuleContext<ANTLRv4Parser::IdentifierContext>((size_t)i);
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::ThrowsSpecContext::COMMA() {
  return getTokens(ANTLRv4Parser::COMMA);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ThrowsSpecContext::COMMA(int i) {
  return getToken(ANTLRv4Parser::COMMA, (size_t)i);
}


ssize_t ANTLRv4Parser::ThrowsSpecContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleThrowsSpec;
}

void ANTLRv4Parser::ThrowsSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterThrowsSpec(this);
}

void ANTLRv4Parser::ThrowsSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitThrowsSpec(this);
}


antlrcpp::Any ANTLRv4Parser::ThrowsSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitThrowsSpec(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::ThrowsSpecContext> ANTLRv4Parser::throwsSpec() {
  Ref<ThrowsSpecContext> _localctx = std::make_shared<ThrowsSpecContext>(_ctx, getState());
  enterRule(_localctx, 48, ANTLRv4Parser::RuleThrowsSpec);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(343);
    match(ANTLRv4Parser::THROWS);
    setState(344);
    identifier();
    setState(349);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::COMMA) {
      setState(345);
      match(ANTLRv4Parser::COMMA);
      setState(346);
      identifier();
      setState(351);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LocalsSpecContext ------------------------------------------------------------------

ANTLRv4Parser::LocalsSpecContext::LocalsSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::LocalsSpecContext::LOCALS() {
  return getToken(ANTLRv4Parser::LOCALS, 0);
}

Ref<ANTLRv4Parser::ArgActionBlockContext> ANTLRv4Parser::LocalsSpecContext::argActionBlock() {
  return getRuleContext<ANTLRv4Parser::ArgActionBlockContext>(0);
}


ssize_t ANTLRv4Parser::LocalsSpecContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleLocalsSpec;
}

void ANTLRv4Parser::LocalsSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLocalsSpec(this);
}

void ANTLRv4Parser::LocalsSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLocalsSpec(this);
}


antlrcpp::Any ANTLRv4Parser::LocalsSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitLocalsSpec(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::LocalsSpecContext> ANTLRv4Parser::localsSpec() {
  Ref<LocalsSpecContext> _localctx = std::make_shared<LocalsSpecContext>(_ctx, getState());
  enterRule(_localctx, 50, ANTLRv4Parser::RuleLocalsSpec);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(352);
    match(ANTLRv4Parser::LOCALS);
    setState(353);
    argActionBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RuleActionContext ------------------------------------------------------------------

ANTLRv4Parser::RuleActionContext::RuleActionContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::RuleActionContext::AT() {
  return getToken(ANTLRv4Parser::AT, 0);
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::RuleActionContext::identifier() {
  return getRuleContext<ANTLRv4Parser::IdentifierContext>(0);
}

Ref<ANTLRv4Parser::ActionBlockContext> ANTLRv4Parser::RuleActionContext::actionBlock() {
  return getRuleContext<ANTLRv4Parser::ActionBlockContext>(0);
}


ssize_t ANTLRv4Parser::RuleActionContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleRuleAction;
}

void ANTLRv4Parser::RuleActionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRuleAction(this);
}

void ANTLRv4Parser::RuleActionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRuleAction(this);
}


antlrcpp::Any ANTLRv4Parser::RuleActionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitRuleAction(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::RuleActionContext> ANTLRv4Parser::ruleAction() {
  Ref<RuleActionContext> _localctx = std::make_shared<RuleActionContext>(_ctx, getState());
  enterRule(_localctx, 52, ANTLRv4Parser::RuleRuleAction);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(355);
    match(ANTLRv4Parser::AT);
    setState(356);
    identifier();
    setState(357);
    actionBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RuleModifiersContext ------------------------------------------------------------------

ANTLRv4Parser::RuleModifiersContext::RuleModifiersContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Ref<ANTLRv4Parser::RuleModifierContext>> ANTLRv4Parser::RuleModifiersContext::ruleModifier() {
  return getRuleContexts<ANTLRv4Parser::RuleModifierContext>();
}

Ref<ANTLRv4Parser::RuleModifierContext> ANTLRv4Parser::RuleModifiersContext::ruleModifier(int i) {
  return getRuleContext<ANTLRv4Parser::RuleModifierContext>((size_t)i);
}


ssize_t ANTLRv4Parser::RuleModifiersContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleRuleModifiers;
}

void ANTLRv4Parser::RuleModifiersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRuleModifiers(this);
}

void ANTLRv4Parser::RuleModifiersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRuleModifiers(this);
}


antlrcpp::Any ANTLRv4Parser::RuleModifiersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitRuleModifiers(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::RuleModifiersContext> ANTLRv4Parser::ruleModifiers() {
  Ref<RuleModifiersContext> _localctx = std::make_shared<RuleModifiersContext>(_ctx, getState());
  enterRule(_localctx, 54, ANTLRv4Parser::RuleRuleModifiers);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(360); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(359);
      ruleModifier();
      setState(362); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~(ssize_t)0x3f) == 0) &&
      ((1ULL << _la) & ((1ULL << ANTLRv4Parser::FRAGMENT)
      | (1ULL << ANTLRv4Parser::PROTECTED)
      | (1ULL << ANTLRv4Parser::PUBLIC)
      | (1ULL << ANTLRv4Parser::PRIVATE))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RuleModifierContext ------------------------------------------------------------------

ANTLRv4Parser::RuleModifierContext::RuleModifierContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::RuleModifierContext::PUBLIC() {
  return getToken(ANTLRv4Parser::PUBLIC, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::RuleModifierContext::PRIVATE() {
  return getToken(ANTLRv4Parser::PRIVATE, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::RuleModifierContext::PROTECTED() {
  return getToken(ANTLRv4Parser::PROTECTED, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::RuleModifierContext::FRAGMENT() {
  return getToken(ANTLRv4Parser::FRAGMENT, 0);
}


ssize_t ANTLRv4Parser::RuleModifierContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleRuleModifier;
}

void ANTLRv4Parser::RuleModifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRuleModifier(this);
}

void ANTLRv4Parser::RuleModifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRuleModifier(this);
}


antlrcpp::Any ANTLRv4Parser::RuleModifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitRuleModifier(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::RuleModifierContext> ANTLRv4Parser::ruleModifier() {
  Ref<RuleModifierContext> _localctx = std::make_shared<RuleModifierContext>(_ctx, getState());
  enterRule(_localctx, 56, ANTLRv4Parser::RuleRuleModifier);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(364);
    _la = _input->LA(1);
    if (!((((_la & ~(ssize_t)0x3f) == 0) &&
      ((1ULL << _la) & ((1ULL << ANTLRv4Parser::FRAGMENT)
      | (1ULL << ANTLRv4Parser::PROTECTED)
      | (1ULL << ANTLRv4Parser::PUBLIC)
      | (1ULL << ANTLRv4Parser::PRIVATE))) != 0))) {
    _errHandler->recoverInline(this);
    } else {
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RuleBlockContext ------------------------------------------------------------------

ANTLRv4Parser::RuleBlockContext::RuleBlockContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::RuleAltListContext> ANTLRv4Parser::RuleBlockContext::ruleAltList() {
  return getRuleContext<ANTLRv4Parser::RuleAltListContext>(0);
}


ssize_t ANTLRv4Parser::RuleBlockContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleRuleBlock;
}

void ANTLRv4Parser::RuleBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRuleBlock(this);
}

void ANTLRv4Parser::RuleBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRuleBlock(this);
}


antlrcpp::Any ANTLRv4Parser::RuleBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitRuleBlock(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::RuleBlockContext> ANTLRv4Parser::ruleBlock() {
  Ref<RuleBlockContext> _localctx = std::make_shared<RuleBlockContext>(_ctx, getState());
  enterRule(_localctx, 58, ANTLRv4Parser::RuleRuleBlock);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(366);
    ruleAltList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RuleAltListContext ------------------------------------------------------------------

ANTLRv4Parser::RuleAltListContext::RuleAltListContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Ref<ANTLRv4Parser::LabeledAltContext>> ANTLRv4Parser::RuleAltListContext::labeledAlt() {
  return getRuleContexts<ANTLRv4Parser::LabeledAltContext>();
}

Ref<ANTLRv4Parser::LabeledAltContext> ANTLRv4Parser::RuleAltListContext::labeledAlt(int i) {
  return getRuleContext<ANTLRv4Parser::LabeledAltContext>((size_t)i);
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::RuleAltListContext::OR() {
  return getTokens(ANTLRv4Parser::OR);
}

Ref<tree::TerminalNode> ANTLRv4Parser::RuleAltListContext::OR(int i) {
  return getToken(ANTLRv4Parser::OR, (size_t)i);
}


ssize_t ANTLRv4Parser::RuleAltListContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleRuleAltList;
}

void ANTLRv4Parser::RuleAltListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRuleAltList(this);
}

void ANTLRv4Parser::RuleAltListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRuleAltList(this);
}


antlrcpp::Any ANTLRv4Parser::RuleAltListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitRuleAltList(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::RuleAltListContext> ANTLRv4Parser::ruleAltList() {
  Ref<RuleAltListContext> _localctx = std::make_shared<RuleAltListContext>(_ctx, getState());
  enterRule(_localctx, 60, ANTLRv4Parser::RuleRuleAltList);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(368);
    labeledAlt();
    setState(373);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::OR) {
      setState(369);
      match(ANTLRv4Parser::OR);
      setState(370);
      labeledAlt();
      setState(375);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LabeledAltContext ------------------------------------------------------------------

ANTLRv4Parser::LabeledAltContext::LabeledAltContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::AlternativeContext> ANTLRv4Parser::LabeledAltContext::alternative() {
  return getRuleContext<ANTLRv4Parser::AlternativeContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LabeledAltContext::POUND() {
  return getToken(ANTLRv4Parser::POUND, 0);
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::LabeledAltContext::identifier() {
  return getRuleContext<ANTLRv4Parser::IdentifierContext>(0);
}


ssize_t ANTLRv4Parser::LabeledAltContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleLabeledAlt;
}

void ANTLRv4Parser::LabeledAltContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLabeledAlt(this);
}

void ANTLRv4Parser::LabeledAltContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLabeledAlt(this);
}


antlrcpp::Any ANTLRv4Parser::LabeledAltContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitLabeledAlt(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::LabeledAltContext> ANTLRv4Parser::labeledAlt() {
  Ref<LabeledAltContext> _localctx = std::make_shared<LabeledAltContext>(_ctx, getState());
  enterRule(_localctx, 62, ANTLRv4Parser::RuleLabeledAlt);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(376);
    alternative();
    setState(379);

    _la = _input->LA(1);
    if (_la == ANTLRv4Parser::POUND) {
      setState(377);
      match(ANTLRv4Parser::POUND);
      setState(378);
      identifier();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LexerRuleSpecContext ------------------------------------------------------------------

ANTLRv4Parser::LexerRuleSpecContext::LexerRuleSpecContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerRuleSpecContext::TOKEN_REF() {
  return getToken(ANTLRv4Parser::TOKEN_REF, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerRuleSpecContext::COLON() {
  return getToken(ANTLRv4Parser::COLON, 0);
}

Ref<ANTLRv4Parser::LexerRuleBlockContext> ANTLRv4Parser::LexerRuleSpecContext::lexerRuleBlock() {
  return getRuleContext<ANTLRv4Parser::LexerRuleBlockContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerRuleSpecContext::SEMI() {
  return getToken(ANTLRv4Parser::SEMI, 0);
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::LexerRuleSpecContext::DOC_COMMENT() {
  return getTokens(ANTLRv4Parser::DOC_COMMENT);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerRuleSpecContext::DOC_COMMENT(int i) {
  return getToken(ANTLRv4Parser::DOC_COMMENT, (size_t)i);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerRuleSpecContext::FRAGMENT() {
  return getToken(ANTLRv4Parser::FRAGMENT, 0);
}


ssize_t ANTLRv4Parser::LexerRuleSpecContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleLexerRuleSpec;
}

void ANTLRv4Parser::LexerRuleSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLexerRuleSpec(this);
}

void ANTLRv4Parser::LexerRuleSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLexerRuleSpec(this);
}


antlrcpp::Any ANTLRv4Parser::LexerRuleSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitLexerRuleSpec(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::LexerRuleSpecContext> ANTLRv4Parser::lexerRuleSpec() {
  Ref<LexerRuleSpecContext> _localctx = std::make_shared<LexerRuleSpecContext>(_ctx, getState());
  enterRule(_localctx, 64, ANTLRv4Parser::RuleLexerRuleSpec);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(384);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::DOC_COMMENT) {
      setState(381);
      match(ANTLRv4Parser::DOC_COMMENT);
      setState(386);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(388);

    _la = _input->LA(1);
    if (_la == ANTLRv4Parser::FRAGMENT) {
      setState(387);
      match(ANTLRv4Parser::FRAGMENT);
    }
    setState(390);
    match(ANTLRv4Parser::TOKEN_REF);
    setState(391);
    match(ANTLRv4Parser::COLON);
    setState(392);
    lexerRuleBlock();
    setState(393);
    match(ANTLRv4Parser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LexerRuleBlockContext ------------------------------------------------------------------

ANTLRv4Parser::LexerRuleBlockContext::LexerRuleBlockContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::LexerAltListContext> ANTLRv4Parser::LexerRuleBlockContext::lexerAltList() {
  return getRuleContext<ANTLRv4Parser::LexerAltListContext>(0);
}


ssize_t ANTLRv4Parser::LexerRuleBlockContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleLexerRuleBlock;
}

void ANTLRv4Parser::LexerRuleBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLexerRuleBlock(this);
}

void ANTLRv4Parser::LexerRuleBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLexerRuleBlock(this);
}


antlrcpp::Any ANTLRv4Parser::LexerRuleBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitLexerRuleBlock(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::LexerRuleBlockContext> ANTLRv4Parser::lexerRuleBlock() {
  Ref<LexerRuleBlockContext> _localctx = std::make_shared<LexerRuleBlockContext>(_ctx, getState());
  enterRule(_localctx, 66, ANTLRv4Parser::RuleLexerRuleBlock);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(395);
    lexerAltList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LexerAltListContext ------------------------------------------------------------------

ANTLRv4Parser::LexerAltListContext::LexerAltListContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Ref<ANTLRv4Parser::LexerAltContext>> ANTLRv4Parser::LexerAltListContext::lexerAlt() {
  return getRuleContexts<ANTLRv4Parser::LexerAltContext>();
}

Ref<ANTLRv4Parser::LexerAltContext> ANTLRv4Parser::LexerAltListContext::lexerAlt(int i) {
  return getRuleContext<ANTLRv4Parser::LexerAltContext>((size_t)i);
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::LexerAltListContext::OR() {
  return getTokens(ANTLRv4Parser::OR);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerAltListContext::OR(int i) {
  return getToken(ANTLRv4Parser::OR, (size_t)i);
}


ssize_t ANTLRv4Parser::LexerAltListContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleLexerAltList;
}

void ANTLRv4Parser::LexerAltListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLexerAltList(this);
}

void ANTLRv4Parser::LexerAltListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLexerAltList(this);
}


antlrcpp::Any ANTLRv4Parser::LexerAltListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitLexerAltList(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::LexerAltListContext> ANTLRv4Parser::lexerAltList() {
  Ref<LexerAltListContext> _localctx = std::make_shared<LexerAltListContext>(_ctx, getState());
  enterRule(_localctx, 68, ANTLRv4Parser::RuleLexerAltList);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(397);
    lexerAlt();
    setState(402);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::OR) {
      setState(398);
      match(ANTLRv4Parser::OR);
      setState(399);
      lexerAlt();
      setState(404);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LexerAltContext ------------------------------------------------------------------

ANTLRv4Parser::LexerAltContext::LexerAltContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::LexerElementsContext> ANTLRv4Parser::LexerAltContext::lexerElements() {
  return getRuleContext<ANTLRv4Parser::LexerElementsContext>(0);
}

Ref<ANTLRv4Parser::LexerCommandsContext> ANTLRv4Parser::LexerAltContext::lexerCommands() {
  return getRuleContext<ANTLRv4Parser::LexerCommandsContext>(0);
}


ssize_t ANTLRv4Parser::LexerAltContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleLexerAlt;
}

void ANTLRv4Parser::LexerAltContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLexerAlt(this);
}

void ANTLRv4Parser::LexerAltContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLexerAlt(this);
}


antlrcpp::Any ANTLRv4Parser::LexerAltContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitLexerAlt(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::LexerAltContext> ANTLRv4Parser::lexerAlt() {
  Ref<LexerAltContext> _localctx = std::make_shared<LexerAltContext>(_ctx, getState());
  enterRule(_localctx, 70, ANTLRv4Parser::RuleLexerAlt);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(410);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ANTLRv4Parser::TOKEN_REF:
      case ANTLRv4Parser::RULE_REF:
      case ANTLRv4Parser::LEXER_CHAR_SET:
      case ANTLRv4Parser::STRING_LITERAL:
      case ANTLRv4Parser::BEGIN_ACTION:
      case ANTLRv4Parser::LPAREN:
      case ANTLRv4Parser::DOT:
      case ANTLRv4Parser::NOT: {
        enterOuterAlt(_localctx, 1);
        setState(405);
        lexerElements();
        setState(407);

        _la = _input->LA(1);
        if (_la == ANTLRv4Parser::RARROW) {
          setState(406);
          lexerCommands();
        }
        break;
      }

      case ANTLRv4Parser::SEMI:
      case ANTLRv4Parser::RPAREN:
      case ANTLRv4Parser::OR: {
        enterOuterAlt(_localctx, 2);

        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LexerElementsContext ------------------------------------------------------------------

ANTLRv4Parser::LexerElementsContext::LexerElementsContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Ref<ANTLRv4Parser::LexerElementContext>> ANTLRv4Parser::LexerElementsContext::lexerElement() {
  return getRuleContexts<ANTLRv4Parser::LexerElementContext>();
}

Ref<ANTLRv4Parser::LexerElementContext> ANTLRv4Parser::LexerElementsContext::lexerElement(int i) {
  return getRuleContext<ANTLRv4Parser::LexerElementContext>((size_t)i);
}


ssize_t ANTLRv4Parser::LexerElementsContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleLexerElements;
}

void ANTLRv4Parser::LexerElementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLexerElements(this);
}

void ANTLRv4Parser::LexerElementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLexerElements(this);
}


antlrcpp::Any ANTLRv4Parser::LexerElementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitLexerElements(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::LexerElementsContext> ANTLRv4Parser::lexerElements() {
  Ref<LexerElementsContext> _localctx = std::make_shared<LexerElementsContext>(_ctx, getState());
  enterRule(_localctx, 72, ANTLRv4Parser::RuleLexerElements);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(413); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(412);
      lexerElement();
      setState(415); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~(ssize_t)0x3f) == 0) &&
      ((1ULL << _la) & ((1ULL << ANTLRv4Parser::TOKEN_REF)
      | (1ULL << ANTLRv4Parser::RULE_REF)
      | (1ULL << ANTLRv4Parser::LEXER_CHAR_SET)
      | (1ULL << ANTLRv4Parser::STRING_LITERAL)
      | (1ULL << ANTLRv4Parser::BEGIN_ACTION)
      | (1ULL << ANTLRv4Parser::LPAREN)
      | (1ULL << ANTLRv4Parser::DOT)
      | (1ULL << ANTLRv4Parser::NOT))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LexerElementContext ------------------------------------------------------------------

ANTLRv4Parser::LexerElementContext::LexerElementContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::LabeledLexerElementContext> ANTLRv4Parser::LexerElementContext::labeledLexerElement() {
  return getRuleContext<ANTLRv4Parser::LabeledLexerElementContext>(0);
}

Ref<ANTLRv4Parser::EbnfSuffixContext> ANTLRv4Parser::LexerElementContext::ebnfSuffix() {
  return getRuleContext<ANTLRv4Parser::EbnfSuffixContext>(0);
}

Ref<ANTLRv4Parser::LexerAtomContext> ANTLRv4Parser::LexerElementContext::lexerAtom() {
  return getRuleContext<ANTLRv4Parser::LexerAtomContext>(0);
}

Ref<ANTLRv4Parser::LexerBlockContext> ANTLRv4Parser::LexerElementContext::lexerBlock() {
  return getRuleContext<ANTLRv4Parser::LexerBlockContext>(0);
}

Ref<ANTLRv4Parser::ActionBlockContext> ANTLRv4Parser::LexerElementContext::actionBlock() {
  return getRuleContext<ANTLRv4Parser::ActionBlockContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerElementContext::QUESTION() {
  return getToken(ANTLRv4Parser::QUESTION, 0);
}


ssize_t ANTLRv4Parser::LexerElementContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleLexerElement;
}

void ANTLRv4Parser::LexerElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLexerElement(this);
}

void ANTLRv4Parser::LexerElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLexerElement(this);
}


antlrcpp::Any ANTLRv4Parser::LexerElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitLexerElement(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::LexerElementContext> ANTLRv4Parser::lexerElement() {
  Ref<LexerElementContext> _localctx = std::make_shared<LexerElementContext>(_ctx, getState());
  enterRule(_localctx, 74, ANTLRv4Parser::RuleLexerElement);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(433);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(417);
      labeledLexerElement();
      setState(419);

      _la = _input->LA(1);
      if ((((_la & ~(ssize_t)0x3f) == 0) &&
        ((1ULL << _la) & ((1ULL << ANTLRv4Parser::QUESTION)
        | (1ULL << ANTLRv4Parser::STAR)
        | (1ULL << ANTLRv4Parser::PLUS))) != 0)) {
        setState(418);
        ebnfSuffix();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(421);
      lexerAtom();
      setState(423);

      _la = _input->LA(1);
      if ((((_la & ~(ssize_t)0x3f) == 0) &&
        ((1ULL << _la) & ((1ULL << ANTLRv4Parser::QUESTION)
        | (1ULL << ANTLRv4Parser::STAR)
        | (1ULL << ANTLRv4Parser::PLUS))) != 0)) {
        setState(422);
        ebnfSuffix();
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(425);
      lexerBlock();
      setState(427);

      _la = _input->LA(1);
      if ((((_la & ~(ssize_t)0x3f) == 0) &&
        ((1ULL << _la) & ((1ULL << ANTLRv4Parser::QUESTION)
        | (1ULL << ANTLRv4Parser::STAR)
        | (1ULL << ANTLRv4Parser::PLUS))) != 0)) {
        setState(426);
        ebnfSuffix();
      }
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(429);
      actionBlock();
      setState(431);

      _la = _input->LA(1);
      if (_la == ANTLRv4Parser::QUESTION) {
        setState(430);
        match(ANTLRv4Parser::QUESTION);
      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LabeledLexerElementContext ------------------------------------------------------------------

ANTLRv4Parser::LabeledLexerElementContext::LabeledLexerElementContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::LabeledLexerElementContext::identifier() {
  return getRuleContext<ANTLRv4Parser::IdentifierContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LabeledLexerElementContext::ASSIGN() {
  return getToken(ANTLRv4Parser::ASSIGN, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LabeledLexerElementContext::PLUS_ASSIGN() {
  return getToken(ANTLRv4Parser::PLUS_ASSIGN, 0);
}

Ref<ANTLRv4Parser::LexerAtomContext> ANTLRv4Parser::LabeledLexerElementContext::lexerAtom() {
  return getRuleContext<ANTLRv4Parser::LexerAtomContext>(0);
}

Ref<ANTLRv4Parser::BlockContext> ANTLRv4Parser::LabeledLexerElementContext::block() {
  return getRuleContext<ANTLRv4Parser::BlockContext>(0);
}


ssize_t ANTLRv4Parser::LabeledLexerElementContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleLabeledLexerElement;
}

void ANTLRv4Parser::LabeledLexerElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLabeledLexerElement(this);
}

void ANTLRv4Parser::LabeledLexerElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLabeledLexerElement(this);
}


antlrcpp::Any ANTLRv4Parser::LabeledLexerElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitLabeledLexerElement(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::LabeledLexerElementContext> ANTLRv4Parser::labeledLexerElement() {
  Ref<LabeledLexerElementContext> _localctx = std::make_shared<LabeledLexerElementContext>(_ctx, getState());
  enterRule(_localctx, 76, ANTLRv4Parser::RuleLabeledLexerElement);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(435);
    identifier();
    setState(436);
    _la = _input->LA(1);
    if (!(_la == ANTLRv4Parser::ASSIGN

    || _la == ANTLRv4Parser::PLUS_ASSIGN)) {
    _errHandler->recoverInline(this);
    } else {
      consume();
    }
    setState(439);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ANTLRv4Parser::TOKEN_REF:
      case ANTLRv4Parser::LEXER_CHAR_SET:
      case ANTLRv4Parser::STRING_LITERAL:
      case ANTLRv4Parser::DOT:
      case ANTLRv4Parser::NOT: {
        setState(437);
        lexerAtom();
        break;
      }

      case ANTLRv4Parser::LPAREN: {
        setState(438);
        block();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LexerBlockContext ------------------------------------------------------------------

ANTLRv4Parser::LexerBlockContext::LexerBlockContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerBlockContext::LPAREN() {
  return getToken(ANTLRv4Parser::LPAREN, 0);
}

Ref<ANTLRv4Parser::LexerAltListContext> ANTLRv4Parser::LexerBlockContext::lexerAltList() {
  return getRuleContext<ANTLRv4Parser::LexerAltListContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerBlockContext::RPAREN() {
  return getToken(ANTLRv4Parser::RPAREN, 0);
}


ssize_t ANTLRv4Parser::LexerBlockContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleLexerBlock;
}

void ANTLRv4Parser::LexerBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLexerBlock(this);
}

void ANTLRv4Parser::LexerBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLexerBlock(this);
}


antlrcpp::Any ANTLRv4Parser::LexerBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitLexerBlock(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::LexerBlockContext> ANTLRv4Parser::lexerBlock() {
  Ref<LexerBlockContext> _localctx = std::make_shared<LexerBlockContext>(_ctx, getState());
  enterRule(_localctx, 78, ANTLRv4Parser::RuleLexerBlock);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(441);
    match(ANTLRv4Parser::LPAREN);
    setState(442);
    lexerAltList();
    setState(443);
    match(ANTLRv4Parser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LexerCommandsContext ------------------------------------------------------------------

ANTLRv4Parser::LexerCommandsContext::LexerCommandsContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerCommandsContext::RARROW() {
  return getToken(ANTLRv4Parser::RARROW, 0);
}

std::vector<Ref<ANTLRv4Parser::LexerCommandContext>> ANTLRv4Parser::LexerCommandsContext::lexerCommand() {
  return getRuleContexts<ANTLRv4Parser::LexerCommandContext>();
}

Ref<ANTLRv4Parser::LexerCommandContext> ANTLRv4Parser::LexerCommandsContext::lexerCommand(int i) {
  return getRuleContext<ANTLRv4Parser::LexerCommandContext>((size_t)i);
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::LexerCommandsContext::COMMA() {
  return getTokens(ANTLRv4Parser::COMMA);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerCommandsContext::COMMA(int i) {
  return getToken(ANTLRv4Parser::COMMA, (size_t)i);
}


ssize_t ANTLRv4Parser::LexerCommandsContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleLexerCommands;
}

void ANTLRv4Parser::LexerCommandsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLexerCommands(this);
}

void ANTLRv4Parser::LexerCommandsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLexerCommands(this);
}


antlrcpp::Any ANTLRv4Parser::LexerCommandsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitLexerCommands(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::LexerCommandsContext> ANTLRv4Parser::lexerCommands() {
  Ref<LexerCommandsContext> _localctx = std::make_shared<LexerCommandsContext>(_ctx, getState());
  enterRule(_localctx, 80, ANTLRv4Parser::RuleLexerCommands);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(445);
    match(ANTLRv4Parser::RARROW);
    setState(446);
    lexerCommand();
    setState(451);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::COMMA) {
      setState(447);
      match(ANTLRv4Parser::COMMA);
      setState(448);
      lexerCommand();
      setState(453);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LexerCommandContext ------------------------------------------------------------------

ANTLRv4Parser::LexerCommandContext::LexerCommandContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::LexerCommandNameContext> ANTLRv4Parser::LexerCommandContext::lexerCommandName() {
  return getRuleContext<ANTLRv4Parser::LexerCommandNameContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerCommandContext::LPAREN() {
  return getToken(ANTLRv4Parser::LPAREN, 0);
}

Ref<ANTLRv4Parser::LexerCommandExprContext> ANTLRv4Parser::LexerCommandContext::lexerCommandExpr() {
  return getRuleContext<ANTLRv4Parser::LexerCommandExprContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerCommandContext::RPAREN() {
  return getToken(ANTLRv4Parser::RPAREN, 0);
}


ssize_t ANTLRv4Parser::LexerCommandContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleLexerCommand;
}

void ANTLRv4Parser::LexerCommandContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLexerCommand(this);
}

void ANTLRv4Parser::LexerCommandContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLexerCommand(this);
}


antlrcpp::Any ANTLRv4Parser::LexerCommandContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitLexerCommand(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::LexerCommandContext> ANTLRv4Parser::lexerCommand() {
  Ref<LexerCommandContext> _localctx = std::make_shared<LexerCommandContext>(_ctx, getState());
  enterRule(_localctx, 82, ANTLRv4Parser::RuleLexerCommand);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(460);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(454);
      lexerCommandName();
      setState(455);
      match(ANTLRv4Parser::LPAREN);
      setState(456);
      lexerCommandExpr();
      setState(457);
      match(ANTLRv4Parser::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(459);
      lexerCommandName();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LexerCommandNameContext ------------------------------------------------------------------

ANTLRv4Parser::LexerCommandNameContext::LexerCommandNameContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::LexerCommandNameContext::identifier() {
  return getRuleContext<ANTLRv4Parser::IdentifierContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerCommandNameContext::MODE() {
  return getToken(ANTLRv4Parser::MODE, 0);
}


ssize_t ANTLRv4Parser::LexerCommandNameContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleLexerCommandName;
}

void ANTLRv4Parser::LexerCommandNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLexerCommandName(this);
}

void ANTLRv4Parser::LexerCommandNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLexerCommandName(this);
}


antlrcpp::Any ANTLRv4Parser::LexerCommandNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitLexerCommandName(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::LexerCommandNameContext> ANTLRv4Parser::lexerCommandName() {
  Ref<LexerCommandNameContext> _localctx = std::make_shared<LexerCommandNameContext>(_ctx, getState());
  enterRule(_localctx, 84, ANTLRv4Parser::RuleLexerCommandName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(464);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ANTLRv4Parser::TOKEN_REF:
      case ANTLRv4Parser::RULE_REF: {
        enterOuterAlt(_localctx, 1);
        setState(462);
        identifier();
        break;
      }

      case ANTLRv4Parser::MODE: {
        enterOuterAlt(_localctx, 2);
        setState(463);
        match(ANTLRv4Parser::MODE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LexerCommandExprContext ------------------------------------------------------------------

ANTLRv4Parser::LexerCommandExprContext::LexerCommandExprContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::LexerCommandExprContext::identifier() {
  return getRuleContext<ANTLRv4Parser::IdentifierContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerCommandExprContext::INT() {
  return getToken(ANTLRv4Parser::INT, 0);
}


ssize_t ANTLRv4Parser::LexerCommandExprContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleLexerCommandExpr;
}

void ANTLRv4Parser::LexerCommandExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLexerCommandExpr(this);
}

void ANTLRv4Parser::LexerCommandExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLexerCommandExpr(this);
}


antlrcpp::Any ANTLRv4Parser::LexerCommandExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitLexerCommandExpr(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::LexerCommandExprContext> ANTLRv4Parser::lexerCommandExpr() {
  Ref<LexerCommandExprContext> _localctx = std::make_shared<LexerCommandExprContext>(_ctx, getState());
  enterRule(_localctx, 86, ANTLRv4Parser::RuleLexerCommandExpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(468);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ANTLRv4Parser::TOKEN_REF:
      case ANTLRv4Parser::RULE_REF: {
        enterOuterAlt(_localctx, 1);
        setState(466);
        identifier();
        break;
      }

      case ANTLRv4Parser::INT: {
        enterOuterAlt(_localctx, 2);
        setState(467);
        match(ANTLRv4Parser::INT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AltListContext ------------------------------------------------------------------

ANTLRv4Parser::AltListContext::AltListContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Ref<ANTLRv4Parser::AlternativeContext>> ANTLRv4Parser::AltListContext::alternative() {
  return getRuleContexts<ANTLRv4Parser::AlternativeContext>();
}

Ref<ANTLRv4Parser::AlternativeContext> ANTLRv4Parser::AltListContext::alternative(int i) {
  return getRuleContext<ANTLRv4Parser::AlternativeContext>((size_t)i);
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::AltListContext::OR() {
  return getTokens(ANTLRv4Parser::OR);
}

Ref<tree::TerminalNode> ANTLRv4Parser::AltListContext::OR(int i) {
  return getToken(ANTLRv4Parser::OR, (size_t)i);
}


ssize_t ANTLRv4Parser::AltListContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleAltList;
}

void ANTLRv4Parser::AltListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAltList(this);
}

void ANTLRv4Parser::AltListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAltList(this);
}


antlrcpp::Any ANTLRv4Parser::AltListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitAltList(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::AltListContext> ANTLRv4Parser::altList() {
  Ref<AltListContext> _localctx = std::make_shared<AltListContext>(_ctx, getState());
  enterRule(_localctx, 88, ANTLRv4Parser::RuleAltList);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(470);
    alternative();
    setState(475);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::OR) {
      setState(471);
      match(ANTLRv4Parser::OR);
      setState(472);
      alternative();
      setState(477);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AlternativeContext ------------------------------------------------------------------

ANTLRv4Parser::AlternativeContext::AlternativeContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::ElementOptionsContext> ANTLRv4Parser::AlternativeContext::elementOptions() {
  return getRuleContext<ANTLRv4Parser::ElementOptionsContext>(0);
}

std::vector<Ref<ANTLRv4Parser::ElementContext>> ANTLRv4Parser::AlternativeContext::element() {
  return getRuleContexts<ANTLRv4Parser::ElementContext>();
}

Ref<ANTLRv4Parser::ElementContext> ANTLRv4Parser::AlternativeContext::element(int i) {
  return getRuleContext<ANTLRv4Parser::ElementContext>((size_t)i);
}


ssize_t ANTLRv4Parser::AlternativeContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleAlternative;
}

void ANTLRv4Parser::AlternativeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlternative(this);
}

void ANTLRv4Parser::AlternativeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlternative(this);
}


antlrcpp::Any ANTLRv4Parser::AlternativeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitAlternative(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::AlternativeContext> ANTLRv4Parser::alternative() {
  Ref<AlternativeContext> _localctx = std::make_shared<AlternativeContext>(_ctx, getState());
  enterRule(_localctx, 90, ANTLRv4Parser::RuleAlternative);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(487);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ANTLRv4Parser::TOKEN_REF:
      case ANTLRv4Parser::RULE_REF:
      case ANTLRv4Parser::STRING_LITERAL:
      case ANTLRv4Parser::BEGIN_ACTION:
      case ANTLRv4Parser::LPAREN:
      case ANTLRv4Parser::LT:
      case ANTLRv4Parser::DOT:
      case ANTLRv4Parser::NOT: {
        enterOuterAlt(_localctx, 1);
        setState(479);

        _la = _input->LA(1);
        if (_la == ANTLRv4Parser::LT) {
          setState(478);
          elementOptions();
        }
        setState(482); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(481);
          element();
          setState(484); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while ((((_la & ~(ssize_t)0x3f) == 0) &&
          ((1ULL << _la) & ((1ULL << ANTLRv4Parser::TOKEN_REF)
          | (1ULL << ANTLRv4Parser::RULE_REF)
          | (1ULL << ANTLRv4Parser::STRING_LITERAL)
          | (1ULL << ANTLRv4Parser::BEGIN_ACTION)
          | (1ULL << ANTLRv4Parser::LPAREN)
          | (1ULL << ANTLRv4Parser::DOT)
          | (1ULL << ANTLRv4Parser::NOT))) != 0));
        break;
      }

      case ANTLRv4Parser::SEMI:
      case ANTLRv4Parser::RPAREN:
      case ANTLRv4Parser::OR:
      case ANTLRv4Parser::POUND: {
        enterOuterAlt(_localctx, 2);

        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementContext ------------------------------------------------------------------

ANTLRv4Parser::ElementContext::ElementContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::LabeledElementContext> ANTLRv4Parser::ElementContext::labeledElement() {
  return getRuleContext<ANTLRv4Parser::LabeledElementContext>(0);
}

Ref<ANTLRv4Parser::EbnfSuffixContext> ANTLRv4Parser::ElementContext::ebnfSuffix() {
  return getRuleContext<ANTLRv4Parser::EbnfSuffixContext>(0);
}

Ref<ANTLRv4Parser::AtomContext> ANTLRv4Parser::ElementContext::atom() {
  return getRuleContext<ANTLRv4Parser::AtomContext>(0);
}

Ref<ANTLRv4Parser::EbnfContext> ANTLRv4Parser::ElementContext::ebnf() {
  return getRuleContext<ANTLRv4Parser::EbnfContext>(0);
}

Ref<ANTLRv4Parser::ActionBlockContext> ANTLRv4Parser::ElementContext::actionBlock() {
  return getRuleContext<ANTLRv4Parser::ActionBlockContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ElementContext::QUESTION() {
  return getToken(ANTLRv4Parser::QUESTION, 0);
}


ssize_t ANTLRv4Parser::ElementContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleElement;
}

void ANTLRv4Parser::ElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElement(this);
}

void ANTLRv4Parser::ElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElement(this);
}


antlrcpp::Any ANTLRv4Parser::ElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitElement(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::ElementContext> ANTLRv4Parser::element() {
  Ref<ElementContext> _localctx = std::make_shared<ElementContext>(_ctx, getState());
  enterRule(_localctx, 92, ANTLRv4Parser::RuleElement);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(504);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(489);
      labeledElement();
      setState(492);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case ANTLRv4Parser::QUESTION:
        case ANTLRv4Parser::STAR:
        case ANTLRv4Parser::PLUS: {
          setState(490);
          ebnfSuffix();
          break;
        }

        case ANTLRv4Parser::TOKEN_REF:
        case ANTLRv4Parser::RULE_REF:
        case ANTLRv4Parser::STRING_LITERAL:
        case ANTLRv4Parser::BEGIN_ACTION:
        case ANTLRv4Parser::SEMI:
        case ANTLRv4Parser::LPAREN:
        case ANTLRv4Parser::RPAREN:
        case ANTLRv4Parser::OR:
        case ANTLRv4Parser::DOT:
        case ANTLRv4Parser::POUND:
        case ANTLRv4Parser::NOT: {
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(494);
      atom();
      setState(497);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case ANTLRv4Parser::QUESTION:
        case ANTLRv4Parser::STAR:
        case ANTLRv4Parser::PLUS: {
          setState(495);
          ebnfSuffix();
          break;
        }

        case ANTLRv4Parser::TOKEN_REF:
        case ANTLRv4Parser::RULE_REF:
        case ANTLRv4Parser::STRING_LITERAL:
        case ANTLRv4Parser::BEGIN_ACTION:
        case ANTLRv4Parser::SEMI:
        case ANTLRv4Parser::LPAREN:
        case ANTLRv4Parser::RPAREN:
        case ANTLRv4Parser::OR:
        case ANTLRv4Parser::DOT:
        case ANTLRv4Parser::POUND:
        case ANTLRv4Parser::NOT: {
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(499);
      ebnf();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(500);
      actionBlock();
      setState(502);

      _la = _input->LA(1);
      if (_la == ANTLRv4Parser::QUESTION) {
        setState(501);
        match(ANTLRv4Parser::QUESTION);
      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LabeledElementContext ------------------------------------------------------------------

ANTLRv4Parser::LabeledElementContext::LabeledElementContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::LabeledElementContext::identifier() {
  return getRuleContext<ANTLRv4Parser::IdentifierContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LabeledElementContext::ASSIGN() {
  return getToken(ANTLRv4Parser::ASSIGN, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LabeledElementContext::PLUS_ASSIGN() {
  return getToken(ANTLRv4Parser::PLUS_ASSIGN, 0);
}

Ref<ANTLRv4Parser::AtomContext> ANTLRv4Parser::LabeledElementContext::atom() {
  return getRuleContext<ANTLRv4Parser::AtomContext>(0);
}

Ref<ANTLRv4Parser::BlockContext> ANTLRv4Parser::LabeledElementContext::block() {
  return getRuleContext<ANTLRv4Parser::BlockContext>(0);
}


ssize_t ANTLRv4Parser::LabeledElementContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleLabeledElement;
}

void ANTLRv4Parser::LabeledElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLabeledElement(this);
}

void ANTLRv4Parser::LabeledElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLabeledElement(this);
}


antlrcpp::Any ANTLRv4Parser::LabeledElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitLabeledElement(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::LabeledElementContext> ANTLRv4Parser::labeledElement() {
  Ref<LabeledElementContext> _localctx = std::make_shared<LabeledElementContext>(_ctx, getState());
  enterRule(_localctx, 94, ANTLRv4Parser::RuleLabeledElement);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(506);
    identifier();
    setState(507);
    _la = _input->LA(1);
    if (!(_la == ANTLRv4Parser::ASSIGN

    || _la == ANTLRv4Parser::PLUS_ASSIGN)) {
    _errHandler->recoverInline(this);
    } else {
      consume();
    }
    setState(510);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ANTLRv4Parser::TOKEN_REF:
      case ANTLRv4Parser::RULE_REF:
      case ANTLRv4Parser::STRING_LITERAL:
      case ANTLRv4Parser::DOT:
      case ANTLRv4Parser::NOT: {
        setState(508);
        atom();
        break;
      }

      case ANTLRv4Parser::LPAREN: {
        setState(509);
        block();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EbnfContext ------------------------------------------------------------------

ANTLRv4Parser::EbnfContext::EbnfContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::BlockContext> ANTLRv4Parser::EbnfContext::block() {
  return getRuleContext<ANTLRv4Parser::BlockContext>(0);
}

Ref<ANTLRv4Parser::BlockSuffixContext> ANTLRv4Parser::EbnfContext::blockSuffix() {
  return getRuleContext<ANTLRv4Parser::BlockSuffixContext>(0);
}


ssize_t ANTLRv4Parser::EbnfContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleEbnf;
}

void ANTLRv4Parser::EbnfContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEbnf(this);
}

void ANTLRv4Parser::EbnfContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEbnf(this);
}


antlrcpp::Any ANTLRv4Parser::EbnfContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitEbnf(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::EbnfContext> ANTLRv4Parser::ebnf() {
  Ref<EbnfContext> _localctx = std::make_shared<EbnfContext>(_ctx, getState());
  enterRule(_localctx, 96, ANTLRv4Parser::RuleEbnf);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(512);
    block();
    setState(514);

    _la = _input->LA(1);
    if ((((_la & ~(ssize_t)0x3f) == 0) &&
      ((1ULL << _la) & ((1ULL << ANTLRv4Parser::QUESTION)
      | (1ULL << ANTLRv4Parser::STAR)
      | (1ULL << ANTLRv4Parser::PLUS))) != 0)) {
      setState(513);
      blockSuffix();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockSuffixContext ------------------------------------------------------------------

ANTLRv4Parser::BlockSuffixContext::BlockSuffixContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::EbnfSuffixContext> ANTLRv4Parser::BlockSuffixContext::ebnfSuffix() {
  return getRuleContext<ANTLRv4Parser::EbnfSuffixContext>(0);
}


ssize_t ANTLRv4Parser::BlockSuffixContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleBlockSuffix;
}

void ANTLRv4Parser::BlockSuffixContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockSuffix(this);
}

void ANTLRv4Parser::BlockSuffixContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockSuffix(this);
}


antlrcpp::Any ANTLRv4Parser::BlockSuffixContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitBlockSuffix(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::BlockSuffixContext> ANTLRv4Parser::blockSuffix() {
  Ref<BlockSuffixContext> _localctx = std::make_shared<BlockSuffixContext>(_ctx, getState());
  enterRule(_localctx, 98, ANTLRv4Parser::RuleBlockSuffix);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(516);
    ebnfSuffix();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EbnfSuffixContext ------------------------------------------------------------------

ANTLRv4Parser::EbnfSuffixContext::EbnfSuffixContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::EbnfSuffixContext::QUESTION() {
  return getTokens(ANTLRv4Parser::QUESTION);
}

Ref<tree::TerminalNode> ANTLRv4Parser::EbnfSuffixContext::QUESTION(int i) {
  return getToken(ANTLRv4Parser::QUESTION, (size_t)i);
}

Ref<tree::TerminalNode> ANTLRv4Parser::EbnfSuffixContext::STAR() {
  return getToken(ANTLRv4Parser::STAR, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::EbnfSuffixContext::PLUS() {
  return getToken(ANTLRv4Parser::PLUS, 0);
}


ssize_t ANTLRv4Parser::EbnfSuffixContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleEbnfSuffix;
}

void ANTLRv4Parser::EbnfSuffixContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEbnfSuffix(this);
}

void ANTLRv4Parser::EbnfSuffixContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEbnfSuffix(this);
}


antlrcpp::Any ANTLRv4Parser::EbnfSuffixContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitEbnfSuffix(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::EbnfSuffixContext> ANTLRv4Parser::ebnfSuffix() {
  Ref<EbnfSuffixContext> _localctx = std::make_shared<EbnfSuffixContext>(_ctx, getState());
  enterRule(_localctx, 100, ANTLRv4Parser::RuleEbnfSuffix);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(530);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ANTLRv4Parser::QUESTION: {
        enterOuterAlt(_localctx, 1);
        setState(518);
        match(ANTLRv4Parser::QUESTION);
        setState(520);

        _la = _input->LA(1);
        if (_la == ANTLRv4Parser::QUESTION) {
          setState(519);
          match(ANTLRv4Parser::QUESTION);
        }
        break;
      }

      case ANTLRv4Parser::STAR: {
        enterOuterAlt(_localctx, 2);
        setState(522);
        match(ANTLRv4Parser::STAR);
        setState(524);

        _la = _input->LA(1);
        if (_la == ANTLRv4Parser::QUESTION) {
          setState(523);
          match(ANTLRv4Parser::QUESTION);
        }
        break;
      }

      case ANTLRv4Parser::PLUS: {
        enterOuterAlt(_localctx, 3);
        setState(526);
        match(ANTLRv4Parser::PLUS);
        setState(528);

        _la = _input->LA(1);
        if (_la == ANTLRv4Parser::QUESTION) {
          setState(527);
          match(ANTLRv4Parser::QUESTION);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LexerAtomContext ------------------------------------------------------------------

ANTLRv4Parser::LexerAtomContext::LexerAtomContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::CharacterRangeContext> ANTLRv4Parser::LexerAtomContext::characterRange() {
  return getRuleContext<ANTLRv4Parser::CharacterRangeContext>(0);
}

Ref<ANTLRv4Parser::TerminalContext> ANTLRv4Parser::LexerAtomContext::terminal() {
  return getRuleContext<ANTLRv4Parser::TerminalContext>(0);
}

Ref<ANTLRv4Parser::NotSetContext> ANTLRv4Parser::LexerAtomContext::notSet() {
  return getRuleContext<ANTLRv4Parser::NotSetContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerAtomContext::LEXER_CHAR_SET() {
  return getToken(ANTLRv4Parser::LEXER_CHAR_SET, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::LexerAtomContext::DOT() {
  return getToken(ANTLRv4Parser::DOT, 0);
}

Ref<ANTLRv4Parser::ElementOptionsContext> ANTLRv4Parser::LexerAtomContext::elementOptions() {
  return getRuleContext<ANTLRv4Parser::ElementOptionsContext>(0);
}


ssize_t ANTLRv4Parser::LexerAtomContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleLexerAtom;
}

void ANTLRv4Parser::LexerAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLexerAtom(this);
}

void ANTLRv4Parser::LexerAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLexerAtom(this);
}


antlrcpp::Any ANTLRv4Parser::LexerAtomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitLexerAtom(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::LexerAtomContext> ANTLRv4Parser::lexerAtom() {
  Ref<LexerAtomContext> _localctx = std::make_shared<LexerAtomContext>(_ctx, getState());
  enterRule(_localctx, 102, ANTLRv4Parser::RuleLexerAtom);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(540);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(532);
      characterRange();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(533);
      terminal();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(534);
      notSet();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(535);
      match(ANTLRv4Parser::LEXER_CHAR_SET);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(536);
      match(ANTLRv4Parser::DOT);
      setState(538);

      _la = _input->LA(1);
      if (_la == ANTLRv4Parser::LT) {
        setState(537);
        elementOptions();
      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtomContext ------------------------------------------------------------------

ANTLRv4Parser::AtomContext::AtomContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<ANTLRv4Parser::CharacterRangeContext> ANTLRv4Parser::AtomContext::characterRange() {
  return getRuleContext<ANTLRv4Parser::CharacterRangeContext>(0);
}

Ref<ANTLRv4Parser::TerminalContext> ANTLRv4Parser::AtomContext::terminal() {
  return getRuleContext<ANTLRv4Parser::TerminalContext>(0);
}

Ref<ANTLRv4Parser::RulerefContext> ANTLRv4Parser::AtomContext::ruleref() {
  return getRuleContext<ANTLRv4Parser::RulerefContext>(0);
}

Ref<ANTLRv4Parser::NotSetContext> ANTLRv4Parser::AtomContext::notSet() {
  return getRuleContext<ANTLRv4Parser::NotSetContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::AtomContext::DOT() {
  return getToken(ANTLRv4Parser::DOT, 0);
}

Ref<ANTLRv4Parser::ElementOptionsContext> ANTLRv4Parser::AtomContext::elementOptions() {
  return getRuleContext<ANTLRv4Parser::ElementOptionsContext>(0);
}


ssize_t ANTLRv4Parser::AtomContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleAtom;
}

void ANTLRv4Parser::AtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtom(this);
}

void ANTLRv4Parser::AtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtom(this);
}


antlrcpp::Any ANTLRv4Parser::AtomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitAtom(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::AtomContext> ANTLRv4Parser::atom() {
  Ref<AtomContext> _localctx = std::make_shared<AtomContext>(_ctx, getState());
  enterRule(_localctx, 104, ANTLRv4Parser::RuleAtom);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(550);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(542);
      characterRange();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(543);
      terminal();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(544);
      ruleref();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(545);
      notSet();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(546);
      match(ANTLRv4Parser::DOT);
      setState(548);

      _la = _input->LA(1);
      if (_la == ANTLRv4Parser::LT) {
        setState(547);
        elementOptions();
      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NotSetContext ------------------------------------------------------------------

ANTLRv4Parser::NotSetContext::NotSetContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::NotSetContext::NOT() {
  return getToken(ANTLRv4Parser::NOT, 0);
}

Ref<ANTLRv4Parser::SetElementContext> ANTLRv4Parser::NotSetContext::setElement() {
  return getRuleContext<ANTLRv4Parser::SetElementContext>(0);
}

Ref<ANTLRv4Parser::BlockSetContext> ANTLRv4Parser::NotSetContext::blockSet() {
  return getRuleContext<ANTLRv4Parser::BlockSetContext>(0);
}


ssize_t ANTLRv4Parser::NotSetContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleNotSet;
}

void ANTLRv4Parser::NotSetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNotSet(this);
}

void ANTLRv4Parser::NotSetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNotSet(this);
}


antlrcpp::Any ANTLRv4Parser::NotSetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitNotSet(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::NotSetContext> ANTLRv4Parser::notSet() {
  Ref<NotSetContext> _localctx = std::make_shared<NotSetContext>(_ctx, getState());
  enterRule(_localctx, 106, ANTLRv4Parser::RuleNotSet);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(556);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(552);
      match(ANTLRv4Parser::NOT);
      setState(553);
      setElement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(554);
      match(ANTLRv4Parser::NOT);
      setState(555);
      blockSet();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockSetContext ------------------------------------------------------------------

ANTLRv4Parser::BlockSetContext::BlockSetContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::BlockSetContext::LPAREN() {
  return getToken(ANTLRv4Parser::LPAREN, 0);
}

std::vector<Ref<ANTLRv4Parser::SetElementContext>> ANTLRv4Parser::BlockSetContext::setElement() {
  return getRuleContexts<ANTLRv4Parser::SetElementContext>();
}

Ref<ANTLRv4Parser::SetElementContext> ANTLRv4Parser::BlockSetContext::setElement(int i) {
  return getRuleContext<ANTLRv4Parser::SetElementContext>((size_t)i);
}

Ref<tree::TerminalNode> ANTLRv4Parser::BlockSetContext::RPAREN() {
  return getToken(ANTLRv4Parser::RPAREN, 0);
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::BlockSetContext::OR() {
  return getTokens(ANTLRv4Parser::OR);
}

Ref<tree::TerminalNode> ANTLRv4Parser::BlockSetContext::OR(int i) {
  return getToken(ANTLRv4Parser::OR, (size_t)i);
}


ssize_t ANTLRv4Parser::BlockSetContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleBlockSet;
}

void ANTLRv4Parser::BlockSetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockSet(this);
}

void ANTLRv4Parser::BlockSetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockSet(this);
}


antlrcpp::Any ANTLRv4Parser::BlockSetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitBlockSet(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::BlockSetContext> ANTLRv4Parser::blockSet() {
  Ref<BlockSetContext> _localctx = std::make_shared<BlockSetContext>(_ctx, getState());
  enterRule(_localctx, 108, ANTLRv4Parser::RuleBlockSet);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(558);
    match(ANTLRv4Parser::LPAREN);
    setState(559);
    setElement();
    setState(564);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::OR) {
      setState(560);
      match(ANTLRv4Parser::OR);
      setState(561);
      setElement();
      setState(566);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(567);
    match(ANTLRv4Parser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SetElementContext ------------------------------------------------------------------

ANTLRv4Parser::SetElementContext::SetElementContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::SetElementContext::TOKEN_REF() {
  return getToken(ANTLRv4Parser::TOKEN_REF, 0);
}

Ref<ANTLRv4Parser::ElementOptionsContext> ANTLRv4Parser::SetElementContext::elementOptions() {
  return getRuleContext<ANTLRv4Parser::ElementOptionsContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::SetElementContext::STRING_LITERAL() {
  return getToken(ANTLRv4Parser::STRING_LITERAL, 0);
}

Ref<ANTLRv4Parser::CharacterRangeContext> ANTLRv4Parser::SetElementContext::characterRange() {
  return getRuleContext<ANTLRv4Parser::CharacterRangeContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::SetElementContext::LEXER_CHAR_SET() {
  return getToken(ANTLRv4Parser::LEXER_CHAR_SET, 0);
}


ssize_t ANTLRv4Parser::SetElementContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleSetElement;
}

void ANTLRv4Parser::SetElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSetElement(this);
}

void ANTLRv4Parser::SetElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSetElement(this);
}


antlrcpp::Any ANTLRv4Parser::SetElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitSetElement(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::SetElementContext> ANTLRv4Parser::setElement() {
  Ref<SetElementContext> _localctx = std::make_shared<SetElementContext>(_ctx, getState());
  enterRule(_localctx, 110, ANTLRv4Parser::RuleSetElement);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(579);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(569);
      match(ANTLRv4Parser::TOKEN_REF);
      setState(571);

      _la = _input->LA(1);
      if (_la == ANTLRv4Parser::LT) {
        setState(570);
        elementOptions();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(573);
      match(ANTLRv4Parser::STRING_LITERAL);
      setState(575);

      _la = _input->LA(1);
      if (_la == ANTLRv4Parser::LT) {
        setState(574);
        elementOptions();
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(577);
      characterRange();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(578);
      match(ANTLRv4Parser::LEXER_CHAR_SET);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

ANTLRv4Parser::BlockContext::BlockContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::BlockContext::LPAREN() {
  return getToken(ANTLRv4Parser::LPAREN, 0);
}

Ref<ANTLRv4Parser::AltListContext> ANTLRv4Parser::BlockContext::altList() {
  return getRuleContext<ANTLRv4Parser::AltListContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::BlockContext::RPAREN() {
  return getToken(ANTLRv4Parser::RPAREN, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::BlockContext::COLON() {
  return getToken(ANTLRv4Parser::COLON, 0);
}

Ref<ANTLRv4Parser::OptionsSpecContext> ANTLRv4Parser::BlockContext::optionsSpec() {
  return getRuleContext<ANTLRv4Parser::OptionsSpecContext>(0);
}

std::vector<Ref<ANTLRv4Parser::RuleActionContext>> ANTLRv4Parser::BlockContext::ruleAction() {
  return getRuleContexts<ANTLRv4Parser::RuleActionContext>();
}

Ref<ANTLRv4Parser::RuleActionContext> ANTLRv4Parser::BlockContext::ruleAction(int i) {
  return getRuleContext<ANTLRv4Parser::RuleActionContext>((size_t)i);
}


ssize_t ANTLRv4Parser::BlockContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleBlock;
}

void ANTLRv4Parser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void ANTLRv4Parser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


antlrcpp::Any ANTLRv4Parser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::BlockContext> ANTLRv4Parser::block() {
  Ref<BlockContext> _localctx = std::make_shared<BlockContext>(_ctx, getState());
  enterRule(_localctx, 112, ANTLRv4Parser::RuleBlock);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(581);
    match(ANTLRv4Parser::LPAREN);
    setState(592);

    _la = _input->LA(1);
    if ((((_la & ~(ssize_t)0x3f) == 0) &&
      ((1ULL << _la) & ((1ULL << ANTLRv4Parser::OPTIONS)
      | (1ULL << ANTLRv4Parser::COLON)
      | (1ULL << ANTLRv4Parser::AT))) != 0)) {
      setState(583);

      _la = _input->LA(1);
      if (_la == ANTLRv4Parser::OPTIONS) {
        setState(582);
        optionsSpec();
      }
      setState(588);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ANTLRv4Parser::AT) {
        setState(585);
        ruleAction();
        setState(590);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(591);
      match(ANTLRv4Parser::COLON);
    }
    setState(594);
    altList();
    setState(595);
    match(ANTLRv4Parser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RulerefContext ------------------------------------------------------------------

ANTLRv4Parser::RulerefContext::RulerefContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::RulerefContext::RULE_REF() {
  return getToken(ANTLRv4Parser::RULE_REF, 0);
}

Ref<ANTLRv4Parser::ArgActionBlockContext> ANTLRv4Parser::RulerefContext::argActionBlock() {
  return getRuleContext<ANTLRv4Parser::ArgActionBlockContext>(0);
}

Ref<ANTLRv4Parser::ElementOptionsContext> ANTLRv4Parser::RulerefContext::elementOptions() {
  return getRuleContext<ANTLRv4Parser::ElementOptionsContext>(0);
}


ssize_t ANTLRv4Parser::RulerefContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleRuleref;
}

void ANTLRv4Parser::RulerefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRuleref(this);
}

void ANTLRv4Parser::RulerefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRuleref(this);
}


antlrcpp::Any ANTLRv4Parser::RulerefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitRuleref(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::RulerefContext> ANTLRv4Parser::ruleref() {
  Ref<RulerefContext> _localctx = std::make_shared<RulerefContext>(_ctx, getState());
  enterRule(_localctx, 114, ANTLRv4Parser::RuleRuleref);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(597);
    match(ANTLRv4Parser::RULE_REF);
    setState(599);

    _la = _input->LA(1);
    if (_la == ANTLRv4Parser::BEGIN_ARGUMENT) {
      setState(598);
      argActionBlock();
    }
    setState(602);

    _la = _input->LA(1);
    if (_la == ANTLRv4Parser::LT) {
      setState(601);
      elementOptions();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CharacterRangeContext ------------------------------------------------------------------

ANTLRv4Parser::CharacterRangeContext::CharacterRangeContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::CharacterRangeContext::STRING_LITERAL() {
  return getTokens(ANTLRv4Parser::STRING_LITERAL);
}

Ref<tree::TerminalNode> ANTLRv4Parser::CharacterRangeContext::STRING_LITERAL(int i) {
  return getToken(ANTLRv4Parser::STRING_LITERAL, (size_t)i);
}

Ref<tree::TerminalNode> ANTLRv4Parser::CharacterRangeContext::RANGE() {
  return getToken(ANTLRv4Parser::RANGE, 0);
}


ssize_t ANTLRv4Parser::CharacterRangeContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleCharacterRange;
}

void ANTLRv4Parser::CharacterRangeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCharacterRange(this);
}

void ANTLRv4Parser::CharacterRangeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCharacterRange(this);
}


antlrcpp::Any ANTLRv4Parser::CharacterRangeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitCharacterRange(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::CharacterRangeContext> ANTLRv4Parser::characterRange() {
  Ref<CharacterRangeContext> _localctx = std::make_shared<CharacterRangeContext>(_ctx, getState());
  enterRule(_localctx, 116, ANTLRv4Parser::RuleCharacterRange);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(604);
    match(ANTLRv4Parser::STRING_LITERAL);
    setState(605);
    match(ANTLRv4Parser::RANGE);
    setState(606);
    match(ANTLRv4Parser::STRING_LITERAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TerminalContext ------------------------------------------------------------------

ANTLRv4Parser::TerminalContext::TerminalContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::TerminalContext::TOKEN_REF() {
  return getToken(ANTLRv4Parser::TOKEN_REF, 0);
}

Ref<ANTLRv4Parser::ElementOptionsContext> ANTLRv4Parser::TerminalContext::elementOptions() {
  return getRuleContext<ANTLRv4Parser::ElementOptionsContext>(0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::TerminalContext::STRING_LITERAL() {
  return getToken(ANTLRv4Parser::STRING_LITERAL, 0);
}


ssize_t ANTLRv4Parser::TerminalContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleTerminal;
}

void ANTLRv4Parser::TerminalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTerminal(this);
}

void ANTLRv4Parser::TerminalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTerminal(this);
}


antlrcpp::Any ANTLRv4Parser::TerminalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitTerminal(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::TerminalContext> ANTLRv4Parser::terminal() {
  Ref<TerminalContext> _localctx = std::make_shared<TerminalContext>(_ctx, getState());
  enterRule(_localctx, 118, ANTLRv4Parser::RuleTerminal);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(616);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ANTLRv4Parser::TOKEN_REF: {
        enterOuterAlt(_localctx, 1);
        setState(608);
        match(ANTLRv4Parser::TOKEN_REF);
        setState(610);

        _la = _input->LA(1);
        if (_la == ANTLRv4Parser::LT) {
          setState(609);
          elementOptions();
        }
        break;
      }

      case ANTLRv4Parser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(612);
        match(ANTLRv4Parser::STRING_LITERAL);
        setState(614);

        _la = _input->LA(1);
        if (_la == ANTLRv4Parser::LT) {
          setState(613);
          elementOptions();
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementOptionsContext ------------------------------------------------------------------

ANTLRv4Parser::ElementOptionsContext::ElementOptionsContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::ElementOptionsContext::LT() {
  return getToken(ANTLRv4Parser::LT, 0);
}

std::vector<Ref<ANTLRv4Parser::ElementOptionContext>> ANTLRv4Parser::ElementOptionsContext::elementOption() {
  return getRuleContexts<ANTLRv4Parser::ElementOptionContext>();
}

Ref<ANTLRv4Parser::ElementOptionContext> ANTLRv4Parser::ElementOptionsContext::elementOption(int i) {
  return getRuleContext<ANTLRv4Parser::ElementOptionContext>((size_t)i);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ElementOptionsContext::GT() {
  return getToken(ANTLRv4Parser::GT, 0);
}

std::vector<Ref<tree::TerminalNode>> ANTLRv4Parser::ElementOptionsContext::COMMA() {
  return getTokens(ANTLRv4Parser::COMMA);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ElementOptionsContext::COMMA(int i) {
  return getToken(ANTLRv4Parser::COMMA, (size_t)i);
}


ssize_t ANTLRv4Parser::ElementOptionsContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleElementOptions;
}

void ANTLRv4Parser::ElementOptionsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementOptions(this);
}

void ANTLRv4Parser::ElementOptionsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementOptions(this);
}


antlrcpp::Any ANTLRv4Parser::ElementOptionsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitElementOptions(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::ElementOptionsContext> ANTLRv4Parser::elementOptions() {
  Ref<ElementOptionsContext> _localctx = std::make_shared<ElementOptionsContext>(_ctx, getState());
  enterRule(_localctx, 120, ANTLRv4Parser::RuleElementOptions);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(618);
    match(ANTLRv4Parser::LT);
    setState(619);
    elementOption();
    setState(624);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ANTLRv4Parser::COMMA) {
      setState(620);
      match(ANTLRv4Parser::COMMA);
      setState(621);
      elementOption();
      setState(626);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(627);
    match(ANTLRv4Parser::GT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementOptionContext ------------------------------------------------------------------

ANTLRv4Parser::ElementOptionContext::ElementOptionContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Ref<ANTLRv4Parser::IdentifierContext>> ANTLRv4Parser::ElementOptionContext::identifier() {
  return getRuleContexts<ANTLRv4Parser::IdentifierContext>();
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::ElementOptionContext::identifier(int i) {
  return getRuleContext<ANTLRv4Parser::IdentifierContext>((size_t)i);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ElementOptionContext::ASSIGN() {
  return getToken(ANTLRv4Parser::ASSIGN, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::ElementOptionContext::STRING_LITERAL() {
  return getToken(ANTLRv4Parser::STRING_LITERAL, 0);
}


ssize_t ANTLRv4Parser::ElementOptionContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleElementOption;
}

void ANTLRv4Parser::ElementOptionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementOption(this);
}

void ANTLRv4Parser::ElementOptionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementOption(this);
}


antlrcpp::Any ANTLRv4Parser::ElementOptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitElementOption(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::ElementOptionContext> ANTLRv4Parser::elementOption() {
  Ref<ElementOptionContext> _localctx = std::make_shared<ElementOptionContext>(_ctx, getState());
  enterRule(_localctx, 122, ANTLRv4Parser::RuleElementOption);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(636);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 84, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(629);
      identifier();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(630);
      identifier();
      setState(631);
      match(ANTLRv4Parser::ASSIGN);
      setState(634);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case ANTLRv4Parser::TOKEN_REF:
        case ANTLRv4Parser::RULE_REF: {
          setState(632);
          identifier();
          break;
        }

        case ANTLRv4Parser::STRING_LITERAL: {
          setState(633);
          match(ANTLRv4Parser::STRING_LITERAL);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

ANTLRv4Parser::IdentifierContext::IdentifierContext(std::weak_ptr<ParserRuleContext> parent, int invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Ref<tree::TerminalNode> ANTLRv4Parser::IdentifierContext::RULE_REF() {
  return getToken(ANTLRv4Parser::RULE_REF, 0);
}

Ref<tree::TerminalNode> ANTLRv4Parser::IdentifierContext::TOKEN_REF() {
  return getToken(ANTLRv4Parser::TOKEN_REF, 0);
}


ssize_t ANTLRv4Parser::IdentifierContext::getRuleIndex() const {
  return ANTLRv4Parser::RuleIdentifier;
}

void ANTLRv4Parser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}

void ANTLRv4Parser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ANTLRv4ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}


antlrcpp::Any ANTLRv4Parser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (dynamic_cast<ANTLRv4ParserVisitor*>(visitor) != nullptr)
    return ((ANTLRv4ParserVisitor *)visitor)->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

Ref<ANTLRv4Parser::IdentifierContext> ANTLRv4Parser::identifier() {
  Ref<IdentifierContext> _localctx = std::make_shared<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 124, ANTLRv4Parser::RuleIdentifier);
  ssize_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(638);
    _la = _input->LA(1);
    if (!(_la == ANTLRv4Parser::TOKEN_REF

    || _la == ANTLRv4Parser::RULE_REF)) {
    _errHandler->recoverInline(this);
    } else {
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> ANTLRv4Parser::_decisionToDFA;
atn::PredictionContextCache ANTLRv4Parser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN ANTLRv4Parser::_atn;
std::vector<uint16_t> ANTLRv4Parser::_serializedATN;

std::vector<std::string> ANTLRv4Parser::_ruleNames = {
  "grammarSpec", "grammarType", "prequelConstruct", "optionsSpec", "option", 
  "optionValue", "delegateGrammars", "delegateGrammar", "tokensSpec", "channelsSpec", 
  "idList", "action", "actionScopeName", "actionBlock", "argActionBlock", 
  "modeSpec", "rules", "ruleSpec", "parserRuleSpec", "exceptionGroup", "exceptionHandler", 
  "finallyClause", "rulePrequel", "ruleReturns", "throwsSpec", "localsSpec", 
  "ruleAction", "ruleModifiers", "ruleModifier", "ruleBlock", "ruleAltList", 
  "labeledAlt", "lexerRuleSpec", "lexerRuleBlock", "lexerAltList", "lexerAlt", 
  "lexerElements", "lexerElement", "labeledLexerElement", "lexerBlock", 
  "lexerCommands", "lexerCommand", "lexerCommandName", "lexerCommandExpr", 
  "altList", "alternative", "element", "labeledElement", "ebnf", "blockSuffix", 
  "ebnfSuffix", "lexerAtom", "atom", "notSet", "blockSet", "setElement", 
  "block", "ruleref", "characterRange", "terminal", "elementOptions", "elementOption", 
  "identifier"
};

std::vector<std::string> ANTLRv4Parser::_literalNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "'options'", "'tokens'", 
  "'channels'", "'import'", "'fragment'", "'lexer'", "'parser'", "'grammar'", 
  "'protected'", "'public'", "'private'", "'returns'", "'locals'", "'throws'", 
  "'catch'", "'finally'", "'mode'"
};

std::vector<std::string> ANTLRv4Parser::_symbolicNames = {
  "", "TOKEN_REF", "RULE_REF", "LEXER_CHAR_SET", "DOC_COMMENT", "BLOCK_COMMENT", 
  "LINE_COMMENT", "INT", "STRING_LITERAL", "UNTERMINATED_STRING_LITERAL", 
  "BEGIN_ARGUMENT", "BEGIN_ACTION", "OPTIONS", "TOKENS", "CHANNELS", "IMPORT", 
  "FRAGMENT", "LEXER", "PARSER", "GRAMMAR", "PROTECTED", "PUBLIC", "PRIVATE", 
  "RETURNS", "LOCALS", "THROWS", "CATCH", "FINALLY", "MODE", "COLON", "COLONCOLON", 
  "COMMA", "SEMI", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "RARROW", "LT", 
  "GT", "ASSIGN", "QUESTION", "STAR", "PLUS_ASSIGN", "PLUS", "OR", "DOLLAR", 
  "RANGE", "DOT", "AT", "POUND", "NOT", "ID", "WS", "ERRCHAR", "END_ARGUMENT", 
  "UNTERMINATED_ARGUMENT", "ARGUMENT_CONTENT", "END_ACTION", "UNTERMINATED_ACTION", 
  "ACTION_CONTENT", "UNTERMINATED_CHAR_SET"
};

dfa::Vocabulary ANTLRv4Parser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> ANTLRv4Parser::_tokenNames;

ANTLRv4Parser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x430, 0xd6d1, 0x8206, 0xad2d, 0x4417, 0xaef1, 0x8d80, 0xaadd, 
    0x3, 0x3f, 0x283, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 
    0x4, 0x29, 0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 
    0x2c, 0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x4, 0x2f, 
    0x9, 0x2f, 0x4, 0x30, 0x9, 0x30, 0x4, 0x31, 0x9, 0x31, 0x4, 0x32, 0x9, 
    0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x4, 0x35, 0x9, 0x35, 
    0x4, 0x36, 0x9, 0x36, 0x4, 0x37, 0x9, 0x37, 0x4, 0x38, 0x9, 0x38, 0x4, 
    0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 0x9, 0x3b, 0x4, 0x3c, 
    0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x4, 0x3e, 0x9, 0x3e, 0x4, 0x3f, 0x9, 
    0x3f, 0x4, 0x40, 0x9, 0x40, 0x3, 0x2, 0x7, 0x2, 0x82, 0xa, 0x2, 0xc, 
    0x2, 0xe, 0x2, 0x85, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 
    0x7, 0x2, 0x8b, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x8e, 0xb, 0x2, 0x3, 0x2, 
    0x3, 0x2, 0x7, 0x2, 0x92, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x95, 0xb, 0x2, 
    0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x5, 0x3, 0x9e, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x5, 0x4, 0xa5, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x7, 0x5, 0xac, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0xaf, 0xb, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0xba, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0xbd, 
    0xb, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0xc2, 0xa, 0x7, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0xc8, 0xa, 0x8, 0xc, 0x8, 
    0xe, 0x8, 0xcb, 0xb, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0xd4, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x5, 0xa, 0xd9, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x5, 0xb, 0xe0, 0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0xe7, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0xea, 
    0xb, 0xc, 0x3, 0xc, 0x5, 0xc, 0xed, 0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x5, 0xd, 0xf3, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0xfb, 0xa, 0xe, 0x3, 0xf, 0x3, 
    0xf, 0x7, 0xf, 0xff, 0xa, 0xf, 0xc, 0xf, 0xe, 0xf, 0x102, 0xb, 0xf, 
    0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 0x7, 0x10, 0x108, 0xa, 0x10, 
    0xc, 0x10, 0xe, 0x10, 0x10b, 0xb, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x7, 0x11, 0x113, 0xa, 0x11, 0xc, 0x11, 
    0xe, 0x11, 0x116, 0xb, 0x11, 0x3, 0x12, 0x7, 0x12, 0x119, 0xa, 0x12, 
    0xc, 0x12, 0xe, 0x12, 0x11c, 0xb, 0x12, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 
    0x120, 0xa, 0x13, 0x3, 0x14, 0x7, 0x14, 0x123, 0xa, 0x14, 0xc, 0x14, 
    0xe, 0x14, 0x126, 0xb, 0x14, 0x3, 0x14, 0x5, 0x14, 0x129, 0xa, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0x12d, 0xa, 0x14, 0x3, 0x14, 0x5, 0x14, 
    0x130, 0xa, 0x14, 0x3, 0x14, 0x5, 0x14, 0x133, 0xa, 0x14, 0x3, 0x14, 
    0x5, 0x14, 0x136, 0xa, 0x14, 0x3, 0x14, 0x7, 0x14, 0x139, 0xa, 0x14, 
    0xc, 0x14, 0xe, 0x14, 0x13c, 0xb, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x7, 0x15, 0x144, 0xa, 0x15, 0xc, 0x15, 
    0xe, 0x15, 0x147, 0xb, 0x15, 0x3, 0x15, 0x5, 0x15, 0x14a, 0xa, 0x15, 
    0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x155, 0xa, 0x18, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x7, 
    0x1a, 0x15e, 0xa, 0x1a, 0xc, 0x1a, 0xe, 0x1a, 0x161, 0xb, 0x1a, 0x3, 
    0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1d, 0x6, 0x1d, 0x16b, 0xa, 0x1d, 0xd, 0x1d, 0xe, 0x1d, 0x16c, 
    0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x7, 0x20, 0x176, 0xa, 0x20, 0xc, 0x20, 0xe, 0x20, 0x179, 0xb, 
    0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x5, 0x21, 0x17e, 0xa, 0x21, 
    0x3, 0x22, 0x7, 0x22, 0x181, 0xa, 0x22, 0xc, 0x22, 0xe, 0x22, 0x184, 
    0xb, 0x22, 0x3, 0x22, 0x5, 0x22, 0x187, 0xa, 0x22, 0x3, 0x22, 0x3, 0x22, 
    0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x24, 0x3, 
    0x24, 0x3, 0x24, 0x7, 0x24, 0x193, 0xa, 0x24, 0xc, 0x24, 0xe, 0x24, 
    0x196, 0xb, 0x24, 0x3, 0x25, 0x3, 0x25, 0x5, 0x25, 0x19a, 0xa, 0x25, 
    0x3, 0x25, 0x5, 0x25, 0x19d, 0xa, 0x25, 0x3, 0x26, 0x6, 0x26, 0x1a0, 
    0xa, 0x26, 0xd, 0x26, 0xe, 0x26, 0x1a1, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 
    0x1a6, 0xa, 0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 0x1aa, 0xa, 0x27, 
    0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 0x1ae, 0xa, 0x27, 0x3, 0x27, 0x3, 0x27, 
    0x5, 0x27, 0x1b2, 0xa, 0x27, 0x5, 0x27, 0x1b4, 0xa, 0x27, 0x3, 0x28, 
    0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x5, 0x28, 0x1ba, 0xa, 0x28, 0x3, 0x29, 
    0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 
    0x2a, 0x7, 0x2a, 0x1c4, 0xa, 0x2a, 0xc, 0x2a, 0xe, 0x2a, 0x1c7, 0xb, 
    0x2a, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 
    0x5, 0x2b, 0x1cf, 0xa, 0x2b, 0x3, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x1d3, 
    0xa, 0x2c, 0x3, 0x2d, 0x3, 0x2d, 0x5, 0x2d, 0x1d7, 0xa, 0x2d, 0x3, 0x2e, 
    0x3, 0x2e, 0x3, 0x2e, 0x7, 0x2e, 0x1dc, 0xa, 0x2e, 0xc, 0x2e, 0xe, 0x2e, 
    0x1df, 0xb, 0x2e, 0x3, 0x2f, 0x5, 0x2f, 0x1e2, 0xa, 0x2f, 0x3, 0x2f, 
    0x6, 0x2f, 0x1e5, 0xa, 0x2f, 0xd, 0x2f, 0xe, 0x2f, 0x1e6, 0x3, 0x2f, 
    0x5, 0x2f, 0x1ea, 0xa, 0x2f, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x5, 0x30, 
    0x1ef, 0xa, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x5, 0x30, 0x1f4, 
    0xa, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x5, 0x30, 0x1f9, 0xa, 0x30, 
    0x5, 0x30, 0x1fb, 0xa, 0x30, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 
    0x5, 0x31, 0x201, 0xa, 0x31, 0x3, 0x32, 0x3, 0x32, 0x5, 0x32, 0x205, 
    0xa, 0x32, 0x3, 0x33, 0x3, 0x33, 0x3, 0x34, 0x3, 0x34, 0x5, 0x34, 0x20b, 
    0xa, 0x34, 0x3, 0x34, 0x3, 0x34, 0x5, 0x34, 0x20f, 0xa, 0x34, 0x3, 0x34, 
    0x3, 0x34, 0x5, 0x34, 0x213, 0xa, 0x34, 0x5, 0x34, 0x215, 0xa, 0x34, 
    0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x5, 
    0x35, 0x21d, 0xa, 0x35, 0x5, 0x35, 0x21f, 0xa, 0x35, 0x3, 0x36, 0x3, 
    0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x5, 0x36, 0x227, 
    0xa, 0x36, 0x5, 0x36, 0x229, 0xa, 0x36, 0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 
    0x3, 0x37, 0x5, 0x37, 0x22f, 0xa, 0x37, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 
    0x3, 0x38, 0x7, 0x38, 0x235, 0xa, 0x38, 0xc, 0x38, 0xe, 0x38, 0x238, 
    0xb, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x39, 0x3, 0x39, 0x5, 0x39, 0x23e, 
    0xa, 0x39, 0x3, 0x39, 0x3, 0x39, 0x5, 0x39, 0x242, 0xa, 0x39, 0x3, 0x39, 
    0x3, 0x39, 0x5, 0x39, 0x246, 0xa, 0x39, 0x3, 0x3a, 0x3, 0x3a, 0x5, 0x3a, 
    0x24a, 0xa, 0x3a, 0x3, 0x3a, 0x7, 0x3a, 0x24d, 0xa, 0x3a, 0xc, 0x3a, 
    0xe, 0x3a, 0x250, 0xb, 0x3a, 0x3, 0x3a, 0x5, 0x3a, 0x253, 0xa, 0x3a, 
    0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3b, 0x3, 0x3b, 0x5, 0x3b, 0x25a, 
    0xa, 0x3b, 0x3, 0x3b, 0x5, 0x3b, 0x25d, 0xa, 0x3b, 0x3, 0x3c, 0x3, 0x3c, 
    0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3d, 0x3, 0x3d, 0x5, 0x3d, 0x265, 0xa, 0x3d, 
    0x3, 0x3d, 0x3, 0x3d, 0x5, 0x3d, 0x269, 0xa, 0x3d, 0x5, 0x3d, 0x26b, 
    0xa, 0x3d, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x7, 0x3e, 0x271, 
    0xa, 0x3e, 0xc, 0x3e, 0xe, 0x3e, 0x274, 0xb, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 
    0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x5, 0x3f, 0x27d, 
    0xa, 0x3f, 0x5, 0x3f, 0x27f, 0xa, 0x3f, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 
    0x2, 0x2, 0x41, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 
    0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 
    0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 
    0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 
    0x5e, 0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 
    0x76, 0x78, 0x7a, 0x7c, 0x7e, 0x2, 0x5, 0x4, 0x2, 0x12, 0x12, 0x16, 
    0x18, 0x4, 0x2, 0x2a, 0x2a, 0x2d, 0x2d, 0x3, 0x2, 0x3, 0x4, 0x2ac, 0x2, 
    0x83, 0x3, 0x2, 0x2, 0x2, 0x4, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x6, 0xa4, 
    0x3, 0x2, 0x2, 0x2, 0x8, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xa, 0xb2, 0x3, 0x2, 
    0x2, 0x2, 0xc, 0xc1, 0x3, 0x2, 0x2, 0x2, 0xe, 0xc3, 0x3, 0x2, 0x2, 0x2, 
    0x10, 0xd3, 0x3, 0x2, 0x2, 0x2, 0x12, 0xd5, 0x3, 0x2, 0x2, 0x2, 0x14, 
    0xdc, 0x3, 0x2, 0x2, 0x2, 0x16, 0xe3, 0x3, 0x2, 0x2, 0x2, 0x18, 0xee, 
    0x3, 0x2, 0x2, 0x2, 0x1a, 0xfa, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xfc, 0x3, 
    0x2, 0x2, 0x2, 0x1e, 0x105, 0x3, 0x2, 0x2, 0x2, 0x20, 0x10e, 0x3, 0x2, 
    0x2, 0x2, 0x22, 0x11a, 0x3, 0x2, 0x2, 0x2, 0x24, 0x11f, 0x3, 0x2, 0x2, 
    0x2, 0x26, 0x124, 0x3, 0x2, 0x2, 0x2, 0x28, 0x145, 0x3, 0x2, 0x2, 0x2, 
    0x2a, 0x14b, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x14f, 0x3, 0x2, 0x2, 0x2, 0x2e, 
    0x154, 0x3, 0x2, 0x2, 0x2, 0x30, 0x156, 0x3, 0x2, 0x2, 0x2, 0x32, 0x159, 
    0x3, 0x2, 0x2, 0x2, 0x34, 0x162, 0x3, 0x2, 0x2, 0x2, 0x36, 0x165, 0x3, 
    0x2, 0x2, 0x2, 0x38, 0x16a, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x16e, 0x3, 0x2, 
    0x2, 0x2, 0x3c, 0x170, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x172, 0x3, 0x2, 0x2, 
    0x2, 0x40, 0x17a, 0x3, 0x2, 0x2, 0x2, 0x42, 0x182, 0x3, 0x2, 0x2, 0x2, 
    0x44, 0x18d, 0x3, 0x2, 0x2, 0x2, 0x46, 0x18f, 0x3, 0x2, 0x2, 0x2, 0x48, 
    0x19c, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x19f, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x1b3, 
    0x3, 0x2, 0x2, 0x2, 0x4e, 0x1b5, 0x3, 0x2, 0x2, 0x2, 0x50, 0x1bb, 0x3, 
    0x2, 0x2, 0x2, 0x52, 0x1bf, 0x3, 0x2, 0x2, 0x2, 0x54, 0x1ce, 0x3, 0x2, 
    0x2, 0x2, 0x56, 0x1d2, 0x3, 0x2, 0x2, 0x2, 0x58, 0x1d6, 0x3, 0x2, 0x2, 
    0x2, 0x5a, 0x1d8, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x1e9, 0x3, 0x2, 0x2, 0x2, 
    0x5e, 0x1fa, 0x3, 0x2, 0x2, 0x2, 0x60, 0x1fc, 0x3, 0x2, 0x2, 0x2, 0x62, 
    0x202, 0x3, 0x2, 0x2, 0x2, 0x64, 0x206, 0x3, 0x2, 0x2, 0x2, 0x66, 0x214, 
    0x3, 0x2, 0x2, 0x2, 0x68, 0x21e, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x228, 0x3, 
    0x2, 0x2, 0x2, 0x6c, 0x22e, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x230, 0x3, 0x2, 
    0x2, 0x2, 0x70, 0x245, 0x3, 0x2, 0x2, 0x2, 0x72, 0x247, 0x3, 0x2, 0x2, 
    0x2, 0x74, 0x257, 0x3, 0x2, 0x2, 0x2, 0x76, 0x25e, 0x3, 0x2, 0x2, 0x2, 
    0x78, 0x26a, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x26c, 0x3, 0x2, 0x2, 0x2, 0x7c, 
    0x27e, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x280, 0x3, 0x2, 0x2, 0x2, 0x80, 0x82, 
    0x7, 0x6, 0x2, 0x2, 0x81, 0x80, 0x3, 0x2, 0x2, 0x2, 0x82, 0x85, 0x3, 
    0x2, 0x2, 0x2, 0x83, 0x81, 0x3, 0x2, 0x2, 0x2, 0x83, 0x84, 0x3, 0x2, 
    0x2, 0x2, 0x84, 0x86, 0x3, 0x2, 0x2, 0x2, 0x85, 0x83, 0x3, 0x2, 0x2, 
    0x2, 0x86, 0x87, 0x5, 0x4, 0x3, 0x2, 0x87, 0x88, 0x5, 0x7e, 0x40, 0x2, 
    0x88, 0x8c, 0x7, 0x22, 0x2, 0x2, 0x89, 0x8b, 0x5, 0x6, 0x4, 0x2, 0x8a, 
    0x89, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8a, 
    0x3, 0x2, 0x2, 0x2, 0x8c, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x8f, 0x3, 
    0x2, 0x2, 0x2, 0x8e, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x93, 0x5, 0x22, 
    0x12, 0x2, 0x90, 0x92, 0x5, 0x20, 0x11, 0x2, 0x91, 0x90, 0x3, 0x2, 0x2, 
    0x2, 0x92, 0x95, 0x3, 0x2, 0x2, 0x2, 0x93, 0x91, 0x3, 0x2, 0x2, 0x2, 
    0x93, 0x94, 0x3, 0x2, 0x2, 0x2, 0x94, 0x96, 0x3, 0x2, 0x2, 0x2, 0x95, 
    0x93, 0x3, 0x2, 0x2, 0x2, 0x96, 0x97, 0x7, 0x2, 0x2, 0x3, 0x97, 0x3, 
    0x3, 0x2, 0x2, 0x2, 0x98, 0x99, 0x7, 0x13, 0x2, 0x2, 0x99, 0x9e, 0x7, 
    0x15, 0x2, 0x2, 0x9a, 0x9b, 0x7, 0x14, 0x2, 0x2, 0x9b, 0x9e, 0x7, 0x15, 
    0x2, 0x2, 0x9c, 0x9e, 0x7, 0x15, 0x2, 0x2, 0x9d, 0x98, 0x3, 0x2, 0x2, 
    0x2, 0x9d, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x9c, 0x3, 0x2, 0x2, 0x2, 
    0x9e, 0x5, 0x3, 0x2, 0x2, 0x2, 0x9f, 0xa5, 0x5, 0x8, 0x5, 0x2, 0xa0, 
    0xa5, 0x5, 0xe, 0x8, 0x2, 0xa1, 0xa5, 0x5, 0x12, 0xa, 0x2, 0xa2, 0xa5, 
    0x5, 0x14, 0xb, 0x2, 0xa3, 0xa5, 0x5, 0x18, 0xd, 0x2, 0xa4, 0x9f, 0x3, 
    0x2, 0x2, 0x2, 0xa4, 0xa0, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa1, 0x3, 0x2, 
    0x2, 0x2, 0xa4, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa3, 0x3, 0x2, 0x2, 
    0x2, 0xa5, 0x7, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa7, 0x7, 0xe, 0x2, 0x2, 
    0xa7, 0xad, 0x7, 0x25, 0x2, 0x2, 0xa8, 0xa9, 0x5, 0xa, 0x6, 0x2, 0xa9, 
    0xaa, 0x7, 0x22, 0x2, 0x2, 0xaa, 0xac, 0x3, 0x2, 0x2, 0x2, 0xab, 0xa8, 
    0x3, 0x2, 0x2, 0x2, 0xac, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xad, 0xab, 0x3, 
    0x2, 0x2, 0x2, 0xad, 0xae, 0x3, 0x2, 0x2, 0x2, 0xae, 0xb0, 0x3, 0x2, 
    0x2, 0x2, 0xaf, 0xad, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xb1, 0x7, 0x26, 0x2, 
    0x2, 0xb1, 0x9, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xb3, 0x5, 0x7e, 0x40, 0x2, 
    0xb3, 0xb4, 0x7, 0x2a, 0x2, 0x2, 0xb4, 0xb5, 0x5, 0xc, 0x7, 0x2, 0xb5, 
    0xb, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xbb, 0x5, 0x7e, 0x40, 0x2, 0xb7, 0xb8, 
    0x7, 0x32, 0x2, 0x2, 0xb8, 0xba, 0x5, 0x7e, 0x40, 0x2, 0xb9, 0xb7, 0x3, 
    0x2, 0x2, 0x2, 0xba, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xbb, 0xb9, 0x3, 0x2, 
    0x2, 0x2, 0xbb, 0xbc, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xc2, 0x3, 0x2, 0x2, 
    0x2, 0xbd, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xc2, 0x7, 0xa, 0x2, 0x2, 
    0xbf, 0xc2, 0x5, 0x1c, 0xf, 0x2, 0xc0, 0xc2, 0x7, 0x9, 0x2, 0x2, 0xc1, 
    0xb6, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xbe, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xbf, 
    0x3, 0x2, 0x2, 0x2, 0xc1, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xc2, 0xd, 0x3, 
    0x2, 0x2, 0x2, 0xc3, 0xc4, 0x7, 0x11, 0x2, 0x2, 0xc4, 0xc9, 0x5, 0x10, 
    0x9, 0x2, 0xc5, 0xc6, 0x7, 0x21, 0x2, 0x2, 0xc6, 0xc8, 0x5, 0x10, 0x9, 
    0x2, 0xc7, 0xc5, 0x3, 0x2, 0x2, 0x2, 0xc8, 0xcb, 0x3, 0x2, 0x2, 0x2, 
    0xc9, 0xc7, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xca, 0x3, 0x2, 0x2, 0x2, 0xca, 
    0xcc, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xc9, 0x3, 0x2, 0x2, 0x2, 0xcc, 0xcd, 
    0x7, 0x22, 0x2, 0x2, 0xcd, 0xf, 0x3, 0x2, 0x2, 0x2, 0xce, 0xcf, 0x5, 
    0x7e, 0x40, 0x2, 0xcf, 0xd0, 0x7, 0x2a, 0x2, 0x2, 0xd0, 0xd1, 0x5, 0x7e, 
    0x40, 0x2, 0xd1, 0xd4, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd4, 0x5, 0x7e, 0x40, 
    0x2, 0xd3, 0xce, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd2, 0x3, 0x2, 0x2, 0x2, 
    0xd4, 0x11, 0x3, 0x2, 0x2, 0x2, 0xd5, 0xd6, 0x7, 0xf, 0x2, 0x2, 0xd6, 
    0xd8, 0x7, 0x25, 0x2, 0x2, 0xd7, 0xd9, 0x5, 0x16, 0xc, 0x2, 0xd8, 0xd7, 
    0x3, 0x2, 0x2, 0x2, 0xd8, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xda, 0x3, 
    0x2, 0x2, 0x2, 0xda, 0xdb, 0x7, 0x26, 0x2, 0x2, 0xdb, 0x13, 0x3, 0x2, 
    0x2, 0x2, 0xdc, 0xdd, 0x7, 0x10, 0x2, 0x2, 0xdd, 0xdf, 0x7, 0x25, 0x2, 
    0x2, 0xde, 0xe0, 0x5, 0x16, 0xc, 0x2, 0xdf, 0xde, 0x3, 0x2, 0x2, 0x2, 
    0xdf, 0xe0, 0x3, 0x2, 0x2, 0x2, 0xe0, 0xe1, 0x3, 0x2, 0x2, 0x2, 0xe1, 
    0xe2, 0x7, 0x26, 0x2, 0x2, 0xe2, 0x15, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xe8, 
    0x5, 0x7e, 0x40, 0x2, 0xe4, 0xe5, 0x7, 0x21, 0x2, 0x2, 0xe5, 0xe7, 0x5, 
    0x7e, 0x40, 0x2, 0xe6, 0xe4, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xea, 0x3, 0x2, 
    0x2, 0x2, 0xe8, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xe8, 0xe9, 0x3, 0x2, 0x2, 
    0x2, 0xe9, 0xec, 0x3, 0x2, 0x2, 0x2, 0xea, 0xe8, 0x3, 0x2, 0x2, 0x2, 
    0xeb, 0xed, 0x7, 0x21, 0x2, 0x2, 0xec, 0xeb, 0x3, 0x2, 0x2, 0x2, 0xec, 
    0xed, 0x3, 0x2, 0x2, 0x2, 0xed, 0x17, 0x3, 0x2, 0x2, 0x2, 0xee, 0xf2, 
    0x7, 0x33, 0x2, 0x2, 0xef, 0xf0, 0x5, 0x1a, 0xe, 0x2, 0xf0, 0xf1, 0x7, 
    0x20, 0x2, 0x2, 0xf1, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xef, 0x3, 0x2, 
    0x2, 0x2, 0xf2, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xf3, 0xf4, 0x3, 0x2, 0x2, 
    0x2, 0xf4, 0xf5, 0x5, 0x7e, 0x40, 0x2, 0xf5, 0xf6, 0x5, 0x1c, 0xf, 0x2, 
    0xf6, 0x19, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xfb, 0x5, 0x7e, 0x40, 0x2, 0xf8, 
    0xfb, 0x7, 0x13, 0x2, 0x2, 0xf9, 0xfb, 0x7, 0x14, 0x2, 0x2, 0xfa, 0xf7, 
    0x3, 0x2, 0x2, 0x2, 0xfa, 0xf8, 0x3, 0x2, 0x2, 0x2, 0xfa, 0xf9, 0x3, 
    0x2, 0x2, 0x2, 0xfb, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xfc, 0x100, 0x7, 0xd, 
    0x2, 0x2, 0xfd, 0xff, 0x7, 0x3e, 0x2, 0x2, 0xfe, 0xfd, 0x3, 0x2, 0x2, 
    0x2, 0xff, 0x102, 0x3, 0x2, 0x2, 0x2, 0x100, 0xfe, 0x3, 0x2, 0x2, 0x2, 
    0x100, 0x101, 0x3, 0x2, 0x2, 0x2, 0x101, 0x103, 0x3, 0x2, 0x2, 0x2, 
    0x102, 0x100, 0x3, 0x2, 0x2, 0x2, 0x103, 0x104, 0x7, 0x3c, 0x2, 0x2, 
    0x104, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x105, 0x109, 0x7, 0xc, 0x2, 0x2, 0x106, 
    0x108, 0x7, 0x3b, 0x2, 0x2, 0x107, 0x106, 0x3, 0x2, 0x2, 0x2, 0x108, 
    0x10b, 0x3, 0x2, 0x2, 0x2, 0x109, 0x107, 0x3, 0x2, 0x2, 0x2, 0x109, 
    0x10a, 0x3, 0x2, 0x2, 0x2, 0x10a, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x10b, 
    0x109, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x10d, 0x7, 0x39, 0x2, 0x2, 0x10d, 
    0x1f, 0x3, 0x2, 0x2, 0x2, 0x10e, 0x10f, 0x7, 0x1e, 0x2, 0x2, 0x10f, 
    0x110, 0x5, 0x7e, 0x40, 0x2, 0x110, 0x114, 0x7, 0x22, 0x2, 0x2, 0x111, 
    0x113, 0x5, 0x42, 0x22, 0x2, 0x112, 0x111, 0x3, 0x2, 0x2, 0x2, 0x113, 
    0x116, 0x3, 0x2, 0x2, 0x2, 0x114, 0x112, 0x3, 0x2, 0x2, 0x2, 0x114, 
    0x115, 0x3, 0x2, 0x2, 0x2, 0x115, 0x21, 0x3, 0x2, 0x2, 0x2, 0x116, 0x114, 
    0x3, 0x2, 0x2, 0x2, 0x117, 0x119, 0x5, 0x24, 0x13, 0x2, 0x118, 0x117, 
    0x3, 0x2, 0x2, 0x2, 0x119, 0x11c, 0x3, 0x2, 0x2, 0x2, 0x11a, 0x118, 
    0x3, 0x2, 0x2, 0x2, 0x11a, 0x11b, 0x3, 0x2, 0x2, 0x2, 0x11b, 0x23, 0x3, 
    0x2, 0x2, 0x2, 0x11c, 0x11a, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x120, 0x5, 
    0x26, 0x14, 0x2, 0x11e, 0x120, 0x5, 0x42, 0x22, 0x2, 0x11f, 0x11d, 0x3, 
    0x2, 0x2, 0x2, 0x11f, 0x11e, 0x3, 0x2, 0x2, 0x2, 0x120, 0x25, 0x3, 0x2, 
    0x2, 0x2, 0x121, 0x123, 0x7, 0x6, 0x2, 0x2, 0x122, 0x121, 0x3, 0x2, 
    0x2, 0x2, 0x123, 0x126, 0x3, 0x2, 0x2, 0x2, 0x124, 0x122, 0x3, 0x2, 
    0x2, 0x2, 0x124, 0x125, 0x3, 0x2, 0x2, 0x2, 0x125, 0x128, 0x3, 0x2, 
    0x2, 0x2, 0x126, 0x124, 0x3, 0x2, 0x2, 0x2, 0x127, 0x129, 0x5, 0x38, 
    0x1d, 0x2, 0x128, 0x127, 0x3, 0x2, 0x2, 0x2, 0x128, 0x129, 0x3, 0x2, 
    0x2, 0x2, 0x129, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x12c, 0x7, 0x4, 
    0x2, 0x2, 0x12b, 0x12d, 0x5, 0x1e, 0x10, 0x2, 0x12c, 0x12b, 0x3, 0x2, 
    0x2, 0x2, 0x12c, 0x12d, 0x3, 0x2, 0x2, 0x2, 0x12d, 0x12f, 0x3, 0x2, 
    0x2, 0x2, 0x12e, 0x130, 0x5, 0x30, 0x19, 0x2, 0x12f, 0x12e, 0x3, 0x2, 
    0x2, 0x2, 0x12f, 0x130, 0x3, 0x2, 0x2, 0x2, 0x130, 0x132, 0x3, 0x2, 
    0x2, 0x2, 0x131, 0x133, 0x5, 0x32, 0x1a, 0x2, 0x132, 0x131, 0x3, 0x2, 
    0x2, 0x2, 0x132, 0x133, 0x3, 0x2, 0x2, 0x2, 0x133, 0x135, 0x3, 0x2, 
    0x2, 0x2, 0x134, 0x136, 0x5, 0x34, 0x1b, 0x2, 0x135, 0x134, 0x3, 0x2, 
    0x2, 0x2, 0x135, 0x136, 0x3, 0x2, 0x2, 0x2, 0x136, 0x13a, 0x3, 0x2, 
    0x2, 0x2, 0x137, 0x139, 0x5, 0x2e, 0x18, 0x2, 0x138, 0x137, 0x3, 0x2, 
    0x2, 0x2, 0x139, 0x13c, 0x3, 0x2, 0x2, 0x2, 0x13a, 0x138, 0x3, 0x2, 
    0x2, 0x2, 0x13a, 0x13b, 0x3, 0x2, 0x2, 0x2, 0x13b, 0x13d, 0x3, 0x2, 
    0x2, 0x2, 0x13c, 0x13a, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x13e, 0x7, 0x1f, 
    0x2, 0x2, 0x13e, 0x13f, 0x5, 0x3c, 0x1f, 0x2, 0x13f, 0x140, 0x7, 0x22, 
    0x2, 0x2, 0x140, 0x141, 0x5, 0x28, 0x15, 0x2, 0x141, 0x27, 0x3, 0x2, 
    0x2, 0x2, 0x142, 0x144, 0x5, 0x2a, 0x16, 0x2, 0x143, 0x142, 0x3, 0x2, 
    0x2, 0x2, 0x144, 0x147, 0x3, 0x2, 0x2, 0x2, 0x145, 0x143, 0x3, 0x2, 
    0x2, 0x2, 0x145, 0x146, 0x3, 0x2, 0x2, 0x2, 0x146, 0x149, 0x3, 0x2, 
    0x2, 0x2, 0x147, 0x145, 0x3, 0x2, 0x2, 0x2, 0x148, 0x14a, 0x5, 0x2c, 
    0x17, 0x2, 0x149, 0x148, 0x3, 0x2, 0x2, 0x2, 0x149, 0x14a, 0x3, 0x2, 
    0x2, 0x2, 0x14a, 0x29, 0x3, 0x2, 0x2, 0x2, 0x14b, 0x14c, 0x7, 0x1c, 
    0x2, 0x2, 0x14c, 0x14d, 0x5, 0x1e, 0x10, 0x2, 0x14d, 0x14e, 0x5, 0x1c, 
    0xf, 0x2, 0x14e, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x14f, 0x150, 0x7, 0x1d, 
    0x2, 0x2, 0x150, 0x151, 0x5, 0x1c, 0xf, 0x2, 0x151, 0x2d, 0x3, 0x2, 
    0x2, 0x2, 0x152, 0x155, 0x5, 0x8, 0x5, 0x2, 0x153, 0x155, 0x5, 0x36, 
    0x1c, 0x2, 0x154, 0x152, 0x3, 0x2, 0x2, 0x2, 0x154, 0x153, 0x3, 0x2, 
    0x2, 0x2, 0x155, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x156, 0x157, 0x7, 0x19, 
    0x2, 0x2, 0x157, 0x158, 0x5, 0x1e, 0x10, 0x2, 0x158, 0x31, 0x3, 0x2, 
    0x2, 0x2, 0x159, 0x15a, 0x7, 0x1b, 0x2, 0x2, 0x15a, 0x15f, 0x5, 0x7e, 
    0x40, 0x2, 0x15b, 0x15c, 0x7, 0x21, 0x2, 0x2, 0x15c, 0x15e, 0x5, 0x7e, 
    0x40, 0x2, 0x15d, 0x15b, 0x3, 0x2, 0x2, 0x2, 0x15e, 0x161, 0x3, 0x2, 
    0x2, 0x2, 0x15f, 0x15d, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x160, 0x3, 0x2, 
    0x2, 0x2, 0x160, 0x33, 0x3, 0x2, 0x2, 0x2, 0x161, 0x15f, 0x3, 0x2, 0x2, 
    0x2, 0x162, 0x163, 0x7, 0x1a, 0x2, 0x2, 0x163, 0x164, 0x5, 0x1e, 0x10, 
    0x2, 0x164, 0x35, 0x3, 0x2, 0x2, 0x2, 0x165, 0x166, 0x7, 0x33, 0x2, 
    0x2, 0x166, 0x167, 0x5, 0x7e, 0x40, 0x2, 0x167, 0x168, 0x5, 0x1c, 0xf, 
    0x2, 0x168, 0x37, 0x3, 0x2, 0x2, 0x2, 0x169, 0x16b, 0x5, 0x3a, 0x1e, 
    0x2, 0x16a, 0x169, 0x3, 0x2, 0x2, 0x2, 0x16b, 0x16c, 0x3, 0x2, 0x2, 
    0x2, 0x16c, 0x16a, 0x3, 0x2, 0x2, 0x2, 0x16c, 0x16d, 0x3, 0x2, 0x2, 
    0x2, 0x16d, 0x39, 0x3, 0x2, 0x2, 0x2, 0x16e, 0x16f, 0x9, 0x2, 0x2, 0x2, 
    0x16f, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x170, 0x171, 0x5, 0x3e, 0x20, 0x2, 
    0x171, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x172, 0x177, 0x5, 0x40, 0x21, 0x2, 
    0x173, 0x174, 0x7, 0x2f, 0x2, 0x2, 0x174, 0x176, 0x5, 0x40, 0x21, 0x2, 
    0x175, 0x173, 0x3, 0x2, 0x2, 0x2, 0x176, 0x179, 0x3, 0x2, 0x2, 0x2, 
    0x177, 0x175, 0x3, 0x2, 0x2, 0x2, 0x177, 0x178, 0x3, 0x2, 0x2, 0x2, 
    0x178, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x179, 0x177, 0x3, 0x2, 0x2, 0x2, 0x17a, 
    0x17d, 0x5, 0x5c, 0x2f, 0x2, 0x17b, 0x17c, 0x7, 0x34, 0x2, 0x2, 0x17c, 
    0x17e, 0x5, 0x7e, 0x40, 0x2, 0x17d, 0x17b, 0x3, 0x2, 0x2, 0x2, 0x17d, 
    0x17e, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x41, 0x3, 0x2, 0x2, 0x2, 0x17f, 0x181, 
    0x7, 0x6, 0x2, 0x2, 0x180, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x181, 0x184, 
    0x3, 0x2, 0x2, 0x2, 0x182, 0x180, 0x3, 0x2, 0x2, 0x2, 0x182, 0x183, 
    0x3, 0x2, 0x2, 0x2, 0x183, 0x186, 0x3, 0x2, 0x2, 0x2, 0x184, 0x182, 
    0x3, 0x2, 0x2, 0x2, 0x185, 0x187, 0x7, 0x12, 0x2, 0x2, 0x186, 0x185, 
    0x3, 0x2, 0x2, 0x2, 0x186, 0x187, 0x3, 0x2, 0x2, 0x2, 0x187, 0x188, 
    0x3, 0x2, 0x2, 0x2, 0x188, 0x189, 0x7, 0x3, 0x2, 0x2, 0x189, 0x18a, 
    0x7, 0x1f, 0x2, 0x2, 0x18a, 0x18b, 0x5, 0x44, 0x23, 0x2, 0x18b, 0x18c, 
    0x7, 0x22, 0x2, 0x2, 0x18c, 0x43, 0x3, 0x2, 0x2, 0x2, 0x18d, 0x18e, 
    0x5, 0x46, 0x24, 0x2, 0x18e, 0x45, 0x3, 0x2, 0x2, 0x2, 0x18f, 0x194, 
    0x5, 0x48, 0x25, 0x2, 0x190, 0x191, 0x7, 0x2f, 0x2, 0x2, 0x191, 0x193, 
    0x5, 0x48, 0x25, 0x2, 0x192, 0x190, 0x3, 0x2, 0x2, 0x2, 0x193, 0x196, 
    0x3, 0x2, 0x2, 0x2, 0x194, 0x192, 0x3, 0x2, 0x2, 0x2, 0x194, 0x195, 
    0x3, 0x2, 0x2, 0x2, 0x195, 0x47, 0x3, 0x2, 0x2, 0x2, 0x196, 0x194, 0x3, 
    0x2, 0x2, 0x2, 0x197, 0x199, 0x5, 0x4a, 0x26, 0x2, 0x198, 0x19a, 0x5, 
    0x52, 0x2a, 0x2, 0x199, 0x198, 0x3, 0x2, 0x2, 0x2, 0x199, 0x19a, 0x3, 
    0x2, 0x2, 0x2, 0x19a, 0x19d, 0x3, 0x2, 0x2, 0x2, 0x19b, 0x19d, 0x3, 
    0x2, 0x2, 0x2, 0x19c, 0x197, 0x3, 0x2, 0x2, 0x2, 0x19c, 0x19b, 0x3, 
    0x2, 0x2, 0x2, 0x19d, 0x49, 0x3, 0x2, 0x2, 0x2, 0x19e, 0x1a0, 0x5, 0x4c, 
    0x27, 0x2, 0x19f, 0x19e, 0x3, 0x2, 0x2, 0x2, 0x1a0, 0x1a1, 0x3, 0x2, 
    0x2, 0x2, 0x1a1, 0x19f, 0x3, 0x2, 0x2, 0x2, 0x1a1, 0x1a2, 0x3, 0x2, 
    0x2, 0x2, 0x1a2, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x1a3, 0x1a5, 0x5, 0x4e, 
    0x28, 0x2, 0x1a4, 0x1a6, 0x5, 0x66, 0x34, 0x2, 0x1a5, 0x1a4, 0x3, 0x2, 
    0x2, 0x2, 0x1a5, 0x1a6, 0x3, 0x2, 0x2, 0x2, 0x1a6, 0x1b4, 0x3, 0x2, 
    0x2, 0x2, 0x1a7, 0x1a9, 0x5, 0x68, 0x35, 0x2, 0x1a8, 0x1aa, 0x5, 0x66, 
    0x34, 0x2, 0x1a9, 0x1a8, 0x3, 0x2, 0x2, 0x2, 0x1a9, 0x1aa, 0x3, 0x2, 
    0x2, 0x2, 0x1aa, 0x1b4, 0x3, 0x2, 0x2, 0x2, 0x1ab, 0x1ad, 0x5, 0x50, 
    0x29, 0x2, 0x1ac, 0x1ae, 0x5, 0x66, 0x34, 0x2, 0x1ad, 0x1ac, 0x3, 0x2, 
    0x2, 0x2, 0x1ad, 0x1ae, 0x3, 0x2, 0x2, 0x2, 0x1ae, 0x1b4, 0x3, 0x2, 
    0x2, 0x2, 0x1af, 0x1b1, 0x5, 0x1c, 0xf, 0x2, 0x1b0, 0x1b2, 0x7, 0x2b, 
    0x2, 0x2, 0x1b1, 0x1b0, 0x3, 0x2, 0x2, 0x2, 0x1b1, 0x1b2, 0x3, 0x2, 
    0x2, 0x2, 0x1b2, 0x1b4, 0x3, 0x2, 0x2, 0x2, 0x1b3, 0x1a3, 0x3, 0x2, 
    0x2, 0x2, 0x1b3, 0x1a7, 0x3, 0x2, 0x2, 0x2, 0x1b3, 0x1ab, 0x3, 0x2, 
    0x2, 0x2, 0x1b3, 0x1af, 0x3, 0x2, 0x2, 0x2, 0x1b4, 0x4d, 0x3, 0x2, 0x2, 
    0x2, 0x1b5, 0x1b6, 0x5, 0x7e, 0x40, 0x2, 0x1b6, 0x1b9, 0x9, 0x3, 0x2, 
    0x2, 0x1b7, 0x1ba, 0x5, 0x68, 0x35, 0x2, 0x1b8, 0x1ba, 0x5, 0x72, 0x3a, 
    0x2, 0x1b9, 0x1b7, 0x3, 0x2, 0x2, 0x2, 0x1b9, 0x1b8, 0x3, 0x2, 0x2, 
    0x2, 0x1ba, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x1bb, 0x1bc, 0x7, 0x23, 0x2, 
    0x2, 0x1bc, 0x1bd, 0x5, 0x46, 0x24, 0x2, 0x1bd, 0x1be, 0x7, 0x24, 0x2, 
    0x2, 0x1be, 0x51, 0x3, 0x2, 0x2, 0x2, 0x1bf, 0x1c0, 0x7, 0x27, 0x2, 
    0x2, 0x1c0, 0x1c5, 0x5, 0x54, 0x2b, 0x2, 0x1c1, 0x1c2, 0x7, 0x21, 0x2, 
    0x2, 0x1c2, 0x1c4, 0x5, 0x54, 0x2b, 0x2, 0x1c3, 0x1c1, 0x3, 0x2, 0x2, 
    0x2, 0x1c4, 0x1c7, 0x3, 0x2, 0x2, 0x2, 0x1c5, 0x1c3, 0x3, 0x2, 0x2, 
    0x2, 0x1c5, 0x1c6, 0x3, 0x2, 0x2, 0x2, 0x1c6, 0x53, 0x3, 0x2, 0x2, 0x2, 
    0x1c7, 0x1c5, 0x3, 0x2, 0x2, 0x2, 0x1c8, 0x1c9, 0x5, 0x56, 0x2c, 0x2, 
    0x1c9, 0x1ca, 0x7, 0x23, 0x2, 0x2, 0x1ca, 0x1cb, 0x5, 0x58, 0x2d, 0x2, 
    0x1cb, 0x1cc, 0x7, 0x24, 0x2, 0x2, 0x1cc, 0x1cf, 0x3, 0x2, 0x2, 0x2, 
    0x1cd, 0x1cf, 0x5, 0x56, 0x2c, 0x2, 0x1ce, 0x1c8, 0x3, 0x2, 0x2, 0x2, 
    0x1ce, 0x1cd, 0x3, 0x2, 0x2, 0x2, 0x1cf, 0x55, 0x3, 0x2, 0x2, 0x2, 0x1d0, 
    0x1d3, 0x5, 0x7e, 0x40, 0x2, 0x1d1, 0x1d3, 0x7, 0x1e, 0x2, 0x2, 0x1d2, 
    0x1d0, 0x3, 0x2, 0x2, 0x2, 0x1d2, 0x1d1, 0x3, 0x2, 0x2, 0x2, 0x1d3, 
    0x57, 0x3, 0x2, 0x2, 0x2, 0x1d4, 0x1d7, 0x5, 0x7e, 0x40, 0x2, 0x1d5, 
    0x1d7, 0x7, 0x9, 0x2, 0x2, 0x1d6, 0x1d4, 0x3, 0x2, 0x2, 0x2, 0x1d6, 
    0x1d5, 0x3, 0x2, 0x2, 0x2, 0x1d7, 0x59, 0x3, 0x2, 0x2, 0x2, 0x1d8, 0x1dd, 
    0x5, 0x5c, 0x2f, 0x2, 0x1d9, 0x1da, 0x7, 0x2f, 0x2, 0x2, 0x1da, 0x1dc, 
    0x5, 0x5c, 0x2f, 0x2, 0x1db, 0x1d9, 0x3, 0x2, 0x2, 0x2, 0x1dc, 0x1df, 
    0x3, 0x2, 0x2, 0x2, 0x1dd, 0x1db, 0x3, 0x2, 0x2, 0x2, 0x1dd, 0x1de, 
    0x3, 0x2, 0x2, 0x2, 0x1de, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x1df, 0x1dd, 0x3, 
    0x2, 0x2, 0x2, 0x1e0, 0x1e2, 0x5, 0x7a, 0x3e, 0x2, 0x1e1, 0x1e0, 0x3, 
    0x2, 0x2, 0x2, 0x1e1, 0x1e2, 0x3, 0x2, 0x2, 0x2, 0x1e2, 0x1e4, 0x3, 
    0x2, 0x2, 0x2, 0x1e3, 0x1e5, 0x5, 0x5e, 0x30, 0x2, 0x1e4, 0x1e3, 0x3, 
    0x2, 0x2, 0x2, 0x1e5, 0x1e6, 0x3, 0x2, 0x2, 0x2, 0x1e6, 0x1e4, 0x3, 
    0x2, 0x2, 0x2, 0x1e6, 0x1e7, 0x3, 0x2, 0x2, 0x2, 0x1e7, 0x1ea, 0x3, 
    0x2, 0x2, 0x2, 0x1e8, 0x1ea, 0x3, 0x2, 0x2, 0x2, 0x1e9, 0x1e1, 0x3, 
    0x2, 0x2, 0x2, 0x1e9, 0x1e8, 0x3, 0x2, 0x2, 0x2, 0x1ea, 0x5d, 0x3, 0x2, 
    0x2, 0x2, 0x1eb, 0x1ee, 0x5, 0x60, 0x31, 0x2, 0x1ec, 0x1ef, 0x5, 0x66, 
    0x34, 0x2, 0x1ed, 0x1ef, 0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1ec, 0x3, 0x2, 
    0x2, 0x2, 0x1ee, 0x1ed, 0x3, 0x2, 0x2, 0x2, 0x1ef, 0x1fb, 0x3, 0x2, 
    0x2, 0x2, 0x1f0, 0x1f3, 0x5, 0x6a, 0x36, 0x2, 0x1f1, 0x1f4, 0x5, 0x66, 
    0x34, 0x2, 0x1f2, 0x1f4, 0x3, 0x2, 0x2, 0x2, 0x1f3, 0x1f1, 0x3, 0x2, 
    0x2, 0x2, 0x1f3, 0x1f2, 0x3, 0x2, 0x2, 0x2, 0x1f4, 0x1fb, 0x3, 0x2, 
    0x2, 0x2, 0x1f5, 0x1fb, 0x5, 0x62, 0x32, 0x2, 0x1f6, 0x1f8, 0x5, 0x1c, 
    0xf, 0x2, 0x1f7, 0x1f9, 0x7, 0x2b, 0x2, 0x2, 0x1f8, 0x1f7, 0x3, 0x2, 
    0x2, 0x2, 0x1f8, 0x1f9, 0x3, 0x2, 0x2, 0x2, 0x1f9, 0x1fb, 0x3, 0x2, 
    0x2, 0x2, 0x1fa, 0x1eb, 0x3, 0x2, 0x2, 0x2, 0x1fa, 0x1f0, 0x3, 0x2, 
    0x2, 0x2, 0x1fa, 0x1f5, 0x3, 0x2, 0x2, 0x2, 0x1fa, 0x1f6, 0x3, 0x2, 
    0x2, 0x2, 0x1fb, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x1fc, 0x1fd, 0x5, 0x7e, 
    0x40, 0x2, 0x1fd, 0x200, 0x9, 0x3, 0x2, 0x2, 0x1fe, 0x201, 0x5, 0x6a, 
    0x36, 0x2, 0x1ff, 0x201, 0x5, 0x72, 0x3a, 0x2, 0x200, 0x1fe, 0x3, 0x2, 
    0x2, 0x2, 0x200, 0x1ff, 0x3, 0x2, 0x2, 0x2, 0x201, 0x61, 0x3, 0x2, 0x2, 
    0x2, 0x202, 0x204, 0x5, 0x72, 0x3a, 0x2, 0x203, 0x205, 0x5, 0x64, 0x33, 
    0x2, 0x204, 0x203, 0x3, 0x2, 0x2, 0x2, 0x204, 0x205, 0x3, 0x2, 0x2, 
    0x2, 0x205, 0x63, 0x3, 0x2, 0x2, 0x2, 0x206, 0x207, 0x5, 0x66, 0x34, 
    0x2, 0x207, 0x65, 0x3, 0x2, 0x2, 0x2, 0x208, 0x20a, 0x7, 0x2b, 0x2, 
    0x2, 0x209, 0x20b, 0x7, 0x2b, 0x2, 0x2, 0x20a, 0x209, 0x3, 0x2, 0x2, 
    0x2, 0x20a, 0x20b, 0x3, 0x2, 0x2, 0x2, 0x20b, 0x215, 0x3, 0x2, 0x2, 
    0x2, 0x20c, 0x20e, 0x7, 0x2c, 0x2, 0x2, 0x20d, 0x20f, 0x7, 0x2b, 0x2, 
    0x2, 0x20e, 0x20d, 0x3, 0x2, 0x2, 0x2, 0x20e, 0x20f, 0x3, 0x2, 0x2, 
    0x2, 0x20f, 0x215, 0x3, 0x2, 0x2, 0x2, 0x210, 0x212, 0x7, 0x2e, 0x2, 
    0x2, 0x211, 0x213, 0x7, 0x2b, 0x2, 0x2, 0x212, 0x211, 0x3, 0x2, 0x2, 
    0x2, 0x212, 0x213, 0x3, 0x2, 0x2, 0x2, 0x213, 0x215, 0x3, 0x2, 0x2, 
    0x2, 0x214, 0x208, 0x3, 0x2, 0x2, 0x2, 0x214, 0x20c, 0x3, 0x2, 0x2, 
    0x2, 0x214, 0x210, 0x3, 0x2, 0x2, 0x2, 0x215, 0x67, 0x3, 0x2, 0x2, 0x2, 
    0x216, 0x21f, 0x5, 0x76, 0x3c, 0x2, 0x217, 0x21f, 0x5, 0x78, 0x3d, 0x2, 
    0x218, 0x21f, 0x5, 0x6c, 0x37, 0x2, 0x219, 0x21f, 0x7, 0x5, 0x2, 0x2, 
    0x21a, 0x21c, 0x7, 0x32, 0x2, 0x2, 0x21b, 0x21d, 0x5, 0x7a, 0x3e, 0x2, 
    0x21c, 0x21b, 0x3, 0x2, 0x2, 0x2, 0x21c, 0x21d, 0x3, 0x2, 0x2, 0x2, 
    0x21d, 0x21f, 0x3, 0x2, 0x2, 0x2, 0x21e, 0x216, 0x3, 0x2, 0x2, 0x2, 
    0x21e, 0x217, 0x3, 0x2, 0x2, 0x2, 0x21e, 0x218, 0x3, 0x2, 0x2, 0x2, 
    0x21e, 0x219, 0x3, 0x2, 0x2, 0x2, 0x21e, 0x21a, 0x3, 0x2, 0x2, 0x2, 
    0x21f, 0x69, 0x3, 0x2, 0x2, 0x2, 0x220, 0x229, 0x5, 0x76, 0x3c, 0x2, 
    0x221, 0x229, 0x5, 0x78, 0x3d, 0x2, 0x222, 0x229, 0x5, 0x74, 0x3b, 0x2, 
    0x223, 0x229, 0x5, 0x6c, 0x37, 0x2, 0x224, 0x226, 0x7, 0x32, 0x2, 0x2, 
    0x225, 0x227, 0x5, 0x7a, 0x3e, 0x2, 0x226, 0x225, 0x3, 0x2, 0x2, 0x2, 
    0x226, 0x227, 0x3, 0x2, 0x2, 0x2, 0x227, 0x229, 0x3, 0x2, 0x2, 0x2, 
    0x228, 0x220, 0x3, 0x2, 0x2, 0x2, 0x228, 0x221, 0x3, 0x2, 0x2, 0x2, 
    0x228, 0x222, 0x3, 0x2, 0x2, 0x2, 0x228, 0x223, 0x3, 0x2, 0x2, 0x2, 
    0x228, 0x224, 0x3, 0x2, 0x2, 0x2, 0x229, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x22a, 
    0x22b, 0x7, 0x35, 0x2, 0x2, 0x22b, 0x22f, 0x5, 0x70, 0x39, 0x2, 0x22c, 
    0x22d, 0x7, 0x35, 0x2, 0x2, 0x22d, 0x22f, 0x5, 0x6e, 0x38, 0x2, 0x22e, 
    0x22a, 0x3, 0x2, 0x2, 0x2, 0x22e, 0x22c, 0x3, 0x2, 0x2, 0x2, 0x22f, 
    0x6d, 0x3, 0x2, 0x2, 0x2, 0x230, 0x231, 0x7, 0x23, 0x2, 0x2, 0x231, 
    0x236, 0x5, 0x70, 0x39, 0x2, 0x232, 0x233, 0x7, 0x2f, 0x2, 0x2, 0x233, 
    0x235, 0x5, 0x70, 0x39, 0x2, 0x234, 0x232, 0x3, 0x2, 0x2, 0x2, 0x235, 
    0x238, 0x3, 0x2, 0x2, 0x2, 0x236, 0x234, 0x3, 0x2, 0x2, 0x2, 0x236, 
    0x237, 0x3, 0x2, 0x2, 0x2, 0x237, 0x239, 0x3, 0x2, 0x2, 0x2, 0x238, 
    0x236, 0x3, 0x2, 0x2, 0x2, 0x239, 0x23a, 0x7, 0x24, 0x2, 0x2, 0x23a, 
    0x6f, 0x3, 0x2, 0x2, 0x2, 0x23b, 0x23d, 0x7, 0x3, 0x2, 0x2, 0x23c, 0x23e, 
    0x5, 0x7a, 0x3e, 0x2, 0x23d, 0x23c, 0x3, 0x2, 0x2, 0x2, 0x23d, 0x23e, 
    0x3, 0x2, 0x2, 0x2, 0x23e, 0x246, 0x3, 0x2, 0x2, 0x2, 0x23f, 0x241, 
    0x7, 0xa, 0x2, 0x2, 0x240, 0x242, 0x5, 0x7a, 0x3e, 0x2, 0x241, 0x240, 
    0x3, 0x2, 0x2, 0x2, 0x241, 0x242, 0x3, 0x2, 0x2, 0x2, 0x242, 0x246, 
    0x3, 0x2, 0x2, 0x2, 0x243, 0x246, 0x5, 0x76, 0x3c, 0x2, 0x244, 0x246, 
    0x7, 0x5, 0x2, 0x2, 0x245, 0x23b, 0x3, 0x2, 0x2, 0x2, 0x245, 0x23f, 
    0x3, 0x2, 0x2, 0x2, 0x245, 0x243, 0x3, 0x2, 0x2, 0x2, 0x245, 0x244, 
    0x3, 0x2, 0x2, 0x2, 0x246, 0x71, 0x3, 0x2, 0x2, 0x2, 0x247, 0x252, 0x7, 
    0x23, 0x2, 0x2, 0x248, 0x24a, 0x5, 0x8, 0x5, 0x2, 0x249, 0x248, 0x3, 
    0x2, 0x2, 0x2, 0x249, 0x24a, 0x3, 0x2, 0x2, 0x2, 0x24a, 0x24e, 0x3, 
    0x2, 0x2, 0x2, 0x24b, 0x24d, 0x5, 0x36, 0x1c, 0x2, 0x24c, 0x24b, 0x3, 
    0x2, 0x2, 0x2, 0x24d, 0x250, 0x3, 0x2, 0x2, 0x2, 0x24e, 0x24c, 0x3, 
    0x2, 0x2, 0x2, 0x24e, 0x24f, 0x3, 0x2, 0x2, 0x2, 0x24f, 0x251, 0x3, 
    0x2, 0x2, 0x2, 0x250, 0x24e, 0x3, 0x2, 0x2, 0x2, 0x251, 0x253, 0x7, 
    0x1f, 0x2, 0x2, 0x252, 0x249, 0x3, 0x2, 0x2, 0x2, 0x252, 0x253, 0x3, 
    0x2, 0x2, 0x2, 0x253, 0x254, 0x3, 0x2, 0x2, 0x2, 0x254, 0x255, 0x5, 
    0x5a, 0x2e, 0x2, 0x255, 0x256, 0x7, 0x24, 0x2, 0x2, 0x256, 0x73, 0x3, 
    0x2, 0x2, 0x2, 0x257, 0x259, 0x7, 0x4, 0x2, 0x2, 0x258, 0x25a, 0x5, 
    0x1e, 0x10, 0x2, 0x259, 0x258, 0x3, 0x2, 0x2, 0x2, 0x259, 0x25a, 0x3, 
    0x2, 0x2, 0x2, 0x25a, 0x25c, 0x3, 0x2, 0x2, 0x2, 0x25b, 0x25d, 0x5, 
    0x7a, 0x3e, 0x2, 0x25c, 0x25b, 0x3, 0x2, 0x2, 0x2, 0x25c, 0x25d, 0x3, 
    0x2, 0x2, 0x2, 0x25d, 0x75, 0x3, 0x2, 0x2, 0x2, 0x25e, 0x25f, 0x7, 0xa, 
    0x2, 0x2, 0x25f, 0x260, 0x7, 0x31, 0x2, 0x2, 0x260, 0x261, 0x7, 0xa, 
    0x2, 0x2, 0x261, 0x77, 0x3, 0x2, 0x2, 0x2, 0x262, 0x264, 0x7, 0x3, 0x2, 
    0x2, 0x263, 0x265, 0x5, 0x7a, 0x3e, 0x2, 0x264, 0x263, 0x3, 0x2, 0x2, 
    0x2, 0x264, 0x265, 0x3, 0x2, 0x2, 0x2, 0x265, 0x26b, 0x3, 0x2, 0x2, 
    0x2, 0x266, 0x268, 0x7, 0xa, 0x2, 0x2, 0x267, 0x269, 0x5, 0x7a, 0x3e, 
    0x2, 0x268, 0x267, 0x3, 0x2, 0x2, 0x2, 0x268, 0x269, 0x3, 0x2, 0x2, 
    0x2, 0x269, 0x26b, 0x3, 0x2, 0x2, 0x2, 0x26a, 0x262, 0x3, 0x2, 0x2, 
    0x2, 0x26a, 0x266, 0x3, 0x2, 0x2, 0x2, 0x26b, 0x79, 0x3, 0x2, 0x2, 0x2, 
    0x26c, 0x26d, 0x7, 0x28, 0x2, 0x2, 0x26d, 0x272, 0x5, 0x7c, 0x3f, 0x2, 
    0x26e, 0x26f, 0x7, 0x21, 0x2, 0x2, 0x26f, 0x271, 0x5, 0x7c, 0x3f, 0x2, 
    0x270, 0x26e, 0x3, 0x2, 0x2, 0x2, 0x271, 0x274, 0x3, 0x2, 0x2, 0x2, 
    0x272, 0x270, 0x3, 0x2, 0x2, 0x2, 0x272, 0x273, 0x3, 0x2, 0x2, 0x2, 
    0x273, 0x275, 0x3, 0x2, 0x2, 0x2, 0x274, 0x272, 0x3, 0x2, 0x2, 0x2, 
    0x275, 0x276, 0x7, 0x29, 0x2, 0x2, 0x276, 0x7b, 0x3, 0x2, 0x2, 0x2, 
    0x277, 0x27f, 0x5, 0x7e, 0x40, 0x2, 0x278, 0x279, 0x5, 0x7e, 0x40, 0x2, 
    0x279, 0x27c, 0x7, 0x2a, 0x2, 0x2, 0x27a, 0x27d, 0x5, 0x7e, 0x40, 0x2, 
    0x27b, 0x27d, 0x7, 0xa, 0x2, 0x2, 0x27c, 0x27a, 0x3, 0x2, 0x2, 0x2, 
    0x27c, 0x27b, 0x3, 0x2, 0x2, 0x2, 0x27d, 0x27f, 0x3, 0x2, 0x2, 0x2, 
    0x27e, 0x277, 0x3, 0x2, 0x2, 0x2, 0x27e, 0x278, 0x3, 0x2, 0x2, 0x2, 
    0x27f, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x280, 0x281, 0x9, 0x4, 0x2, 0x2, 0x281, 
    0x7f, 0x3, 0x2, 0x2, 0x2, 0x57, 0x83, 0x8c, 0x93, 0x9d, 0xa4, 0xad, 
    0xbb, 0xc1, 0xc9, 0xd3, 0xd8, 0xdf, 0xe8, 0xec, 0xf2, 0xfa, 0x100, 0x109, 
    0x114, 0x11a, 0x11f, 0x124, 0x128, 0x12c, 0x12f, 0x132, 0x135, 0x13a, 
    0x145, 0x149, 0x154, 0x15f, 0x16c, 0x177, 0x17d, 0x182, 0x186, 0x194, 
    0x199, 0x19c, 0x1a1, 0x1a5, 0x1a9, 0x1ad, 0x1b1, 0x1b3, 0x1b9, 0x1c5, 
    0x1ce, 0x1d2, 0x1d6, 0x1dd, 0x1e1, 0x1e6, 0x1e9, 0x1ee, 0x1f3, 0x1f8, 
    0x1fa, 0x200, 0x204, 0x20a, 0x20e, 0x212, 0x214, 0x21c, 0x21e, 0x226, 
    0x228, 0x22e, 0x236, 0x23d, 0x241, 0x245, 0x249, 0x24e, 0x252, 0x259, 
    0x25c, 0x264, 0x268, 0x26a, 0x272, 0x27c, 0x27e, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  for (int i = 0; i < _atn.getNumberOfDecisions(); i++) { 
    _decisionToDFA.push_back(dfa::DFA(_atn.getDecisionState(i), i));
  }
}

ANTLRv4Parser::Initializer ANTLRv4Parser::_init;
