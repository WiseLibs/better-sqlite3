# better-sqlite3

*You want [Node](http://nodejs.org/)?*

*You want [Sqlite](http://sqlite.org/)?*

*You want your life to be* **easy?**

##### **Well you're in luck because better-sqlite3 is here!!!!**

## Installation

```bash
npm install --save better-sqlite3
```

## Usage

```js
var Database = require('better-sqlite3');
var db = new Database('foobar.db', {memory: true, wal: false});
```

## Features

 - Full transaction support
 - Full Buffer/Blob support
 - Big test suite
 - Written in modern C++ and tested for memory leaks

# License

[MIT](https://github.com/JoshuaWise/better-sqlite3/blob/master/LICENSE.md).
