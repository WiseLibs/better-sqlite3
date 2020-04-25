# Unsafe mode

By default, `better-sqlite3` prevents you from doing things that might corrupt your database or cause undefined behavior. Such unsafe operations include:

- Anything blocked by [`SQLITE_DBCONFIG_DEFENSIVE`](https://www.sqlite.org/c3ref/c_dbconfig_defensive.html#sqlitedbconfigdefensive)
- Mutating the database while [iterating](https://github.com/JoshuaWise/better-sqlite3/blob/master/docs/api.md#iteratebindparameters---iterator) through a query's result set

However, some advanced users might want to use these functionalities at their own risk. For this reason, users have the option of enabling "unsafe mode".

```js
db.unsafeMode(); // Unsafe mode ON
db.unsafeMode(true); // Unsafe mode ON
db.unsafeMode(false); // Unsafe mode OFF
```

Unsafe mode can be toggled at any time, and independently for each database connection. While toggled on, `better-sqlite3` will not prevent you from performing the dangerous operations listed above.
