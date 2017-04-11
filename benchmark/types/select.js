'use strict';
require('../runner')(function (benchmark, dbs, ctx) {
	var SQL = 'SELECT ' + ctx.columns.join(', ') + ' FROM ' + ctx.table + ' WHERE rowid=?';
	var betterSqlite3 = dbs['better-sqlite3'];
	var nodeSqlite3 = dbs['node-sqlite3'];
	
	benchmark.add('better-sqlite3', function (deferred) {
		betterSqlite3.prepare(SQL).get(1);
		deferred.resolve();
	});
	benchmark.add('node-sqlite3', function (deferred) {
		nodeSqlite3.get(SQL, 1).then(function () {deferred.resolve();});
	});
});
