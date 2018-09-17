# Benchmark

To run the benchmark yourself:

```bash
git clone https://github.com/JoshuaWise/better-sqlite3.git
cd better-sqlite3
npm install # if you're doing this as the root user, --unsafe-perm is required
node benchmark
```

# Results

These results are from 08/29/2017, on a MacBook Pro (Retina, 15-inch, Mid 2014, OSX 10.11.6), using nodejs v6.10.3.

### Reading rows individually (`.get()`)

```
better-sqlite3 x 154,550 ops/sec ±0.52%
node-sqlite3   x 18,484 ops/sec ±1.63%
```

### Reading 100 rows into an array (`.all()`)

```
better-sqlite3 x 7,719 ops/sec ±0.32%
node-sqlite3   x 2,078 ops/sec ±1.91%
```

### Iterating over 100 rows (`.iterate()`)

```
better-sqlite3 x 5,387 ops/sec ±1.50%
node-sqlite3   x 191 ops/sec ±1.64%
```

### Inserting rows individually (`.run()`)

```
--- normal journal mode ---
better-sqlite3 x 2,305 ops/sec ±9.06%
node-sqlite3   x 1,770 ops/sec ±10.11%

--- WAL mode ---
better-sqlite3 x 65,569 ops/sec ±3.10%
node-sqlite3   x 18,302 ops/sec ±3.50%
```

### Inserting 100 rows in a single transaction

```
better-sqlite3 x 1,296 ops/sec ±7.52%
node-sqlite3   x 215 ops/sec ±3.57%
```

### "Real world" benchmark

```
--- normal journal mode ---
better-sqlite3 x 4,348 ops/sec ±1.54%
node-sqlite3   x 3,141 ops/sec ±11.96%

--- WAL mode ---
better-sqlite3 x 102,749 ops/sec ±2.69%
node-sqlite3   x 17,532 ops/sec ±6.14%
```
