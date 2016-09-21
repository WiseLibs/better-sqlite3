'use strict';

exports = module.exports = function (ourDb, theirDb, count, columnName) {
	var SQL = 'SELECT ' + columnName + ' FROM entries WHERE rowid=?';
	
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
	var t0 = process.hrtime();
	for (var i=0; i<count; ++i) {
		exports.data = db.prepare(SQL).get(i % 1000 + 1);
	}
	var td = process.hrtime(t0);
	report('better-sqlite3', count, td);
	done();
}
function theirTest(db, count, SQL, done) {
	var completed = 0;
	var t0 = process.hrtime();
	for (var i=0; i<count; ++i) {
		db.get(SQL, i % 1000 + 1, callback);
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
	console.log(name + '\t' + count + ' SELECTs in ' + ms + 'ms');
}
