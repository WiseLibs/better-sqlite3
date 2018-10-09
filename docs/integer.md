# The `Integer` Class

SQLite3 can store data in 64-bit signed integers, which are too big for JavaScript's [number format](https://en.wikipedia.org/wiki/Double-precision_floating-point_format) to fully represent. To support this data type, `better-sqlite3` uses the immutable `Integer` class. To view the complete `Integer` documentation, [click here](https://github.com/JoshuaWise/integer).

```js
var Integer = require('better-sqlite3').Integer;

var integer = Integer('95073701505997');
integer.toString(); // returns "95073701505997"
integer.toNumber(); // returns 95073701505997

var bigInteger = Integer('1152735103331642317');
bigInteger.toString(); // returns "1152735103331642317"
bigInteger.toNumber(); // throws a RangeError, cannot be represented in JavaScript
```

# Binding Integers

`Integers` can bind to [`Statements`](./api.md#class-statement) and [`Transactions`](./api.md#class-transaction) just like regular numbers. You can also return `Integers` in [registered functions](./api.md#registeroptions-function---this).

```js
db.prepare("SELECT * FROM users WHERE id=?").get(Integer('1152735103331642317'));
db.prepare("INSERT INTO big_numbers VALUES (?)").run(Integer('1152735103331642317'));
```

# Getting Integers from the database

By default, integers returned from the database are normal JavaScript numbers (this includes the `info.lastInsertROWID` property returned by the [`run()`](./api.md#runbindparameters---object) methods). You can change this default as you please:

```js
db.defaultSafeIntegers(); // Integers by default
db.defaultSafeIntegers(true); // Integers by default
db.defaultSafeIntegers(false); // JavaScript numbers by default
```

Additionally, you can override the default for individual [`statements`](./api.md#class-statement) and [`transactions`](./api.md#class-transaction) like so:

```js
var stmt = db.prepare(SQL);

stmt.safeIntegers(); // Safe integers ON
stmt.safeIntegers(true); // Safe integers ON
stmt.safeIntegers(false); // Safe integers OFF

// You can do the same thing with Transaction objects.
```

[Registered functions](./api.md#registeroptions-function---this) can also receive `Integers` as arguments. You can override the database's default setting like so:

```js
db.register({safeIntegers: true}, function isInt(value) {
  return value instanceof Integer;
});
stmt.prepare('SELECT isInt(?)').get('foobar'); // => false
stmt.prepare('SELECT isInt(?)').get(Integer.MAX_VALUE); // => true
```

It's worth noting that REAL (FLOAT) values returned from the database will always be represented as JavaScript numbers.
