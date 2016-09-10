'use strict';
var createTable = require('../create-table');
var count = 2500;

createTable('CREATE TABLE people (name TEXT, age INTEGER)',
	__filename, testOurs, testTheirs);

function testOurs(db, done) {
	var len = count;
	var completed = 0;
	var failures = 0;
	var stmts = new Array(len);
	for (var i=0; i<len; ++i) {
		stmts[i] = db.statement('INSERT INTO people VALUES (?, @age)');
	}
	var t0 = process.hrtime();
	for (var i=0; i<len; ++i) {
		stmts[i].run('John Smith', {age: 25}, callback);
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
	var preparedCount = 0;
	var stmts = new Array(len);
	var t0;
	for (var i=0; i<len; ++i) {
		stmts[i] = db.prepare('INSERT INTO people VALUES (?, @age)', prepared);
	}
	function prepared() {
		if (++preparedCount === len) {
			t0 = process.hrtime();
			for (var i=0; i<len; ++i) {
				stmts[i].run('John Smith', {age: 25}, callback);
			}
		}
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
