'use strict';
// Inserts 1 row
require('../runner')((benchmark, dbs, ctx) => {
	const factory = require('../factory');
	const SQL = `INSERT INTO ${ctx.table} (${ctx.columns.join(', ')}) VALUES ${factory.params(ctx.columns.length)}`;
	const betterSqlite3 = dbs['better-sqlite3'];
	const nodeSqlite3 = dbs['node-sqlite3'];
	const data = factory(ctx.table, ctx.columns);
	
	const betterSqlite3Insert = betterSqlite3.prepare(SQL);
	
	benchmark.add('better-sqlite3', () => {
		betterSqlite3Insert.run(data);
	});
	benchmark.add('node-sqlite3', (deferred) => {
		nodeSqlite3.run(SQL, data).then(() => void deferred.resolve());
	});
});
