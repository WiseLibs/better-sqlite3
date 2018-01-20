'use strict';
// Selects 100 rows
require('../runner')((benchmark, dbs, ctx) => {
	const SQL = `SELECT ${ctx.columns.join(', ')} FROM ${ctx.table} WHERE rowid>=? LIMIT 100`;
	const betterSqlite3 = dbs['better-sqlite3'];
	const nodeSqlite3 = dbs['node-sqlite3'];
	
	let rowid = 99;
	benchmark.on('cycle', () => { rowid = 99; });
	
	const betterSqlite3Select = betterSqlite3.prepare(SQL);
	
	benchmark.add('better-sqlite3', () => {
		betterSqlite3Select.all(rowid - 98);
		rowid = (rowid + 100) % 1000;
	});
	benchmark.add('node-sqlite3', (deferred) => {
		nodeSqlite3.all(SQL, rowid - 98).then(() => void deferred.resolve());
		rowid = (rowid + 100) % 1000;
	});
});
