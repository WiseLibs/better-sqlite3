'use strict';

exports = module.exports = function (ourDb, theirDb, count, data) {
	function callback0() {
		global.gc();
		ourTest(ourDb, count, data, callback1);
	}
	function callback1() {
		global.gc();
		theirTest(theirDb, count, data, callback2);
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

function ourTest(db, count, data, done) {
	var t0 = process.hrtime();
	for (var i=0; i<count; ++i) {
		exports.data = db.prepare('INSERT INTO entries VALUES (?)').run(data);
	}
	var td = process.hrtime(t0);
	report('better-sqlite3', count, td);
	done();
}
function theirTest(db, count, data, done) {
	var completed = 0;
	var t0 = process.hrtime();
	for (var i=0; i<count; ++i) {
		db.run('INSERT INTO entries VALUES (?)', data, callback);
	}
	function callback(err) {
		exports.data = this;
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
	console.log(name + '\t' + count + ' INSERTs in ' + ms + 'ms');
}
