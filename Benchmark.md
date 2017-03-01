# Running the benchmark

To run the benchmark yourself:
```bash
git clone https://github.com/JoshuaWise/better-sqlite3.git
cd better-sqlite3
npm install
node benchmark
```

# Results

These results are from 03/01/2017, on a MacBook Pro (Retina, 15-inch, Mid 2014, OSX 10.11.4).

### Creating prepared statements
```
better-sqlite3	100000 prepared statements in 1098ms
node-sqlite3	100000 prepared statements in 1974ms
```

### Reading rows individually (`.get()`)
```
better-sqlite3	10000 SELECTs in 196ms
node-sqlite3	10000 SELECTs in 431ms
```

### Reading 1000 rows into an array (`.all()`)
```
better-sqlite3	100 SELECTs (1000 rows each) in 48ms
node-sqlite3	100 SELECTs (1000 rows each) in 137ms
```

### Iterating over 1000 rows (`.each()`)
```
better-sqlite3	100 SELECTs (1000 rows each) in 33ms
node-sqlite3	100 SELECTs (1000 rows each) in 1483ms
```

### Inserting rows individually (`.run()`)
```
--- normal journal mode ---
better-sqlite3	500 INSERTs in 216ms
node-sqlite3	500 INSERTs in 216ms

--- WAL mode ---
better-sqlite3	5000 INSERTs in 133ms
node-sqlite3	5000 INSERTs in 181ms
```

### Inserting many rows in a single transaction
```
--- normal journal mode ---
better-sqlite3	5000 INSERTs in 30ms
node-sqlite3	5000 INSERTs in 157ms

--- WAL mode ---
better-sqlite3	5000 INSERTs in 30ms
node-sqlite3	5000 INSERTs in 158ms
```

### "Real world" benchmark
```
--- normal journal mode ---
better-sqlite3	1000 INSERT or SELECTs in 249ms
node-sqlite3	1000 INSERT or SELECTs in 256ms

--- WAL mode ---
better-sqlite3	10000 INSERT or SELECTs in 293ms
node-sqlite3	10000 INSERT or SELECTs in 609ms
```
