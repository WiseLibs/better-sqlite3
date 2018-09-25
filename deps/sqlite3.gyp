# ===
# This configuration defines options specific to compiling SQLite3 itself.
# Compile-time options are loaded by the auto-generated file "defines.gypi".
# Before SQLite3 is compiled, it gets extracted from "sqlite3.tar.gz".
# ===

{
  'includes': ['common.gypi', 'defines.gypi'],
  'target_defaults': {
    'configurations': {
      'Debug': {
        'cflags': [
          '-Wno-unused-function',
        ],
        'xcode_settings': {
          'WARNING_CFLAGS': [
            '-Wno-unused-function',
          ],
        },
        'msvs_settings': {
          'VCCLCompilerTool': {
            'RuntimeLibrary': 1, # static debug
          },
        },
      },
      'Release': {
        'msvs_settings': {
          'VCCLCompilerTool': {
            'RuntimeLibrary': 0, # static release
          },
        },
      },
    },
  },
  'targets': [
    {
      'target_name': 'action_before_build',
      'type': 'none',
      'hard_dependency': 1,
      'actions': [{
        'action_name': 'unpack_sqlite_dep',
        'inputs': ['sqlite3.tar.gz'],
        'outputs': [
          '<(SHARED_INTERMEDIATE_DIR)/sqlite3/sqlite3.c',
          '<(SHARED_INTERMEDIATE_DIR)/sqlite3/sqlite3.h',
          '<(SHARED_INTERMEDIATE_DIR)/sqlite3/sqlite3ext.h',
        ],
        'action': ['node', 'extract.js', '<(SHARED_INTERMEDIATE_DIR)/sqlite3'],
      }],
    },
    {
      'target_name': 'sqlite3',
      'type': 'static_library',
      'dependencies': ['action_before_build'],
      'sources': ['<(SHARED_INTERMEDIATE_DIR)/sqlite3/sqlite3.c'],
      'include_dirs': ['<(SHARED_INTERMEDIATE_DIR)/sqlite3/'],
      'direct_dependent_settings': {
        'include_dirs': ['<(SHARED_INTERMEDIATE_DIR)/sqlite3/'],
      },
      'cflags': [
        '-std=c99',
        '-Wno-sign-compare',
      ],
      'xcode_settings': {
        'OTHER_CFLAGS': [
          '-std=c99',
        ],
        'WARNING_CFLAGS': [
          '-Wno-sign-compare',
        ],
      },
    },
  ],
}
