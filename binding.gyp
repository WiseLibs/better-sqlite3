# ===
# This is the main GYP file, which builds better-sqlite3 with SQLite3 itself.
# ===

{
  'includes': ['deps/common.gypi'],
  'targets': [
    {
      'target_name': 'better_sqlite3',
      'dependencies': ['deps/sqlite3.gyp:sqlite3'],
      'sources': ['src/better_sqlite3.cpp'],
      'cflags': [
        '-std=c++11',
      ],
      'xcode_settings': {
        'OTHER_CPLUSPLUSFLAGS': [
          '-std=c++11',
          '-stdlib=libc++',
        ],
      },
    },
    {
      'target_name': 'test_extension',
      'dependencies': ['deps/sqlite3.gyp:action_before_build'],
      'sources': ['deps/test_extension.c'],
    },
  ],
}
