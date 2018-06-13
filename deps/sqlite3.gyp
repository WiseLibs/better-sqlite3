{
  'includes': [ 'common.gypi' ],
  'target_defaults': {
    'default_configuration': 'Release',
    'cflags': [
      '-std=c99'
    ],
    'xcode_settings': {
      'OTHER_CFLAGS': [
        '-std=c99'
      ],
    },
    'configurations': {
      'Debug': {
        'defines': [ 'DEBUG', '_DEBUG', 'SQLITE_ENABLE_API_ARMOR'],
        'msvs_settings': {
          'VCCLCompilerTool': {
            'RuntimeLibrary': 1, # static debug
          },
        },
      },
      'Release': {
        'defines': [ 'NDEBUG' ],
        'msvs_settings': {
          'VCCLCompilerTool': {
            'RuntimeLibrary': 0, # static release
          },
        },
      }
    },
    'msvs_settings': {
      'VCCLCompilerTool': {
      },
      'VCLibrarianTool': {
      },
      'VCLinkerTool': {
        'GenerateDebugInformation': 'true',
      },
    },
    'conditions': [
      ['OS == "win"', {
        'defines': [
          'WIN32'
        ],
      }]
    ],
  },

  'targets': [
    {
      'target_name': 'action_before_build',
      'type': 'none',
      'hard_dependency': 1,
      'actions': [
        {
          'action_name': 'unpack_sqlite_dep',
          'inputs': [
            './sqlite3-amalg.tar.gz'
          ],
          'outputs': [
            '<(SHARED_INTERMEDIATE_DIR)/sqlite3-amalg/sqlite3.c',
            '<(SHARED_INTERMEDIATE_DIR)/sqlite3-amalg/sqlite3.h'
          ],
          'action': ['python','./extract.py','<@(_inputs)','<(SHARED_INTERMEDIATE_DIR)/sqlite3-amalg/']
        }
      ],
      'direct_dependent_settings': {
        'include_dirs': [
          '<(SHARED_INTERMEDIATE_DIR)/sqlite3-amalg/',
        ]
      },
    },
    {
      'target_name': 'sqlite3',
      'type': 'static_library',
      'include_dirs': [ '<(SHARED_INTERMEDIATE_DIR)/sqlite3-amalg/' ],
      'dependencies': [
        'action_before_build'
      ],
      'sources': [
        '<(SHARED_INTERMEDIATE_DIR)/sqlite3-amalg/sqlite3.c'
      ],
      'direct_dependent_settings': {
        'include_dirs': [ '<(SHARED_INTERMEDIATE_DIR)/sqlite3-amalg/' ]
      },
      'cflags_cc': [
        '-Wno-unused-value',
      ],
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
        'SQLITE_DEFAULT_WAL_SYNCHRONOUS=1'
      ],
      'export_dependent_settings': [
        'action_before_build',
      ]
    }
  ]
}
