{
  "includes": [ "deps/common-sqlite.gypi" ],
  "targets": [
    {
      "target_name": "node_sqlite3_plus",
      "include_dirs": ["<!(node -e \"require('nan')\")"],
      "cflags": [ "-include ../src/gcc-preinclude.h" ],
      "sources": [
        "src/database.cc",
        "src/node_sqlite3_plus.cc",
        "src/statement.cc"
      ]
    }
  ]
}
