## Improving concurrency

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