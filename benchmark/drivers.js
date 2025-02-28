'use strict';

/*
	Every benchmark trial will be executed once for each SQLite driver listed
	below. Each driver has a function to open a new database connection on a
	given filename and a list of PRAGMA statements.
 */

module.exports = new Map([
	['better-sqlite3', async (filename, pragma) => {
		const db = require('../.')(filename);
		for (const str of pragma) db.pragma(str);
		return db;
	}],
	['node-sqlite3', async (filename, pragma) => {
		const driver = require('sqlite3').Database;
		const db = await (require('sqlite').open)({ filename, driver });
		for (const str of pragma) await db.run(`PRAGMA ${str}`);
		return db;
	}],
]);

const moduleExists = (m) => { try { return require.resolve(m); } catch (e) {} };
if (moduleExists('node:sqlite')) {
	module.exports.set('node:sqlite', async (filename, pragma) => {
		const db = new (require('node:sqlite').DatabaseSync)(filename, {open: true});
		for (const str of pragma) db.exec(`PRAGMA ${str}`);
		return db;
	});
}
