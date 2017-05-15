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
        "src2/better_sqlite3.cpp"
      ]
    }
  ]
}
