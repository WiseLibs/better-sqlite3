'use strict';

exports = module.exports = function (ourDb, theirDb, count, small) {
	var SQL = small ? 'SELECT aaaa FROM entries WHERE rowid=?'
	                : 'SELECT * FROM entries WHERE rowid=?';
	
	function callback0() {
		global.gc();
		ourTest(ourDb, count, SQL, small, callback1);
	}
	function callback1() {
		global.gc();
		theirTest(theirDb, count, SQL, small, callback2);
	}
	function callback2() {
		process.exit();
	}
	setTimeout(callback0, 100);
};

exports.data = undefined;

function ourTest(db, count, SQL, pluck, done) {
	if (pluck) {
		var t0 = process.hrtime();
		for (var i=0; i<count; ++i) {
			exports.data = db.statement(SQL).pluck().get(i + 1);
		}
	} else {
		var t0 = process.hrtime();
		for (var i=0; i<count; ++i) {
			exports.data = db.statement(SQL).get(i + 1);
		}
	}
	var td = process.hrtime(t0);
	report('better-sqlite3', count, td);
	done();
}
function theirTest(db, count, SQL, pluck, done) {
	var completed = 0;
	var failures = 0;
	var t0 = process.hrtime();
	for (var i=0; i<count; ++i) {
		db.get(SQL, i + 1, callback);
	}
	function callback(err, data) {
		exports.data = data;
		if (err) {++failures;}
		if (++completed === count) {
			var td = process.hrtime(t0);
			report('node-sqlite3', count - failures, td);
			done();
		}
	}
}

function report(name, count, time) {
	var ms = time[0] * 1000 + Math.round(time[1] / 1000000);
	console.log(name + '\t' + count + ' SELECTs in ' + ms + 'ms');
}
