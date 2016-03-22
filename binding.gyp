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
        "src/workers/open.cc",
        "src/workers/close.cc",
        "src/workers/run.cc",
        "src/workers/get.cc",
        "src/workers/all.cc",
        "src/workers/each.cc",
        "src/binder/binder.cc",
        "src/sqlite3_plus.cc"
      ]
    }
  ]
}
