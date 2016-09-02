{
  "includes": [ "deps/common-sqlite.gypi" ],
  "targets": [
    {
      "target_name": "sqlite3_plus",
      "include_dirs": ["<!(node -e \"require('nan')\")"],
      "dependencies": [
        "deps/sqlite3.gyp:sqlite3"
      ],
      "sources": [
        "src/objects/database/database.cc",
        "src/objects/statement/statement.cc",
        "src/objects/transaction/transaction.cc",
        "src/workers/database-workers/open.cc",
        "src/workers/database-workers/close.cc",
        "src/workers/statement-workers/run.cc",
        "src/workers/statement-workers/get.cc",
        "src/workers/statement-workers/all.cc",
        "src/workers/statement-workers/each.cc",
        "src/workers/transaction-worker.cc",
        "src/binder/binder.cc",
        "src/multi-binder/multi-binder.cc",
        "src/sqlite3_plus.cc"
      ]
    }
  ]
}
