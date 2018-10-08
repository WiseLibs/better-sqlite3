'use strict';
// Reading rows individually (`.get()`)

exports['better-sqlite3'] = (db, { table, columns, count }) => {
	const stmt = db.prepare(`SELECT ${columns.join(', ')} FROM ${table} WHERE rowid = ?`);
	let rowid = -1;
	return () => stmt.get(++rowid % count + 1);
};

exports['node-sqlite3'] = async (db, { table, columns, count }) => {
	const sql = `SELECT ${columns.join(', ')} FROM ${table} WHERE rowid = ?`;
	let rowid = -1;
	return () => db.get(sql, ++rowid % count + 1);
};
