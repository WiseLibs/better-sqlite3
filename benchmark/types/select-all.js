const readonly = true; // Reading 100 rows into an array (`.all()`)

const betterSqlite3 = (db, { table, columns, count }) => {
	const stmt = db.prepare(`SELECT ${columns.join(', ')} FROM ${table} WHERE rowid >= ? LIMIT 100`);
	let rowid = -100;
	return () => stmt.all((rowid += 100) % count + 1);
};

const nodeSqlite3 = async (db, { table, columns, count }) => {
	const sql = `SELECT ${columns.join(', ')} FROM ${table} WHERE rowid >= ? LIMIT 100`;
	let rowid = -100;
	return () => db.all(sql, (rowid += 100) % count + 1);
};

export default {
	readonly,
	['better-sqlite3']: betterSqlite3,
	['node-sqlite3']: nodeSqlite3,
};