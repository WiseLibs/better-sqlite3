# Custom configuration

If you want to use a customized version of [SQLite](https://www.sqlite.org) with `better-sqlite3`, you can compile it against your own [amalgamation](https://www.sqlite.org/amalgamation.html) (a directory containing `sqlite3.c` and `sqlite3.h`).

`better-sqlite3` ships with prebuilt binaries and does not compile anything when it's installed, so you'll need to compile it yourself. The easiest way to do this automatically is to add a `postinstall` script to your own `package.json`, which compiles `better-sqlite3` after the rest of your dependencies have been installed. Once compiled, your build is used instead of the prebuilt binary.

### Step by step example

1. Download the SQLite source code from [their website](https://sqlite.com/download.html) (e.g., `sqlite-amalgamation-1234567.zip`)
2. Unzip it, and move the `sqlite3.c` and `sqlite3.h` files into a folder in your project (e.g., `sqlite-amalgamation/`)
3. Define your preferred [compile time options](https://www.sqlite.org/compile.html) at the top of `sqlite3.c` (see [below](#compile-time-options))
4. Add `better-sqlite3` to your `dependencies` as usual
5. Save the script below as `scripts/build-sqlite.js` in your project
6. Add a `postinstall` script to your `package.json`, as shown below
7. Run `npm install` in your project folder

```js
// scripts/build-sqlite.js
'use strict';
const { execFileSync } = require('child_process');
const path = require('path');

// This must be an absolute path.
const amalgamation = path.resolve(__dirname, '..', 'sqlite-amalgamation');
const betterSqlite3 = path.dirname(require.resolve('better-sqlite3/package.json'));

// npm sets this variable to the location of its bundled node-gyp.
if (!process.env.npm_config_node_gyp) {
  throw new Error('This script must be run by npm (e.g., "npm run postinstall")');
}

execFileSync(process.execPath, [
  process.env.npm_config_node_gyp,
  'rebuild',
  '--release',
  '--force_build=1',
  `--sqlite3=${amalgamation}`,
], { cwd: betterSqlite3, stdio: 'inherit' });
```

```json
{
  "scripts": {
    "postinstall": "node scripts/build-sqlite.js"
  },
  "dependencies": {
    "better-sqlite3": "..."
  }
}
```

From then on, `npm install` and `npm ci` will compile `better-sqlite3` with your amalgamation every time. Compiling requires the usual [`node-gyp` prerequisites](https://github.com/nodejs/node-gyp#installation) (Python and a C++ compiler); see [troubleshooting](./troubleshooting.md) if the build fails.

There are some cases where npm won't run your `postinstall` script, and you'll get the prebuilt binary instead:

- When you add or upgrade a specific package (e.g., `npm install better-sqlite3@latest`), npm doesn't run your project's own install scripts. Run `npm install` (with no arguments) afterwards to compile it again.
- `npm rebuild` doesn't run your project's own install scripts either. Use `npm run postinstall` instead.
- Your build won't be compiled if install scripts are disabled (e.g., `--ignore-scripts`).

To verify which SQLite build you're using, check `db.pragma('compile_options')`.

### Compile time options

When you use a custom amalgamation, none of the [bundled configuration's](#bundled-configuration) compile time options are applied; the only option that `better-sqlite3` defines for you is `SQLITE_ENABLE_COLUMN_METADATA`, which it requires. Any other [compile time options](https://www.sqlite.org/compile.html) must be defined directly within `sqlite3.c`, as shown below.

```c
// These go at the top of the file
#define SQLITE_ENABLE_FTS5 1
#define SQLITE_DEFAULT_CACHE_SIZE 16000

// ... the original content of the file remains below
```

### Encryption

If you're using a SQLite encryption extension that is a drop-in replacement for SQLite (such as [SEE](https://www.sqlite.org/see/doc/release/www/readme.wiki) or [SQLite3MultipleCiphers](https://github.com/utelle/SQLite3MultipleCiphers)), then simply replace `sqlite3.c` and `sqlite3.h` with the source files of your encryption extension.

# Bundled configuration

By default, this distribution currently uses SQLite **version 3.54.1** with the following [compilation options](https://www.sqlite.org/compile.html):

```
HAVE_INT16_T=1
HAVE_INT32_T=1
HAVE_INT8_T=1
HAVE_STDINT_H=1
HAVE_UINT16_T=1
HAVE_UINT32_T=1
HAVE_UINT8_T=1
HAVE_USLEEP=1
SQLITE_DEFAULT_CACHE_SIZE=-16000
SQLITE_DEFAULT_FOREIGN_KEYS=1
SQLITE_DEFAULT_MEMSTATUS=0
SQLITE_DEFAULT_WAL_SYNCHRONOUS=1
SQLITE_DQS=0
SQLITE_ENABLE_COLUMN_METADATA
SQLITE_ENABLE_DBSTAT_VTAB
SQLITE_ENABLE_DESERIALIZE
SQLITE_ENABLE_FTS3
SQLITE_ENABLE_FTS3_PARENTHESIS
SQLITE_ENABLE_FTS4
SQLITE_ENABLE_FTS5
SQLITE_ENABLE_GEOPOLY
SQLITE_ENABLE_JSON1
SQLITE_ENABLE_MATH_FUNCTIONS
SQLITE_ENABLE_PERCENTILE
SQLITE_ENABLE_RTREE
SQLITE_ENABLE_STAT4
SQLITE_ENABLE_UPDATE_DELETE_LIMIT
SQLITE_LIKE_DOESNT_MATCH_BLOBS
SQLITE_OMIT_DEPRECATED
SQLITE_OMIT_PROGRESS_CALLBACK
SQLITE_OMIT_SHARED_CACHE
SQLITE_OMIT_TCL_VARIABLE
SQLITE_SOUNDEX
SQLITE_THREADSAFE=2
SQLITE_TRACE_SIZE_LIMIT=32
SQLITE_USE_URI=0
```
