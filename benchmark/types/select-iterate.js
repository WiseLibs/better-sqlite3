const readonly = true; // Iterating over 100 rows (`.iterate()`)

const betterSqlite3 = (db, { table, columns, count }) => {
	const stmt = db.prepare(`SELECT ${columns.join(', ')} FROM ${table} WHERE rowid >= ? LIMIT 100`);
	let rowid = -100;
	return () => {
		for (const row of stmt.iterate((rowid += 100) % count + 1)) {
		}
	};
};

const nodeSqlite3 = async (db, { table, columns, count }) => {
	const sql = `SELECT ${columns.join(', ')} FROM ${table} WHERE rowid = ?`;
	let rowid = -100;
	return () => {
		rowid += 100;
		let index = 0;
		return (function next() {
			if (index === 100) return;
			return db.get(sql, (rowid + index++) % count + 1).then(next);
		})();
	};
};

export default {
	readonly,
	['better-sqlite3']: betterSqlite3,
	['node-sqlite3']: nodeSqlite3,
};