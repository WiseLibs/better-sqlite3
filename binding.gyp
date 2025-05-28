# ===
# This is the main GYP file, which builds better-sqlite3 with SQLite itself.
# ===

{
  'includes': ['deps/common.gypi'],
  'targets': [
    {
      'target_name': 'better_sqlite3',
      'dependencies': ['deps/sqlite3.gyp:sqlite3'],
      'sources': [
        'src/better_sqlite3.cpp',
        'src/objects/database.cpp',
        'src/objects/statement.cpp',
        'src/objects/statement-iterator.cpp',
        'src/objects/backup.cpp',
        'src/util/macros.cpp',
        'src/util/constants.cpp',
        'src/util/bind-map.cpp',
        'src/util/binder.cpp',
        'src/util/data-converter.cpp',
        'src/util/custom-function.cpp',
        'src/util/custom-aggregate.cpp',
        'src/util/custom-table.cpp',
        'src/util/data.cpp'
      ],
      'cflags_cc': ['-std=c++20'],
      'xcode_settings': {
        'OTHER_CPLUSPLUSFLAGS': ['-std=c++20', '-stdlib=libc++'],
      },
      'msvs_settings': {
        'VCCLCompilerTool': {
          'AdditionalOptions': [
            '/std:c++20',
          ],
        },
      },
      'conditions': [
        ['OS=="linux"', {
          'ldflags': [
            '-Wl,-Bsymbolic',
            '-Wl,--exclude-libs,ALL',
          ],
        }],
      ],
    },
    {
      'target_name': 'test_extension',
      'dependencies': ['deps/sqlite3.gyp:sqlite3'],
      'conditions': [['sqlite3 == ""', { 'sources': ['deps/test_extension.c'] }]],
    },
  ],
}
