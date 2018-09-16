# Performance

Concurrently reading and writing from an SQLite3 database can be very slow in some cases. Since concurrency is usually very important in web applications, it's recommended to turn on [WAL mode](https://www.sqlite.org/wal.html) to greatly increase overall performance.

```js
db.pragma('journal_mode = WAL');
```

WAL mode has a *few* disadvantages to consider:

- Transactions that involve ATTACHed databases are atomic for each individual database, but are not atomic across all databases as a set.
- Under rare circumstances, the [WAL file](https://www.sqlite.org/wal.html) may experience "checkpoint starvation" (see below).
- There are some hardware/system limitations that may affect some users, [listed here](https://www.sqlite.org/wal.html).

However, you trade those disadvantages for extremely fast performance in most web applications.

## Checkpoint starvation

Checkpoint starvation is when SQLite3 is unable to recycle the [WAL file](https://www.sqlite.org/wal.html) due to everlasting concurrent reads to the database. If this happens, the WAL file will grow without bound, leading to unacceptable amounts of disk usage and deteriorating performance.

If you don't access the database from multiple processes simultaneously, you'll never encounter this issue.

If you do access the database from multiple processes simultaneously, just use the [`db.checkpoint()`](./api.md#checkpointdatabasename---this) method when the WAL file gets too big.

```js
setInterval(fs.stat.bind(null, 'foobar.db-wal', (err, stat) => {
  if (err) {
    if (err.code !== 'ENOENT') throw err;
  } else if (stat.size > someUnacceptableSize) {
    db.checkpoint();
  }
}), 5000).unref();
```

## A note about durability

This distribution of SQLite3 uses the `SQLITE_DEFAULT_WAL_SYNCHRONOUS=1` [compile-time option](https://sqlite.org/compile.html#default_wal_synchronous), which makes databases in WAL mode default to the ["NORMAL" synchronous setting](https://sqlite.org/pragma.html#pragma_synchronous). This allows applications to achieve extreme performance, but introduces a slight loss of [durability](https://en.wikipedia.org/wiki/Durability_(database_systems)) while in WAL mode.

You can override this setting by running `db.pragma('synchronous = FULL')`.
