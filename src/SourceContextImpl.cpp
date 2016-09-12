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

#include "SourceContextImpl.h"

#include "ANTLRv4ParserBaseListener.h"

using namespace graps;

using namespace antlr4;
using namespace antlr4::atn;
using namespace antlr4::tree;

/**
 * Returns the terminal node at the given position, or null if there is no terminal at that position,
 * which is given as (column, row) pair.
 */
static Ref<TerminalNode> terminalFromPosition(Ref<Tree> const& root, std::pair<ssize_t, ssize_t> position)
{
  // Does the root node actually contain the position? If not we don't need to look further.
  if (antlrcpp::is<TerminalNode>(root))
  {
    Ref<TerminalNode> terminal = std::dynamic_pointer_cast<TerminalNode>(root);
    Token *token = terminal->getSymbol();
    if (token->getLine() != position.second)
      return Ref<TerminalNode>();

    int tokenStop = token->getCharPositionInLine() + (token->getStopIndex() - token->getStartIndex() + 1);
    if (token->getCharPositionInLine() <= position.first && tokenStop >= position.first)
      return terminal;
    return Ref<TerminalNode>();
  }
  else
  {
    Token *start = std::dynamic_pointer_cast<ParserRuleContext>(root)->start;
    Token *stop = std::dynamic_pointer_cast<ParserRuleContext>(root)->stop;
    if (start == nullptr || stop == nullptr) // Invalid tree?
      return Ref<TerminalNode>();

    if (start->getLine() > position.second
        || (start->getLine() == position.second && position.first < start->getCharPositionInLine()))
      return Ref<TerminalNode>();

    int tokenStop = stop->getCharPositionInLine() + (start->getStopIndex() - start->getStartIndex() + 1);
    if (stop->getLine() < position.second || (stop->getLine() == position.second && tokenStop < position.first))
      return Ref<TerminalNode>();
  }

  for (auto &child : root->children)
  {
    Ref<TerminalNode> result = terminalFromPosition(child, position);
    if (result != nullptr)
      return result;
  }

  return Ref<TerminalNode>();
}

//----------------------------------------------------------------------------------------------------------------------

static std::string sourceTextForContext(ParserRuleContext *ctx, bool keepQuotes)
{
  if (ctx == nullptr)
    return "";

  CharStream *cs = ctx->start->getTokenSource()->getInputStream();

  int start = ctx->start->getStartIndex();
  int stop = ctx->stop->getStopIndex();

  // For mode definitions we only need the init line, not all the lexer rules following it.
  if (ctx->getRuleIndex() == ANTLRv4Parser::RuleModeSpec)
    stop = ((ANTLRv4Parser::ModeSpecContext *)ctx)->SEMI()->getSymbol()->getStopIndex();

  std::string result = cs->getText(misc::Interval(start, stop));
  if (keepQuotes || result.size() < 2)
    return result;

  char quoteChar = result[0];
  if ((quoteChar == '"' || quoteChar == '`' || quoteChar == '\'') && quoteChar == result.back())
    return result.substr(1, result.size() - 2);
  return result;
}

//----------------------------------------------------------------------------------------------------------------------

class DetailsListener : public ANTLRv4ParserBaseListener {
public:
  std::string tokenVocab;

  DetailsListener(std::map<std::string, std::pair<std::string, antlr4::ParserRuleContext *>> &map,
                  std::vector<std::string> &imports)
  : _symbolMap(map), _imports(imports)
  {
    _symbolMap["DEFAULT"] = { "Predefined token channel", nullptr };
    _symbolMap["HIDDEN"] = { "Predefined token channel", nullptr };
  }

  virtual void exitLexerRuleSpec(ANTLRv4Parser::LexerRuleSpecContext *ctx) override
  {
    std::string symbol = ctx->TOKEN_REF()->getText();
    _symbolMap[symbol] = { "Lexer rule", ctx };
  }

  virtual void exitParserRuleSpec(ANTLRv4Parser::ParserRuleSpecContext *ctx) override
  {
    std::string symbol = ctx->RULE_REF()->getText();
    _symbolMap[symbol] = { "Parser rule", ctx };
  }

  virtual void exitTokensSpec(ANTLRv4Parser::TokensSpecContext *ctx) override
  {
    if (ctx->idList() != nullptr)
    {
      for (auto identifier : ctx->idList()->identifier())
      {
        std::string symbol = identifier->getText();
        _symbolMap[symbol] = { "Virtual lexer token", identifier.get() };
      }
    }
  }

  virtual void exitChannelsSpec(ANTLRv4Parser::ChannelsSpecContext *ctx) override
  {
    if (ctx->idList() != nullptr)
    {
      for (auto identifier : ctx->idList()->identifier())
      {
        std::string symbol = identifier->getText();
        _symbolMap[symbol] = { "Token channel", ctx };
      }
    }
  }

  virtual void exitModeSpec(ANTLRv4Parser::ModeSpecContext *ctx) override
  {
    std::string symbol = ctx->identifier()->getText();
    _symbolMap[symbol] = { "Lexer mode", ctx };
  }

  virtual void exitDelegateGrammar(ANTLRv4Parser::DelegateGrammarContext *ctx) override
  {
    if (ctx->identifier().size() == 1)
      _imports.push_back(sourceTextForContext(ctx->identifier(0).get(), true));
    else
      _imports.push_back(sourceTextForContext(ctx->identifier(1).get(), true));
  }

  virtual void exitOption(ANTLRv4Parser::OptionContext *ctx) override
  {
    std::string option = ctx->identifier()->getText();
    if (option == "tokenVocab")
      tokenVocab = ctx->optionValue()->getText();
  }

private:
  std::map<std::string, std::pair<std::string, antlr4::ParserRuleContext *>> &_symbolMap;
  std::vector<std::string> &_imports;
};

//----------------------------------------------------------------------------------------------------------------------

SourceContextImpl::SourceContextImpl(std::string const& sourceId)
: _lexer(&_input), _tokens(&_lexer), _parser(&_tokens), _sourceId(sourceId)
{
}

//----------------------------------------------------------------------------------------------------------------------

void SourceContextImpl::parse(std::string const& source)
{
  imports.clear();
  _symbolTable.clear();
  _dependencies.clear();

  _input.load(source);
  _lexer.reset();
  _lexer.setInputStream(&_input);
  _tokens.setTokenSource(&_lexer);
  ANTLRv4Parser parser(&_tokens);

  parser.reset();
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
    _tokens.reset();
    _parser.reset();
    _parser.setErrorHandler(std::make_shared<DefaultErrorStrategy>());
    _parser.getInterpreter<ParserATNSimulator>()->setPredictionMode(PredictionMode::LL);
    _parser.addErrorListener(&ConsoleErrorListener::INSTANCE);
    _tree = _parser.grammarSpec();
  }

#if DEBUG == 1
  std::cout << "Found errors: " << parser.getNumberOfSyntaxErrors() << std::endl;
  std::cout << "Parse tree: \n" << _tree->toStringTree(&parser) << std::endl;
#endif

  DetailsListener listener(_symbolTable, imports);
  tree::ParseTreeWalker::DEFAULT.walk(&listener, _tree.get());

  // We don't create source context instances for dependencies (token vocabularies or imports) here and instead rely on
  // an outer context to do this and pass on references to us. This way we avoid duplicate instances.
  if (!listener.tokenVocab.empty())
    imports.insert(imports.begin(), listener.tokenVocab);
}

//----------------------------------------------------------------------------------------------------------------------

/**
 * Determines the text for the given symbol from either our own symbol table or one of our dependencies.
 * Returns an array with these details:
 * 0 - the source id for this context, 1 - a short symbol description, 2 - the symbol definition
 */
std::vector<std::string> SourceContextImpl::getTextForSymbol(std::string const& symbol)
{
  // First look in our own symbol table, which overrides any imported grammar rule.
  if (_symbolTable.count(symbol) > 0)
  {
    auto &symbolInfo = _symbolTable[symbol];
    std::string source = _sourceId;
    if (symbolInfo.second == nullptr)
      source = "ANTLR runtime";
    return { source, symbolInfo.first, sourceTextForContext(symbolInfo.second, true) };
  }

  // Nothing in our table, so try the dependencies in order of appearance (effectively implementing rule overrides this way).
  for (auto dep : _dependencies)
  {
    std::vector<std::string> result = dep->getTextForSymbol(symbol);
    if (!result.empty())
      return result;
  }
  return {};
}

//----------------------------------------------------------------------------------------------------------------------

std::vector<std::string> SourceContextImpl::infoForSymbolAtPosition(size_t row, size_t column)
{
  Ref<TerminalNode> terminal = terminalFromPosition(_tree, { column, row });
  if (terminal == nullptr)
    return {};

  // We only want to show info for symbols in specific contexts.
  auto parent = std::dynamic_pointer_cast<ParserRuleContext>(terminal->parent.lock());
  if (parent->getRuleIndex() == ANTLRv4Parser::RuleIdentifier)
    parent = std::dynamic_pointer_cast<ParserRuleContext>(parent->parent.lock());

  switch (parent->getRuleIndex())
  {
    case ANTLRv4Parser::RuleRuleref:
    case ANTLRv4Parser::RuleTerminalRule:
    case ANTLRv4Parser::RuleLexerCommandExpr:
      return getTextForSymbol(terminal->getText());
  }

  return {};
}

//----------------------------------------------------------------------------------------------------------------------

/**
 * Returns all grammar names (excluding extensions) on which this context depends on (tokenVocab setting + imports).
 */
void SourceContextImpl::addDependency(SourceContextImpl *context)
{
  _dependencies.push_back(context);
}

//----------------------------------------------------------------------------------------------------------------------

