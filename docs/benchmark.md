# Benchmark

To run the benchmark yourself:

```bash
git clone https://github.com/JoshuaWise/better-sqlite3.git
cd better-sqlite3
npm install # if you're doing this as the root user, --unsafe-perm is required
node benchmark
```

# Results

These results are from 10/08/2018, on a MacBook Pro (Retina, 15-inch, Mid 2014, OSX 10.11.6), using nodejs v10.11.0. All benchmarks are executed in [WAL mode](./performance.md).


```
--- reading rows individually ---
better-sqlite3 x 283,745 ops/sec ±0.16%
node-sqlite3   x 27,191 ops/sec ±0.39%

--- reading 100 rows into an array ---
better-sqlite3 x 6,650 ops/sec ±0.25%
node-sqlite3   x 2,978 ops/sec ±0.33%

--- iterating over 100 rows ---
better-sqlite3 x 5,231 ops/sec ±0.28%
node-sqlite3   x 278 ops/sec ±0.62%

--- inserting rows individually ---
better-sqlite3 x 64,920 ops/sec ±5.86%
node-sqlite3   x 23,564 ops/sec ±3.58%

--- inserting 100 rows in a single transaction ---
better-sqlite3 x 4,155 ops/sec ±4.45%
node-sqlite3   x 321 ops/sec ±1.4%
```
