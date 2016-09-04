
// Generated from ANTLRv4Parser.g4 by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"
#include "ANTLRv4Parser.h"


namespace parsers {

/**
 * This interface defines an abstract listener for a parse tree produced by ANTLRv4Parser.
 */
class ANTLRv4ParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterGrammarSpec(ANTLRv4Parser::GrammarSpecContext *ctx) = 0;
  virtual void exitGrammarSpec(ANTLRv4Parser::GrammarSpecContext *ctx) = 0;

  virtual void enterGrammarType(ANTLRv4Parser::GrammarTypeContext *ctx) = 0;
  virtual void exitGrammarType(ANTLRv4Parser::GrammarTypeContext *ctx) = 0;

  virtual void enterPrequelConstruct(ANTLRv4Parser::PrequelConstructContext *ctx) = 0;
  virtual void exitPrequelConstruct(ANTLRv4Parser::PrequelConstructContext *ctx) = 0;

  virtual void enterOptionsSpec(ANTLRv4Parser::OptionsSpecContext *ctx) = 0;
  virtual void exitOptionsSpec(ANTLRv4Parser::OptionsSpecContext *ctx) = 0;

  virtual void enterOption(ANTLRv4Parser::OptionContext *ctx) = 0;
  virtual void exitOption(ANTLRv4Parser::OptionContext *ctx) = 0;

  virtual void enterOptionValue(ANTLRv4Parser::OptionValueContext *ctx) = 0;
  virtual void exitOptionValue(ANTLRv4Parser::OptionValueContext *ctx) = 0;

  virtual void enterDelegateGrammars(ANTLRv4Parser::DelegateGrammarsContext *ctx) = 0;
  virtual void exitDelegateGrammars(ANTLRv4Parser::DelegateGrammarsContext *ctx) = 0;

  virtual void enterDelegateGrammar(ANTLRv4Parser::DelegateGrammarContext *ctx) = 0;
  virtual void exitDelegateGrammar(ANTLRv4Parser::DelegateGrammarContext *ctx) = 0;

  virtual void enterTokensSpec(ANTLRv4Parser::TokensSpecContext *ctx) = 0;
  virtual void exitTokensSpec(ANTLRv4Parser::TokensSpecContext *ctx) = 0;

  virtual void enterChannelsSpec(ANTLRv4Parser::ChannelsSpecContext *ctx) = 0;
  virtual void exitChannelsSpec(ANTLRv4Parser::ChannelsSpecContext *ctx) = 0;

  virtual void enterIdList(ANTLRv4Parser::IdListContext *ctx) = 0;
  virtual void exitIdList(ANTLRv4Parser::IdListContext *ctx) = 0;

  virtual void enterAction(ANTLRv4Parser::ActionContext *ctx) = 0;
  virtual void exitAction(ANTLRv4Parser::ActionContext *ctx) = 0;

  virtual void enterActionScopeName(ANTLRv4Parser::ActionScopeNameContext *ctx) = 0;
  virtual void exitActionScopeName(ANTLRv4Parser::ActionScopeNameContext *ctx) = 0;

  virtual void enterActionBlock(ANTLRv4Parser::ActionBlockContext *ctx) = 0;
  virtual void exitActionBlock(ANTLRv4Parser::ActionBlockContext *ctx) = 0;

  virtual void enterArgActionBlock(ANTLRv4Parser::ArgActionBlockContext *ctx) = 0;
  virtual void exitArgActionBlock(ANTLRv4Parser::ArgActionBlockContext *ctx) = 0;

  virtual void enterModeSpec(ANTLRv4Parser::ModeSpecContext *ctx) = 0;
  virtual void exitModeSpec(ANTLRv4Parser::ModeSpecContext *ctx) = 0;

  virtual void enterRules(ANTLRv4Parser::RulesContext *ctx) = 0;
  virtual void exitRules(ANTLRv4Parser::RulesContext *ctx) = 0;

  virtual void enterRuleSpec(ANTLRv4Parser::RuleSpecContext *ctx) = 0;
  virtual void exitRuleSpec(ANTLRv4Parser::RuleSpecContext *ctx) = 0;

  virtual void enterParserRuleSpec(ANTLRv4Parser::ParserRuleSpecContext *ctx) = 0;
  virtual void exitParserRuleSpec(ANTLRv4Parser::ParserRuleSpecContext *ctx) = 0;

  virtual void enterExceptionGroup(ANTLRv4Parser::ExceptionGroupContext *ctx) = 0;
  virtual void exitExceptionGroup(ANTLRv4Parser::ExceptionGroupContext *ctx) = 0;

  virtual void enterExceptionHandler(ANTLRv4Parser::ExceptionHandlerContext *ctx) = 0;
  virtual void exitExceptionHandler(ANTLRv4Parser::ExceptionHandlerContext *ctx) = 0;

  virtual void enterFinallyClause(ANTLRv4Parser::FinallyClauseContext *ctx) = 0;
  virtual void exitFinallyClause(ANTLRv4Parser::FinallyClauseContext *ctx) = 0;

  virtual void enterRulePrequel(ANTLRv4Parser::RulePrequelContext *ctx) = 0;
  virtual void exitRulePrequel(ANTLRv4Parser::RulePrequelContext *ctx) = 0;

  virtual void enterRuleReturns(ANTLRv4Parser::RuleReturnsContext *ctx) = 0;
  virtual void exitRuleReturns(ANTLRv4Parser::RuleReturnsContext *ctx) = 0;

  virtual void enterThrowsSpec(ANTLRv4Parser::ThrowsSpecContext *ctx) = 0;
  virtual void exitThrowsSpec(ANTLRv4Parser::ThrowsSpecContext *ctx) = 0;

  virtual void enterLocalsSpec(ANTLRv4Parser::LocalsSpecContext *ctx) = 0;
  virtual void exitLocalsSpec(ANTLRv4Parser::LocalsSpecContext *ctx) = 0;

  virtual void enterRuleAction(ANTLRv4Parser::RuleActionContext *ctx) = 0;
  virtual void exitRuleAction(ANTLRv4Parser::RuleActionContext *ctx) = 0;

  virtual void enterRuleModifiers(ANTLRv4Parser::RuleModifiersContext *ctx) = 0;
  virtual void exitRuleModifiers(ANTLRv4Parser::RuleModifiersContext *ctx) = 0;

  virtual void enterRuleModifier(ANTLRv4Parser::RuleModifierContext *ctx) = 0;
  virtual void exitRuleModifier(ANTLRv4Parser::RuleModifierContext *ctx) = 0;

  virtual void enterRuleBlock(ANTLRv4Parser::RuleBlockContext *ctx) = 0;
  virtual void exitRuleBlock(ANTLRv4Parser::RuleBlockContext *ctx) = 0;

  virtual void enterRuleAltList(ANTLRv4Parser::RuleAltListContext *ctx) = 0;
  virtual void exitRuleAltList(ANTLRv4Parser::RuleAltListContext *ctx) = 0;

  virtual void enterLabeledAlt(ANTLRv4Parser::LabeledAltContext *ctx) = 0;
  virtual void exitLabeledAlt(ANTLRv4Parser::LabeledAltContext *ctx) = 0;

  virtual void enterLexerRuleSpec(ANTLRv4Parser::LexerRuleSpecContext *ctx) = 0;
  virtual void exitLexerRuleSpec(ANTLRv4Parser::LexerRuleSpecContext *ctx) = 0;

  virtual void enterLexerRuleBlock(ANTLRv4Parser::LexerRuleBlockContext *ctx) = 0;
  virtual void exitLexerRuleBlock(ANTLRv4Parser::LexerRuleBlockContext *ctx) = 0;

  virtual void enterLexerAltList(ANTLRv4Parser::LexerAltListContext *ctx) = 0;
  virtual void exitLexerAltList(ANTLRv4Parser::LexerAltListContext *ctx) = 0;

  virtual void enterLexerAlt(ANTLRv4Parser::LexerAltContext *ctx) = 0;
  virtual void exitLexerAlt(ANTLRv4Parser::LexerAltContext *ctx) = 0;

  virtual void enterLexerElements(ANTLRv4Parser::LexerElementsContext *ctx) = 0;
  virtual void exitLexerElements(ANTLRv4Parser::LexerElementsContext *ctx) = 0;

  virtual void enterLexerElement(ANTLRv4Parser::LexerElementContext *ctx) = 0;
  virtual void exitLexerElement(ANTLRv4Parser::LexerElementContext *ctx) = 0;

  virtual void enterLabeledLexerElement(ANTLRv4Parser::LabeledLexerElementContext *ctx) = 0;
  virtual void exitLabeledLexerElement(ANTLRv4Parser::LabeledLexerElementContext *ctx) = 0;

  virtual void enterLexerBlock(ANTLRv4Parser::LexerBlockContext *ctx) = 0;
  virtual void exitLexerBlock(ANTLRv4Parser::LexerBlockContext *ctx) = 0;

  virtual void enterLexerCommands(ANTLRv4Parser::LexerCommandsContext *ctx) = 0;
  virtual void exitLexerCommands(ANTLRv4Parser::LexerCommandsContext *ctx) = 0;

  virtual void enterLexerCommand(ANTLRv4Parser::LexerCommandContext *ctx) = 0;
  virtual void exitLexerCommand(ANTLRv4Parser::LexerCommandContext *ctx) = 0;

  virtual void enterLexerCommandName(ANTLRv4Parser::LexerCommandNameContext *ctx) = 0;
  virtual void exitLexerCommandName(ANTLRv4Parser::LexerCommandNameContext *ctx) = 0;

  virtual void enterLexerCommandExpr(ANTLRv4Parser::LexerCommandExprContext *ctx) = 0;
  virtual void exitLexerCommandExpr(ANTLRv4Parser::LexerCommandExprContext *ctx) = 0;

  virtual void enterAltList(ANTLRv4Parser::AltListContext *ctx) = 0;
  virtual void exitAltList(ANTLRv4Parser::AltListContext *ctx) = 0;

  virtual void enterAlternative(ANTLRv4Parser::AlternativeContext *ctx) = 0;
  virtual void exitAlternative(ANTLRv4Parser::AlternativeContext *ctx) = 0;

  virtual void enterElement(ANTLRv4Parser::ElementContext *ctx) = 0;
  virtual void exitElement(ANTLRv4Parser::ElementContext *ctx) = 0;

  virtual void enterLabeledElement(ANTLRv4Parser::LabeledElementContext *ctx) = 0;
  virtual void exitLabeledElement(ANTLRv4Parser::LabeledElementContext *ctx) = 0;

  virtual void enterEbnf(ANTLRv4Parser::EbnfContext *ctx) = 0;
  virtual void exitEbnf(ANTLRv4Parser::EbnfContext *ctx) = 0;

  virtual void enterBlockSuffix(ANTLRv4Parser::BlockSuffixContext *ctx) = 0;
  virtual void exitBlockSuffix(ANTLRv4Parser::BlockSuffixContext *ctx) = 0;

  virtual void enterEbnfSuffix(ANTLRv4Parser::EbnfSuffixContext *ctx) = 0;
  virtual void exitEbnfSuffix(ANTLRv4Parser::EbnfSuffixContext *ctx) = 0;

  virtual void enterLexerAtom(ANTLRv4Parser::LexerAtomContext *ctx) = 0;
  virtual void exitLexerAtom(ANTLRv4Parser::LexerAtomContext *ctx) = 0;

  virtual void enterAtom(ANTLRv4Parser::AtomContext *ctx) = 0;
  virtual void exitAtom(ANTLRv4Parser::AtomContext *ctx) = 0;

  virtual void enterNotSet(ANTLRv4Parser::NotSetContext *ctx) = 0;
  virtual void exitNotSet(ANTLRv4Parser::NotSetContext *ctx) = 0;

  virtual void enterBlockSet(ANTLRv4Parser::BlockSetContext *ctx) = 0;
  virtual void exitBlockSet(ANTLRv4Parser::BlockSetContext *ctx) = 0;

  virtual void enterSetElement(ANTLRv4Parser::SetElementContext *ctx) = 0;
  virtual void exitSetElement(ANTLRv4Parser::SetElementContext *ctx) = 0;

  virtual void enterBlock(ANTLRv4Parser::BlockContext *ctx) = 0;
  virtual void exitBlock(ANTLRv4Parser::BlockContext *ctx) = 0;

  virtual void enterRuleref(ANTLRv4Parser::RulerefContext *ctx) = 0;
  virtual void exitRuleref(ANTLRv4Parser::RulerefContext *ctx) = 0;

  virtual void enterCharacterRange(ANTLRv4Parser::CharacterRangeContext *ctx) = 0;
  virtual void exitCharacterRange(ANTLRv4Parser::CharacterRangeContext *ctx) = 0;

  virtual void enterTerminal(ANTLRv4Parser::TerminalContext *ctx) = 0;
  virtual void exitTerminal(ANTLRv4Parser::TerminalContext *ctx) = 0;

  virtual void enterElementOptions(ANTLRv4Parser::ElementOptionsContext *ctx) = 0;
  virtual void exitElementOptions(ANTLRv4Parser::ElementOptionsContext *ctx) = 0;

  virtual void enterElementOption(ANTLRv4Parser::ElementOptionContext *ctx) = 0;
  virtual void exitElementOption(ANTLRv4Parser::ElementOptionContext *ctx) = 0;

  virtual void enterIdentifier(ANTLRv4Parser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(ANTLRv4Parser::IdentifierContext *ctx) = 0;


};

}  // namespace parsers
