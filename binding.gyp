# ===
# This is the main GYP file, which builds better-sqlite3 with SQLite itself.
# ===

{
  'includes': ['deps/common.gypi'],
  'variables': {
    # npm's implicit node-gyp rebuild should do nothing when the package
    # contains a prebuild for the host. Explicit build scripts override this.
    'force_build%': 0,
    'prebuild_exists%': '<!(node lib/binding.js)',
  },
  'targets': [
    {
      'target_name': 'better_sqlite3',
      'conditions': [
        ['force_build==1 or prebuild_exists==0', {
          'dependencies': ['deps/sqlite3.gyp:sqlite3'],
          'sources': ['src/better_sqlite3.cpp'],
          'include_dirs': ["<!@(node -p \"require('node-addon-api').include\")"],
          'defines': ['NAPI_VERSION=10', 'NAPI_DISABLE_CPP_EXCEPTIONS'],
          'cflags_cc': ['-std=c++20', '-fvisibility=hidden', '-fvisibility-inlines-hidden', '-flto'],
          'ldflags': ['-flto'],
          'xcode_settings': {
            'OTHER_CPLUSPLUSFLAGS': ['-std=c++20', '-stdlib=libc++'],
            'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES',
            'GCC_INLINES_ARE_PRIVATE_EXTERN': 'YES',
            'LLVM_LTO': 'YES',
          },
          'msvs_settings': {
            'VCCLCompilerTool': {
              'AdditionalOptions': ['/std:c++20'],
              'WholeProgramOptimization': 'true',
            },
            'VCLinkerTool': {
              'LinkTimeCodeGeneration': 1,
            },
          },
          'conditions': [['OS=="linux"', {
            'ldflags': ['-flto', '-Wl,-Bsymbolic', '-Wl,--exclude-libs,ALL'],
            'libraries': ['-ldl'],
          }]],
        }, {
          'type': 'none',
        }],
      ],
    },
    {
      'target_name': 'test_extension',
      'conditions': [
        ['force_build==1 or prebuild_exists==0', {
          'dependencies': ['deps/sqlite3.gyp:sqlite3'],
          'conditions': [['sqlite3 == ""', { 'sources': ['deps/test_extension.c'] }]],
        }, {
          'type': 'none',
        }],
      ],
    },
  ],
}
