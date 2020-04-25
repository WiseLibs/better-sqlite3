# API

- [class `Database`](#class-database)
- [class `Statement`](#class-statement)

# class *Database*

- [new Database()](#new-databasepath-options)
- [Database#prepare()](#preparestring---statement) (see [`Statement`](#class-statement))
- [Database#transaction()](#transactionfunction---function)
- [Database#pragma()](#pragmastring-options---results)
- [Database#backup()](#backupdestination-options---promise)
- [Database#function()](#functionname-options-function---this)
- [Database#aggregate()](#aggregatename-options---this)
- [Database#loadExtension()](#loadextensionpath-entrypoint---this)
- [Database#exec()](#execstring---this)
- [Database#close()](#close---this)
- [Properties](#properties)

### new Database(*path*, [*options*])

Creates a new database connection. If the database file does not exist, it is created. This happens synchronously, which means you can start executing queries right away. You can create an [in-memory database](https://www.sqlite.org/inmemorydb.html) by passing `":memory:"` as the first argument.

Various options are accepted:

- `options.readonly`: open the database connection in readonly mode (default: `false`).

- `options.fileMustExist`: if the database does not exist, an `Error` will be thrown instead of creating a new file. This option does not affect in-memory or readonly database connections (default: `false`).

- `options.timeout`: the number of milliseconds to wait when executing queries on a locked database, before throwing a `SQLITE_BUSY` error (default: `5000`).

- `options.verbose`: provide a function that gets called with every SQL string executed by the database connection (default: `null`).

```js
const Database = require('better-sqlite3');
const db = new Database('foobar.db', { verbose: console.log });
```

### .prepare(*string*) -> *Statement*

Creates a new prepared [`Statement`](#class-statement) from the given SQL string.

```js
const stmt = db.prepare('SELECT name, age FROM cats');
```

### .transaction(*function*) -> *function*

Creates a function that always runs inside a [transaction](https://sqlite.org/lang_transaction.html). When the function is invoked, it will begin a new transaction. When the function returns, the transaction will be committed. If an exception is thrown, the transaction will be rolled back (and the exception will propagate as usual).

```js
const insert = db.prepare('INSERT INTO cats (name, age) VALUES (@name, @age)');

const insertMany = db.transaction((cats) => {
  for (const cat of cats) insert.run(cat);
});

insertMany([
  { name: 'Joey', age: 2 },
  { name: 'Sally', age: 4 },
  { name: 'Junior', age: 1 },
]);
```

Transaction functions can be called from inside other transaction functions. When doing so, the inner transaction becomes a [savepoint](https://www.sqlite.org/lang_savepoint.html).

```js
const newExpense = db.prepare('INSERT INTO expenses (note, dollars) VALUES (?, ?)');

const adopt = db.transaction((cats) => {
  newExpense.run('adoption fees', 20);
  insertMany(cats); // nested transaction
});
```

Transactions also come with `deferred`, `immediate`, and `exclusive` versions.

```js
insertMany(cats); // uses "BEGIN"
insertMany.deferred(cats); // uses "BEGIN DEFERRED"
insertMany.immediate(cats); // uses "BEGIN IMMEDIATE"
insertMany.exclusive(cats); // uses "BEGIN EXCLUSIVE"
```

Any arguments passed to the transaction function will be forwarded to the wrapped function, and any values returned from the wrapped function will be returned from the transaction function. The wrapped function will also have access to the same [`this`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/this) binding as the transaction function.

#### Caveats

If you'd like to manage transactions manually, you're free to do so with regular [prepared statements](#preparestring---statement) (using `BEGIN`, `COMMIT`, etc.). However, manually managed transactions should not be mixed with transactions managed by this `.transaction()` method. In other words, using raw `COMMIT` or `ROLLBACK` statements inside a transaction function is not supported.

Transaction functions do not work with async functions. Technically speaking, async functions always return after the first `await`, which means the transaction will already be committed before any async code executes. Also, because SQLite3 serializes all transactions, it's generally a very bad idea to keep a transaction open across event loop ticks anyways.

It's important to know that SQLite3 may sometimes rollback a transaction without us asking it to. This can happen either because of an [`ON CONFLICT`](https://sqlite.org/lang_conflict.html) clause, the [`RAISE()`](https://www.sqlite.org/lang_createtrigger.html) trigger function, or certain errors such as `SQLITE_FULL` or `SQLITE_BUSY`. In other words, if you catch an SQLite3 error *within* a transaction, you must be aware that any futher SQL that you execute might not be within the same transaction. Usually, the best course of action for such cases is to simply re-throw the error, exiting the transaction function.

```js
try {
  ...
} catch (err) {
  if (!db.inTransaction) throw err; // (transaction was forcefully rolled back)
  ...
}
```

### .pragma(*string*, [*options*]) -> *results*

Executes the given PRAGMA and returns its result. By default, the return value will be an array of result rows. Each row is represented by an object whose keys correspond to column names.

Since most PRAGMA statements return a single value, the `simple` option is provided to make things easier. When `simple` is `true`, only the first column of the first row will be returned.

```js
db.pragma('cache_size = 32000');
console.log(db.pragma('cache_size', { simple: true })); // => 32000
```

If execution of the PRAGMA fails, an `Error` is thrown.

It's better to use this method instead of normal [prepared statements](#preparestring---statement) when executing PRAGMA, because this method normalizes some odd behavior that may otherwise be experienced. The documentation on SQLite3 PRAGMA can be found [here](https://www.sqlite.org/pragma.html).

### .backup(*destination*, [*options*]) -> *promise*

Initiates a [backup](https://www.sqlite.org/backup.html) of the database, returning a [promise](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Using_promises) for when the backup is complete. If the backup fails, the promise will be rejected with an `Error`. You can optionally backup an attached database by setting the `attached` option to the name of the desired attached database.

```js
db.backup(`backup-${Date.now()}.db`)
  .then(() => {
    console.log('backup complete!');
  })
  .catch((err) => {
    console.log('backup failed:', err);
  });
```

You can continue to use the database normally while a backup is in progress. If the same database connection mutates the database while performing a backup, those mutations will be reflected in the backup automatically. However, if a *different* connection mutates the database during a backup, the backup will be forcefully restarted. Therefore, it's recommended that only a single connection is responsible for mutating the database if online backups are being performed.

You can monitor the progress of the backup by setting the `progress` option to a callback function. That function will be invoked every time the backup makes progress, providing an object with two properties:

- `.totalPages`: the total number of pages in the source database (and thus, the number of pages that the backup will have when completed) at the time of this progress report.
- `.remainingPages`: the number of pages that still must be transferred before the backup is complete.

By default, `100` [pages](https://www.sqlite.org/fileformat.html#pages) will be transferred after each cycle of the event loop. However, you can change this setting as often as you like by returning a number from the `progress` callback. You can even return `0` to effectively pause the backup altogether. In general, the goal is to maximize throughput while reducing pause times. If the transfer size is very low, pause times will be low, but it may take a while to complete the backup. On the flip side, if the setting is too high, pause times will be greater, but the backup might complete sooner. In most cases, `100` has proven to be a strong compromise, but the best setting is dependent on your computer's specifications and the nature of your program. Do not change this setting without measuring the effectiveness of your change. You should not assume that your change will even have the intended effect, unless you measure it for your unique situation.

If the backup is successful, the returned promise will contain an object that has the same properties as the one provided to the `progress` callback, and `.remainingPages` will necessarily be `0`. If the `progress` callback throws an exception, the backup will be aborted. Usually this happens due to an unexpected error, but you can also use this behavior to voluntarily cancel the backup operation. If the parent database connection is closed, all pending backups will be automatically aborted.

```js
let paused = false;
db.backup(`backup-${Date.now()}.db`, {
  progress({ totalPages: t, remainingPages: r }) {
    console.log(`progress: ${((t - r) / t * 100).toFixed(1)}%`);
    return paused ? 0 : 200;
  }
});
```

### .function(*name*, [*options*], *function*) -> *this*

Registers a user-defined `function` so that it can be used by SQL statements.

```js
db.function('add2', (a, b) => a + b);

db.prepare('SELECT add2(?, ?)').pluck().get(12, 4); // => 16
db.prepare('SELECT add2(?, ?)').pluck().get('foo', 'bar'); // => "foobar"
db.prepare('SELECT add2(?, ?, ?)').pluck().get(12, 4, 18); // => Error: wrong number of arguments
```

By default, user-defined functions have a strict number of arguments (determined by `function.length`). You can register multiple functions of the same name, each with a different number of arguments, causing SQLite3 to execute a different function depending on how many arguments were passed to it. If you register two functions with same name and the same number of arguments, the second registration will erase the first one.

If `options.varargs` is `true`, the registered function can accept any number of arguments.

If your function is [deterministic](https://en.wikipedia.org/wiki/Deterministic_algorithm), you can set `options.deterministic` to `true`, which may improve performance under some circumstances.

```js
db.function('void', { deterministic: true, varargs: true }, () => {});

db.prepare("SELECT void()").pluck().get(); // => null
db.prepare("SELECT void(?, ?)").pluck().get(55, 19); // => null
```

### .aggregate(*name*, *options*) -> *this*

Registers a user-defined [aggregate function](https://sqlite.org/lang_aggfunc.html).

```js
db.aggregate('addAll', {
  start: 0,
  step: (total, nextValue) => total + nextValue,
});

db.prepare('SELECT addAll(dollars) FROM expenses').pluck().get(); // => 92
```

The `step()` function will be invoked once for each row passed to the aggregate, using its return value as the new aggregate value. This works similarly to [Array#reduce()](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/Reduce).

If `options.start` is a function, it will be invoked at the beginning of each aggregate, using its return value as the initial aggregate value. If `options.start` is *not* a function, it will be used as the initial aggregate value *as-is* (shown in the example above). If not provided, the initial aggregate value will be `null`.

You can also provide a `result()` function to transform the final aggregate value:

```js
db.aggregate('getAverage', {
  start: () => [],
  step: (array, nextValue) => {
    array.push(nextValue);
  },
  result: array => array.reduce(sum) / array.length,
});

db.prepare('SELECT getAverage(dollars) FROM expenses').pluck().get(); // => 20.2
```

As shown above, you can use arbitrary JavaScript objects as your aggregation context, as long as a valid SQLite3 value is returned by `result()` in the end. If `step()` doesn't return anything (`undefined`), the aggregate value will not be replaced (be careful of this when using functions that return `undefined` when `null` is desired).

Just like regular [user-defined functions](#functionname-options-function---this), user-defined aggregates can accept multiple arguments. Furthermore, `options.varargs` and `options.deterministic` [are also](#functionname-options-function---this) accepted.

If you provide an `inverse()` function, the aggregate can be used as a [window function](https://www.sqlite.org/windowfunctions.html). Where `step()` is used to add a row to the current window, `inverse()` is used to remove a row from the current window. When using window functions, `result()` may be invoked multiple times.

```js
db.aggregate('addAll', {
  start: 0,
  step: (total, nextValue) => total + nextValue,
  inverse: (total, droppedValue) => total - droppedValue,
  result: total => Math.round(total),
});

db.prepare(`
  SELECT timestamp, dollars, addAll(dollars) OVER day as dayTotal
  FROM expenses
  WINDOW day AS (PARTITION BY date(timestamp))
  ORDER BY timestamp
`).all();
```

### .loadExtension(*path*, [*entryPoint*]) -> *this*

Loads a compiled [SQLite3 extension](https://sqlite.org/loadext.html) and applies it to the current database connection.

It's your responsibility to make sure the extensions you load are compiled/linked against a version of [SQLite3](https://www.sqlite.org/) that is compatible with `better-sqlite3`. Keep in mind that new versions of `better-sqlite3` will periodically use newer versions of [SQLite3](https://www.sqlite.org/). You can see which version is being used [here](./compilation.md#bundled-configuration).

```js
db.loadExtension('./my-extensions/compress.so');
```

### .exec(*string*) -> *this*

Executes the given SQL string. Unlike [prepared statements](#preparestring---statement), this can execute strings that contain multiple SQL statements. This function performs worse and is less safe than using [prepared statements](#preparestring---statement). You should only use this method when you need to execute SQL from an external source (usually a file). If an error occurs, execution stops and further statements are not executed. You must rollback changes manually.

```js
const migration = fs.readFileSync('migrate-schema.sql', 'utf8');
db.exec(migration);
```

### .close() -> *this*

Closes the database connection. After invoking this method, no statements can be created or executed.

```js
process.on('exit', () => db.close());
process.on('SIGHUP', () => process.exit(128 + 1));
process.on('SIGINT', () => process.exit(128 + 2));
process.on('SIGTERM', () => process.exit(128 + 15));
```

## Properties

**.open -> _boolean_** - Whether the database connection is currently open.

**.inTransaction -> _boolean_** - Whether the database connection is currently in an open transaction.

**.name -> _string_** - The string that was used to open the database connection.

**.memory -> _boolean_** - Whether the database is an in-memory database.

**.readonly -> _boolean_** - Whether the database connection was created in readonly mode.

# class *Statement*

An object representing a single SQL statement.

- [Statement#run()](#runbindparameters---object)
- [Statement#get()](#getbindparameters---row)
- [Statement#all()](#allbindparameters---array-of-rows)
- [Statement#iterate()](#iteratebindparameters---iterator)
- [Statement#pluck()](#plucktogglestate---this)
- [Statement#expand()](#expandtogglestate---this)
- [Statement#raw()](#rawtogglestate---this)
- [Statement#columns()](#columns---array-of-objects)
- [Statement#bind()](#bindbindparameters---this)
- [Properties](#properties-1)

### .run([*...bindParameters*]) -> *object*

**(only on statements that do not return data)*

Executes the prepared statement. When execution completes it returns an `info` object describing any changes made. The `info` object has two properties:

- `info.changes`: the total number of rows that were inserted, updated, or deleted by this operation. Changes made by [foreign key actions](https://www.sqlite.org/foreignkeys.html#fk_actions) or [trigger programs](https://www.sqlite.org/lang_createtrigger.html) do not count.
- `info.lastInsertRowid`: the [rowid](https://www.sqlite.org/lang_createtable.html#rowid) of the last row inserted into the database (ignoring those caused by [trigger programs](https://www.sqlite.org/lang_createtrigger.html)). If the current statement did not insert any rows into the database, this number should be completely ignored.

If execution of the statement fails, an `Error` is thrown.

You can specify [bind parameters](#binding-parameters), which are only bound for the given execution.

```js
const stmt = db.prepare('INSERT INTO cats (name, age) VALUES (?, ?)');
const info = stmt.run('Joey', 2);

console.log(info.changes); // => 1
```

### .get([*...bindParameters*]) -> *row*

**(only on statements that return data)*

Executes the prepared statement. When execution completes it returns an object that represents the first row retrieved by the query. The object's keys represent column names.

If the statement was successful but found no data, `undefined` is returned. If execution of the statement fails, an `Error` is thrown.

You can specify [bind parameters](#binding-parameters), which are only bound for the given execution.

```js
const stmt = db.prepare('SELECT age FROM cats WHERE name = ?');
const cat = stmt.get('Joey');

console.log(cat.age); // => 2
```

### .all([*...bindParameters*]) -> *array of rows*

**(only on statements that return data)*

Similar to [`.get()`](#getbindparameters---row), but instead of only retrieving one row all matching rows will be retrieved. The return value is an array of row objects.

If no rows are found, the array will be empty. If execution of the statement fails, an `Error` is thrown.

You can specify [bind parameters](#binding-parameters), which are only bound for the given execution.

```js
const stmt = db.prepare('SELECT * FROM cats WHERE name = ?');
const cats = stmt.all('Joey');

console.log(cats.length); // => 1
```

### .iterate([*...bindParameters*]) -> *iterator*

**(only on statements that return data)*

Similar to [`.all()`](#allbindparameters---array-of-rows), but instead of returning every row together, an [iterator](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Iteration_protocols) is returned so you can retrieve the rows one by one. If you plan on retrieving every row anyways, [`.all()`](#allbindparameters---array-of-rows) will perform slightly better.

If execution of the statement fails, an `Error` is thrown and the iterator is closed.

You can specify [bind parameters](#binding-parameters), which are only bound for the given execution.

```js
const stmt = db.prepare('SELECT * FROM cats');

for (const cat of stmt.iterate()) {
  if (cat.name === 'Joey') {
    console.log('found him!');
    break;
  }
}
```

### .pluck([toggleState]) -> *this*

**(only on statements that return data)*

Causes the prepared statement to only return the value of the first column of any rows that it retrieves, rather than the entire row object.

You can toggle this on/off as you please:

```js
stmt.pluck(); // plucking ON
stmt.pluck(true); // plucking ON
stmt.pluck(false); // plucking OFF
```

> When plucking is turned on, [expansion](#expandtogglestate---this) and [raw mode](#rawtogglestate---this) are turned off (they are mutually exclusive options).

### .expand([toggleState]) -> *this*

**(only on statements that return data)*

Causes the prepared statement to return data namespaced by table. Each key in a row object will be a table name, and each corresponding value will be a nested object that contains the associated column data. This is useful when performing a `JOIN` between two tables that have overlapping column names. If a result column is an expression or subquery, it will be available within the special `$` namespace.

You can toggle this on/off as you please:

```js
stmt.expand(); // expansion ON
stmt.expand(true); // expansion ON
stmt.expand(false); // expansion OFF
```

> When expansion is turned on, [plucking](#plucktogglestate---this) and [raw mode](#rawtogglestate---this) are turned off (they are mutually exclusive options).

### .raw([toggleState]) -> *this*

**(only on statements that return data)*

Causes the prepared statement to return rows as arrays instead of objects. This is primarily used as a performance optimization when retrieving a very high number of rows. Column names can be recovered by using the [`.columns()`](#columns---array-of-objects) method.

You can toggle this on/off as you please:

```js
stmt.raw(); // raw mode ON
stmt.raw(true); // raw mode ON
stmt.raw(false); // raw mode OFF
```

> When raw mode is turned on, [plucking](#plucktogglestate---this) and [expansion](#expandtogglestate---this) are turned off (they are mutually exclusive options).

### .columns() -> *array of objects*

**(only on statements that return data)*

This method is primarily used in conjunction with [raw mode](#rawtogglestate---this). It returns an array of objects, where each object describes a result column of the prepared statement. Each object has the following properties:

- `.name`: the name (or alias) of the result column.
- `.column`: the name of the originating table column, or `null` if it's an expression or subquery.
- `.table`: the name of the originating table, or `null` if it's an expression or subquery.
- `.database`: the name of the originating database, or `null` if it's an
expression or subquery.
- `.type`: the name of the [declared type](https://www.sqlite.org/datatype3.html#determination_of_column_affinity), or `null` if it's an expression or subquery.

```js
const fs = require('fs');

function* toRows(stmt) {
  yield stmt.columns().map(column => column.name);
  yield* stmt.raw().iterate();
}

function writeToCSV(filename, stmt) {
  return new Promise((resolve, reject) => {
    const stream = fs.createWriteStream(filename);
    for (const row of toRows(stmt)) {
      stream.write(row.join(',') + '\n');
    }
    stream.on('error', reject);
    stream.end(resolve);
  });
}
```

> When a table's schema is altered, existing prepared statements might start returning different result columns. However, such changes will not be reflected by this method until the prepared statement is re-executed. For this reason, it's perhaps better to invoke `.columns()` _after_ `.get()`, `.all()`, or `.iterate()`.

### .bind([*...bindParameters*]) -> *this*

[Binds the given parameters](#binding-parameters) to the statement *permanently*. Unlike binding parameters upon execution, these parameters will stay bound to the prepared statement for its entire life.

After a statement's parameters are bound this way, you may no longer provide it with execution-specific (temporary) bound parameters.

This method is primarily used as a performance optimization when you need to execute the same prepared statement many times with the same bound parameters.

```js
const stmt = db.prepare('SELECT * FROM cats WHERE name = ?').bind('Joey');
const cat = stmt.get();

console.log(cat.name); // => "Joey"
```

## Properties

**.database -> _object_** - The parent database object.

**.source -> _string_** - The source string that was used to create the prepared statement.

**.reader -> _boolean_** - Whether the prepared statement returns data.

# Binding Parameters

This section refers to anywhere in the documentation that specifies the optional argument [*`...bindParameters`*].

There are many ways to bind parameters to a prepared statement. The simplest way is with anonymous parameters:

```js
const stmt = db.prepare('INSERT INTO people VALUES (?, ?, ?)');

// The following are equivalent.
stmt.run('John', 'Smith', 45);
stmt.run(['John', 'Smith', 45]);
stmt.run(['John'], ['Smith', 45]);
```

You can also use named parameters. SQLite3 provides [3 different syntaxes for named parameters](https://www.sqlite.org/lang_expr.html) (`@foo`, `:foo`, and `$foo`), all of which are supported by `better-sqlite3`.

```js
// The following are equivalent.
const stmt = db.prepare('INSERT INTO people VALUES (@firstName, @lastName, @age)');
const stmt = db.prepare('INSERT INTO people VALUES (:firstName, :lastName, :age)');
const stmt = db.prepare('INSERT INTO people VALUES ($firstName, $lastName, $age)');
const stmt = db.prepare('INSERT INTO people VALUES (@firstName, :lastName, $age)');

stmt.run({
  firstName: 'John',
  lastName: 'Smith',
  age: 45
});
```

Below is an example of mixing anonymous parameters with named parameters.

```js
const stmt = db.prepare('INSERT INTO people VALUES (@name, @name, ?)');
stmt.run(45, { name: 'Henry' });
```
