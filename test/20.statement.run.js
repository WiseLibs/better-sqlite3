'use strict';
const Database = require('../.');

describe('Statement#run()', function () {
	let db;
	before(function () {
		db = new Database(util.next());
	});
	
	it('should throw an exception when used on a statement that returns data', function () {
		const stmt = db.prepare('SELECT 555');
		expect(() => stmt.run()).to.throw(TypeError);
	});
	it('should work with CREATE TABLE', function () {
		const stmt = db.prepare('CREATE TABLE entries (a TEXT, b INTEGER, c REAL, d BLOB)');
		const info = stmt.run();
		expect(info.changes).to.equal(0);
		expect(info.lastInsertRowid).to.equal(0);
	});
	it('should work with CREATE TABLE IF NOT EXISTS', function () {
		const stmt = db.prepare('CREATE TABLE IF NOT EXISTS entries (a TEXT, b INTEGER, c REAL, d BLOB)');
		const info = stmt.run();
		expect(info.changes).to.equal(0);
		expect(info.lastInsertRowid).to.equal(0);
	});
	it('should work with INSERT INTO', function () {
		let stmt = db.prepare("INSERT INTO entries VALUES ('foo', 25, 3.14, x'1133ddff')");
		let info = stmt.run();
		expect(info.changes).to.equal(1);
		expect(info.lastInsertRowid).to.equal(1);
		
		info = stmt.run();
		expect(info.changes).to.equal(1);
		expect(info.lastInsertRowid).to.equal(2);
		
		stmt = db.prepare("INSERT INTO entries VALUES ('foo', 25, 3.14, x'1133ddff'), ('foo', 25, 3.14, x'1133ddff')");
		info = stmt.run();
		expect(info.changes).to.equal(2);
		expect(info.lastInsertRowid).to.equal(4);
	});
	it('should work with UPDATE', function () {
		const stmt = db.prepare("UPDATE entries SET a='bar' WHERE rowid=1");
		expect(stmt.run().changes).to.equal(1);
	});
	it('should work with DELETE FROM', function () {
		let stmt = db.prepare("DELETE FROM entries WHERE a='foo'");
		expect(stmt.run().changes).to.equal(3);
		
		stmt = db.prepare("INSERT INTO entries VALUES ('foo', 25, 3.14, x'1133ddff')");
		const info = stmt.run();
		expect(info.changes).to.equal(1);
		expect(info.lastInsertRowid).to.equal(2);
	});
	it('should work with BEGIN and COMMIT', function () {
		expect(db.inTransaction).to.equal(false);
		expect(db.prepare("BEGIN TRANSACTION").run().changes).to.equal(0);
		expect(db.inTransaction).to.equal(true);
		const info = db.prepare("INSERT INTO entries VALUES ('foo', 25, 3.14, x'1133ddff')").run();
		expect(info.changes).to.equal(1);
		expect(info.lastInsertRowid).to.equal(3);
		expect(db.inTransaction).to.equal(true);
		expect(db.prepare("COMMIT TRANSACTION").run().changes).to.equal(0);
		expect(db.inTransaction).to.equal(false);
	});
	it('should work with DROP TABLE', function () {
		const stmt = db.prepare("DROP TABLE entries");
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
		let stmt = db.prepare("INSERT INTO ages VALUES (30, 3)");
		expect(() => stmt.run()).to.throw(Database.SqliteError).with.property('code', 'SQLITE_CONSTRAINT_FOREIGNKEY');
		stmt = db.prepare("INSERT INTO ages VALUES (30, NULL)");
		expect(() => stmt.run()).to.throw(Database.SqliteError).with.property('code', 'SQLITE_CONSTRAINT_NOTNULL');
	});
	it('should allow ad-hoc transactions', function () {
		expect(db.prepare("BEGIN TRANSACTION").run().changes).to.equal(0);
		expect(db.prepare("INSERT INTO ages VALUES (45, 2)").run().changes).to.equal(1);
		const stmt = db.prepare("INSERT INTO ages VALUES (30, 3)");
		expect(() => stmt.run()).to.throw(Database.SqliteError).with.property('code', 'SQLITE_CONSTRAINT_FOREIGNKEY');
		expect(db.prepare("ROLLBACK TRANSACTION").run().changes).to.equal(0);
	});
	it('should not count changes from indirect mechanisms', function () {
		const stmt = db.prepare("UPDATE people SET id=55 WHERE id=2");
		expect(stmt.run().changes).to.equal(1);
	});
	it('should count accurate DELETE changes when a dropped table has side effects', function () {
		const stmt = db.prepare("DROP TABLE people");
		expect(stmt.run().changes).to.equal(2);
	});
	it('should obey the restrictions of readonly mode', function () {
		const db2 = new Database(db.name, { readonly: true });
		const stmt = db2.prepare('CREATE TABLE people (name TEXT)');
		expect(() => stmt.run()).to.throw(Database.SqliteError).with.property('code', 'SQLITE_READONLY');
	});
	it('should accept bind parameters', function () {
		db.prepare("CREATE TABLE entries (a TEXT CHECK(typeof(a)=='text'), b INTEGER CHECK(typeof(b)=='integer' OR typeof(b)=='real'), c REAL CHECK(typeof(c)=='real' OR typeof(c)=='integer'), d BLOB CHECK(typeof(d)=='blob'))").run();
		db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run('foo', 25, 25, Buffer.alloc(8).fill(0xdd));
		db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run(['foo', 25, 25, Buffer.alloc(8).fill(0xdd)]);
		db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run(['foo', 25], [25], Buffer.alloc(8).fill(0xdd));
		db.prepare('INSERT INTO entries VALUES (@a, @b, @c, @d)').run({ a: 'foo', b: 25, c: 25, d: Buffer.alloc(8).fill(0xdd) });
		db.prepare('INSERT INTO entries VALUES ($a, $b, $c, $d)').run({ a: 'foo', b: 25, c: 25, d: Buffer.alloc(8).fill(0xdd) });
		db.prepare('INSERT INTO entries VALUES (:a, :b, :c, :d)').run({ a: 'foo', b: 25, c: 25, d: Buffer.alloc(8).fill(0xdd) });
		db.prepare('INSERT INTO entries VALUES (?, @a, @a, ?)').run({ a: 25 }, ['foo'], Buffer.alloc(8).fill(0xdd));
		expect(() =>
			db.prepare('INSERT INTO entries VALUES (?, @a, @a, ?)').run({ a: 25 }, ['foo'], Buffer.alloc(8).fill(0xdd), Buffer.alloc(8).fill(0xdd))
		).to.throw(RangeError);
		expect(() =>
			db.prepare('INSERT INTO entries VALUES (?, @a, @a, ?)').run({ a: 25 }, ['foo'])
		).to.throw(RangeError);
		db.prepare('INSERT INTO entries VALUES (?, @a, @a, ?)').run({ a: 25, c: 25 }, ['foo'], Buffer.alloc(8).fill(0xdd));
		expect(() =>
			db.prepare('INSERT INTO entries VALUES (?, @a, @a, ?)').run({}, ['foo'], Buffer.alloc(8).fill(0xdd))
		).to.throw(RangeError);
		expect(() =>
			db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run(25, 'foo', 25, Buffer.alloc(8).fill(0xdd))
		).to.throw(Database.SqliteError).with.property('code', 'SQLITE_CONSTRAINT_CHECK');
		db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run('foo', 25, 25, Buffer.alloc(8).fill(0xdd), {});
		db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run('foo', 25, 25, Buffer.alloc(8).fill(0xdd), { foo: 'foo' });
		expect(() =>
			db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run('foo', 25, 25, { 4: Buffer.alloc(8).fill(0xdd) })
		).to.throw(RangeError);
		expect(() =>
			db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run()
		).to.throw(RangeError);
		expect(() =>
			db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run({ length: 4, 0: 'foo', 1: 25, 2: 25, 3: Buffer.alloc(8).fill(0xdd) })
		).to.throw(RangeError);
		expect(() =>
			db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run('foo', 25, new Number(25), Buffer.alloc(8).fill(0xdd))
		).to.throw(TypeError);
		expect(() =>
			db.prepare('INSERT INTO entries VALUES (?, ?, ?, ?)').run('foo', { low: 25, high: 25 }, 25, Buffer.alloc(8).fill(0xdd))
		).to.throw(RangeError);
		function Foo() {
			this.a = 'foo';
			this.b = 25;
			this.c = 25;
			this.d = Buffer.alloc(8).fill(0xdd);
		}
		expect(() =>
			db.prepare('INSERT INTO entries VALUES (@a, @b, @c, @d)').run(new Foo)
		).to.throw(TypeError);
		
		// This part of the test may fail is Statement#get() does not work.
		let i = 0;
		let row;
		while (row = db.prepare(`SELECT * FROM entries WHERE rowid=${++i}`).get()) {
			expect(row).to.deep.equal({ a: 'foo', b: 25, c: 25, d: Buffer.alloc(8).fill(0xdd) });
		}
		expect(i).to.equal(11);
	});
});
