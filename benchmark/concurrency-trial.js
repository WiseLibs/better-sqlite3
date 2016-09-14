'use strict';

module.exports = function (ourDbs, theirDbs, count, countPerCycle) {
	if (countPerCycle > 1000) {
		throw new Error('countPerCycle must be <= 1000');
	}
	var params = ['John Smith', 123456, null];
	if (count % countPerCycle !== 0) {
		count = count + countPerCycle - count % countPerCycle;
	}
	function callback0() {
		global.gc();
		ourTest(ourDbs, count, countPerCycle, params, callback1);
	}
	function callback1() {
		global.gc();
		theirTest(theirDbs, count, countPerCycle, params, callback2);
	}
	function callback2() {
		var closedCount = 0;
		ourDbs[0].on('close', closed).close();
		ourDbs[1].on('close', closed).close();
		theirDbs[0].close(closed);
		theirDbs[1].close(closed);
		function closed() {
			++closedCount === 4 && process.exit();
		}
	}
	setTimeout(callback0, 100);
};

exports.data = undefined;

function ourTest(dbs, count, countPerCycle, params, done) {
	var requested = 0;
	var t0 = process.hrtime();
	(function request() {
		for (var i=0; i<countPerCycle; ++i) {
			if (i % 2) {
				exports.data = dbs[0].prepare('INSERT INTO entries VALUES (?, ?, ?)').run(params);
			} else {
				exports.data = dbs[1].prepare('SELECT name FROM entries WHERE rowid=?').pluck().get(i + 1);
			}
		}
		if ((requested += countPerCycle) < count) {
			setImmediate(request);
		} else {
			var td = process.hrtime(t0);
			report('better-sqlite3', count, td);
			done();
		}
	}());
}
function theirTest(dbs, count, countPerCycle, params, done) {
	var requested = 0;
	var completed = 0;
	var failures = 0;
	var t0 = process.hrtime();
	(function request() {
		for (var i=0; i<countPerCycle; ++i) {
			if (i % 2) {
				dbs[0].run('INSERT INTO entries VALUES (?, ?, ?)', params, callback);
			} else {
				dbs[1].get('SELECT name FROM entries WHERE rowid=?', i + 1, callback);
			}
		}
		if ((requested += countPerCycle) < count) {
			setImmediate(request);
		}
	}());
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
	console.log(name + '\t' + count + ' overlapping INSERT or SELECTs in ' + ms + 'ms');
}
