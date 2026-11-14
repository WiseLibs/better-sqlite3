# Opening a database from a file descriptor

On Unix-like systems (Linux, macOS, etc.), instead of passing a path to [`new Database()`](./api.md#new-databasepath-options), you can pass a file descriptor (a non-negative integer) for the database file, along with a second file descriptor for its [rollback journal](https://www.sqlite.org/lockingv3.html#rollback) (`options.journalFd`). The process doesn't need any permission to open files in the database's directory. For example, a privileged parent process can open a database that only it has access to, and pass the file descriptors to an unprivileged child process.

```js
const fs = require('fs');
const { spawn } = require('child_process');
const Database = require('better-sqlite3');

// Parent process (privileged)
fs.closeSync(fs.openSync('/var/lib/app/app.db', 'a')); // Create the files if needed
fs.closeSync(fs.openSync('/var/lib/app/app.db-journal', 'a')); // A journal file is also required
const databaseFd = fs.openSync('/var/lib/app/app.db', 'r+');
const journalFd = fs.openSync('/var/lib/app/app.db-journal', 'r+');
spawn('node', ['child.js'], {
  stdio: ['inherit', 'inherit', 'inherit', databaseFd, journalFd], // Becomes fds 3 and 4
  uid: 1000,
  gid: 1000,
});

// Child process (unprivileged)
const db = new Database(3, { journalFd: 4 });
```

The journal file must be the file named `<database>-journal`, in the same directory as the database file. This allows all other SQLite connections to find it and recover the database after a crash, so you get the full [atomicity and durability](https://www.sqlite.org/atomiccommit.html) guarantees of SQLite. The journal file can be empty, but it must exist.

Both file descriptors must be readable. Unless the `readonly` option is used, they must also be writable (i.e., opened with `'r+'` or `'w+'`, not `'r'`). They must not be in append mode (`'a'` or `'a+'`). Otherwise, a `TypeError` is thrown.

The file descriptors are duplicated, so the caller retains ownership of the ones that were passed in. However, they must not be closed until the database is closed (see the caveat about locking below).

The `.name` property of the database is `"fd:N"` (where `N` is the database file descriptor).

### Caveats

#### No WAL mode

Since the journal file can't be re-created without permission to create files in the directory, it's never deleted. Instead, it's truncated (which SQLite treats the same as a deleted journal). The `DELETE` (default), `TRUNCATE`, `PERSIST`, `MEMORY`, and `OFF` [journal modes](https://www.sqlite.org/pragma.html#pragma_journal_mode) are all supported, but `WAL` mode is not. Databases that are already in WAL mode cannot be opened this way (convert them first, using `PRAGMA journal_mode = DELETE` on a normal connection).

#### Other processes should not delete the journal file

If the database file **or the journal file** is deleted or replaced by another process (e.g., by a connection that opens the database by path and uses `journal_mode = DELETE`), this connection can no longer safely coordinate crash recovery with other connections. Therefore, every subsequent transaction fails with a `SQLITE_CANTOPEN` error, and the database must be reopened with new file descriptors. Concurrent connections that only read the database (or writers that use `journal_mode = TRUNCATE` or `PERSIST`) are safe.

> Also note that any connection with write permissions will automatically perform crash recovery and delete the journal if it finds one left behind by a process that crashed; that generally only matters if you have multiple concurrent file descriptor connections on the same database.

#### Limited functionality for attached databases

Transactions that write to multiple databases (using [`ATTACH`](https://www.sqlite.org/lang_attach.html)) are not supported, because they require creating a "super-journal" file. Such transactions fail when committed (and are rolled back). Otherwise, attached databases are opened by path, as normal.

#### File locking edge-cases

Locking is compatible with normal SQLite connections in other processes, so multiple processes can safely share the database, whether they open it by path or from file descriptors (including file descriptors inherited from the same parent process). Multiple connections in the same process that are opened from file descriptors (even the same ones) also coordinate with each other.

However, locking uses [POSIX advisory locks](https://www.sqlite.org/howtocorrupt.html), which are owned by the whole process. As a result, closing *any* file descriptor that refers to the database file (including the one you passed in) will silently release all locks held by the process, which can lead to database corruption. Therefore, keep the original file descriptors open until the database is closed, and don't open the database file by any other means (including by path) in the same process.

#### Platform compatibility

This feature is not supported on Windows.
