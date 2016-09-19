# The `Int64` Class

SQLite3 can store data in 64-bit signed integers, which are too big for JavaScript's [number format](https://en.wikipedia.org/wiki/IEEE_floating_point) to fully represent. To support this data type, `better-sqlite3` provides the immutable `Int64` class:

```js
var Int64 = require('better-sqlite3').Int64;

var number = new Int64(0x1234abcd, 0x00005678);
number.toString(); // returns "95073701505997"
+number;           // returns 95073701505997

var bigNumber = new Int64(0x01234abcd, 0x0fff5678);
bigNumber.toString(); // returns "1152735103331642317"
+bigNumber;           // returns NaN, cannot be represented in JavaScript

// Equality checker
number.equals(bigNumber); // returns false
number.equals(+number); // returns true
```

An `Int64` is constructed of two parts: its lower 32 bits, and its higher 32 bits, respectively. The higher bits are optional, and default to `0`.

You can convert any `Int64` to a string to see its full value. If you try to convert an `Int64` to a JavaScript number but the `Int64` is too big to be accurately represented, it will convert to `NaN` to protect you from accidentally corrupting the accuracy of your database.

# Binding Int64s

`Int64s` can bind to [`Statements`](https://github.com/JoshuaWise/better-sqlite3/wiki/API#class-statement) and [`Transactions`](https://github.com/JoshuaWise/better-sqlite3/wiki/API#class-transaction) just like normal numbers.

```js
db.prepare("SELECT * FROM users WHERE id=?").get(new Int64(0x01234abcd, 0x0fff5678));
db.prepare("INSERT INTO big_numbers VALUES (?)").run(new Int64(0x01234abcd, 0x0fff5678));
```

# Getting Int64s from the database

By default, integers returned from the database are normal JavaScript numbers (this includes the `info.lastInsertROWID` property returned by the [`run()`](https://github.com/JoshuaWise/better-sqlite3/wiki/API#runbindparameters---object) methods). You can change this default as you please:

```js
db.defaultSafeIntegers(true); // Int64s by default
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

It's worth noting that FLOAT values returned from the database will always be represented as JavaScript numbers.

# Extending Int64

`Int64` objects are very basic and do not provide advanced functionality. However, they expose accessors for their `low` and `high` bits, which makes them compatible with the very comprehensive [Long](https://github.com/dcodeIO/long.js) library. If you need to manipulate 64 bit integers, the strategy is quite simple:

```js
var Int64 = require('better-sqlite3').Int64;
var Long = require('long');
Long.prototype.value = Int64.prototype.value;
Object.assign(Int64.prototype, Long.prototype);

// Now you can use methods from the Long library.
var int64 = statement.safeIntegers().pluck().get();
int64 = int64.multiply(2).value();
```

Since most [Long](https://github.com/dcodeIO/long.js) methods return new `Long` objects, the `.value()` method is necessary to convert it back to an `Int64`.
