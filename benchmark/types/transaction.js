'use strict';
// Inserts 100 rows
require('../runner')(function (benchmark, dbs, ctx) {
	var SQL = 'INSERT INTO ' + ctx.table + ' (' + ctx.columns.join(', ') + ') VALUES (' + namedParams(ctx.columns).join(', ') + ')';
	var betterSqlite3 = dbs['better-sqlite3'];
	var nodeSqlite3 = dbs['node-sqlite3'];
	var data = namedData(ctx.table, ctx.columns);
	var dataWithPrefix = namedData(ctx.table, ctx.columns, true);
	
	var transaction = betterSqlite3.transaction(new Array(100).fill(SQL));
	
	benchmark.add('better-sqlite3', function () {
		betterSqlite3.transaction(new Array(100).fill(SQL)).run(data);
	});
	benchmark.add(' + optimized', function () {
		transaction.run(data);
	});
	benchmark.add('node-sqlite3', function (deferred) {
		var count = 0;
		nodeSqlite3.run('BEGIN').then(function insert() {
			if (++count < 100) {
				return nodeSqlite3.run(SQL, dataWithPrefix).then(insert);
			}
			return nodeSqlite3.run(SQL, dataWithPrefix).then(function () {
				return nodeSqlite3.run('COMMIT').then(function () {deferred.resolve();});
			});
		});
	});
});

function namedParams(columns) {
	return columns.map(function (_, i) {return '@x' + i;});
}

function namedData(table, columns, withPrefix) {
	var data = require('../factory')(table, columns);
	var bindNames = namedParams(columns);
	var wrappedData = data.map(function (item, i) {
		var wrappedItem = {};
		wrappedItem[withPrefix ? bindNames[i] : bindNames[i].slice(1)] = item;
		return wrappedItem;
	});
	return Object.assign.apply(Object, [{}].concat(wrappedData));
}
