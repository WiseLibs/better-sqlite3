# Running the benchmark

To run the benchmark yourself:
```bash
git clone https://github.com/JoshuaWise/better-sqlite3.git
cd better-sqlite3
npm install # if you're doing this as the root user, --unsafe-perm is required
node benchmark
```

# Results

These results are from 06/05/2017, on a MacBook Pro (Retina, 15-inch, Mid 2014, OSX 10.11.4), using nodejs v6.10.2.

### Reading rows individually (`.get()`)
```
better-sqlite3 x 143,686 ops/sec ±2.37%
node-sqlite3   x 18,468 ops/sec ±1.52%
```

### Reading 100 rows into an array (`.all()`)
```
better-sqlite3 x 7,329 ops/sec ±0.47%
node-sqlite3   x 2,143 ops/sec ±0.71%
```

### Iterating over 100 rows (`.each()`)
```
better-sqlite3 x 6,831 ops/sec ±1.47%
node-sqlite3   x 2,001 ops/sec ±2.19%
```

### Inserting rows individually (`.run()`)
```
--- normal journal mode ---
better-sqlite3 x 2,142 ops/sec ±12.80%
node-sqlite3   x 1,772 ops/sec ±10.32%

--- WAL mode ---
better-sqlite3 x 67,944 ops/sec ±2.93%
node-sqlite3   x 19,549 ops/sec ±3.74%
```

### Inserting 100 rows in a single transaction
```
better-sqlite3 x 1,307 ops/sec ±8.23%
node-sqlite3   x 212 ops/sec ±2.84%
```

### "Real world" benchmark
```
--- normal journal mode ---
better-sqlite3 x 4,799 ops/sec ±2.92%
node-sqlite3   x 3,386 ops/sec ±8.48%

--- WAL mode ---
better-sqlite3 x 103,417 ops/sec ±2.36%
node-sqlite3   x 17,112 ops/sec ±5.63%
```
