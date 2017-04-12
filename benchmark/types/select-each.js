'use strict';
// Selects 100 rows
require('../runner')(function (benchmark, dbs, ctx) {
	var SQL = 'SELECT ' + ctx.columns.join(', ') + ' FROM ' + ctx.table + ' WHERE rowid>=? LIMIT 100';
	var betterSqlite3 = dbs['better-sqlite3'];
	var nodeSqlite3 = dbs['node-sqlite3'];
	var rowid = 99;
	benchmark.on('cycle', function () {rowid = 0;});
	
	var betterSqlite3Select = betterSqlite3.prepare(SQL);
	
	benchmark.add('better-sqlite3', function () {
		betterSqlite3Select.each(rowid % 1000 - 98, function () {});
		rowid += 100;
	});
	benchmark.add('node-sqlite3', function (deferred) {
		nodeSqlite3.each(SQL, rowid % 1000 - 98, function () {}).then(function () {deferred.resolve();});
		rowid += 100;
	});
});
