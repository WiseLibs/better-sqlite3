# Running the benchmark

To run the benchmark yourself:
```bash
git clone https://github.com/JoshuaWise/better-sqlite3.git
cd better-sqlite3
npm install
node benchmark
```

# Results

These results are from 09/13/2016, on a MacBook Pro (Retina, 15-inch, Mid 2014, OSX 10.11.4).

### Concurrently reading and writing on multiple connections (WAL mode)
```
better-sqlite3	10000 overlapping INSERT or SELECTs in 268ms
node-sqlite3	10000 overlapping INSERT or SELECTs in 553ms
```

### Reading and writing on a single connection

```
--- normal journal mode ---
better-sqlite3	1000 INSERT or SELECTs in 409ms
node-sqlite3	1000 INSERT or SELECTs in 793ms

--- WAL mode ---
better-sqlite3	10000 INSERT or SELECTs in 265ms
node-sqlite3	10000 INSERT or SELECTs in 282ms
```

### Inserting small rows of data individually (`.run()`)
```
--- normal journal mode ---
better-sqlite3	500 INSERTs in 1414ms
node-sqlite3	500 INSERTs in 2776ms

--- WAL mode ---
better-sqlite3	5000 INSERTs in 152ms
node-sqlite3	5000 INSERTs in 144ms
```

### Inserting large rows of data individually (`.run()`)
```
--- normal journal mode ---
better-sqlite3	250 INSERTs in 1085ms
node-sqlite3	250 INSERTs in 1606ms

--- WAL mode ---
better-sqlite3	250 INSERTs in 1464ms
node-sqlite3	250 INSERTs in 2965ms
```

### Selecting small rows of data individually (`.get()`)
```
better-sqlite3	10000 SELECTs in 138ms
node-sqlite3	10000 SELECTs in 228ms
```

### Selecting large rows of data individually (`.get()`)
```
better-sqlite3	1000 SELECTs in 800ms
node-sqlite3	1000 SELECTs in 1438ms
```

### Reading 1000 large rows of data in a single operation (`.all()`)
```
better-sqlite3	1 multi-row SELECTs in 770ms
node-sqlite3	1 multi-row SELECTs in 1600ms
```

### Reading 1000 small rows of data in a single operation (`.all()`)
```
better-sqlite3	100 multi-row SELECTs in 89ms
node-sqlite3	100 multi-row SELECTs in 136ms
```

### Iterating through 1000 large rows of data in a single operation (`.each()`)
```
better-sqlite3	1 SELECT iterations in 787ms
node-sqlite3	1 SELECT iterations in 1093ms
```

### Iterating through 1000 small rows of data in a single operation (`.each()`)
```
better-sqlite3	100 SELECT iterations in 64ms
node-sqlite3	100 SELECT iterations in 1648ms
```

### Inserting many small rows in a single transaction.
```
--- normal journal mode ---
better-sqlite3	5000 INSERTs (single TRANSACTION) in 45ms
node-sqlite3	5000 INSERTs (single TRANSACTION) in 125ms

--- WAL mode ---
better-sqlite3	5000 INSERTs (single TRANSACTION) in 45ms
node-sqlite3	5000 INSERTs (single TRANSACTION) in 131ms
```

### Inserting many large rows in a single transaction.
```
--- normal journal mode ---
better-sqlite3	250 INSERTs (single TRANSACTION) in 596ms
node-sqlite3	250 INSERTs (single TRANSACTION) in 1062ms

--- WAL mode ---
better-sqlite3	250 INSERTs (single TRANSACTION) in 1117ms
node-sqlite3	250 INSERTs (single TRANSACTION) in 2437ms
```
