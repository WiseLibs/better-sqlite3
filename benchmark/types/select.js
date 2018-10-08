'use strict';
// Reading rows individually (`.get()`)

exports['better-sqlite3'] = (db, { table, columns, count }) => {
	const stmt = db.prepare(`SELECT ${columns.join(', ')} FROM ${table} WHERE rowid = ?`);
	let rowid = 0;
	return () => void stmt.get(++rowid % count);
};

exports['node-sqlite3'] = async (db, { table, columns, count }) => {
	const sql = `SELECT ${columns.join(', ')} FROM ${table} WHERE rowid = ?`;
	let rowid = 0;
	return () => db.get(sql, ++rowid % count);
};
