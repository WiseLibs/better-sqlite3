# Improving concurrency

Concurrently reading and writing from an SQLite3 database can be very slow in some cases. Since concurrency is usually very important in web applications, it's recommended to turn on [WAL mode](https://www.sqlite.org/wal.html) to greatly increase overall performance.

```js
db.pragma('journal_mode = WAL');
```

WAL mode has a *few* disadvantages to consider:
- Transactions that involve ATTACHed databases are atomic for each individual database, but are not atomic across all databases as a set.
- Under rare circumstances, the [WAL file](https://www.sqlite.org/wal.html) may experience "checkpoint starvation" (see below).
- There are some hardware/system limitations that may affect some users, [listed here](https://www.sqlite.org/wal.html).

However, you trade those disadvantages for greatly improved performance in most web applications.

### Checkpoint starvation

Checkpoint starvation is when SQLite3 is unable to recycle the [WAL file](https://www.sqlite.org/wal.html) due to everlasting concurrent reads to the database. If this happens, the WAL file will grow without bound, leading to unacceptable amounts of disk usage and deteriorating performance.

To prevent this, just periodically use the [db.checkpoint()](https://github.com/JoshuaWise/better-sqlite3/wiki/API#checkpointforce---number) method to force checkpointing whenever you deem appropriate.

If you don't access the database from multiple processes simultaneously, you'll never encounter this issue.

# Maximum power

If you want to *further* improve write performance and you're willing to sacrifice a tiny bit of [durability](https://en.wikipedia.org/wiki/Durability_(database_systems)), you can use this:

```js
db.pragma('journal_mode = WAL');
db.pragma('synchronous = 1');
```

Normally, setting `synchronous = 1` would introduce the risk of database corruption following a power loss or hard reboot. But in [WAL mode](https://www.sqlite.org/wal.html), you do not introduce this risk. The combination of these two PRAGMAs provides extremely fast performance.