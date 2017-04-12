'use strict';
// Inserts 1 row
require('../runner')(function (benchmark, dbs, ctx) {
	var factory = require('../factory');
	var SQL = 'INSERT INTO ' + ctx.table + ' (' + ctx.columns.join(', ') + ') VALUES ' + factory.params(ctx.columns.length);
	var betterSqlite3 = dbs['better-sqlite3'];
	var nodeSqlite3 = dbs['node-sqlite3'];
	var data = factory(ctx.table, ctx.columns);
	
	var stmt = betterSqlite3.prepare(SQL);
	
	benchmark.add('better-sqlite3', function () {
		betterSqlite3.prepare(SQL).run(data);
	});
	benchmark.add(' + optimized', function () {
		stmt.run(data);
	});
	benchmark.add('node-sqlite3', function (deferred) {
		nodeSqlite3.run(SQL, data).then(function () {deferred.resolve();});
	});
});
