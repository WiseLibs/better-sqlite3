# Helpful tips for SQLite3
## Creating safe tables
It's a good idea to use `INTEGER PRIMARY KEY AUTOINCREMENT` as one of the columns in a table. This ensures two things:
- `INTEGER PRIMARY KEY`: improved performance by reusing SQLite3's built-in `rowid` column.
- `AUTOINCREMENT`: no future row will have the same ID as an old one that was deleted. This can prevent potential bugs and security breaches.

If you don't use `INTEGER PRIMARY KEY`, then you *must* use `NOT NULL` in all of your your primary key columns. Otherwise you'll be victim to an SQLite3 bug that allows primary keys to be `NULL`.

Any column with `INTEGER PRIMARY KEY` will automatically increment when setting its value to `NULL`. But without `AUTOINCREMENT`, the behavior only ensures uniqueness from currently existing rows.

It should be noted that `NULL` values count as unique from each other. This has implications when using the `UNIQUE` contraint or any other equality test.

## Default values
When a column has a `DEFAULT` value, it only gets applied when no value is specified for an `INSERT` statement. If the `INSERT` statement specifies a `NULL` value, the `DEFAULT` value is **NOT** used.

## Foreign keys
Foreign key constraints are not enforced if the child's column value is `NULL`. To ensure that a relationship is always enforced, use `NOT NULL` on the child column.

Example:
```sql
CREATE TABLE comments (value TEXT, user_id INTEGER NOT NULL REFERENCES users);
```

Foreign key clauses can be followed by `ON DELETE` and/or `ON UPDATE`, with the following possible values:
- `SET NULL`: if the parent column is deleted or updated, the child column becomes `NULL`.
  - *NOTE: This still causes a constraint violation if the child column has `NOT NULL`*.
- `SET DEFAULT`: if the parent column is updated or deleted, the child column becomes its `DEFAULT` value.
  - *NOTE: This still causes a constraint violation if the child column's `DEFAULT` value does not correspond with an actual parent row*.
- `CASCADE`: if the parent row is deleted, the child row is deleted; if the parent column is updated, the new value is propogated to all children.

