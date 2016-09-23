'use strict';
var expect = require('chai').expect;
var Database = require('../.');
var db;

before(function (done) {
	db = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.db');
	db.on('open', done);
});

describe('Transaction#run()', function () {
	it('should work with CREATE TABLE', function () {
		var trans = db.transaction(['CREATE TABLE entries (a TEXT, b INTEGER, c REAL, d BLOB)']);
		var info = trans.run();
		expect(info.changes).to.equal(0);
		expect(info.lastInsertROWID).to.equal(0);
	});
	it('should work with INSERT INTO', function () {
		var trans = db.transaction(["INSERT INTO entries VALUES ('foo', 25, 3.14, x'1133ddff')"]);
		var info = trans.run();
		expect(info.changes).to.equal(1);
		expect(info.lastInsertROWID).to.equal(1);
		
		info = trans.run();
		expect(info.changes).to.equal(1);
		expect(info.lastInsertROWID).to.equal(2);
		
		trans = db.transaction(["INSERT INTO entries VALUES ('foo', 25, 3.14, x'1133ddff')", "INSERT INTO entries VALUES ('foo', 25, 3.14, x'1133ddff')"]);
		info = trans.run();
		expect(info.changes).to.equal(2);
		expect(info.lastInsertROWID).to.equal(4);
	});
	it('should work with UPDATE', function () {
		var trans = db.transaction(["UPDATE entries SET a='bar' WHERE rowid=1"]);
		expect(trans.run().changes).to.equal(1);
	});
	it('should work with DELETE FROM', function () {
		var trans = db.transaction(["DELETE FROM entries WHERE a='foo'"]);
		expect(trans.run().changes).to.equal(3);
		
		trans = db.transaction(["INSERT INTO entries VALUES ('foo', 25, 3.14, x'1133ddff')"]);
		var info = trans.run();
		expect(info.changes).to.equal(1);
		expect(info.lastInsertROWID).to.equal(2);
	});
	it('should work with DROP TABLE', function () {
		var trans = db.transaction(["DROP TABLE entries"]);
		expect(trans.run().changes).to.equal(0);
	});
	it('should rollback and throw an exception for failed constraints', function () {
		db.transaction(['CREATE TABLE people (id INTEGER PRIMARY KEY, name TEXT)']).run();
		db.transaction(['CREATE TABLE ages (age INTEGER, person INTEGER NOT NULL REFERENCES people ON DELETE CASCADE ON UPDATE CASCADE)']).run();
		db.transaction([
			"INSERT INTO people VALUES (NULL, 'bob')",
			"INSERT INTO people VALUES (NULL, 'sarah')"
		]).run();
		db.transaction([
			"INSERT INTO ages VALUES (25, 1)",
			"INSERT INTO ages VALUES (30, 2)",
			"INSERT INTO ages VALUES (35, 2)"
		]).run();
		var trans = db.transaction([
			"INSERT INTO ages VALUES (40, 1)",
			"INSERT INTO ages VALUES (30, 3)"
		]);
		expect(function () {trans.run();}).to.throw(Error);
		trans = db.transaction([
			"INSERT INTO ages VALUES (40, 1)",
			"INSERT INTO ages VALUES (30, NULL)"
		]);
		expect(function () {trans.run();}).to.throw(Error);
		expect(db.prepare('SELECT * FROM ages WHERE age==35').get()).to.not.be.undefined;
		expect(db.prepare('SELECT * FROM ages WHERE age==40').get()).to.be.undefined;
		db.transaction([
			"INSERT INTO ages VALUES (40, 1)",
			"INSERT INTO ages VALUES (30, 2)"
		]).run();
		expect(db.prepare('SELECT * FROM ages WHERE age==40').get()).to.not.be.undefined;
	});
	it('should not count changes from indirect mechanisms', function () {
		var trans = db.transaction(["UPDATE people SET id=55 WHERE id=2"]);
		expect(trans.run().changes).to.equal(1);
	});
	it('should count accurate DELETE changes when a dropped table has side effects', function () {
		var trans = db.transaction(["DROP TABLE people"]);
		expect(trans.run().changes).to.equal(2);
	});
	it('should accept bind parameters', function () {
		db.transaction(["CREATE TABLE entries (a TEXT CHECK(typeof(a)=='text'), b INTEGER CHECK(typeof(b)=='integer' OR typeof(b)=='real'), c REAL CHECK(typeof(c)=='real' OR typeof(c)=='integer'), d BLOB CHECK(typeof(d)=='blob'))"]).run();
		
		db.transaction(['INSERT INTO entries VALUES (?, ?, ?, ?)', 'INSERT INTO entries VALUES (?, ?, ?, ?)'])
			.run('foo', 25, 25, Buffer.alloc(8).fill(0xdd), 'foo', 25, 25, Buffer.alloc(8).fill(0xdd));
			
		db.transaction(['INSERT INTO entries VALUES (?, ?, ?, ?)', 'INSERT INTO entries VALUES (?, ?, ?, ?)'])
			.run(['foo', 25, 25, Buffer.alloc(8).fill(0xdd), 'foo', 25, 25, Buffer.alloc(8).fill(0xdd)]);
			
		db.transaction(['INSERT INTO entries VALUES (?, ?, ?, ?)', 'INSERT INTO entries VALUES (?, ?, ?, ?)'])
			.run(['foo', 25], [25], Buffer.alloc(8).fill(0xdd), ['foo', 25, 25, Buffer.alloc(8).fill(0xdd)]);
			
		db.transaction(['INSERT INTO entries VALUES (@a, @b, @c, @d)', 'INSERT INTO entries VALUES (@a, @b, @c, @d)'])
			.run({a: 'foo', b: 25, c: 25, d: Buffer.alloc(8).fill(0xdd)});
			
		db.transaction(['INSERT INTO entries VALUES ($a, $b, $c, $d)', 'INSERT INTO entries VALUES ($a, $b, $c, $d)'])
			.run({a: 'foo', b: 25, c: 25, d: Buffer.alloc(8).fill(0xdd)});
			
		db.transaction(['INSERT INTO entries VALUES (:a, :b, :c, :d)', 'INSERT INTO entries VALUES (:a, :b, :c, :d)'])
			.run({a: 'foo', b: 25, c: 25, d: Buffer.alloc(8).fill(0xdd)});
			
		db.transaction(['INSERT INTO entries VALUES (?, @a, @a, ?)', 'INSERT INTO entries VALUES (?, @a, @a, ?)'])
			.run({a: 25}, ['foo'], [Buffer.alloc(8).fill(0xdd), 'foo'], Buffer.alloc(8).fill(0xdd));
		
		expect(function () {
			db.transaction(['INSERT INTO entries VALUES (?, @a, @a, ?)', 'INSERT INTO entries VALUES (?, @a, @a, ?)'])
				.run({a: 25}, ['foo'], Buffer.alloc(8).fill(0xdd), 'foo', Buffer.alloc(8).fill(0xdd), Buffer.alloc(8).fill(0xdd));
		}).to.throw(Error);
		
		expect(function () {
			db.transaction(['INSERT INTO entries VALUES (?, @a, @a, ?)', 'INSERT INTO entries VALUES (?, @a, @a, ?)'])
				.run({a: 25}, ['foo'], Buffer.alloc(8).fill(0xdd), 'foo');
		}).to.throw(Error);
		
		expect(function () {
			db.transaction(['INSERT INTO entries VALUES (?, @a, @a, ?)', 'INSERT INTO entries VALUES (?, @a, @a, ?)'])
				.run({a: 25, c: 25}, ['foo'], Buffer.alloc(8).fill(0xdd), ['foo'], Buffer.alloc(8).fill(0xdd));
		}).to.throw(Error);
		
		expect(function () {
			db.transaction(['INSERT INTO entries VALUES (?, @a, @a, ?)'])
				.run({}, ['foo'], Buffer.alloc(8).fill(0xdd), ['foo'], Buffer.alloc(8).fill(0xdd));
		}).to.throw(Error);
		
		expect(function () {
			db.transaction(['INSERT INTO entries VALUES (?, ?, ?, ?)', 'INSERT INTO entries VALUES (?, ?, ?, ?)'])
				.run(25, 'foo', 25, Buffer.alloc(8).fill(0xdd), 'foo', 25, 25, Buffer.alloc(8).fill(0xdd));
		}).to.throw(Error);
		
		expect(function () {
			db.transaction(['INSERT INTO entries VALUES (?, ?, ?, ?)', 'INSERT INTO entries VALUES (?, ?, ?, ?)'])
				.run('foo', 25, 25, Buffer.alloc(8).fill(0xdd), 'foo', 25, 25, Buffer.alloc(8).fill(0xdd), {foo: 'foo'});
		}).to.throw(Error);
		
		db.transaction(['INSERT INTO entries VALUES (?, ?, ?, ?)', 'INSERT INTO entries VALUES (?, ?, ?, ?)'])
			.run('foo', 25, 25, Buffer.alloc(8).fill(0xdd), 'foo', 25, 25, Buffer.alloc(8).fill(0xdd), {});
		
		expect(function () {
			db.transaction(['INSERT INTO entries VALUES (?, ?, ?, ?)'])
				.run('foo', 25, 25, {4: Buffer.alloc(8).fill(0xdd)});
		}).to.throw(Error);
		
		expect(function () {
			db.transaction(['INSERT INTO entries VALUES (?, ?, ?, ?)'])
				.run();
		}).to.throw(Error);
		
		expect(function () {
			db.transaction(['INSERT INTO entries VALUES (?, ?, ?, ?)'])
				.run({length: 4, 0: 'foo', 1: 25, 2: 25, 3: Buffer.alloc(8).fill(0xdd)});
		}).to.throw(Error);
		
		expect(function () {
			db.transaction(['INSERT INTO entries VALUES (?, ?, ?, ?)'])
				.run('foo', 25, new Number(25), Buffer.alloc(8).fill(0xdd));
		}).to.throw(Error);
		
		expect(function () {
			db.transaction(['INSERT INTO entries VALUES (?, ?, ?, ?)'])
				.run('foo', {low: 25, high: 25}, 25, Buffer.alloc(8).fill(0xdd));
		}).to.throw(Error);
		
		expect(function () {
			db.transaction(['INSERT INTO entries VALUES (?, ?, ?, ?)', "INSERT INTO entries VALUES ('foo', 25, 25, x'dddddddd')", 'INSERT INTO entries VALUES (?, ?, ?, ?)'])
				.run('foo', 25, 25, Buffer.alloc(8).fill(0xdd));
		}).to.throw(Error);
		
		function Foo() {
			this.a = 'foo';
			this.b = 25;
			this.c = 25;
			this.d = Buffer.alloc(8).fill(0xdd);
		}
		expect(function () {
			db.transaction(['INSERT INTO entries VALUES (@a, @b, @c, @d)', 'INSERT INTO entries VALUES (@a, @b, @c, @d)']).run(new Foo);
		}).to.throw(Error);
		
		var i = 0;
		var row;
		while (row = db.prepare('SELECT * FROM entries WHERE rowid=' + ++i).get()) {
			expect(row).to.deep.equal({a: 'foo', b: 25, c: 25, d: Buffer.alloc(8).fill(0xdd)});
		}
		expect(i).to.equal(17);
	});
});
