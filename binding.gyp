{
  "targets": [
    {
      "target_name": "antlr_graps",
      "sources": [
        "<!@(ls -1 src/*.cpp)",
        "<!@(ls -1 parser/*.cpp)",
        "<!@(ls -1 antlr4-runtime/*.cpp)",
        "<!@(ls -1 antlr4-runtime/atn/*.cpp)",
        "<!@(ls -1 antlr4-runtime/dfa/*.cpp)",
        "<!@(ls -1 antlr4-runtime/misc/*.cpp)",
        "<!@(ls -1 antlr4-runtime/support/*.cpp)",
        "<!@(ls -1 antlr4-runtime/tree/*.cpp)",
        "<!@(ls -1 antlr4-runtime/tree/pattern/*.cpp)",
        "<!@(ls -1 antlr4-runtime/tree/xpath/*.cpp)"
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
            'Debug': {
              'defines': [ 'WIN32' ],
              'msvs_settings': {
                'VCCLCompilerTool': {
                  'RuntimeLibrary': 3, # shared debug
                  'ExceptionHandling': 1, # /EHsc
                  'AdditionalOptions': [
                    '/EHsc'
                  ]
                }
              }
            },
            'Release': {
              'defines': [ 'WIN32' ],
              'msvs_settings': {
                'VCCLCompilerTool': {
                  'RuntimeLibrary': 2, # shared release
                  'ExceptionHandling': 1, # /EHsc
                  'AdditionalOptions': [
                    '/EHsc'
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
