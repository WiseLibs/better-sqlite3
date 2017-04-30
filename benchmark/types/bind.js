'use strict';
require('../runner')(function (benchmark, dbs, ctx) {
	var SQL = 'SELECT ' + ctx.columns.join(', ') + ' FROM ' + ctx.table;
	var db = dbs['better-sqlite3'];
	var rowid = 0;
	benchmark.on('cycle', function () {rowid = 0;});
	
	var named = db.prepare(SQL + ' WHERE rowid=@someParamName').pluck();
	var anonymous = db.prepare(SQL + ' WHERE rowid=?').pluck();
	
	benchmark.add('named', function () {
		named.get({someParamName: rowid++ % 1000 + 1});
	});
	benchmark.add('anonymous', function () {
		anonymous.get(rowid++ % 1000 + 1);
	});
});
