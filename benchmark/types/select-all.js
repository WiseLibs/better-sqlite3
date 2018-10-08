'use strict';
// Reading 100 rows into an array (`.all()`)

exports['better-sqlite3'] = (db, { table, columns, count }) => {
	const stmt = db.prepare(`SELECT ${columns.join(', ')} FROM ${table} WHERE rowid >= ? LIMIT 100`);
	let rowid = -100;
	return () => void stmt.all((rowid += 100) % count + 1);
};

exports['node-sqlite3'] = async (db, { table, columns, count }) => {
	const sql = `SELECT ${columns.join(', ')} FROM ${table} WHERE rowid >= ? LIMIT 100`;
	let rowid = -100;
	return () => db.all(sql, (rowid += 100) % count + 1);
};
