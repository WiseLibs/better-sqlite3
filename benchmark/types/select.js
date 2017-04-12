'use strict';
// Selects 1 row
require('../runner')(function (benchmark, dbs, ctx) {
	var SQL = 'SELECT ' + ctx.columns.join(', ') + ' FROM ' + ctx.table + ' WHERE rowid=?';
	var betterSqlite3 = dbs['better-sqlite3'];
	var nodeSqlite3 = dbs['node-sqlite3'];
	var rowid = 0;
	benchmark.on('cycle', function () {rowid = 0;});
	
	var stmt = betterSqlite3.prepare(SQL).pluck();
	
	benchmark.add('better-sqlite3', function () {
		betterSqlite3.prepare(SQL).get(rowid++ % 1000 + 1);
	});
	benchmark.add(' + optimized', function () {
		stmt.get(rowid++ % 1000 + 1);
	});
	benchmark.add('node-sqlite3', function (deferred) {
		nodeSqlite3.get(SQL, rowid++ % 1000 + 1).then(function () {deferred.resolve();});
	});
});
