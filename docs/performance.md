# Performance

Concurrently reading and writing from an SQLite database can be very slow in some cases. Since concurrency is usually very important in web applications, it's recommended to turn on [WAL mode](https://www.sqlite.org/wal.html) to greatly increase overall performance.

```js
db.pragma('journal_mode = WAL');
```

WAL mode has a *few* disadvantages to consider:

- Transactions that involve ATTACHed databases are atomic for each individual database, but are not atomic across all databases as a set.
- Under rare circumstances, the [WAL file](https://www.sqlite.org/wal.html) may experience "checkpoint starvation" (see below).
- There are some hardware/system limitations that may affect some users, [listed here](https://www.sqlite.org/wal.html).

However, you trade those disadvantages for extremely fast performance in most web applications.

## Checkpoint starvation

Checkpoint starvation is when SQLite is unable to recycle the [WAL file](https://www.sqlite.org/wal.html) due to everlasting concurrent reads to the database. If this happens, the WAL file will grow without bound, leading to unacceptable amounts of disk usage and deteriorating performance.

If you don't access the database from multiple processes or threads simultaneously, you'll never encounter this issue.

If you do access the database from multiple processes or threads simultaneously, just use the [`wal_checkpoint(RESTART)`](https://www.sqlite.org/pragma.html#pragma_wal_checkpoint) pragma when the WAL file gets too big.

```js
setInterval(fs.stat.bind(null, 'foobar.db-wal', (err, stat) => {
  if (err) {
    if (err.code !== 'ENOENT') throw err;
  } else if (stat.size > someUnacceptableSize) {
    db.pragma('wal_checkpoint(RESTART)');
  }
}), 5000).unref();
```

## Checkpoints and the event loop

In WAL mode, SQLite automatically runs a checkpoint when the WAL file grows past [`wal_autocheckpoint`](https://www.sqlite.org/pragma.html#pragma_wal_autocheckpoint) pages (1000 by default). That checkpoint runs inside the statement whose commit crosses the threshold, and it ends with an `fsync()` of the database file. Since better-sqlite3 is synchronous, the `fsync()` blocks the calling thread, which in most applications is the event loop.

On an idle disk this takes milliseconds. On a busy disk (a backup, another process writing, a shared VM) the `fsync()` can take far longer, and an ordinary `INSERT` can block the event loop for seconds. In one measurement (2-CPU Linux container, disk throttled to 120 MB/s and 400 IOPS, two background processes rewriting 256 MB files with `fsync()`, 4 KB commits every 5 ms for 20 seconds), the slowest commit took 3.5 to 5.9 seconds, at either `synchronous = FULL` or `NORMAL`. With the checkpoint moved to a worker thread, the slowest commit took about 2 ms.

If worst-case latency matters, turn off the automatic checkpoint on the main connection and checkpoint from a worker thread with its own connection:

```js
// main thread
db.pragma('wal_autocheckpoint = 0');
new Worker('./checkpointer.js', { workerData: { filename: db.name } }).unref();
```

```js
// checkpointer.js
const { workerData } = require('worker_threads');
const Database = require('better-sqlite3');

const db = new Database(workerData.filename);
setInterval(() => db.pragma('wal_checkpoint(PASSIVE)'), 1000);
```

A [`PASSIVE`](https://www.sqlite.org/c3ref/wal_checkpoint_v2.html) checkpoint never takes the write lock, so the main connection keeps committing while the worker copies pages into the database file. Once `wal_autocheckpoint` is `0`, nothing else checkpoints the database, so the worker must keep running; otherwise the WAL file grows without bound.

## A note about durability

This distribution of SQLite uses the `SQLITE_DEFAULT_WAL_SYNCHRONOUS=1` [compile-time option](https://sqlite.org/compile.html#default_wal_synchronous), which makes databases in WAL mode default to the ["NORMAL" synchronous setting](https://sqlite.org/pragma.html#pragma_synchronous). This allows applications to achieve extreme performance, but introduces a slight loss of [durability](https://en.wikipedia.org/wiki/Durability_(database_systems)) while in WAL mode.

You can override this setting by running `db.pragma('synchronous = FULL')`.
