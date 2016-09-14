### Concurrently reading and writing on multiple connections (WAL mode)
```
better-sqlite3	10000 overlapping INSERT or SELECTs in 268ms
node-sqlite3	10000 overlapping INSERT or SELECTs in 553ms
```

### Reading and writing on a single connection
normal journal mode:
```
better-sqlite3	1000 INSERT or SELECTs in 409ms
node-sqlite3	1000 INSERT or SELECTs in 793ms
```

WAL mode:
```
better-sqlite3	10000 INSERT or SELECTs in 265ms
node-sqlite3	10000 INSERT or SELECTs in 282ms
```

insert.sync.large.js
```
better-sqlite3	250 INSERTs in 1085ms
node-sqlite3	250 INSERTs in 1606ms
```

insert.sync.small.js
better-sqlite3	500 INSERTs in 1414ms
node-sqlite3	500 INSERTs in 2776ms

insert.wal.large.js
```
better-sqlite3	250 INSERTs in 1464ms
node-sqlite3	250 INSERTs in 2965ms
```

insert.wal.small.js
```
better-sqlite3	5000 INSERTs in 152ms
node-sqlite3	5000 INSERTs in 144ms
```

select-all.sync.large.js
```
better-sqlite3	1 multi-row SELECTs in 770ms
node-sqlite3	1 multi-row SELECTs in 1600ms
```

select-all.sync.small.js
```
better-sqlite3	100 multi-row SELECTs in 89ms
node-sqlite3	100 multi-row SELECTs in 136ms
```

select-each.sync.large.js
```
better-sqlite3	1 SELECT iterations in 787ms
node-sqlite3	1 SELECT iterations in 1093ms
```

select-each.sync.small.js
```
better-sqlite3	100 SELECT iterations in 64ms
node-sqlite3	100 SELECT iterations in 1648ms
```

select.sync.large.js
```
better-sqlite3	1000 SELECTs in 815ms
node-sqlite3	1000 SELECTs in 1426ms
```

select.sync.small.js
```
better-sqlite3	10000 SELECTs in 193ms
node-sqlite3	10000 SELECTs in 271ms
```

select.wal.large.js
```
better-sqlite3	1000 SELECTs in 800ms
node-sqlite3	1000 SELECTs in 1438ms
```

select.wal.small.js
```
better-sqlite3	10000 SELECTs in 138ms
node-sqlite3	10000 SELECTs in 228ms
```

transaction.sync.large.js
```
better-sqlite3	250 INSERTs (single TRANSACTION) in 596ms
node-sqlite3	250 INSERTs (single TRANSACTION) in 1062ms
```

transaction.sync.small.js
```
better-sqlite3	5000 INSERTs (single TRANSACTION) in 45ms
node-sqlite3	5000 INSERTs (single TRANSACTION) in 125ms
```

transaction.wal.large.js
```
better-sqlite3	250 INSERTs (single TRANSACTION) in 1117ms
node-sqlite3	250 INSERTs (single TRANSACTION) in 2437ms
```

transaction.wal.small.js
```
better-sqlite3	5000 INSERTs (single TRANSACTION) in 45ms
node-sqlite3	5000 INSERTs (single TRANSACTION) in 131ms
```