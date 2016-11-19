# better-sqlite3 [![Build Status](https://travis-ci.org/JoshuaWise/better-sqlite3.svg?branch=master)](https://travis-ci.org/JoshuaWise/better-sqlite3)

## Electron Fork

Using the work of [Ben Gotow](https://github.com/bengotow) to patch better-sqlite3 for use with Electron. 

Here's a checklist for building this successfully with Electron:
- Ensure that your node version matches your version of Electron's. If you're using NVM, check your current version by navigating to your app directory and running `nvm version`, and to set your version run `nvm use x.x.x`.
- Ensure that you have setup a post installation workflow with node gyp to set the appropriate headers. Again we turn to the work of [Ben Gotow](https://github.com/bengotow) for the easiest solution by [using this script in your post install workflow](https://github.com/bengotow/electron-RxDB/blob/master/post-install.js) and add `"postinstall": "node ./post-install.js"` (or point to whichever directory you're putting it in) to your package.json (or if going the two package.json route, the package.json you're using for development).

The fastest and simplest library for SQLite3 in Node.js.

- Full transaction support
- Geared for performance and efficiency
- Easy-to-use synchronous API *(faster than an asynchronous API... yes, you read that correctly)*
- 64-bit integer support *(invisible until you need it)*

## Installation

```bash
npm install --save better-sqlite3
```

## Usage

```js
var Database = require('better-sqlite3');
var db = new Database('foobar.db', options);

db.on('open', function () {
	var row = db.prepare('SELECT * FROM users WHERE id=?').get(userId);
	console.log(row.firstName, row.lastName, row.email);
});
```

## Why should I use this instead of [node-sqlite3](https://github.com/mapbox/node-sqlite3)?

- `node-sqlite3` uses asynchronous APIs for tasks that don't wait for I/O. That's not only bad design, but it wastes tons of resources.
- `node-sqlite3` exposes low-level (C language) memory management functions. `better-sqlite3` does it the JavaScript way, allowing the garbage collector to worry about memory management.
- `better-sqlite3` is simpler to use, and it provides nice utilities for some operations that are very difficult or impossible in `node-sqlite3`.
- `better-sqlite3` is much faster than `node-sqlite3` in most cases, and just as fast in all other cases.

# Documentation

- [API documentation](https://github.com/JoshuaWise/better-sqlite3/wiki/API)
- [Performance](https://github.com/JoshuaWise/better-sqlite3/wiki/Performance) (also see [benchmark results](https://github.com/JoshuaWise/better-sqlite3/wiki/Benchmark))
- [64-bit integer support](https://github.com/JoshuaWise/better-sqlite3/wiki/64-bit-integer-support)
- [SQLite3 compilation options](https://github.com/JoshuaWise/better-sqlite3/wiki/SQLite3-compilation-options)

# License

[MIT](https://github.com/JoshuaWise/better-sqlite3/blob/master/LICENSE)
