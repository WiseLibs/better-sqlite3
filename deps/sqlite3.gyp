# ===
# This configuration defines options specific to compiling SQLite3 itself.
# Compile-time options are loaded by the auto-generated file "defines.gypi".
# Before SQLite3 is compiled, it gets extracted from "sqlite3.tar.gz".
# The --sqlite3 option can be provided to use a custom amalgamation instead.
# ===

{
  'includes': ['common.gypi'],
  'targets': [
    {
      'target_name': 'locate_sqlite3',
      'type': 'none',
      'hard_dependency': 1,
      'conditions': [['sqlite3 == ""', {
        'actions': [{
          'action_name': 'extract_sqlite3',
          'inputs': ['sqlite3.tar.gz'],
          'outputs': [
            '<(SHARED_INTERMEDIATE_DIR)/sqlite3/sqlite3.c',
            '<(SHARED_INTERMEDIATE_DIR)/sqlite3/sqlite3.h',
            '<(SHARED_INTERMEDIATE_DIR)/sqlite3/sqlite3ext.h',
          ],
          'action': ['node', 'extract.js', '<(SHARED_INTERMEDIATE_DIR)/sqlite3'],
        }],
      }, {
        'actions': [{
          'action_name': 'symlink_sqlite3',
          'inputs': [],
          'outputs': [
            '<(SHARED_INTERMEDIATE_DIR)/sqlite3/sqlite3.c',
            '<(SHARED_INTERMEDIATE_DIR)/sqlite3/sqlite3.h',
          ],
          'action': ['node', 'symlink.js', '<(SHARED_INTERMEDIATE_DIR)/sqlite3', '<(sqlite3)'],
        }],
      }]],
    },
    {
      'target_name': 'sqlite3',
      'type': 'static_library',
      'conditions': [['sqlite3 == ""', { 'includes': ['defines.gypi'] }]],
      'dependencies': ['locate_sqlite3'],
      'sources': ['<(SHARED_INTERMEDIATE_DIR)/sqlite3/sqlite3.c'],
      'include_dirs': ['<(SHARED_INTERMEDIATE_DIR)/sqlite3/'],
      'direct_dependent_settings': {
        'include_dirs': ['<(SHARED_INTERMEDIATE_DIR)/sqlite3/'],
      },
      'cflags': [
        '-std=c99',
        '-Wno-unused-function',
        '-Wno-sign-compare',
      ],
      'xcode_settings': {
        'OTHER_CFLAGS': [
          '-std=c99',
        ],
        'WARNING_CFLAGS': [
          '-Wno-unused-function',
          '-Wno-sign-compare',
        ],
      },
      'configurations': {
        'Debug': {
          'msvs_settings': { 'VCCLCompilerTool': { 'RuntimeLibrary': 1 } }, # static debug
        },
        'Release': {
          'msvs_settings': { 'VCCLCompilerTool': { 'RuntimeLibrary': 0 } }, # static release
        },
      },
    },
  ],
}
