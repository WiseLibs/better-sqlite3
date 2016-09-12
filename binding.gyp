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
        '-std=c++11',
        '-Wno-error',
        '-c'
      ],
      'xcode_settings': {
        'OTHER_CPLUSPLUSFLAGS': [
          '-std=c++11',
          '-stdlib=libc++'
        ],
      },
      "sources": [
        "src/objects/database/database.cc",
        "src/objects/statement/statement.cc",
        "src/objects/transaction/transaction.cc",
        "src/workers/database-workers/open.cc",
        "src/workers/database-workers/close.cc",
        "src/workers/database-workers/checkpoint.cc",
        "src/workers/statement-workers/run.cc",
        "src/workers/statement-workers/get.cc",
        "src/workers/statement-workers/all.cc",
        "src/workers/statement-workers/each.cc",
        "src/workers/transaction-worker.cc",
        "src/binder/binder.cc",
        "src/multi-binder/multi-binder.cc",
        "src/better_sqlite3.cc"
      ]
    }
  ]
}
