
// Generated from ANTLRv4Parser.g4 by ANTLR 4.5.3

#pragma once


#include "antlr4-runtime.h"
#include "ANTLRv4Parser.h"


namespace graps {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by ANTLRv4Parser.
 */
class ANTLRv4ParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ANTLRv4Parser.
   */
    virtual antlrcpp::Any visitGrammarSpec(ANTLRv4Parser::GrammarSpecContext *context) = 0;

    virtual antlrcpp::Any visitGrammarType(ANTLRv4Parser::GrammarTypeContext *context) = 0;

    virtual antlrcpp::Any visitPrequelConstruct(ANTLRv4Parser::PrequelConstructContext *context) = 0;

    virtual antlrcpp::Any visitOptionsSpec(ANTLRv4Parser::OptionsSpecContext *context) = 0;

    virtual antlrcpp::Any visitOption(ANTLRv4Parser::OptionContext *context) = 0;

    virtual antlrcpp::Any visitOptionValue(ANTLRv4Parser::OptionValueContext *context) = 0;

    virtual antlrcpp::Any visitDelegateGrammars(ANTLRv4Parser::DelegateGrammarsContext *context) = 0;

    virtual antlrcpp::Any visitDelegateGrammar(ANTLRv4Parser::DelegateGrammarContext *context) = 0;

    virtual antlrcpp::Any visitTokensSpec(ANTLRv4Parser::TokensSpecContext *context) = 0;

    virtual antlrcpp::Any visitChannelsSpec(ANTLRv4Parser::ChannelsSpecContext *context) = 0;

    virtual antlrcpp::Any visitIdList(ANTLRv4Parser::IdListContext *context) = 0;

    virtual antlrcpp::Any visitNamedAction(ANTLRv4Parser::NamedActionContext *context) = 0;

    virtual antlrcpp::Any visitActionScopeName(ANTLRv4Parser::ActionScopeNameContext *context) = 0;

    virtual antlrcpp::Any visitActionBlock(ANTLRv4Parser::ActionBlockContext *context) = 0;

    virtual antlrcpp::Any visitArgActionBlock(ANTLRv4Parser::ArgActionBlockContext *context) = 0;

    virtual antlrcpp::Any visitModeSpec(ANTLRv4Parser::ModeSpecContext *context) = 0;

    virtual antlrcpp::Any visitRules(ANTLRv4Parser::RulesContext *context) = 0;

    virtual antlrcpp::Any visitRuleSpec(ANTLRv4Parser::RuleSpecContext *context) = 0;

    virtual antlrcpp::Any visitParserRuleSpec(ANTLRv4Parser::ParserRuleSpecContext *context) = 0;

    virtual antlrcpp::Any visitExceptionGroup(ANTLRv4Parser::ExceptionGroupContext *context) = 0;

    virtual antlrcpp::Any visitExceptionHandler(ANTLRv4Parser::ExceptionHandlerContext *context) = 0;

    virtual antlrcpp::Any visitFinallyClause(ANTLRv4Parser::FinallyClauseContext *context) = 0;

    virtual antlrcpp::Any visitRulePrequel(ANTLRv4Parser::RulePrequelContext *context) = 0;

    virtual antlrcpp::Any visitRuleReturns(ANTLRv4Parser::RuleReturnsContext *context) = 0;

    virtual antlrcpp::Any visitThrowsSpec(ANTLRv4Parser::ThrowsSpecContext *context) = 0;

    virtual antlrcpp::Any visitLocalsSpec(ANTLRv4Parser::LocalsSpecContext *context) = 0;

    virtual antlrcpp::Any visitRuleAction(ANTLRv4Parser::RuleActionContext *context) = 0;

    virtual antlrcpp::Any visitRuleModifiers(ANTLRv4Parser::RuleModifiersContext *context) = 0;

    virtual antlrcpp::Any visitRuleModifier(ANTLRv4Parser::RuleModifierContext *context) = 0;

    virtual antlrcpp::Any visitRuleBlock(ANTLRv4Parser::RuleBlockContext *context) = 0;

    virtual antlrcpp::Any visitRuleAltList(ANTLRv4Parser::RuleAltListContext *context) = 0;

    virtual antlrcpp::Any visitLabeledAlt(ANTLRv4Parser::LabeledAltContext *context) = 0;

    virtual antlrcpp::Any visitLexerRuleSpec(ANTLRv4Parser::LexerRuleSpecContext *context) = 0;

    virtual antlrcpp::Any visitLexerRuleBlock(ANTLRv4Parser::LexerRuleBlockContext *context) = 0;

    virtual antlrcpp::Any visitLexerAltList(ANTLRv4Parser::LexerAltListContext *context) = 0;

    virtual antlrcpp::Any visitLexerAlt(ANTLRv4Parser::LexerAltContext *context) = 0;

    virtual antlrcpp::Any visitLexerElements(ANTLRv4Parser::LexerElementsContext *context) = 0;

    virtual antlrcpp::Any visitLexerElement(ANTLRv4Parser::LexerElementContext *context) = 0;

    virtual antlrcpp::Any visitLabeledLexerElement(ANTLRv4Parser::LabeledLexerElementContext *context) = 0;

    virtual antlrcpp::Any visitLexerBlock(ANTLRv4Parser::LexerBlockContext *context) = 0;

    virtual antlrcpp::Any visitLexerCommands(ANTLRv4Parser::LexerCommandsContext *context) = 0;

    virtual antlrcpp::Any visitLexerCommand(ANTLRv4Parser::LexerCommandContext *context) = 0;

    virtual antlrcpp::Any visitLexerCommandName(ANTLRv4Parser::LexerCommandNameContext *context) = 0;

    virtual antlrcpp::Any visitLexerCommandExpr(ANTLRv4Parser::LexerCommandExprContext *context) = 0;

    virtual antlrcpp::Any visitAltList(ANTLRv4Parser::AltListContext *context) = 0;

    virtual antlrcpp::Any visitAlternative(ANTLRv4Parser::AlternativeContext *context) = 0;

    virtual antlrcpp::Any visitElement(ANTLRv4Parser::ElementContext *context) = 0;

    virtual antlrcpp::Any visitLabeledElement(ANTLRv4Parser::LabeledElementContext *context) = 0;

    virtual antlrcpp::Any visitEbnf(ANTLRv4Parser::EbnfContext *context) = 0;

    virtual antlrcpp::Any visitBlockSuffix(ANTLRv4Parser::BlockSuffixContext *context) = 0;

    virtual antlrcpp::Any visitEbnfSuffix(ANTLRv4Parser::EbnfSuffixContext *context) = 0;

    virtual antlrcpp::Any visitLexerAtom(ANTLRv4Parser::LexerAtomContext *context) = 0;

    virtual antlrcpp::Any visitAtom(ANTLRv4Parser::AtomContext *context) = 0;

    virtual antlrcpp::Any visitNotSet(ANTLRv4Parser::NotSetContext *context) = 0;

    virtual antlrcpp::Any visitBlockSet(ANTLRv4Parser::BlockSetContext *context) = 0;

    virtual antlrcpp::Any visitSetElement(ANTLRv4Parser::SetElementContext *context) = 0;

    virtual antlrcpp::Any visitBlock(ANTLRv4Parser::BlockContext *context) = 0;

    virtual antlrcpp::Any visitRuleref(ANTLRv4Parser::RulerefContext *context) = 0;

    virtual antlrcpp::Any visitCharacterRange(ANTLRv4Parser::CharacterRangeContext *context) = 0;

    virtual antlrcpp::Any visitTerminalRule(ANTLRv4Parser::TerminalRuleContext *context) = 0;

    virtual antlrcpp::Any visitElementOptions(ANTLRv4Parser::ElementOptionsContext *context) = 0;

    virtual antlrcpp::Any visitElementOption(ANTLRv4Parser::ElementOptionContext *context) = 0;

    virtual antlrcpp::Any visitIdentifier(ANTLRv4Parser::IdentifierContext *context) = 0;


};

}  // namespace graps
