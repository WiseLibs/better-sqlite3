'use strict';
// Inserting 100 rows in a single transaction

exports['better-sqlite3'] = (db, { table, columns }) => {
	const stmt = db.prepare(`INSERT INTO ${table} (${columns.join(', ')}) VALUES (${columns.map(x => '@' + x).join(', ')})`);
	const row = db.prepare(`SELECT * FROM ${table} LIMIT 1`).get();
	const trx = db.transaction((row) => {
		for (let i = 0; i < 100; ++i) stmt.run(row);
	});
	return () => trx(row);
};

exports['node-sqlite3'] = async (db, { table, columns, driver, filename, pragma }) => {
	const sql = `INSERT INTO ${table} (${columns.join(', ')}) VALUES (${columns.map(x => '@' + x).join(', ')})`;
	const row = Object.assign({}, ...Object.entries(await db.get(`SELECT * FROM ${table} LIMIT 1`))
		.filter(([k]) => columns.includes(k))
		.map(([k, v]) => ({ ['@' + k]: v })));
	const open = require('../drivers').get(driver);
	/*
		The only way to create an isolated transaction with node-sqlite3 in a
		random-access environment (i.e., a web server) is to open a new database
		connection for each transaction.
		(http://github.com/mapbox/node-sqlite3/issues/304#issuecomment-45242331)
	 */
	return () => open(filename, pragma).then(async (db) => {
		try {
			await db.run('BEGIN');
			try {
				for (let i = 0; i < 100; ++i) await db.run(sql, row);
				await db.run('COMMIT');
			} catch (err) {
				try { await db.run('ROLLBACK'); }
				catch (_) { /* this is necessary because there's no db.inTransaction property */ }
				throw err;
			}
		} finally {
			await db.close();
		}
	});
};
