# The `BigInt` primitive type

SQLite3 can store data in 64-bit signed integers, which are too big for JavaScript's [number format](https://en.wikipedia.org/wiki/Double-precision_floating-point_format) to fully represent. To support this data type, `better-sqlite3` is fully compatible with [BigInts](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/BigInt).

```js
const big = BigInt('1152735103331642317');
big === 1152735103331642317n; // returns true
big.toString(); // returns "1152735103331642317"
typeof big; // returns "bigint"
```

## Binding BigInts

`BigInts` can bind to [`Statements`](./api.md#class-statement) just like regular numbers. You can also return `BigInts` from [user-defined functions](./api.md#functionname-options-function---this). However, if you provide a `BigInt` that's too large to be a 64-bit signed integer, you'll get an error so that data integrity is protected.

```js
db.prepare("SELECT * FROM users WHERE id=?").get(BigInt('1152735103331642317'));
db.prepare("INSERT INTO users (id) VALUES (?)").run(BigInt('1152735103331642317'));

db.prepare("SELECT ?").get(2n ** 63n - 1n); // returns successfully
db.prepare("SELECT ?").get(2n ** 63n); // throws a RangeError
```

## Getting BigInts from the database

By default, integers returned from the database (including the [`info.lastInsertRowid`](./api.md#runbindparameters---object) property) are normal JavaScript numbers. You can change this default as you please:

```js
db.defaultSafeIntegers(); // BigInts by default
db.defaultSafeIntegers(true); // BigInts by default
db.defaultSafeIntegers(false); // Numbers by default
```

Additionally, you can override the default for individual [`Statements`](./api.md#class-statement) like so:

```js
const stmt = db.prepare(SQL);

stmt.safeIntegers(); // Safe integers ON
stmt.safeIntegers(true); // Safe integers ON
stmt.safeIntegers(false); // Safe integers OFF
```

[User-defined functions](./api.md#functionname-options-function---this) can receive `BigInts` as arguments. You can override the database's default setting like so:

```js
db.function('isInt', { safeIntegers: true }, (value) => {
  return String(typeof value === 'bigint');
});

db.prepare('SELECT isInt(?)').pluck().get(10); // => "false"
db.prepare('SELECT isInt(?)').pluck().get(10n); // => "true"
```

Likewise, [user-defined aggregates](./api.md#aggregatename-options---this) and [virtual tables](./api.md#tablename-definition---this) can also receive `BigInts` as arguments:

```js
db.aggregate('addInts', {
  safeIntegers: true,
  start: 0n,
  step: (total, nextValue) => total + nextValue,
});
```

```js
db.table('sequence', {
  safeIntegers: true,
  columns: ['value'],
  parameters: ['length', 'start'],
  rows: function* (length, start = 0n) {
    const end = start + length;
    for (let n = start; n < end; ++n) {
      yield { value: n };
    }
  },
});
```

It's worth noting that REAL (FLOAT) values returned from the database will always be represented as normal numbers.
