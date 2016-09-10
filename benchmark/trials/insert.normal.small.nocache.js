'use strict';
var createTable = require('../create-table');
var count = 2500;

createTable('CREATE TABLE people (name TEXT, age INTEGER)',
	__filename, testOurs, testTheirs);

function testOurs(db, done) {
	var len = count;
	var completed = 0;
	var failures = 0;
	var t0 = process.hrtime();
	for (var i=0; i<len; ++i) {
		db.statement('INSERT INTO people VALUES (?, @age)').run('John Smith', {age: 25}, callback);
	}
	function callback(err) {
		if (err) {++failures;}
		if (++completed === len) {
			var td = process.hrtime(t0);
			report('better-sqlite3', failures, td);
			done();
		}
	}
}

function testTheirs(db, done) {
	var len = count;
	var completed = 0;
	var failures = 0;
	var t0 = process.hrtime();
	for (var i=0; i<len; ++i) {
		db.run('INSERT INTO people VALUES (?, @age)', 'John Smith', {age: 25}, callback);
	}
	function callback(err) {
		if (err) {++failures;}
		if (++completed === len) {
			var td = process.hrtime(t0);
			report('node-sqlite3', failures, td);
			done();
		}
	}
}

function report(name, failures, time) {
	var ms = time[0] * 1000 + Math.round(time[1] / 1000000);
	console.log(name + '\t' + (count - failures) + ' INSERTs in ' + ms + 'ms');
}
