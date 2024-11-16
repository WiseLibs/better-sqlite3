import NodeSqlite from 'sqlite3';
import BetterSqlite from '../lib/index.js';

/*
	Every benchmark trial will be executed once for each SQLite3 driver listed
	below. Each driver has a function to open a new database connection on a
	given filename and a list of PRAGMA statements.
 */

export default new Map([
	['better-sqlite3', async (filename, pragma) => {
		const db = BetterSqlite(filename);
		for (const str of pragma) db.pragma(str);
		return db;
	}],
	['node-sqlite3', async (filename, pragma) => {
		const db = await (await import('sqlite')).open({ filename, driver: NodeSqlite.Database });
		for (const str of pragma) await db.run(`PRAGMA ${str}`);
		return db;
	}],
]);
