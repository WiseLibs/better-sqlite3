'use strict';

exports = module.exports = function (ourDb, theirDb, count, small) {
	var SQL = small ? 'SELECT aaaa FROM entries'
	                : 'SELECT * FROM entries';
	
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
	var completed = 0;
	var failures = 0;
	if (pluck) {
		var t0 = process.hrtime();
		for (var i=0; i<count; ++i) {
			db.statement(SQL).pluck().each(dataCallback, callback);
		}
	} else {
		var t0 = process.hrtime();
		for (var i=0; i<count; ++i) {
			db.statement(SQL).each(dataCallback, callback);
		}
	}
	function dataCallback(data) {
		exports.data = data;
	}
	function callback(err) {
		if (err) {++failures;}
		if (++completed === count) {
			var td = process.hrtime(t0);
			report('better-sqlite3', count - failures, td);
			done();
		}
	}
}
function theirTest(db, count, SQL, pluck, done) {
	var completed = 0;
	var failures = 0;
	var partialCompleted = 0;
	var t0 = process.hrtime();
	for (var i=0; i<count; ++i) {
		db.each(SQL, dataCallback);
	}
	function dataCallback(err, data) {
		exports.data = data;
		if (err) {completed = count - 1; failures = Infinity; callback();}
		if (++partialCompleted === 1000) {
			partialCompleted = 0;
			callback();
		}
	}
	function callback() {
		if (++completed === count) {
			var td = process.hrtime(t0);
			report('node-sqlite3', count - failures, td);
			done();
		}
	}
}

function report(name, count, time) {
	var ms = time[0] * 1000 + Math.round(time[1] / 1000000);
	console.log(name + '\t' + count + ' SELECT iterations in ' + ms + 'ms');
}
