# Custom configuration

If you want to use a customized version of [SQLite3](https://www.sqlite.org) with `better-sqlite3`, you can do so by specifying the directory of your [custom amalgamation](https://www.sqlite.org/amalgamation.html) during installation.

```bash
npm install --sqlite3=/my/path/to/sqlite-amalgamation
```

Your amalgamation directory should contain `sqlite3.c` and `sqlite3.h`. Any desired [compile time options](https://www.sqlite.org/compile.html) must be defined directly within `sqlite3.c`.

# Bundled configuration

By default, this distribution currently uses SQLite3 **version 3.29.0** with the following [compilation options](https://www.sqlite.org/compile.html):

```
SQLITE_THREADSAFE=0
SQLITE_DEFAULT_MEMSTATUS=0
SQLITE_OMIT_DEPRECATED
SQLITE_OMIT_GET_TABLE
SQLITE_OMIT_TCL_VARIABLE
SQLITE_OMIT_PROGRESS_CALLBACK
SQLITE_TRACE_SIZE_LIMIT=32
SQLITE_DEFAULT_CACHE_SIZE=-16000
SQLITE_DEFAULT_FOREIGN_KEYS=1
SQLITE_DEFAULT_WAL_SYNCHRONOUS=1
SQLITE_USE_URI=1
SQLITE_ENABLE_COLUMN_METADATA
SQLITE_ENABLE_UPDATE_DELETE_LIMIT
SQLITE_ENABLE_STAT4
SQLITE_ENABLE_FTS3_PARENTHESIS
SQLITE_ENABLE_FTS3
SQLITE_ENABLE_FTS4
SQLITE_ENABLE_FTS5
SQLITE_ENABLE_JSON1
SQLITE_ENABLE_RTREE
SQLITE_INTROSPECTION_PRAGMAS
SQLITE_SOUNDEX
```
