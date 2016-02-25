{
  "includes": [ "deps/common-sqlite.gypi" ],
  "targets": [
    {
      "target_name": "sqlite3_plus",
      "include_dirs": ["<!(node -e \"require('nan')\")"],
      "sources": [
        "src/database.cc",
        "src/sqlite3_plus.cc",
        "src/statement.cc"
      ]
    }
  ]
}
