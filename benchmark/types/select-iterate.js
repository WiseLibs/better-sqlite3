'use strict';
// Iterating over 100 rows (`.iterate()`)

exports['better-sqlite3'] = (db, { table, columns, count }) => {
	const stmt = db.prepare(`SELECT ${columns.join(', ')} FROM ${table} WHERE rowid >= ? LIMIT 100`);
	let rowid = -99;
	return () => {
		for (const row of stmt.iterate((rowid += 100) % count)) {}
	};
};

exports['node-sqlite3'] = async (db, { table, columns, count }) => {
	const sql = `SELECT ${columns.join(', ')} FROM ${table} WHERE rowid = ?`;
	let rowid = -99;
	return () => {
		rowid += 100;
		let index = 0;
		return (function next() {
			if (index === 100) return;
			return db.get(sql, (rowid + index++) % count).then(next);
		})();
	};
};
