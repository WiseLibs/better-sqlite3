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
        "src/database.cc",
        "src/sqlite3_plus.cc",
        # "src/statement.cc"
      ]
    }
  ]
}
