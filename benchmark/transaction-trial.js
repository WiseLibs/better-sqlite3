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
		var closedCount = 0;
		ourDb.on('close', closed).close();
		theirDb.close(closed);
		function closed() {
			++closedCount === 2 && process.exit();
		}
	}
	setTimeout(callback0, 100);
};

function ourTest(db, count, params, done) {
	params = {a: params[0], b: params[1], c: params[2]};
	var statements = new Array(count).fill('INSERT INTO entries VALUES (@a, @b, @c);');
	var t0 = process.hrtime();
	db.transaction(statements).run(params);
	var td = process.hrtime(t0);
	report('better-sqlite3', count, td);
	done();
}
function theirTest(db, count, params, done) {
	function run() {
		db.run('BEGIN TRANSACTION;');
		for (var i=0; i<count; ++i) {
			db.run('INSERT INTO entries VALUES (?, ?, ?);', params);
		}
		db.run('COMMIT TRANSACTION;', callback);
	}
	var t0 = process.hrtime();
	db.serialize(run);
	function callback(err) {
		var td = process.hrtime(t0);
		report('node-sqlite3', err ? 0 : count, td);
		done();
	}
}

function report(name, count, time) {
	var ms = time[0] * 1000 + Math.round(time[1] / 1000000);
	console.log(name + '\t' + count + ' INSERTs (single TRANSACTION) in ' + ms + 'ms');
}
