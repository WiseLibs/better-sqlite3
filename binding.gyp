{
  "includes": [ "deps/common.gypi" ],
  "targets": [
    {
      "target_name": "better_sqlite3",
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
        "src/better_sqlite3.cc"
      ]
    }
  ]
}
