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

std::string toLower(std::string const& s)
{
  std::string result = s;
  for (auto &c : result)
    c = tolower(c);
  return result;
}

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

    int tokenStop = stop->getCharPositionInLine() + (stop->getStopIndex() - stop->getStartIndex() + 1);
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

static Definition definitionForContext(ParserRuleContext *ctx, bool keepQuotes)
{
  if (ctx == nullptr)
    return {};

  CharStream *cs = ctx->start->getTokenSource()->getInputStream();

  Definition result = { "",
    ctx->start->getCharPositionInLine(), ctx->start->getLine(),
    ctx->stop->getCharPositionInLine(), ctx->stop->getLine()
  };

  int start = ctx->start->getStartIndex();
  int stop = ctx->stop->getStopIndex();

  // For mode definitions we only need the init line, not all the lexer rules following it.
  if (ctx->getRuleIndex() == ANTLRv4Parser::RuleModeSpec)
  {
    ANTLRv4Parser::ModeSpecContext *modeSpec = (ANTLRv4Parser::ModeSpecContext *)ctx;
    stop = modeSpec->SEMI()->getSymbol()->getStopIndex();
    result.endColumn = modeSpec->SEMI()->getSymbol()->getCharPositionInLine();
    result.endRow = modeSpec->SEMI()->getSymbol()->getLine();
  }
  else if (ctx->getRuleIndex() == ANTLRv4Parser::RuleGrammarSpec)
  {
    // Similar for entire grammars. We only need the introducer line here.
    ANTLRv4Parser::GrammarSpecContext *grammarSpec = (ANTLRv4Parser::GrammarSpecContext *)ctx;
    stop = grammarSpec->SEMI()->getSymbol()->getStopIndex();
    result.endColumn = grammarSpec->SEMI()->getSymbol()->getCharPositionInLine();
    result.endRow = grammarSpec->SEMI()->getSymbol()->getLine();

    start = grammarSpec->grammarType()->start->getStartIndex();
    result.startColumn = grammarSpec->grammarType()->start->getCharPositionInLine();
    result.startRow = grammarSpec->grammarType()->start->getLine();
  }

  result.text = cs->getText(misc::Interval(start, stop));
  if (keepQuotes || result.text.size() < 2)
    return result;

  char quoteChar = result.text[0];
  if ((quoteChar == '"' || quoteChar == '`' || quoteChar == '\'') && quoteChar == result.text.back())
    result.text = result.text.substr(1, result.text.size() - 2);
  return result;
}

//----------------- DetailsListener ------------------------------------------------------------------------------------

class DetailsListener : public ANTLRv4ParserBaseListener {
public:
  std::string tokenVocab;

  DetailsListener(SymbolTable &symbolTable, std::vector<std::string> &imports) : _symbolTable(symbolTable), _imports(imports)
  {
    _symbolTable[SKBuiltInChannel]["DEFAULT"] = nullptr;
    _symbolTable[SKBuiltInChannel]["HIDDEN"] = nullptr;
    _symbolTable[SKBuiltInLexerToken]["EOF"] = nullptr;
    _symbolTable[SKBuiltInMode]["DEFAULT_MODE"] = nullptr;
  }

  virtual void exitLexerRuleSpec(ANTLRv4Parser::LexerRuleSpecContext *ctx) override
  {
    if (ctx->TOKEN_REF() != nullptr)
    {
      std::string symbol = ctx->TOKEN_REF()->getText();
      if (ctx->FRAGMENT() != nullptr)
        _symbolTable[SKFragmentLexerToken][symbol] = ctx;
      else
        _symbolTable[SKLexerToken][symbol] = ctx;
    }
  }

  virtual void exitParserRuleSpec(ANTLRv4Parser::ParserRuleSpecContext *ctx) override
  {
    std::string symbol = ctx->RULE_REF()->getText();
    _symbolTable[SKParserRule][symbol] = ctx;
  }

  virtual void exitTokensSpec(ANTLRv4Parser::TokensSpecContext *ctx) override
  {
    if (ctx->idList() != nullptr)
    {
      for (auto identifier : ctx->idList()->identifier())
      {
        std::string symbol = identifier->getText();
        _symbolTable[SKVirtualLexerToken][symbol] = identifier.get();
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
        _symbolTable[SKTokenChannel][symbol] = ctx;
      }
    }
  }

  virtual void exitModeSpec(ANTLRv4Parser::ModeSpecContext *ctx) override
  {
    std::string symbol = ctx->identifier()->getText();
    _symbolTable[SKLexerMode][symbol] = ctx;
  }

  virtual void exitDelegateGrammar(ANTLRv4Parser::DelegateGrammarContext *ctx) override
  {
    ANTLRv4Parser::IdentifierContext *context = ctx->identifier().back().get();
    _imports.push_back(definitionForContext(context, false).text);
    _symbolTable[SkImport][_imports.back()] = context;
  }

  virtual void exitOption(ANTLRv4Parser::OptionContext *ctx) override
  {
    std::string option = ctx->identifier()->getText();
    if (toLower(option) == "tokenvocab")
    {
      tokenVocab = ctx->optionValue()->getText();
      _symbolTable[SKTokenVocab][tokenVocab] = ctx->optionValue().get();
    }
  }

private:
  SymbolTable &_symbolTable;
  std::vector<std::string> &_imports;
};

//----------------- SemanticListener -----------------------------------------------------------------------------------

enum SymbolLookupKind { // Multiple symbol kinds can be involved in a symbol lookup.
  SLKTokenRef,
  SLKRuleRef,
  SLKLexerMode,
  SLKTokenChannel,
};

class SemanticListener : public ANTLRv4ParserBaseListener {
public:
  SemanticListener(std::vector<ErrorEntry> &errors, std::function<bool (SymbolLookupKind, std::string)> checkSymbol)
  : _errors(errors), _checkSymbol(checkSymbol)
  {
  }

  virtual void exitTerminalRule(ANTLRv4Parser::TerminalRuleContext *ctx) override
  {
    if (ctx->TOKEN_REF() != nullptr)
    {
      std::string symbol = ctx->TOKEN_REF()->getText();
      checkAndAddError(SLKTokenRef, symbol, "Unknown token reference", ctx->TOKEN_REF()->getSymbol());
    }
  }

  virtual void exitRuleref(ANTLRv4Parser::RulerefContext *ctx) override
  {
    std::string symbol = ctx->RULE_REF()->getText();
    checkAndAddError(SLKRuleRef, symbol, "Unknown parser rule", ctx->RULE_REF()->getSymbol());
  }

  virtual void exitSetElement(ANTLRv4Parser::SetElementContext *ctx) override
  {
    if (ctx->TOKEN_REF() != nullptr)
    {
      std::string symbol = ctx->TOKEN_REF()->getText();
      checkAndAddError(SLKTokenRef, symbol, "Unknown token reference", ctx->TOKEN_REF()->getSymbol());
    }
  }
  
  virtual void exitLexerCommand(ANTLRv4Parser::LexerCommandContext *ctx) override
  {
    if (ctx->lexerCommandExpr() != nullptr && ctx->lexerCommandExpr()->identifier() != nullptr)
    {
      std::string name = ctx->lexerCommandName()->getText();
      SymbolLookupKind kind = SLKTokenRef;

      std::string value = toLower(name);
      if (value == "pushmode" || value == "mode")
      {
        name = "mode";
        kind = SLKLexerMode;
      } else if (value == "channel")
        kind = SLKTokenChannel;
      std::string symbol = ctx->lexerCommandExpr()->identifier()->getText();
      checkAndAddError(kind, symbol, "Unknown " + name, ctx->lexerCommandExpr()->identifier()->start);
    }
  }

protected:
  void checkAndAddError(SymbolLookupKind kind, std::string const& symbol, std::string const& message, Token *offendingToken)
  {
    if (!_checkSymbol(kind, symbol))
    {
      _errors.push_back({ message + " '" + symbol + "'", offendingToken->getCharPositionInLine(), offendingToken->getLine(),
        offendingToken->getStopIndex() - offendingToken->getStartIndex() + 1 });
    }
  }

private:
  std::vector<ErrorEntry> &_errors;
  std::function<bool (SymbolLookupKind, std::string)> _checkSymbol;
};

//----------------- ContextErrorListener -------------------------------------------------------------------------------

void ContextErrorListener::syntaxError(IRecognizer *, Token * offendingSymbol, size_t line,
  int charPositionInLine, const std::string &msg, std::exception_ptr)
{
  if (offendingSymbol == nullptr)
    _errors.push_back({ msg, charPositionInLine, (int)line, 1});
  else
    _errors.push_back({ msg, charPositionInLine, (int)line, offendingSymbol->getStopIndex() - offendingSymbol->getStartIndex() + 1});
}

//----------------- SourceContextImpl ----------------------------------------------------------------------------------

SourceContextImpl::SourceContextImpl(std::string const& sourceId)
: _lexer(&_input), _tokens(&_lexer), _parser(&_tokens), _errorListener(_syntaxErrors), _sourceId(sourceId)
{
  _lexer.removeErrorListeners();
  _lexer.addErrorListener(&_errorListener);
  _parser.removeErrorListeners();
  _parser.addErrorListener(&_errorListener);
}

//----------------------------------------------------------------------------------------------------------------------

void SourceContextImpl::parse(std::string const& source)
{
  imports.clear();
  _symbolTable.clear();
  _dependencies.clear();
  _syntaxErrors.clear();

  _input.load(source);
  _lexer.reset();
  _lexer.setInputStream(&_input);
  _tokens.setTokenSource(&_lexer);

  _parser.reset();
  _parser.setBuildParseTree(true);

  // First parse with the bail error strategy to get quick feedback for correct queries.
  _parser.setErrorHandler(std::make_shared<BailErrorStrategy>());
  _parser.getInterpreter<ParserATNSimulator>()->setPredictionMode(PredictionMode::SLL);

  try {
    _tree = _parser.grammarSpec();
  } catch (ParseCancellationException &) {
    // If parsing was canceled we either really have a syntax error or we need to do a second step,
    // now with the default strategy and LL parsing.
    _tokens.reset();
    _parser.reset();
    _parser.setErrorHandler(std::make_shared<DefaultErrorStrategy>());
    _parser.getInterpreter<ParserATNSimulator>()->setPredictionMode(PredictionMode::LL);
    _tree = _parser.grammarSpec();
  }

#if DEBUG == 1
  std::cout << "Found errors: " << _parser.getNumberOfSyntaxErrors() << std::endl;
  std::cout << "Parse tree: \n" << _tree->toStringTree(&_parser) << std::endl;
#endif

  DetailsListener listener(_symbolTable, imports);
  tree::ParseTreeWalker::DEFAULT.walk(&listener, _tree.get());

  // We don't create source context instances for dependencies (token vocabularies or imports) here and instead rely on
  // an outer context to do this and pass on references to us. This way we avoid duplicate instances.
  if (!listener.tokenVocab.empty())
    imports.insert(imports.begin(), listener.tokenVocab);
}

//----------------------------------------------------------------------------------------------------------------------

std::vector<ErrorEntry> SourceContextImpl::getErrors()
{
  std::vector<ErrorEntry> result = _syntaxErrors;

  std::vector<ErrorEntry> semanticErrors;
  SemanticListener semanticListener(semanticErrors, [this](SymbolLookupKind kind, std::string const& symbol) -> bool {

    auto lookup = [this](SymbolKind kind, std::string const& symbol) -> bool {
      if (_symbolTable[kind].count(symbol) > 0)
        return true;

      for (auto dep : _dependencies)
      {
        if (dep->_symbolTable[kind].count(symbol) > 0)
          return true;
      }
      return false;
    };

    switch (kind)
    {
      case SLKTokenRef:
        if (lookup(SKBuiltInLexerToken, symbol))
          return true;
        if (lookup(SKVirtualLexerToken, symbol))
          return true;
        if (lookup(SKFragmentLexerToken, symbol))
          return true;
        if (lookup(SKLexerToken, symbol))
          return true;
        break;

      case SLKLexerMode:
        if (lookup(SKBuiltInMode, symbol))
          return true;
        if (lookup(SKLexerMode, symbol))
          return true;
        break;

      case SLKTokenChannel:
        if (lookup(SKBuiltInChannel, symbol))
          return true;
        if (lookup(SKTokenChannel, symbol))
          return true;
        break;

      case SLKRuleRef:
        if (lookup(SKParserRule, symbol))
          return true;
        break;
    }

    return false;
  });

  tree::ParseTreeWalker::DEFAULT.walk(&semanticListener, _tree.get());
  result.insert(result.end(), semanticErrors.begin(), semanticErrors.end());

  return result;
}

//----------------------------------------------------------------------------------------------------------------------

/**
 * Determines the text and other details for the given symbol from either our own symbol table or one of our dependencies.
 */
SymbolInfo SourceContextImpl::getSymbolInfo(std::string const& symbol)
{
  // First look in our own symbol table, which overrides any imported grammar rule.
  for (auto &kind : _symbolTable)
  {
    if (kind.second.count(symbol) > 0)
    {
      auto context = kind.second[symbol];

      if (kind.first == SKTokenVocab || kind.first == SkImport)
      {
        // Get the source id from a dependent module.
        for (auto dep : _dependencies)
          if (dep->_sourceId.find(symbol) == 0)
          {
            return { kind.first, symbol, dep->_sourceId,
              definitionForContext(std::dynamic_pointer_cast<ParserRuleContext>(dep->_tree).get(), true) };
          }
      }

      std::string source = _sourceId;
      if (context == nullptr)
        source = "ANTLR runtime";
      return { kind.first, symbol, source, definitionForContext(context, true) };
    }
  }

  // Nothing in our table, so try the dependencies in order of appearance (effectively implementing rule overrides this way).
  for (auto dep : _dependencies)
  {
    SymbolInfo result = dep->getSymbolInfo(symbol);
    if (!result.source.empty())
      return result;
  }
  return {};
}

//----------------------------------------------------------------------------------------------------------------------

SymbolInfo SourceContextImpl::infoForSymbolAtPosition(size_t row, size_t column)
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
    case ANTLRv4Parser::RuleOptionValue:
    case ANTLRv4Parser::RuleDelegateGrammar:
    case ANTLRv4Parser::RuleModeSpec:
      return getSymbolInfo(terminal->getText());
  }

  return {};
}

//----------------------------------------------------------------------------------------------------------------------

std::vector<SymbolInfo> SourceContextImpl::listSymbols()
{
  std::vector<SymbolInfo> result;

  for (SymbolKind kind : {
    SKTokenVocab, SkImport, SKBuiltInLexerToken, SKVirtualLexerToken, SKFragmentLexerToken, SKLexerToken,
    SKBuiltInMode, SKLexerMode, SKBuiltInChannel, SKTokenChannel, SKParserRule})
  {
    for (auto &symbol : _symbolTable[kind])
    {
      if (symbol.second == nullptr)
        continue;

      // The symbols list only includes symbols from this source context, hence the source id is always
      // that of this context, even for imports and token vocabs. This is different for individual symbols.
      result.push_back({ kind, symbol.first, _sourceId, definitionForContext(symbol.second, true) });
    }
  }

  return result;
}

//----------------------------------------------------------------------------------------------------------------------

/**
 * Adds the given context to our list we use for symbol lookups.
 */
void SourceContextImpl::addDependency(SourceContextImpl *context)
{
  _dependencies.push_back(context);
}

//----------------------------------------------------------------------------------------------------------------------

