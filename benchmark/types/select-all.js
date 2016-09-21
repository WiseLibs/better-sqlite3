'use strict';
var RPS;

exports = module.exports = function (ourDb, theirDb, count, rowsPerSelect, columnName) {
	if (rowsPerSelect > 1000) {
		throw new Error('rowsPerSelect cannot be greater than 1000');
	}
	if (rowsPerSelect === 1000) {
		var SQL = 'SELECT ' + columnName + ' FROM entries';
	} else {
		var SQL = 'SELECT ' + columnName + ' FROM entries WHERE rowid <= ' + rowsPerSelect;
	}
	RPS = rowsPerSelect;
	
	function callback0() {
		global.gc();
		ourTest(ourDb, count, SQL, callback1);
	}
	function callback1() {
		global.gc();
		theirTest(theirDb, count, SQL, callback2);
	}
	function callback2() {
		var closedCount = 0;
		ourDb.on('close', closed).close();
		theirDb.close(closed);
		function closed() {
			++closedCount === 2 && process.exit();
		}
	}
	setTimeout(callback0, 100);
};

exports.data = undefined;

function ourTest(db, count, SQL, done) {
	if (!/^\s*(no|off|0|false)\s*$/i.test(process.env.USE_PLUCK)) {
		var t0 = process.hrtime();
		for (var i=0; i<count; ++i) {
			exports.data = db.prepare(SQL).pluck().all();
		}
	} else {
		var t0 = process.hrtime();
		for (var i=0; i<count; ++i) {
			exports.data = db.prepare(SQL).all();
		}
	}
	var td = process.hrtime(t0);
	report('better-sqlite3', count, td);
	done();
}
function theirTest(db, count, SQL, done) {
	var completed = 0;
	var t0 = process.hrtime();
	for (var i=0; i<count; ++i) {
		db.all(SQL, callback);
	}
	function callback(err, data) {
		exports.data = data;
		if (err) {throw err;}
		if (++completed === count) {
			var td = process.hrtime(t0);
			report('node-sqlite3', count, td);
			done();
		}
	}
}

function report(name, count, time) {
	var ms = time[0] * 1000 + Math.round(time[1] / 1000000);
	console.log(name + '\t' + count + ' SELECTs (' + RPS + ' rows each) in ' + ms + 'ms');
}
