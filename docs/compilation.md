# Compilation options

This distribution currently uses **SQLite version 3.24.0** with the following [compilation options]:

- SQLITE_OMIT_DEPRECATED
- SQLITE_ENABLE_FTS4
- SQLITE_ENABLE_FTS5
- SQLITE_ENABLE_JSON1
- SQLITE_ENABLE_RTREE
- SQLITE_DEFAULT_CACHE_SIZE=-16000
- SQLITE_DEFAULT_FOREIGN_KEYS=1
- SQLITE_DEFAULT_WAL_SYNCHRONOUS=1

[compilation options]: https://www.sqlite.org/compile.html
