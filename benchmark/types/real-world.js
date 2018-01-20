'use strict';
// Concurrently reads and writes single rows
require('../runner')((benchmark, dbs, ctx) => {
	const factory = require('../factory');
	const SELECT = `SELECT ${ctx.columns.join(', ')} FROM ${ctx.table} WHERE rowid=?`;
	const INSERT = `INSERT INTO ${ctx.table} (${ctx.columns.join(', ')}) VALUES ${factory.params(ctx.columns.length)}`;
	const betterSqlite3 = dbs['better-sqlite3'];
	const nodeSqlite3 = dbs['node-sqlite3'];
	const data = factory(ctx.table, ctx.columns);
	let rowid = 0;
	
	const betterSqlite3Select = betterSqlite3.prepare(SELECT);
	const betterSqlite3Insert = betterSqlite3.prepare(INSERT);
	
	benchmark.add('better-sqlite3', () => {
		for (rowid = 0; rowid < 1000; ++rowid) {
			if (rowid % 2) betterSqlite3Select.get(rowid + 1);
			else betterSqlite3Insert.run(data);
		}
	});
	benchmark.add('node-sqlite3', (deferred) => {
		let count = 0;
		const done = () => void (++count === 1000 && deferred.resolve());
		for (rowid = 0; rowid < 1000; ++rowid) {
			if (rowid % 2) nodeSqlite3.get(SELECT, rowid + 1).then(() => done());
			else nodeSqlite3.run(INSERT, data).then(() => done());
		}
	});
}, 1000);
