# better-sqlite3 [![Build Status](https://travis-ci.org/JoshuaWise/better-sqlite3.svg?branch=master)](https://travis-ci.org/JoshuaWise/better-sqlite3)

The fastest and simplest library for SQLite3 in Node.js.

- Full transaction support
- Geared for performance, efficiency, and safety
- Easy-to-use synchronous API *(faster than an asynchronous API... yes, you read that correctly)*
- Custom SQL function support
- 64-bit integer support *(invisible until you need it)*

## How other libraries compare

|   |select 1 row &nbsp;`get()`&nbsp;|select 100 rows &nbsp;&nbsp;`all()`&nbsp;&nbsp;|select 100 rows `iterate()` 1-by-1|insert 1 row `run()`|insert 100 rows in a transaction|
|---|---|---|---|---|---|
|better-sqlite3|1x|1x|1x|1x|1x|
|[sqlite](https://www.npmjs.com/package/sqlite) and [sqlite3](https://www.npmjs.com/package/sqlite3)|8.4x slower|3.7x slower|28.2x slower|3.6x slower|6.0x slower|

> You can verify these results by [running the benchmark yourself](https://github.com/JoshuaWise/better-sqlite3/wiki/Benchmark).
> *Both [npm/sqlite](https://www.npmjs.com/package/sqlite) and [npm/sqlite3](https://www.npmjs.com/package/sqlite3) have nearly identical performance because they both use the [same engine](https://github.com/mapbox/node-sqlite3).*

## Installation

```bash
npm install --save better-sqlite3
```

> If you have trouble installing, check the [troubleshooting guide](https://github.com/JoshuaWise/better-sqlite3/wiki/Troubleshooting-installation).

## Usage

```js
const db = require('better-sqlite3')('foobar.db', options);

const row = db.prepare('SELECT * FROM users WHERE id=?').get(userId);
console.log(row.firstName, row.lastName, row.email);
```

## Why should I use this instead of [node-sqlite3](https://github.com/mapbox/node-sqlite3)?

- `node-sqlite3` uses asynchronous APIs for tasks that are either CPU-bound or serialized. That's not only bad design, but it wastes tons of resources. It also causes [mutex thrashing](https://en.wikipedia.org/wiki/Resource_contention) which has devastating effects on performance.
- `node-sqlite3` exposes low-level (C language) memory management functions. `better-sqlite3` does it the JavaScript way, allowing the garbage collector to worry about memory management.
- `better-sqlite3` is simpler to use, and it provides nice utilities for some operations that are very difficult or impossible in `node-sqlite3`.
- `better-sqlite3` is much faster than `node-sqlite3` in most cases, and just as fast in all other cases.

#### When is this library not appropriate?

In most cases, if you're attempting something that cannot be reasonably accomplished with `better-sqlite3`, it probably cannot be reasonably accomplished with SQLite3 in general. For example, if you're executing queries that take nearly one second to complete, and you expect to have many concurrent users executing those queries, no amount of asynchronicity will save you from SQLite3's serialized nature. Fortunately, SQLite3 is very *very* fast. With proper indexing, I've been able to achieve upward of 2000 queries per second with 5-way-joins in a 60 GB database, where each query was handling 5–50 kilobytes of real data.

If you have a performance problem, the most likely causes are inefficient queries, improper indexing, or a lack of [WAL mode](https://github.com/JoshuaWise/better-sqlite3/wiki/Performance)—not `better-sqlite3` itself. However, there are some cases where `better-sqlite3` would not be appropriate.

- If you expect a high volume of concurrent reads each returning hundreds of megabytes of data (i.e., videos)
- If you expect a high volume of concurrent writes (i.e., for a social media site)
- If your database's size is near the terabyte range

If you fall into the first category listed above, then perhaps [`node-sqlite3`](https://github.com/mapbox/node-sqlite3) would be more appropriate. On the other hand, if you fall into the second or third categories (or indeed the first), then you should probably use a full-fledged RDBMS such as [PostgreSQL](https://www.postgresql.org/).

# Documentation

- [API documentation](https://github.com/JoshuaWise/better-sqlite3/wiki/API)
- [Performance](https://github.com/JoshuaWise/better-sqlite3/wiki/Performance) (also see [benchmark results](https://github.com/JoshuaWise/better-sqlite3/wiki/Benchmark))
- [64-bit integer support](https://github.com/JoshuaWise/better-sqlite3/wiki/64-bit-integer-support)
- [SQLite3 compilation options](https://github.com/JoshuaWise/better-sqlite3/wiki/SQLite3-compilation-options)

# License

[MIT](https://github.com/JoshuaWise/better-sqlite3/blob/master/LICENSE)
