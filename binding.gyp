{
  "includes": [ "deps/common.gypi" ],
  "targets": [
    {
      "target_name": "better_sqlite3",
      "include_dirs": ["<!(node -e \"require('nan')\")"],
      "dependencies": [
        "deps/sqlite3.gyp:sqlite3"
      ],
      'cflags': [
        '-std=c++11'
      ],
      'xcode_settings': {
        'OTHER_CPLUSPLUSFLAGS': [
          '-std=c++11',
          '-stdlib=libc++'
        ],
      },
      "sources": [
        "src/objects/int64/int64.cc",
        "src/objects/database/database.cc",
        "src/objects/statement/statement.cc",
        "src/objects/transaction/transaction.cc",
        "src/workers/open.cc",
        "src/workers/close.cc",
        "src/binder/binder.cc",
        "src/multi-binder/multi-binder.cc",
        "src/better_sqlite3.cc"
      ]
    }
  ]
}
