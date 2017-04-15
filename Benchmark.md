# Running the benchmark

To run the benchmark yourself:
```bash
git clone https://github.com/JoshuaWise/better-sqlite3.git
cd better-sqlite3
npm install # if you're doing this as the root user, --unsafe-perm is required
node benchmark
```

# Results

These results are from 04/13/2017, on a MacBook Pro (Retina, 15-inch, Mid 2014, OSX 10.11.4), using nodejs v6.9.1.

### Reading rows individually (`.get()`)
```
better-sqlite3 x 139,927 ops/sec ±1.61%
node-sqlite3   x 17,862 ops/sec ±1.54%
```

### Reading 100 rows into an array (`.all()`)
```
better-sqlite3 x 6,649 ops/sec ±1.53%
node-sqlite3   x 2,018 ops/sec ±1.83%
```

### Iterating over 100 rows (`.each()`)
```
better-sqlite3 x 6,210 ops/sec ±2.43%
node-sqlite3   x 1,925 ops/sec ±2.56%
```

### Inserting rows individually (`.run()`)
```
--- normal journal mode ---
better-sqlite3 x 2,166 ops/sec ±10.90%
node-sqlite3   x 1,821 ops/sec ±7.31%

--- WAL mode ---
better-sqlite3 x 64,078 ops/sec ±4.31%
node-sqlite3   x 17,978 ops/sec ±3.23%
```

### Inserting 100 rows in a single transaction
```
better-sqlite3 x 1,302 ops/sec ±7.31%
node-sqlite3   x 209 ops/sec ±2.10%
```

### "Real world" benchmark
```
--- normal journal mode ---
better-sqlite3 x 4,756 ops/sec ±1.57%
node-sqlite3   x 3,324 ops/sec ±9.14%

--- WAL mode ---
better-sqlite3 x 99,210 ops/sec ±3.12%
node-sqlite3   x 16,942 ops/sec ±5.67%
```
