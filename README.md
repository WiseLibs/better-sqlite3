# better-sqlite3 [![Build Status](https://travis-ci.org/JoshuaWise/better-sqlite3.svg?branch=master)](https://travis-ci.org/JoshuaWise/better-sqlite3)

The fastest and most carefully designed library for SQLite3 in Node.js.

- Full transaction support
- Geared for performance and efficiency
- Idiomatic node-style API
- Includes convenient time-saving utilities

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
- `node-sqlite3` exposes low-level (C language) memory management functions. `better-sqlite3` does it the JavaScript way, allowing the garbage collector to worry about memory management.
- `better-sqlite3` is just as fast, (even faster in some cases) than `node-sqlite3`.

# API

## new Database(*path*, [*options*])

Creates a new database connection. If the database file does not exist, it is created.

When the database connection is ready, the `open` event is fired.

If the database is closed, the `close` event will be fired. If the database was closed because of an error, the associated `Error` object will be available as the first parameter of the `close` event. If there was no error, the first parameter will be `null`.

If `options.memory` is `true`, an in-memory database will be created, rather than a disk-bound one. Default is `false`.

### .statement(string) -> Statement

Creates a new prepared [`Statement`](#class-statement) object. This method will throw an exception if the provided string is not a valid SQL statement.

### .transaction(arrayOfStrings) -> Transaction

Creates a new prepared [`Transaction`](#class-transaction) object. Each string in the given array must be a valid SQL statement. [`Transaction`](#class-transaction) objects cannot contain read-only statements. In `better-sqlite3`, transactions serve the sole purpose of batch-write operations. For read-only operations, use regular [prepared statements](#statementstring---statement).

### .pragma(string, [simplify]) -> results

This method will execute the given PRAGMA statement **synchronously** and return its result. By default, the return value will be an array of result rows. Each row is represented by an object whose keys correspond to column names.

Since most PRAGMA statements return a single value, the `simplify` option is provided to make things easier. With this option, only the first column of the first row will be returned.

```js
db.pragma('cache_size = 32000');
var cacheSize = db.pragma('cache_size', true); // returns the string "32000"
```

The data returned by `.pragma()` is always in string format. The documentation on SQLite3 PRAGMA statements can be found [here](https://www.sqlite.org/pragma.html).

### .checkpoint([force], callback) -> this

This method is provided because [.pragma()](#pragmastring-simplify---results)'s synchronous nature makes it unsuitable for running [WAL mode checkpoints](https://www.sqlite.org/wal.html).

By default, this method will execute a checkpoint in "PASSIVE" mode, which means it might not perform a *complete* checkpoint if there are pending reads or write on the database. If the first argument is `true`, it will execute the checkpoint in "RESTART" mode, which ensures a complete checkpoint operation.

When the operation is complete, the callback is invoked with an `Error` or `null` as its first parameter, depending on if the operation was successful. If successful, the callback's second parameter will be a number between `0` and `1`, indicating the fraction of the WAL file that was checkpointed. For forceful checkpoints ("RESTART" mode), this number will always be `1` unless there is no WAL file.

### .close() -> this

Closes the database connection. After invoking this method, no statements/transactions can be created or executed. The underlying connection will wait for any outstanding queries to complete before gracefully closing the connection. When all outstanding queries have completed, the `close` event will be fired.

### *get* .open -> boolean

Returns whether the database is currently open.

### *get* .filename -> string

Returns the string used to open the databse connection.

## class *Statement*

An object representing a single SQL statement.

### .run([...bindParameters], callback) -> this

**(only on write statements)*

Executes the prepared statement. When execution completes the callback will be invoked with either an `Error` or `null` as its first parameter.

If successful, the callback's second parameter will be an `info` object describing any changes made. The `info` object has two properties:

- `info.changes`: The total number of rows that were inserted, updated, or deleted by this operation. Changes made by [foreign key actions](https://www.sqlite.org/foreignkeys.html#fk_actions) or [trigger programs](https://www.sqlite.org/lang_createtrigger.html) do not count.
- `info.lastInsertROWID`: The [rowid](https://www.sqlite.org/lang_createtable.html#rowid) of the last row inserted into the database. If the current statement did not insert any rows into the database, this number should be completely ignored.

You can optionally specify [bind parameters](#binding-parameters), which are automatically unbound when execution completes.

### .get([...bindParameters], callback) -> this

**(only on read-only statements)*

Executes the prepared statement. When execution completes the callback will be invoked with either an `Error` or `null` as its first parameter.

If successful, the callback's second parameter will be an object that represents the first row retrieved by the query. The object's keys represent column names. If the statement was successful but retrieved no data, the second parameter will be `undefined` instead.

You can optionally specify [bind parameters](#binding-parameters), which are automatically unbound when execution completes.

### .all([...bindParameters], callback) -> this

**(only on read-only statements)*

Similar to [`.get()`](#getbindparameters-callback---this), but instead of only retrieving one row all matching rows will be retrieved. The callback's second parameter will be an array of row objects. If no rows are retrieved, the array will be empty.

You can optionally specify [bind parameters](#binding-parameters), which are automatically unbound when execution completes.

### .each([...bindParameters], rowCallback, finalCallback) -> this

**(only on read-only statements)*

Similar to [`.all()`](#allbindparameters-callback---this), but instead of returning every row together, `rowCallback` will be invoked for each row as they are retrieved, one by one. After all rows have been consumed, `finalCallback` is invoked to indicate completion.

If execution of the statement fails, `finalCallback` will be invoked with an `Error` object as its first argument, and iteration will stop.

You can optionally specify [bind parameters](#binding-parameters), which are automatically unbound when execution completes.

### .pluck() -> this

**(only on read-only statements)*

Causes the prepared statement to only return the value of the first column of any rows that it retrieves, rather than the entire row object.

This method can only be invoked before the statement is first executed. After a statement invokes this method, it cannot be undone.

### .bind([...bindParameters]) -> this

[Binds the given parameters](#binding-parameters) to the statement *permanently*. Unlike binding parameters upon execution, these parameters will stay bound to the prepared statement for its entire life.

This method can only be invoked before the statement is first executed. After a statement's parameters are bound this way, you may no longer provide it with execution-specific (temporary) bound parameters.

This method is primarily used as a performance optimization when you need to execute the same prepared statement many times with the same bound parameters.

### *get* .busy -> boolean

Returns whether the prepared statement is mid-execution. If a statement is busy, it cannot be executed again until its query completes.

### *get* .source -> string

Returns the source string that was used to create the prepared statement.

### *get* .readonly -> boolean

Returns whether the prepared statement is read-only.

## class *Transaction*

An object representing many SQL statements grouped into a single logical [transaction](https://www.sqlite.org/lang_transaction.html).

### .run([...bindParameters], callback) -> this

Similar to [`Statement#run()`](#runbindparameters-callback---this).

Each statement in the transaction is executed in order. Failed transactions are automatically rolled back.

If successful, the callback's second parameter will be an `info` object describing any changes made. The `info` object has two properties:

- `info.changes`: The total number of rows that were inserted, updated, or deleted by this transaction. Changes made by [foreign key actions](https://www.sqlite.org/foreignkeys.html#fk_actions) or [trigger programs](https://www.sqlite.org/lang_createtrigger.html) do not count.
- `info.lastInsertROWID`: The [rowid](https://www.sqlite.org/lang_createtable.html#rowid) of the last row inserted into the database. If the current transaction did not insert any rows into the database, this number should be completely ignored.

You can optionally specify [bind parameters](#binding-parameters), which are automatically unbound when execution completes.

### .bind([...bindParameters]) -> this

Same as [`Statement#bind()`](#bindbindparameters---this).

### *get* .busy -> boolean

Same as [`Statement#busy`](#get-busy---boolean).

### *get* .source -> string

Returns a concatenation of every source string that was used to create the prepared transaction. The source strings are seperated by newline characters (`\n`).


# Binding Parameters

This section applies to anywhere in the documentation that specifies the optional argument `[...bindParameters]`.

There are many ways to bind parameters to a prepared statement or transaction. The simplest way is with anonymous parameters:

```js
var stmt = db.statement('INSERT INTO people VALUES (?, ?, ?)');

// The following are equivalent.
stmt.run('John', 'Smith', 45, callback);
stmt.run(['John', 'Smith', 45], callback);
stmt.run(['John'], ['Smith', 45], callback);
```

You can also use named parameters. SQLite3 provides [4 different syntaxes for named parameters](https://www.sqlite.org/lang_expr.html), three of which are supported by `better-sqlite3` (`@foo`, `:foo`, and `$foo`). However, if you use named parameters, make sure to only use **one** syntax within a given [`Statement`](#class-statement) or [`Transaction`](#class-transaction) object. Mixing syntaxes within the same object is not supported.

```js
// The following are equivalent.
var stmt = db.statement('INSERT INTO people VALUES (@firstName, @lastName, @age)');
var stmt = db.statement('INSERT INTO people VALUES (:firstName, :lastName, :age)');
var stmt = db.statement('INSERT INTO people VALUES ($firstName, $lastName, $age)');

stmt.run({
	firstName: 'John',
	lastName: 'Smith',
	age: 45
}, callback);
```

Below is an example of mixing anonymous parameters with named parameters.

```js
var stmt = db.statement('INSERT INTO people VALUES (@name, @name, ?)');
stmt.run(45, {name: 'Henry'}, callback);
```

# Performance

Concurrently reading and writing from an SQLite3 database can be very slow in some cases. Since concurrency is usually very important in web applications, it's recommended to turn on [WAL mode](https://www.sqlite.org/wal.html) to greatly increase overall performance and concurrency.

```js
db.pragma('journal_mode = WAL');
```

WAL mode has a *few* disadvantages to consider:
- Transactions that involve ATTACHed databases are atomic for each individual database, but are not atomic across all databases as a set.
- Under rare circumstances, the [WAL file](https://www.sqlite.org/wal.html) may experience "checkpoint starvation" (see below).
- There are some hardware/system limitations that may affect some users, [listed here](https://www.sqlite.org/wal.html).

However, you trade those disadvantages for greatly improved performance in most web applications.

If you want to *further* improve write performance and you're willing to sacrifice a tiny bit of [durability](https://en.wikipedia.org/wiki/Durability_(database_systems)), you can use this:

```js
db.pragma('journal_mode = WAL');
db.pragma('synchronous = 1');
```

Normally, setting `synchronous = 1` would introduce the risk of database corruption following a power loss or hard reboot. But in [WAL mode](https://www.sqlite.org/wal.html), you do not introduce this risk. The combination of these two PRAGMAs provides extremely fast performance.

### Checkpoint starvation

Checkpoint starvation is when SQLite3 is unable to recycle the [WAL file](https://www.sqlite.org/wal.html) due to everlasting concurrent reads to the database. If this happens, the WAL file will grow without bound, leading to unacceptable amounts of disk usage and deteriorating performance.

To prevent this, you can use the [db.checkpoint()](#checkpointforce-callback---this) method to force checkpointing whenever you deem appropriate.

# SQLite3 compilation options

The following [compilation options](https://www.sqlite.org/compile.html) are used:
- SQLITE_THREADSAFE=1
- SQLITE_ENABLE_FTS5
- SQLITE_ENABLE_JSON1
- SQLITE_ENABLE_RTREE
- SQLITE_DEFAULT_CACHE_SIZE=-16000
- SQLITE_DEFAULT_FOREIGN_KEYS=1
- SQLITE_USE_URI=1

# License

[MIT](https://github.com/JoshuaWise/better-sqlite3/blob/master/LICENSE)
