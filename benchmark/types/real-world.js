'use strict';
// Concurrently reads and writes single rows
require('../runner')(function (benchmark, dbs, ctx) {
	var factory = require('../factory');
	var SELECT = 'SELECT ' + ctx.columns.join(', ') + ' FROM ' + ctx.table + ' WHERE rowid=?';
	var INSERT = 'INSERT INTO ' + ctx.table + ' (' + ctx.columns.join(', ') + ') VALUES ' + factory.params(ctx.columns.length);
	var betterSqlite3 = dbs['better-sqlite3'];
	var nodeSqlite3 = dbs['node-sqlite3'];
	var data = factory(ctx.table, ctx.columns);
	var rowid = 0;
	benchmark.on('cycle', function () {rowid = 0;});
	
	var betterSqlite3Select = betterSqlite3.prepare(SELECT);
	var betterSqlite3Insert = betterSqlite3.prepare(INSERT);
	
	benchmark.add('better-sqlite3', function () {
		if (rowid % 2) {betterSqlite3Select.get(rowid % 1000 + 1);}
		else {betterSqlite3Insert.run(data);}
		rowid += 1;
	});
	benchmark.add('node-sqlite3', function (deferred) {
		if (rowid % 2) {
			nodeSqlite3.get(SELECT, rowid % 1000 + 1).then(function () {deferred.resolve();});
		} else {
			nodeSqlite3.run(INSERT, data).then(function () {deferred.resolve();});
		}
		rowid += 1;
	});
});
