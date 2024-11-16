import database from './database.js';
import sqlite_error from './sqlite-error.js';

export const SqliteError = sqlite_error;
Object.assign(database, { SqliteError });
export default database;
