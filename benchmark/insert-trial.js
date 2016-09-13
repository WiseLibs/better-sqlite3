'use strict';

module.exports = function (ourDb, theirDb, count, params) {
	function callback0() {
		global.gc();
		ourTest(ourDb, count, params, callback1);
	}
	function callback1() {
		global.gc();
		theirTest(theirDb, count, params, callback2);
	}
	function callback2() {
		process.exit();
	}
	setTimeout(callback0, 100);
};

function ourTest(db, count, params, done) {
	var t0 = process.hrtime();
	for (var i=0; i<count; ++i) {
		db.prepare('INSERT INTO entries VALUES (?, ?, ?)').run(params);
	}
	var td = process.hrtime(t0);
	report('better-sqlite3', count, td);
	done();
}
function theirTest(db, count, params, done) {
	var completed = 0;
	var failures = 0;
	var t0 = process.hrtime();
	for (var i=0; i<count; ++i) {
		db.run('INSERT INTO entries VALUES (?, ?, ?)', params, callback);
	}
	function callback(err) {
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
	console.log(name + '\t' + count + ' INSERTs in ' + ms + 'ms');
}
