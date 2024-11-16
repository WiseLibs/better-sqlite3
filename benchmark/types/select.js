const readonly = true; // Reading rows individually (`.get()`)

const betterSqlite3 = (db, { table, columns, count }) => {
	const stmt = db.prepare(`SELECT ${columns.join(', ')} FROM ${table} WHERE rowid = ?`);
	let rowid = -1;
	return () => stmt.get(++rowid % count + 1);
};

const nodeSqlite3 = async (db, { table, columns, count }) => {
	const sql = `SELECT ${columns.join(', ')} FROM ${table} WHERE rowid = ?`;
	let rowid = -1;
	return () => db.get(sql, ++rowid % count + 1);
};

export default {
	readonly,
	['better-sqlite3']: betterSqlite3,
	['node-sqlite3']: nodeSqlite3,
};