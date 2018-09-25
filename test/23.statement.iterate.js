'use strict';
const { expect } = require('chai');
const Database = require('../.');
const db = new Database(require('./util').next());

describe('Statement#iterate()', function () {
	it('should throw an exception when used on a statement that returns no data', function () {
		db.prepare('CREATE TABLE entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)').run();
		
		let stmt = db.prepare("INSERT INTO entries VALUES ('foo', 1, 3.14, x'dddddddd', NULL)");
		expect(stmt.reader).to.be.false;
		expect(() => stmt.iterate()).to.throw(TypeError);
		
		stmt = db.prepare("CREATE TABLE IF NOT EXISTS entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)");
		expect(stmt.reader).to.be.false;
		expect(() => stmt.iterate()).to.throw(TypeError);
		
		stmt = db.prepare("BEGIN TRANSACTION");
		expect(stmt.reader).to.be.false;
		expect(() => stmt.iterate()).to.throw(TypeError);
		
		db.prepare("INSERT INTO entries WITH RECURSIVE temp(a, b, c, d, e) AS (SELECT 'foo', 1, 3.14, x'dddddddd', NULL UNION ALL SELECT a, b + 1, c, d, e FROM temp LIMIT 10) SELECT * FROM temp").run();
	});
	it('should return an iterator over each matching row', function () {
		const row = { a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null };
		
		let count = 0;
		let stmt = db.prepare("SELECT * FROM entries ORDER BY rowid");
		expect(stmt.reader).to.be.true;
		
		const iterator = stmt.iterate();
		expect(iterator).to.not.be.null;
		expect(typeof iterator).to.equal('object');
		expect(iterator.next).to.be.a('function');
		expect(iterator.return).to.be.a('function');
		expect(iterator.throw).to.not.be.a('function');
		expect(iterator[Symbol.iterator]).to.be.a('function');
		expect(iterator[Symbol.iterator]()).to.equal(iterator);
		
		for (const data of iterator) {
			row.b = ++count;
			expect(data).to.deep.equal(row);
		}
		expect(count).to.equal(10);
		
		count = 0;
		stmt = db.prepare("SELECT * FROM entries WHERE b > 5 ORDER BY rowid");
		const iterator2 = stmt.iterate();
		expect(iterator).to.not.equal(iterator2);
		for (const data of iterator2) {
			row.b = ++count + 5;
			expect(data).to.deep.equal(row);
		}
		expect(count).to.equal(5);
	});
	it('should obey the current pluck setting', function () {
		const row = { a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null };
		const stmt = db.prepare("SELECT * FROM entries ORDER BY rowid");
		shouldHave(row);
		stmt.pluck(true);
		shouldHave('foo');
		shouldHave('foo');
		stmt.pluck(false);
		shouldHave(row);
		shouldHave(row);
		stmt.pluck();
		shouldHave('foo');
		shouldHave('foo');
		
		function shouldHave(desiredData) {
			let i = 0;
			for (const data of stmt.iterate()) {
				++i;
				if (typeof desiredData === 'object' && desiredData !== null) {
					desiredData.b = i;
				}
				expect(data).to.deep.equal(desiredData);
			}
			expect(i).to.equal(10);
		}
	});
	it('should not be able to invoke .pluck() while the database is busy', function () {
		const stmt1 = db.prepare("SELECT * FROM entries");
		const stmt2 = db.prepare("SELECT * FROM entries LIMIT 2");
		let i = 0;
		for (const data of stmt1.iterate()) {
			++i;
			expect(() => stmt1.pluck()).to.throw(TypeError);
			expect(() => stmt2.pluck()).to.throw(TypeError);
			expect(() => stmt1.pluck(false)).to.throw(TypeError);
			expect(() => stmt2.pluck(false)).to.throw(TypeError);
		}
		expect(i).to.equal(10);
	});
	it('should close the iterator when throwing in a for-of loop', function () {
		const err = new Error('foobar');
		const stmt = db.prepare("SELECT * FROM entries");
		const iterator = stmt.iterate();
		let count = 0;
		expect(() => {
			for (const row of iterator) { ++count; throw err; }
		}).to.throw(err);
		expect(count).to.equal(1);
		expect(iterator.next()).to.deep.equal({ value: undefined, done: true });
		for (const row of iterator) ++count;
		expect(count).to.equal(1);
		for (const row of stmt.iterate()) ++count;
		expect(count).to.equal(11);
	});
	it('should close the iterator when using break in a for-of loop', function () {
		const stmt = db.prepare("SELECT * FROM entries");
		const iterator = stmt.iterate();
		let count = 0;
		for (const row of iterator) { ++count; break; }
		expect(count).to.equal(1);
		expect(iterator.next()).to.deep.equal({ value: undefined, done: true });
		for (const row of iterator) ++count;
		expect(count).to.equal(1);
		for (const row of stmt.iterate()) ++count;
		expect(count).to.equal(11);
	});
	it('should return an empty iterator when no rows were found', function () {
		const stmt = db.prepare("SELECT * FROM entries WHERE b == 999");
		expect(stmt.iterate().next()).to.deep.equal({ value: undefined, done: true });
		for (const data of stmt.pluck().iterate()) {
			throw new Error('This callback should not have been invoked');
		}
	});
	it('should not allow other database operations to execute while open', function () {
		const stmt1 = db.prepare('SELECT * FROM entries');
		const stmt2 = db.prepare('CREATE TABLE numbers (number INTEGER)');
		const trans = db.transaction(['CREATE TABLE numbers (number INTEGER)']);
		let count = 0;
		for (const row of db.prepare('SELECT * FROM entries').iterate()) {
			++count;
			expect(() => db.close()).to.throw(TypeError);
			expect(() => db.pragma('cache_size')).to.throw(TypeError);
			expect(() => db.checkpoint()).to.throw(TypeError);
			expect(() => db.prepare('SELECT * FROM entries')).to.throw(TypeError);
			expect(() => db.transaction(['CREATE TABLE numbers (number INTEGER)'])).to.throw(TypeError);
			expect(() => stmt1.get()).to.throw(TypeError);
			expect(() => stmt1.all()).to.throw(TypeError);
			expect(() => stmt1.iterate()).to.throw(TypeError);
			expect(() => stmt2.run()).to.throw(TypeError);
			expect(() => trans.run()).to.throw(TypeError);
		}
		expect(count).to.equal(10);
	});
	it('should allow database operations after closing the iterator', function () {
		const row = { a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null };
		const stmt = db.prepare("SELECT * FROM entries");
		db.prepare('SELECT 555');
		const iterator = stmt.iterate();
		expect(() => db.prepare('SELECT 555')).to.throw(TypeError);
		expect(iterator.next()).to.deep.equal({ value: row, done: false });
		row.b += 1;
		expect(() => db.prepare('SELECT 555')).to.throw(TypeError);
		expect(iterator.next()).to.deep.equal({ value: row, done: false });
		row.b += 1;
		expect(() => db.prepare('SELECT 555')).to.throw(TypeError);
		expect(iterator.next()).to.deep.equal({ value: row, done: false });
		expect(() => db.prepare('SELECT 555')).to.throw(TypeError);
		expect(iterator.return()).to.deep.equal({ value: undefined, done: true });
		db.prepare('SELECT 555');
		expect(iterator.next()).to.deep.equal({ value: undefined, done: true });
		db.prepare('SELECT 555');
		expect(iterator.return()).to.deep.equal({ value: undefined, done: true });
		db.prepare('SELECT 555');
		expect(iterator.next()).to.deep.equal({ value: undefined, done: true });
		db.prepare('SELECT 555');
	});
	it('should accept bind parameters', function () {
		const row = { a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null };
		const SQL1 = 'SELECT * FROM entries WHERE a=? AND b=? AND c=? AND d=? AND e IS ?';
		const SQL2 = 'SELECT * FROM entries WHERE a=@a AND b=@b AND c=@c AND d=@d AND e IS @e';
		
		shouldHave(SQL1, row, ['foo', 1, 3.14, Buffer.alloc(4).fill(0xdd), null])
		shouldHave(SQL1, row, [['foo', 1, 3.14, Buffer.alloc(4).fill(0xdd), null]])
		shouldHave(SQL1, row, [['foo', 1], [3.14], Buffer.alloc(4).fill(0xdd), [,]])
		shouldHave(SQL2, row, [{ a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: undefined }])
		
		for (const data of db.prepare(SQL2).iterate({ a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xaa), e: undefined })) {
			throw new Error('This callback should not have been invoked');
		}
		
		expect(() =>
			db.prepare(SQL2).iterate(row, () => {})
		).to.throw(TypeError);
		
		expect(() =>
			db.prepare(SQL2).iterate({ a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd) })
		).to.throw(RangeError);
		
		expect(() =>
			db.prepare(SQL1).iterate()
		).to.throw(RangeError);
		
		expect(() =>
			db.prepare(SQL2).iterate()
		).to.throw(TypeError);
		
		expect(() =>
			db.prepare(SQL2).iterate(row, {})
		).to.throw(TypeError);
		
		expect(() =>
			db.prepare(SQL2).iterate({})
		).to.throw(RangeError);
		
		db.prepare(SQL1).iterate('foo', 1, 3.14, Buffer.alloc(4).fill(0xdd), null).return();
		expect(() =>
			db.prepare(SQL1).iterate('foo', 1, new (function(){})(), Buffer.alloc(4).fill(0xdd), null)
		).to.throw(TypeError);
		
		function shouldHave(SQL, desiredData, args) {
			let i = 0;
			const stmt = db.prepare(SQL);
			for (const data of stmt.iterate(...args)) {
				desiredData.b = ++i;
				expect(data).to.deep.equal(desiredData);
			}
			expect(i).to.equal(1);
		}
	});
});
