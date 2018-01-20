'use strict';
// Selects 1 row
require('../runner')((benchmark, dbs, ctx) => {
	const SQL = `SELECT ${ctx.columns.join(', ')} FROM ${ctx.table} WHERE rowid=?`;
	const betterSqlite3 = dbs['better-sqlite3'];
	const nodeSqlite3 = dbs['node-sqlite3'];
	
	let rowid = 0;
	benchmark.on('cycle', () => { rowid = 0; });
	
	const betterSqlite3Select = betterSqlite3.prepare(SQL);
	
	benchmark.add('better-sqlite3', () => {
		betterSqlite3Select.get(rowid + 1);
		rowid = (rowid + 1) % 1000;
	});
	benchmark.add('node-sqlite3', (deferred) => {
		nodeSqlite3.get(SQL, rowid + 1).then(() => void deferred.resolve());
		rowid = (rowid + 1) % 1000;
	});
});
