'use strict';

exports = module.exports = function (ourDb, theirDb, count) {	
	function callback0() {
		global.gc();
		ourTest(ourDb, count, callback1);
	}
	function callback1() {
		global.gc();
		theirTest(theirDb, count, callback2);
	}
	function callback2() {
		ourDb.close();
		theirDb.close(process.exit);
	}
	setTimeout(callback0, 100);
};

exports.data = undefined;

function ourTest(db, count, done) {
	var t0 = process.hrtime();
	for (var i=0; i<count; ++i) {
		exports.data = db.prepare('SELECT * FROM entries');
	}
	var td = process.hrtime(t0);
	report('better-sqlite3', count, td);
	done();
}
function theirTest(db, count, done) {
	var completed = 0;
	var t0 = process.hrtime();
	for (var i=0; i<count; ++i) {
		db.prepare('SELECT * FROM entries', callback);
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
	console.log(name + '\t' + count + ' prepared statements in ' + ms + 'ms');
}
