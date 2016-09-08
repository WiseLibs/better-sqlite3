# better-sqlite3

The fastest and most carefully designed library for SQLite3 in Node.js.

- Full transaction support
- Full atomicity on a single connection
- Geared for performance and efficiency
- Easy-to-use node-style API

## Installation

```bash
npm install --save better-sqlite3
```

## Usage

```js
var Database = require('better-sqlite3');
var db = new Database('foobar.db', options);

db.on('open', function () {
	db.statement('SELECT * FROM users WHERE id=?').get(userId, function (err, row) {
		console.log(row.firstName, row.lastName, row.email);
	});
})
```

## Why should I use this instead of [node-sqlite3](https://github.com/mapbox/node-sqlite3)?

- `node-sqlite3` uses asynchronous APIs for tasks that don't touch the hard disk. That's not only bad besign, but it wastes tons of resources.
- `node-sqlite3` forces you to manage the memory of SQLite3 statements yourself. `better-sqlite3` does it the JavaScript way, allowing the garbage collector to worry about memory management.
- This module secretly splits your database connectino into two parts; a read-only connection, and a writable connection, which gives you completely atomic transactions and protects you from reading uncommitted data.

# API

## new Database(*path*, [*options*])

This creates a database connection. If the database file does not exist, it is created.

When the database connection is ready, the `open` event is fired.

If the database is closed, the `close` event will be fired. If the database was closed because of an error, the associated `Error` object will be available as the first argument of the `close` event. If there was no error, the first argument will be `null`.

### Options

#### *options.memory*

If this option is `true`, an in-memory database will be created, rather than a disk-bound one. Default is `false`.

#### *options.wal*

If this option is `true` (the default), the following PRAGMA are applied:
- `PRAGMA journal_mode = WAL;`
- `PRAGMA synchronous = 1;`

This means the database will be opened in [Write Ahead Logging](https://www.sqlite.org/wal.html) mode. If you set this option to `false`, the old [Rollback Journal](https://www.sqlite.org/lockingv3.html#rollback) mode will be used, as well as the default `synchronous` setting.

### .statement(sqlString) -> Statement

Creates a new prepared `Statement` object. This method will throw an exception if the provided string is not a valid SQL statement.

### .transaction(arrayOfStrings) -> Transaction

Creates a new prepared `Transaction` object. Each string in the given array must be a valid SQL statement. `Transaction` objects cannot contain read-only statements. In `better-sqlite3`, transactions serve the sole purpose of batch-write operations. For read-only operations, use regular [prepared statements](#statementsqlstring---statement).

### .pragma(sqlString, [returnSimpleData]) -> results

This method will execute the given PRAGMA statement **synchronously** and return its result. By default, the return value will be an array of result rows. Each row is represented by an object whose keys correspond to column names.

Since most PRAGMA statements return a single value, the `returnSimpleData` option is provided to make things easier. With this option, only the first column of the first row will be returned.

```js
db.pragma('cache_size = 32000');
var cacheSize = db.pragma('cache_size', true); // returns the string "32000"
```

The data returned by `.pragma()` is always in string format.

The documentation on SQLite3 PRAGMA statements can be found [here](https://www.sqlite.org/pragma.html).

##### WARNING:

You should **NOT** use normal prepared statements or transactions to run PRAGMA statements. Doing so could potentially corrupt the database.


### .close() -> this

Closes the database connection. After invoking this method, no statements/transactions can be created or executed. The underlying connection will wait for any outstanding queries to complete before gracefully closing the connection. When all outstanding queries have completed, the `close` event will be fired.

### *get* .open -> boolean

Returns whether the database is currently open.

# License

[MIT](https://github.com/JoshuaWise/better-sqlite3/blob/master/LICENSE.md)
