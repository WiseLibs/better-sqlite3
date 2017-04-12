# Running the benchmark

To run the benchmark yourself:
```bash
git clone https://github.com/JoshuaWise/better-sqlite3.git
cd better-sqlite3
npm install # if you're doing this as the root user, --unsafe-perm is required
node benchmark
```

# Results

These results are from 04/12/2017, on a MacBook Pro (Retina, 15-inch, Late 2013, OSX 10.11.6), using nodejs v6.10.0.

### Reading rows individually (`.get()`)
```
better-sqlite3 x 124,973 ops/sec ±1.96%
node-sqlite3   x 16,110 ops/sec ±1.68%
```

### Reading 100 rows into an array (`.all()`)
```
better-sqlite3 x 5,426 ops/sec ±3.70%
node-sqlite3   x 1,851 ops/sec ±1.88%
```

### Iterating over 100 rows (`.each()`)
```
better-sqlite3 x 5,598 ops/sec ±1.90%
node-sqlite3   x 1,751 ops/sec ±2.84%
```

### Inserting rows individually (`.run()`)
```
--- normal journal mode ---
better-sqlite3 x 2,243 ops/sec ±7.48%
node-sqlite3   x 1,901 ops/sec ±9.06%

--- WAL mode ---
better-sqlite3 x 10,991 ops/sec ±1.89%
node-sqlite3   x 6,739 ops/sec ±1.79%
```

### Inserting 100 rows in a single transaction
```
better-sqlite3 x 1,355 ops/sec ±9.24%
node-sqlite3   x 187 ops/sec ±2.48%
```

### "Real world" benchmark
```
--- normal journal mode ---
better-sqlite3 x 4,424 ops/sec ±6.88%
node-sqlite3   x 2,714 ops/sec ±8.81%

--- WAL mode ---
better-sqlite3 x 20,530 ops/sec ±1.85%
node-sqlite3   x 8,826 ops/sec ±3.41%
```
