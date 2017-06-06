# The `Integer` Class

SQLite3 can store data in 64-bit signed integers, which are too big for JavaScript's [number format](https://en.wikipedia.org/wiki/IEEE_floating_point) to fully represent. To support this data type, `better-sqlite3` uses the immutable [`Integer`](https://github.com/JoshuaWise/integer) class:

```js
var Integer = require('better-sqlite3').Integer;

var integer = Integer('95073701505997');
integer.toString(); // returns "95073701505997"
integer.toNumber(); // returns 95073701505997

var bigInteger = Integer('1152735103331642317');
bigInteger.toString(); // returns "1152735103331642317"
bigInteger.toNumber(); // throws a RangeError, cannot be represented in JavaScript
```

You can convert any `Integer` to a string to see its full value. If you try to convert an `Integer` to a regular number but the `Integer` is too big to be accurately represented, a `RangeError` will be thrown to protect you from accidentally corrupting the accuracy of your database.

# Binding Integers

`Integers` can bind to [`Statements`](https://github.com/JoshuaWise/better-sqlite3/wiki/API#class-statement) and [`Transactions`](https://github.com/JoshuaWise/better-sqlite3/wiki/API#class-transaction) just like regular numbers. You can also return `Integers` in [registered functions](https://github.com/JoshuaWise/better-sqlite3/wiki/API#registeroptions-function---this).

```js
db.prepare("SELECT * FROM users WHERE id=?").get(Integer.fromBits(0x01234abcd, 0x0fff5678));
db.prepare("INSERT INTO big_numbers VALUES (?)").run(Integer.fromBits(0x01234abcd, 0x0fff5678));
```

# Getting Integers from the database

By default, integers returned from the database are normal JavaScript numbers (this includes the `info.lastInsertROWID` property returned by the [`run()`](https://github.com/JoshuaWise/better-sqlite3/wiki/API#runbindparameters---object) methods). You can change this default as you please:

```js
db.defaultSafeIntegers(); // Integers by default
db.defaultSafeIntegers(true); // Integers by default
db.defaultSafeIntegers(false); // JavaScript numbers by default
```

Additionally, you can override the default for individual [`statements`](https://github.com/JoshuaWise/better-sqlite3/wiki/API#class-statement) and [`transactions`](https://github.com/JoshuaWise/better-sqlite3/wiki/API#class-transaction) like so:

```js
var stmt = db.prepare(SQL);

stmt.safeIntegers(); // Safe integers ON
stmt.safeIntegers(true); // Safe integers ON
stmt.safeIntegers(false); // Safe integers OFF

// You can do the same thing with Transaction objects.
```

[Registered functions](https://github.com/JoshuaWise/better-sqlite3/wiki/API#registeroptions-function---this) can also receive `Integers` as arguments. You can override the database's default setting like so:

```js
db.register({safeIntegers: true}, function isInt(value) {
  return value instanceof Integer;
});
stmt.prepare('SELECT isInt(?)').get('foobar'); // => false
stmt.prepare('SELECT isInt(?)').get(Integer.MAX_VALUE); // => true
```

It's worth noting that REAL (FLOAT) values returned from the database will always be represented as JavaScript numbers.

# Learn more

To view the complete `Integer` documentation, [click here](https://github.com/JoshuaWise/integer).
