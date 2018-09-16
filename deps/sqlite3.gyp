{
  'includes': ['common.gypi'],
  'target_defaults': {
    'configurations': {
      'Debug': {
        'cflags': [
          '-Wno-sign-compare',
          '-Wno-unused-function',
        ],
        'xcode_settings': {
          'WARNING_CFLAGS': [
            '-Wno-sign-compare',
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
        'inputs': ['./sqlite-autoconf-<@(sqlite_version).tar.gz'],
        'outputs': ['<(SHARED_INTERMEDIATE_DIR)/sqlite-autoconf-<@(sqlite_version)/sqlite3.c'],
        'action': ['node', './extract.js', './sqlite-autoconf-<@(sqlite_version).tar.gz', '<(SHARED_INTERMEDIATE_DIR)'],
      }],
    },
    {
      'target_name': 'sqlite3',
      'type': 'static_library',
      'dependencies': ['action_before_build'],
      'sources': ['<(SHARED_INTERMEDIATE_DIR)/sqlite-autoconf-<@(sqlite_version)/sqlite3.c'],
      'include_dirs': ['<(SHARED_INTERMEDIATE_DIR)/sqlite-autoconf-<@(sqlite_version)/'],
      'direct_dependent_settings': {
        'include_dirs': ['<(SHARED_INTERMEDIATE_DIR)/sqlite-autoconf-<@(sqlite_version)/'],
      },
      'cflags': [
        '-std=c99',
      ],
      'xcode_settings': {
        'OTHER_CFLAGS': [
          '-std=c99',
        ],
      },
      'defines': [
        'SQLITE_THREADSAFE=0',
        'SQLITE_DEFAULT_MEMSTATUS=0',
        'SQLITE_OMIT_DECLTYPE',
        'SQLITE_OMIT_DEPRECATED',
        'SQLITE_OMIT_PROGRESS_CALLBACK',
        'SQLITE_ENABLE_FTS4',
        'SQLITE_ENABLE_FTS5',
        'SQLITE_ENABLE_JSON1',
        'SQLITE_ENABLE_RTREE',
        'SQLITE_USE_URI=1',
        'SQLITE_DEFAULT_CACHE_SIZE=-16000',
        'SQLITE_DEFAULT_FOREIGN_KEYS=1',
        'SQLITE_DEFAULT_WAL_SYNCHRONOUS=1',
      ],
    },
  ],
}
