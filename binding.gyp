{
  "targets": [
    {
      "target_name": "antlr4_graps",
      "sources": [
	    "antlr4-runtime/ANTLRFileStream.cpp",
        "antlr4-runtime/ANTLRInputStream.cpp",
        "antlr4-runtime/atn/AbstractPredicateTransition.cpp",
        "antlr4-runtime/atn/ActionTransition.cpp",
        "antlr4-runtime/atn/AmbiguityInfo.cpp",
        "antlr4-runtime/atn/ArrayPredictionContext.cpp",
        "antlr4-runtime/atn/ATN.cpp",
        "antlr4-runtime/atn/ATNConfig.cpp",
        "antlr4-runtime/atn/ATNConfigSet.cpp",
        "antlr4-runtime/atn/ATNDeserializationOptions.cpp",
        "antlr4-runtime/atn/ATNDeserializer.cpp",
        "antlr4-runtime/atn/ATNSerializer.cpp",
        "antlr4-runtime/atn/ATNSimulator.cpp",
        "antlr4-runtime/atn/ATNState.cpp",
        "antlr4-runtime/atn/AtomTransition.cpp",
        "antlr4-runtime/atn/BasicBlockStartState.cpp",
        "antlr4-runtime/atn/BasicState.cpp",
        "antlr4-runtime/atn/BlockEndState.cpp",
        "antlr4-runtime/atn/ContextSensitivityInfo.cpp",
        "antlr4-runtime/atn/DecisionEventInfo.cpp",
        "antlr4-runtime/atn/DecisionInfo.cpp",
        "antlr4-runtime/atn/DecisionState.cpp",
        "antlr4-runtime/atn/EmptyPredictionContext.cpp",
        "antlr4-runtime/atn/EpsilonTransition.cpp",
        "antlr4-runtime/atn/ErrorInfo.cpp",
        "antlr4-runtime/atn/LexerActionExecutor.cpp",
        "antlr4-runtime/atn/LexerATNConfig.cpp",
        "antlr4-runtime/atn/LexerATNSimulator.cpp",
        "antlr4-runtime/atn/LexerChannelAction.cpp",
        "antlr4-runtime/atn/LexerCustomAction.cpp",
        "antlr4-runtime/atn/LexerIndexedCustomAction.cpp",
        "antlr4-runtime/atn/LexerModeAction.cpp",
        "antlr4-runtime/atn/LexerMoreAction.cpp",
        "antlr4-runtime/atn/LexerPopModeAction.cpp",
        "antlr4-runtime/atn/LexerPushModeAction.cpp",
        "antlr4-runtime/atn/LexerSkipAction.cpp",
        "antlr4-runtime/atn/LexerTypeAction.cpp",
        "antlr4-runtime/atn/LL1Analyzer.cpp",
        "antlr4-runtime/atn/LookaheadEventInfo.cpp",
        "antlr4-runtime/atn/LoopEndState.cpp",
        "antlr4-runtime/atn/NotSetTransition.cpp",
        "antlr4-runtime/atn/OrderedATNConfigSet.cpp",
        "antlr4-runtime/atn/ParseInfo.cpp",
        "antlr4-runtime/atn/ParserATNSimulator.cpp",
        "antlr4-runtime/atn/PlusBlockStartState.cpp",
        "antlr4-runtime/atn/PlusLoopbackState.cpp",
        "antlr4-runtime/atn/PrecedencePredicateTransition.cpp",
        "antlr4-runtime/atn/PredicateEvalInfo.cpp",
        "antlr4-runtime/atn/PredicateTransition.cpp",
        "antlr4-runtime/atn/PredictionContext.cpp",
        "antlr4-runtime/atn/PredictionMode.cpp",
        "antlr4-runtime/atn/ProfilingATNSimulator.cpp",
        "antlr4-runtime/atn/RangeTransition.cpp",
        "antlr4-runtime/atn/RuleStartState.cpp",
        "antlr4-runtime/atn/RuleStopState.cpp",
        "antlr4-runtime/atn/RuleTransition.cpp",
        "antlr4-runtime/atn/SemanticContext.cpp",
        "antlr4-runtime/atn/SetTransition.cpp",
        "antlr4-runtime/atn/SingletonPredictionContext.cpp",
        "antlr4-runtime/atn/StarBlockStartState.cpp",
        "antlr4-runtime/atn/StarLoopbackState.cpp",
        "antlr4-runtime/atn/StarLoopEntryState.cpp",
        "antlr4-runtime/atn/TokensStartState.cpp",
        "antlr4-runtime/atn/Transition.cpp",
        "antlr4-runtime/atn/WildcardTransition.cpp",
        "antlr4-runtime/BailErrorStrategy.cpp",
        "antlr4-runtime/BaseErrorListener.cpp",
        "antlr4-runtime/BufferedTokenStream.cpp",
        "antlr4-runtime/CharStream.cpp",
        "antlr4-runtime/CommonToken.cpp",
        "antlr4-runtime/CommonTokenFactory.cpp",
        "antlr4-runtime/CommonTokenStream.cpp",
        "antlr4-runtime/ConsoleErrorListener.cpp",
        "antlr4-runtime/DefaultErrorStrategy.cpp",
        "antlr4-runtime/dfa/DFA.cpp",
        "antlr4-runtime/dfa/DFASerializer.cpp",
        "antlr4-runtime/dfa/DFAState.cpp",
        "antlr4-runtime/dfa/LexerDFASerializer.cpp",
        "antlr4-runtime/DiagnosticErrorListener.cpp",
        "antlr4-runtime/Exceptions.cpp",
        "antlr4-runtime/FailedPredicateException.cpp",
        "antlr4-runtime/InputMismatchException.cpp",
        "antlr4-runtime/InterpreterRuleContext.cpp",
        "antlr4-runtime/IntStream.cpp",
        "antlr4-runtime/Lexer.cpp",
        "antlr4-runtime/LexerInterpreter.cpp",
        "antlr4-runtime/LexerNoViableAltException.cpp",
        "antlr4-runtime/ListTokenSource.cpp",
        "antlr4-runtime/misc/Interval.cpp",
        "antlr4-runtime/misc/IntervalSet.cpp",
        "antlr4-runtime/misc/MurmurHash.cpp",
        "antlr4-runtime/NoViableAltException.cpp",
        "antlr4-runtime/Parser.cpp",
        "antlr4-runtime/ParserInterpreter.cpp",
        "antlr4-runtime/ParserRuleContext.cpp",
        "antlr4-runtime/ProxyErrorListener.cpp",
        "antlr4-runtime/RecognitionException.cpp",
        "antlr4-runtime/Recognizer.cpp",
        "antlr4-runtime/RuleContext.cpp",
        "antlr4-runtime/RuleContextWithAltNum.cpp",
        "antlr4-runtime/RuntimeMetaData.cpp",
        "antlr4-runtime/support/Arrays.cpp",
        "antlr4-runtime/support/CPPUtils.cpp",
        "antlr4-runtime/support/guid.cpp",
        "antlr4-runtime/support/StringUtils.cpp",
        "antlr4-runtime/TokenStream.cpp",
        "antlr4-runtime/TokenStreamRewriter.cpp",
        "antlr4-runtime/tree/ErrorNodeImpl.cpp",
        "antlr4-runtime/tree/ParseTreeWalker.cpp",
        "antlr4-runtime/tree/pattern/ParseTreeMatch.cpp",
        "antlr4-runtime/tree/pattern/ParseTreePattern.cpp",
        "antlr4-runtime/tree/pattern/ParseTreePatternMatcher.cpp",
        "antlr4-runtime/tree/pattern/RuleTagToken.cpp",
        "antlr4-runtime/tree/pattern/TagChunk.cpp",
        "antlr4-runtime/tree/pattern/TextChunk.cpp",
        "antlr4-runtime/tree/pattern/TokenTagToken.cpp",
        "antlr4-runtime/tree/TerminalNodeImpl.cpp",
        "antlr4-runtime/tree/Tree.cpp",
        "antlr4-runtime/tree/Trees.cpp",
        "antlr4-runtime/tree/xpath/XPath.cpp",
        "antlr4-runtime/tree/xpath/XPathElement.cpp",
        "antlr4-runtime/tree/xpath/XPathLexer.cpp",
        "antlr4-runtime/tree/xpath/XPathLexerErrorListener.cpp",
        "antlr4-runtime/tree/xpath/XPathRuleAnywhereElement.cpp",
        "antlr4-runtime/tree/xpath/XPathRuleElement.cpp",
        "antlr4-runtime/tree/xpath/XPathTokenAnywhereElement.cpp",
        "antlr4-runtime/tree/xpath/XPathTokenElement.cpp",
        "antlr4-runtime/tree/xpath/XPathWildcardAnywhereElement.cpp",
        "antlr4-runtime/tree/xpath/XPathWildcardElement.cpp",
        "antlr4-runtime/UnbufferedCharStream.cpp",
        "antlr4-runtime/UnbufferedTokenStream.cpp",
        "antlr4-runtime/Vocabulary.cpp",
        "parser/ANTLRv4Lexer.cpp",
        "parser/ANTLRv4Parser.cpp",
        "parser/ANTLRv4ParserBaseListener.cpp",
        "parser/ANTLRv4ParserBaseVisitor.cpp",
        "parser/ANTLRv4ParserListener.cpp",
        "parser/ANTLRv4ParserVisitor.cpp",
        "parser/LexerAdaptor.cpp",
        "src/antlr-graps.cpp",
        "src/SourceContextImpl.cpp"
	  ],
      "include_dirs": [
        "antlr4-runtime",
        "parser",
      ],

      "conditions": [
        [ "OS=='mac'", {
          "xcode_settings": {
            'MACOSX_DEPLOYMENT_TARGET': '10.9',
            "CLANG_CXX_LIBRARY": "libc++",
            "GCC_ENABLE_CPP_RTTI": "YES",
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
          },
        }],

        [ 'OS=="win"', {
          'configurations': {
            'Debug': { # Note: on Windows there are by default no debug node libs.
              'defines': [ 'ANTLR4CPP_EXPORTS', 'DELAYIMP_INSECURE_WRITABLE_HOOKS' ],
              'msvs_settings': {
                'VCCLCompilerTool': {
                  'ExceptionHandling': 1, # /EHsc
                  'WarningLevel': 4,
                  'RuntimeTypeInfo': 'true',
                  'DisableSpecificWarnings': [ "4100" ], # Unused parameter
                  'AdditionalOptions': [
                  ]
                }
              }
            },
            'Release': {
              'defines': [ 'ANTLR4CPP_EXPORTS', 'DELAYIMP_INSECURE_WRITABLE_HOOKS' ],
              'msvs_settings': {
                'VCCLCompilerTool': {
                  'ExceptionHandling': 1, # /EHsc
                  'WarningLevel': 4,
                  'RuntimeTypeInfo': 'true',
                  'DisableSpecificWarnings': [ "4100" ],
                  'AdditionalOptions': [
                  ]
                }
              }
            }
          }
        }],

        [ "OS=='linux'", {
          'configurations': {
            'Debug': {
              'cflags': [ '-std=c++0x', '-fexceptions', '-frtti' ],
              'cflags_cc': [ '-std=c++0x', '-fexceptions', '-frtti' ]
            },
            'Release': {
              'cflags': [ '-std=c++0x', '-fexceptions', '-frtti' ],
              'cflags_cc': [ '-std=c++0x', '-fexceptions', '-frtti' ]
            }
          }
        }]
      ],
    }
  ]
}
