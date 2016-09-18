var expect = require('chai').expect;
var fs = require('fs');
var Database = require('../.');
var db;

before(function (done) {
	db = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.db');
	db.on('open', done);
});

describe('Database#close()', function () {
	it('should prevent statements and transactions from operating', function (done) {
		db.prepare('CREATE TABLE people (name TEXT)').run();
		var stmt1 = db.prepare('SELECT * FROM people');
		var stmt2 = db.prepare("INSERT INTO people VALUES ('foobar')");
		var trans = db.transaction(["INSERT INTO people VALUES ('foobar')"]);
		
		db.prepare('SELECT * FROM people').bind();
		db.prepare("INSERT INTO people VALUES ('foobar')").bind();
		db.transaction(["INSERT INTO people VALUES ('foobar')"]).bind();
		db.prepare('SELECT * FROM people').get();
		db.prepare('SELECT * FROM people').all();
		db.prepare('SELECT * FROM people').each(function () {});
		db.prepare("INSERT INTO people VALUES ('foobar')").run();
		db.transaction(["INSERT INTO people VALUES ('foobar')"]).run();
		
		db.close();
		
		expect(function () {stmt1.bind();}).to.throw(Error);
		expect(function () {stmt2.bind();}).to.throw(Error);
		expect(function () {trans.bind();}).to.throw(Error);
		expect(function () {stmt1.get();}).to.throw(Error);
		expect(function () {stmt1.all();}).to.throw(Error);
		expect(function () {stmt1.each(function () {});}).to.throw(Error);
		expect(function () {stmt2.run();}).to.throw(Error);
		expect(function () {trans.run();}).to.throw(Error);
		
		db.on('close', function () {
			expect(function () {stmt1.bind();}).to.throw(Error);
			expect(function () {stmt2.bind();}).to.throw(Error);
			expect(function () {trans.bind();}).to.throw(Error);
			expect(function () {stmt1.get();}).to.throw(Error);
			expect(function () {stmt1.all();}).to.throw(Error);
			expect(function () {stmt1.each(function () {});}).to.throw(Error);
			expect(function () {stmt2.run();}).to.throw(Error);
			expect(function () {trans.run();}).to.throw(Error);
			done();
		});
	});
});
