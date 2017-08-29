'use strict';
// Selects 100 rows
require('../runner')(function (benchmark, dbs, ctx) {
	var SQL = 'SELECT ' + ctx.columns.join(', ') + ' FROM ' + ctx.table + ' WHERE rowid>=? LIMIT 100';
	var oneByOneSQL = SQL.replace(/\bLIMIT\s+\d+/i, 'LIMIT 1');
	var betterSqlite3 = dbs['better-sqlite3'];
	var nodeSqlite3 = dbs['node-sqlite3'];
	var rowid = 99;
	benchmark.on('cycle', function () {rowid = 99;});
	
	var betterSqlite3Select = betterSqlite3.prepare(SQL);
	
	benchmark.add('better-sqlite3', function () {
		for (var obj of betterSqlite3Select.iterate(rowid % 1000 - 98)) {}
		rowid += 100;
	});
	benchmark.add('node-sqlite3', function (deferred) {
		var goal = rowid + 100;
		function next() {
			if (++rowid === goal) {
				deferred.resolve();
			} else {
				nodeSqlite3.get(oneByOneSQL, rowid % 1000 - 98).then(next);
			}
		}
		nodeSqlite3.get(oneByOneSQL, rowid % 1000 - 98).then(next);
	});
});
