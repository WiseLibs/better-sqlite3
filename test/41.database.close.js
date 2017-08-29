var expect = require('chai').expect;
var fs = require('fs');
var Database = require('../.');
var util = (function () {
	var path = require('path');
	var dbId = 0;
	var obj;
	return obj = {
		current: function () {
			return 'temp/' + path.basename(__filename).split('.')[0] + '.' + dbId + '.db';
		},
		next: function () {++dbId; return obj.current();}
	};
}());

describe('Database#close()', function () {
	it('should prevent statements and transactions from operating', function () {
		var db = new Database(util.next());
		db.prepare('CREATE TABLE people (name TEXT)').run();
		var stmt1 = db.prepare('SELECT * FROM people');
		var stmt2 = db.prepare("INSERT INTO people VALUES ('foobar')");
		var trans = db.transaction(["INSERT INTO people VALUES ('foobar')"]);
		
		db.prepare('SELECT * FROM people').bind();
		db.prepare("INSERT INTO people VALUES ('foobar')").bind();
		db.transaction(["INSERT INTO people VALUES ('foobar')"]).bind();
		db.prepare('SELECT * FROM people').get();
		db.prepare('SELECT * FROM people').all();
		db.prepare('SELECT * FROM people').iterate().return();
		db.prepare("INSERT INTO people VALUES ('foobar')").run();
		db.transaction(["INSERT INTO people VALUES ('foobar')"]).run();
		
		db.close();
		
		expect(function () {stmt1.bind();}).to.throw(TypeError);
		expect(function () {stmt2.bind();}).to.throw(TypeError);
		expect(function () {trans.bind();}).to.throw(TypeError);
		expect(function () {stmt1.get();}).to.throw(TypeError);
		expect(function () {stmt1.all();}).to.throw(TypeError);
		expect(function () {stmt1.iterate();}).to.throw(TypeError);
		expect(function () {stmt2.run();}).to.throw(TypeError);
		expect(function () {trans.run();}).to.throw(TypeError);
	});
	it('should delete the database\'s associated temporary files', function () {
		var db = new Database(util.next());
		fs.accessSync(util.current());
		db.pragma('journal_mode = WAL');
		db.prepare('CREATE TABLE people (name TEXT)').run();
		db.prepare('INSERT INTO people VALUES (?)').run('foobar');
		fs.accessSync(util.current() + '-wal');
		
		db.close();
		
		fs.accessSync(util.current());
		expect(function () {
			fs.accessSync(util.current() + '-wal');
		}).to.throw();
	});
});
