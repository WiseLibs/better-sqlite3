'use strict';
// Inserts 100 rows
require('../runner')((benchmark, dbs, ctx) => {
	const SQL = `INSERT INTO ${ctx.table} (${ctx.columns.join(', ')}) VALUES (${namedParams(ctx.columns).join(', ')})`;
	const betterSqlite3 = dbs['better-sqlite3'];
	const nodeSqlite3 = dbs['node-sqlite3'];
	const data = namedData(ctx.table, ctx.columns);
	const dataWithPrefix = namedData(ctx.table, ctx.columns, true);
	
	const betterSqlite3Insert = betterSqlite3.prepare(SQL);
	const betterSqlite3Transaction = betterSqlite3.transaction((obj) => {
		for (let i = 0; i < 100; ++i) {
			betterSqlite3Insert.run(obj);
		}
	});
	
	benchmark.add('better-sqlite3', () => {
		betterSqlite3Transaction(data);
	});
	benchmark.add('node-sqlite3', (deferred) => {
		let count = 0;
		nodeSqlite3.run('BEGIN').then(function insert() {
			if (++count < 100) {
				return nodeSqlite3.run(SQL, dataWithPrefix).then(insert);
			} else {
				return nodeSqlite3.run(SQL, dataWithPrefix).then(() => {
					return nodeSqlite3.run('COMMIT').then(() => void deferred.resolve());
				});
			}
		});
	});
});

function namedParams(columns) {
	return columns.map((_, i) => '@x' + i);
}

function namedData(table, columns, withPrefix) {
	const data = require('../factory')(table, columns);
	const bindNames = namedParams(columns);
	const wrappedData = data.map((item, i) => ({ [bindNames[i].slice(+!withPrefix)]: item }));
	return Object.assign({}, ...wrappedData);
}
