# Benchmark

To run the benchmark yourself:

```bash
git clone https://github.com/JoshuaWise/better-sqlite3.git
cd better-sqlite3
npm install # if you're doing this as the root user, --unsafe-perm is required
node benchmark
```

# Results

These results are from 03/29/2020, on a MacBook Pro (Retina, 15-inch, Mid 2014, OSX 10.11.6), using nodejs v12.16.1.

```
--- reading rows individually ---
better-sqlite3 x 313,899 ops/sec ±0.13%
node-sqlite3   x 26,780 ops/sec ±2.9%

--- reading 100 rows into an array ---
better-sqlite3 x 8,508 ops/sec ±0.27%
node-sqlite3   x 2,930 ops/sec ±0.37%

--- iterating over 100 rows ---
better-sqlite3 x 6,532 ops/sec ±0.32%
node-sqlite3   x 268 ops/sec ±3.4%

--- inserting rows individually ---
better-sqlite3 x 62,554 ops/sec ±7.33%
node-sqlite3   x 22,637 ops/sec ±4.37%

--- inserting 100 rows in a single transaction ---
better-sqlite3 x 4,141 ops/sec ±4.57%
node-sqlite3   x 265 ops/sec ±4.87%
```

> All benchmarks are executed in [WAL mode](./performance.md).
