// Type definitions for better-sqlite3 v3.1.1
// Project: <https://github.com/JoshuaWise/better-sqlite3>
// Definitions by: Matthew McEachen <matthew-github@mceachen.org

export = BetterSqlite3;

declare namespace BetterSqlite3 {

  interface CtorOptions {
    memory: boolean;
    readonly: boolean;
  }

  interface RegisterOptions {
    name: string;
    varargs: boolean;
    deterministic: boolean;
  }

  type Callback = (...arr: any[]) => void;

  export class Database {
    /**
     * Creates a new database connection. If the database file does not exist,
     * it is created. This happens synchronously, which means you can start
     * executing queries right away.
     *
     * If options.memory is true, an in-memory database will be created, rather
     * than a disk-bound one. Default is false.
     *
     * If options.readonly is true, the database connection will be opened in
     * readonly mode. Default is false.
     */
    constructor(path: string, options?: Partial<CtorOptions>)

    /**
     * Creates a new prepared Statement from the given SQL string
     */
    prepare(statement: string): Statement;

    /**
     * Creates a new prepared Transaction from the given array of SQL strings.
     *
     * NOTE: Transaction objects cannot contain read-only statements. In
     * better-sqlite3, these objects serve the sole purpose of batch-write
     * operations. For more complex transactions, simply run BEGIN and COMMIT
     * with regular prepared statements. This restriction may change in the
     * future
     */
    transaction(statements: string[]): Transaction;

    /**
     * Executes the given PRAGMA and returns its result. By default, the return
     * value will be an array of result rows. Each row is represented by an
     * object whose keys correspond to column names.
     *
     * Since most PRAGMA statements return a single value, the simplify option
     * is provided to make things easier. When simplify is true, only the first
     * column of the first row will be returned
     */
    pragma(pragma: string, simplify?: boolean): any;

    /**
     * Runs a WAL mode checkpoint on all attached databases (including the main
     * database).
     *
     * Unlike automatic checkpoints, this method executes a checkpoint in
     * "RESTART" mode, which ensures a complete checkpoint operation even if
     * other processes are using the database at the same time. You only need to
     * use this method if you are accessing the database from multiple processes
     * at the same time.
     *
     * If databaseName is provided, it should be the name of an attached
     * database (or "main"). This causes only that database to be checkpointed.
     */
    checkpoint(): this;

    /**
     * Registers the given function so that it can be used by SQL statements.
     *
     * By default, registered functions have a strict number of arguments
     * (determined by function.length). You can register multiple functions of
     * the same name, each with a different number of arguments, causing SQLite3
     * to execute a different function depending on how many arguments were
     * passed to it. If you register two functions with same name and the same
     * number of arguments, the second registration will erase the first one.
     *
     * If options.name is given, the function will be registered under that name
     * (instead of defaulting to function.name).
     *
     * If options.varargs is true, the registered function can accept any number
     * of arguments.
     *
     * If your function is deterministic, you can set options.deterministic to
     * true, which may improve performance under some circumstances.
     */
    register(options: Partial<RegisterOptions>, callback: Callback): this;
    register(callback: Callback): this;

    /**
     * Executes the given SQL string. Unlike prepared statements, this can
     * execute strings that contain multiple SQL statements. This function
     * performs worse and is less safe than using prepared statements. You
     * should only use this method when you need to execute SQL from an external
     * source (usually a file). If an error occurs, execution stops and further
     * statements are not executed. You must rollback changes manually.
     */
    exec(statement: string): this;

    /**
     * Closes the database connection. After invoking this method, no
     * statements/transactions can be created or executed.
     */
    close(): this;

    /**
     * Whether the database connection is currently open
     */
    readonly open: boolean;

    /**
     * Whether the database connection is currently in an open transaction
     */
    readonly inTransaction: boolean;

    /**
     * The string that was used to open the database connection
     */
    readonly name: string;

    /**
     * Whether the database is an in-memory database
     */
    readonly memory: boolean;

    /**
     * Whether the database connection was created in readonly mode
     */
    readonly readonly: boolean;
  }

  export interface RunInfo {
    /**
     * The total number of rows that were inserted, updated, or deleted by this
     * operation. Changes made by foreign key actions or trigger programs do not
     * count
     */
    changes: number;

    /**
     * The rowid of the last row inserted into the database (ignoring those
     * caused by trigger programs). If the current statement did not insert any
     * rows into the database, this number should be completely ignored
     */
    lastInsertROWID: number;
  }

  // See https://www.typescriptlang.org/docs/handbook/release-notes/typescript-2-2.html#object-type
  export type Row = object;

  export interface Statement {
    /**
     * (use `run` only on statements that do not return data)
     *
     * Executes the prepared statement. When execution completes it returns an
     * info object describing any changes made.
     *
     * If execution of the statement fails, an Error is thrown.
     *
     * You can specify bind parameters, which are only bound for the given
     * execution.
     */
    run(bindParams?: any): RunInfo;

    /**
     * (use `get` only on statements that return data)
     *
     * Executes the prepared statement. When execution completes it returns an
     * object that represents the first row retrieved by the query. The object's
     * keys represent column names.
     *
     * If the statement was successful but found no data, undefined is returned.
     * If execution of the statement fails, an Error is thrown.
     *
     * You can specify bind parameters, which are only bound for the given
     * execution.
     */
    get(bindParams?: any): Row;

    /**
     * (use `all` only on statements that return data)
     *
     * Similar to .get(), but instead of only retrieving one row all matching
     * rows will be retrieved. The return value is an array of row objects.
     *
     * If no rows are found, the array will be empty. If execution of the
     * statement fails, an Error is thrown.
     *
     * You can specify bind parameters, which are only bound for the given
     * execution.
     */
    all(bindParams?: any): Row[];

    /**
     * (use `each` only on statements that return data)
     *
     * Similar to .all(), but instead of returning every row together, the
     * callback is invoked for each row as they are retrieved, one by one.
     *
     * After all rows have been consumed, undefined is returned. If execution of
     * the statement fails, an Error is thrown and iteration stops.
     *
     * You can specify bind parameters, which are only bound for the given
     * execution
     */
    each(bindParams: any[], callback: (row: Row) => void): void;
    each(callback: (row: Row) => void): void;

    /**
     * Causes the prepared statement to only return the value of the first
     * column of any rows that it retrieves, rather than the entire row object.
     */
    pluck(enable?: boolean): void;

    /**
     * Binds the given parameters to the statement permanently.Unlike binding
     * parameters upon execution, these parameters will stay bound to the prepared
     * statement for its entire life.
     *
     * After a statement's parameters are bound this way, you may no longer provide
     * it with execution-specific (temporary) bound parameters.
     *
     * This method is primarily used as a performance optimization when you need to
     * execute the same prepared statement many times with the same bound
     * parameters.
     */
    bind: WithBindParameters<this>;

    /**
     * The source string that was used to create the prepared statement
     */
    readonly source: string;

    /**
     * Whether the prepared statement returns data.
     */
    readonly returnsData: boolean;
  }

  export interface Transaction {

    /**
     * Similar to Statement#run().
     *
     * Each statement in the transaction is executed in order. Failed
     * transactions are automatically rolled back. If execution of the
     * transaction fails, an Error is thrown.
     *
     * You can specify bind parameters, which are only bound for the given
     * execution.
     */
    run: WithBindParameters<RunInfo>;

    /**
     * Same as {@link Statement#bind}
     */
    bind: WithBindParameters<this>;

    /**
     * A concatenation of each source string that was used to create the
     * prepared transaction. The source strings are seperated by newline
     * characters (\n).
     */
    readonly source: string;
  }

  export type Native = string | number | boolean;

  export interface WithBindParameters<T> {
    (...values: Native[]): T;
    (values: object | Native[]): T;
  }
}
