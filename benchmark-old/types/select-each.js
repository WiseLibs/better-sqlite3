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
		ourDb.close();
		theirDb.close(process.exit);
	}
	setTimeout(callback0, 100);
};

exports.data = undefined;

function ourTest(db, count, SQL, done) {
	if (!/^\s*(no|off|0|false)\s*$/i.test(process.env.USE_PLUCK)) {
		var t0 = process.hrtime();
		for (var i=0; i<count; ++i) {
			db.prepare(SQL).pluck().each(dataCallback);
		}
	} else {
		var t0 = process.hrtime();
		for (var i=0; i<count; ++i) {
			db.prepare(SQL).each(dataCallback);
		}
	}
	function dataCallback(data) {
		exports.data = data;
	}
	var td = process.hrtime(t0);
	report('better-sqlite3', count, td);
	done();
}
function theirTest(db, count, SQL, done) {
	var completed = 0;
	var partialCompleted = 0;
	var t0 = process.hrtime();
	for (var i=0; i<count; ++i) {
		db.each(SQL, dataCallback);
	}
	function dataCallback(err, data) {
		exports.data = data;
		if (err) {throw err;}
		if (++partialCompleted === 1000) {
			partialCompleted = 0;
			callback();
		}
	}
	function callback() {
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
