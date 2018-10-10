'use strict';
exports.readonly = false; // Inserting rows individually (`.run()`)

exports['better-sqlite3'] = (db, { table, columns }) => {
	const stmt = db.prepare(`INSERT INTO ${table} (${columns.join(', ')}) VALUES (${columns.map(x => '@' + x).join(', ')})`);
	const row = db.prepare(`SELECT * FROM ${table} LIMIT 1`).get();
	return () => stmt.run(row);
};

exports['node-sqlite3'] = async (db, { table, columns }) => {
	const sql = `INSERT INTO ${table} (${columns.join(', ')}) VALUES (${columns.map(x => '@' + x).join(', ')})`;
	const row = Object.assign({}, ...Object.entries(await db.get(`SELECT * FROM ${table} LIMIT 1`))
		.filter(([k]) => columns.includes(k))
		.map(([k, v]) => ({ ['@' + k]: v })));
	return () => db.run(sql, row);
};
