'use strict';
// Selects 100 rows
require('../runner')((benchmark, dbs, ctx) => {
	const SQL = `SELECT ${ctx.columns.join(', ')} FROM ${ctx.table} WHERE rowid>=? LIMIT 100`;
	const oneByOneSQL = SQL.replace(/\bLIMIT\s+\d+/i, 'LIMIT 1');
	const betterSqlite3 = dbs['better-sqlite3'];
	const nodeSqlite3 = dbs['node-sqlite3'];
	
	let rowid = 99;
	benchmark.on('cycle', () => { rowid = 99; });
	
	const betterSqlite3Select = betterSqlite3.prepare(SQL);
	
	benchmark.add('better-sqlite3',  () => {
		for (const obj of betterSqlite3Select.iterate(rowid - 98)) {}
		rowid = (rowid + 100) % 1000;
	});
	benchmark.add('node-sqlite3', (deferred) => {
		let count = 0;
		function next() {
			if (++count === 100) {
				rowid = (rowid + 100) % 1000;
				deferred.resolve();
			} else {
				nodeSqlite3.get(oneByOneSQL, rowid + count - 98).then(next);
			}
		}
		nodeSqlite3.get(oneByOneSQL, rowid + count - 98).then(next);
	});
});
