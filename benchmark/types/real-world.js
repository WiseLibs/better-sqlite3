'use strict';

exports = module.exports = function (ourDb, theirDb, count, countPerCycle) {
	if (countPerCycle > 1000) {
		throw new Error('countPerCycle must be <= 1000');
	}
	if (count % countPerCycle !== 0) {
		count = count + countPerCycle - count % countPerCycle;
	}
	
	var params = [
		'John Peter Smith',
		12345,
		0.12345,
		Buffer.alloc(16).fill(0xdd),
		null
	];
	
	function callback0() {
		global.gc();
		ourTest(ourDb, count, countPerCycle, params, callback1);
	}
	function callback1() {
		global.gc();
		theirTest(theirDb, count, countPerCycle, params, callback2);
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

function ourTest(db, count, countPerCycle, params, done) {
	var requested = 0;
	var t0 = process.hrtime();
	(function request() {
		for (var i=0; i<countPerCycle; ++i) {
			if (i % 2) {
				exports.data = db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?, ?)').run(params);
			} else {
				exports.data = db.prepare('SELECT * FROM entries WHERE rowid=?').get(i % 1000 + 1);
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
function theirTest(db, count, countPerCycle, params, done) {
	var requested = 0;
	var completed = 0;
	var t0 = process.hrtime();
	(function request() {
		for (var i=0; i<countPerCycle; ++i) {
			if (i % 2) {
				db.run('INSERT INTO entries VALUES (?, ?, ?, ?, ?)', params, callback);
			} else {
				db.get('SELECT * FROM entries WHERE rowid=?', i % 1000 + 1, callback);
			}
		}
		if ((requested += countPerCycle) < count) {
			setImmediate(request);
		}
	}());
	function callback(err, data) {
		exports.data = data || this;
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
	console.log(name + '\t' + count + ' INSERT or SELECTs in ' + ms + 'ms');
}
