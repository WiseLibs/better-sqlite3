'use strict';
var expect = require('chai').expect;
var Database = require('../.');
var db;

before(function () {
	db = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.db');
});

describe('Statement#run()', function () {
	it('should throw an exception when used on a statement that returns data', function () {
		var stmt = db.prepare('SELECT 555');
		expect(function () {stmt.run();}).to.throw(TypeError);
	});
	it('should work with CREATE TABLE', function () {
		var stmt = db.prepare('CREATE TABLE entries (a TEXT, b INTEGER, c REAL, d BLOB)');
		var info = stmt.run();
		expect(info.changes).to.equal(0);
		expect(info.lastInsertROWID).to.equal(0);
	});
	it('should work with CREATE TABLE IF NOT EXISTS', function () {
		var stmt = db.prepare('CREATE TABLE IF NOT EXISTS entries (a TEXT, b INTEGER, c REAL, d BLOB)');
		var info = stmt.run();
		expect(info.changes).to.equal(0);
		expect(info.lastInsertROWID).to.equal(0);
	});
	it('should work with INSERT INTO', function () {
		var stmt = db.prepare("INSERT INTO entries VALUES ('foo', 25, 3.14, x'1133ddff')");
		var info = stmt.run();
		expect(info.changes).to.equal(1);
		expect(info.lastInsertROWID).to.equal(1);
		
		info = stmt.run();
		expect(info.changes).to.equal(1);
		expect(info.lastInsertROWID).to.equal(2);
		
		stmt = db.prepare("INSERT INTO entries VALUES ('foo', 25, 3.14, x'1133ddff'), ('foo', 25, 3.14, x'1133ddff')");
		info = stmt.run();
		expect(info.changes).to.equal(2);
		expect(info.lastInsertROWID).to.equal(4);
	});
	it('should work with UPDATE', function () {
		var stmt = db.prepare("UPDATE entries SET a='bar' WHERE rowid=1");
		expect(stmt.run().changes).to.equal(1);
	});
	it('should work with DELETE FROM', function () {
		var stmt = db.prepare("DELETE FROM entries WHERE a='foo'");
		expect(stmt.run().changes).to.equal(3);
		
		stmt = db.prepare("INSERT INTO entries VALUES ('foo', 25, 3.14, x'1133ddff')");
		var info = stmt.run();
		expect(info.changes).to.equal(1);
		expect(info.lastInsertROWID).to.equal(2);
	});
	it('should work with BEGIN and COMMIT', function () {
		expect(db.prepare("BEGIN TRANSACTION").run().changes).to.equal(0);
		var info = db.prepare("INSERT INTO entries VALUES ('foo', 25, 3.14, x'1133ddff')").run();
		expect(info.changes).to.equal(1);
		expect(info.lastInsertROWID).to.equal(3);
		expect(db.prepare("COMMIT TRANSACTION").run().changes).to.equal(0);
	});
	it('should work with DROP TABLE', function () {
		var stmt = db.prepare("DROP TABLE entries");
		expect(stmt.run().changes).to.equal(0);
	});
	it('should throw an exception for failed constraints', function () {
		db.prepare('CREATE TABLE people (id INTEGER PRIMARY KEY, name TEXT)').run();
		db.prepare('CREATE TABLE ages (age INTEGER, person INTEGER NOT NULL REFERENCES people ON DELETE CASCADE ON UPDATE CASCADE)').run();
		db.prepare("INSERT INTO people VALUES (NULL, 'bob')").run();
		db.prepare("INSERT INTO people VALUES (NULL, 'sarah')").run();
		db.prepare("INSERT INTO ages VALUES (25, 1)").run();
		db.prepare("INSERT INTO ages VALUES (30, 2)").run();
		db.prepare("INSERT INTO ages VALUES (35, 2)").run();
		var stmt = db.prepare("INSERT INTO ages VALUES (30, 3)");
		expect(function () {stmt.run();}).to.throw(Error).with.property('code', 'SQLITE_CONSTRAINT_FOREIGNKEY');
		stmt = db.prepare("INSERT INTO ages VALUES (30, NULL)");
		expect(function () {stmt.run();}).to.throw(Error).with.property('code', 'SQLITE_CONSTRAINT_NOTNULL');
	});
	it('should allow ad-hoc transactions', function () {
		expect(db.prepare("BEGIN TRANSACTION").run().changes).to.equal(0);
		expect(db.prepare("INSERT INTO ages VALUES (45, 2)").run().changes).to.equal(1);
		var stmt = db.prepare("INSERT INTO ages VALUES (30, 3)");
		expect(function () {stmt.run()}).to.throw(Error).with.property('code', 'SQLITE_CONSTRAINT_FOREIGNKEY');
		expect(db.prepare("ROLLBACK TRANSACTION").run().changes).to.equal(0);
	});
	it('should not count changes from indirect mechanisms', function () {
		var stmt = db.prepare("UPDATE people SET id=55 WHERE id=2");
		expect(stmt.run().changes).to.equal(1);
	});
	it('should count accurate DELETE changes when a dropped table has side effects', function () {
		var stmt = db.prepare("DROP TABLE people");
		expect(stmt.run().changes).to.equal(2);
	});
	it('should obey the restrictions of readonly mode', function () {
		var db2 = new Database(db.name, {readonly: true});
		var stmt = db2.prepare('CREATE TABLE people (name TEXT)');
		expect(function () {stmt.run()}).to.throw(Error).with.property('code', 'SQLITE_READONLY');
	});
	it('should accept bind parameters', function () {
		db.prepare("CREATE TABLE entries (a TEXT CHECK(typeof(a)=='text'), b INTEGER CHECK(typeof(b)=='integer' OR typeof(b)=='real'), c REAL CHECK(typeof(c)=='real' OR typeof(c)=='integer'), d BLOB CHECK(typeof(d)=='blob'))").run();
		db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run('foo', 25, 25, bufferOfSize(8).fill(0xdd));
		db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run(['foo', 25, 25, bufferOfSize(8).fill(0xdd)]);
		db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run(['foo', 25], [25], bufferOfSize(8).fill(0xdd));
		db.prepare('INSERT INTO entries VALUES (@a, @b, @c, @d)').run({a: 'foo', b: 25, c: 25, d: bufferOfSize(8).fill(0xdd)});
		db.prepare('INSERT INTO entries VALUES ($a, $b, $c, $d)').run({a: 'foo', b: 25, c: 25, d: bufferOfSize(8).fill(0xdd)});
		db.prepare('INSERT INTO entries VALUES (:a, :b, :c, :d)').run({a: 'foo', b: 25, c: 25, d: bufferOfSize(8).fill(0xdd)});
		db.prepare('INSERT INTO entries VALUES (?, @a, @a, ?)').run({a: 25}, ['foo'], bufferOfSize(8).fill(0xdd));
		expect(function () {
			db.prepare('INSERT INTO entries VALUES (?, @a, @a, ?)').run({a: 25}, ['foo'], bufferOfSize(8).fill(0xdd), bufferOfSize(8).fill(0xdd));
		}).to.throw(Error);
		expect(function () {
			db.prepare('INSERT INTO entries VALUES (?, @a, @a, ?)').run({a: 25}, ['foo']);
		}).to.throw(Error);
		db.prepare('INSERT INTO entries VALUES (?, @a, @a, ?)').run({a: 25, c: 25}, ['foo'], bufferOfSize(8).fill(0xdd));
		expect(function () {
			db.prepare('INSERT INTO entries VALUES (?, @a, @a, ?)').run({}, ['foo'], bufferOfSize(8).fill(0xdd));
		}).to.throw(Error);
		expect(function () {
			db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run(25, 'foo', 25, bufferOfSize(8).fill(0xdd));
		}).to.throw(Error);
		db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run('foo', 25, 25, bufferOfSize(8).fill(0xdd), {});
		db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run('foo', 25, 25, bufferOfSize(8).fill(0xdd), {foo: 'foo'});
		expect(function () {
			db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run('foo', 25, 25, {4: bufferOfSize(8).fill(0xdd)});
		}).to.throw(Error);
		expect(function () {
			db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run();
		}).to.throw(Error);
		expect(function () {
			db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run({length: 4, 0: 'foo', 1: 25, 2: 25, 3: bufferOfSize(8).fill(0xdd)});
		}).to.throw(Error);
		expect(function () {
			db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run('foo', 25, new Number(25), bufferOfSize(8).fill(0xdd));
		}).to.throw(Error);
		expect(function () {
			db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run('foo', {low: 25, high: 25}, 25, bufferOfSize(8).fill(0xdd));
		}).to.throw(Error);
		function Foo() {
			this.a = 'foo';
			this.b = 25;
			this.c = 25;
			this.d = bufferOfSize(8).fill(0xdd);
		}
		expect(function () {
			db.prepare('INSERT INTO entries VALUES (@a, @b, @c, @d)').run(new Foo);
		}).to.throw(Error);
		
		// This part of the test may fail is Statement#get() does not work.
		var i = 0;
		var row;
		while (row = db.prepare('SELECT * FROM entries WHERE rowid=' + ++i).get()) {
			expect(row).to.deep.equal({a: 'foo', b: 25, c: 25, d: bufferOfSize(8).fill(0xdd)});
		}
		expect(i).to.equal(11);
	});
});

function bufferOfSize(size) {
	return Buffer.alloc ? Buffer.alloc(+size) : new Buffer(+size);
}
