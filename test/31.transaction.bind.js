'use strict';
const Database = require('../.');

describe('Transaction#bind()', function () {
	let db;
	before(function () {
		db = new Database(util.next());
	});
	
	it('should permanently bind the given parameters', function () {
		db.transaction(['CREATE TABLE entries (a TEXT, b INTEGER, c BLOB)']).run();
		const trans = db.transaction(['INSERT INTO entries VALUES (?, ?, ?)']);
		const buffer = Buffer.alloc(4).fill(0xdd);
		trans.bind('foobar', 25, buffer)
		trans.run();
		buffer.fill(0xaa);
		trans.run();
		const row1 = db.prepare('SELECT * FROM entries WHERE rowid=1').get();
		const row2 = db.prepare('SELECT * FROM entries WHERE rowid=2').get();
		expect(row1.a).to.equal(row2.a);
		expect(row1.b).to.equal(row2.b);
		expect(row1.c).to.deep.equal(row2.c);
	});
	it('should not allow you to bind temporary parameters afterwards', function () {
		const trans = db.transaction(['INSERT INTO entries VALUES (?, ?, ?)']);
		const buffer = Buffer.alloc(4).fill(0xdd);
		trans.bind('foobar', 25, buffer)
		expect(() => trans.run(null)).to.throw(TypeError);
		expect(() => trans.run(buffer)).to.throw(TypeError);
		expect(() => trans.run('foobar', 25, buffer)).to.throw(TypeError);
	});
	it('should throw an exception when invoked twice on the same transaction', function () {
		let trans = db.transaction(['INSERT INTO entries VALUES (?, ?, ?)']);
		trans.bind('foobar', 25, null);
		expect(() => trans.bind('foobar', 25, null)).to.throw(TypeError);
		expect(() => trans.bind()).to.throw(TypeError);
		
		trans = db.transaction(["INSERT INTO entries VALUES ('foobar', 25, null)"]);
		trans.bind();
		expect(() => trans.bind()).to.throw(TypeError);
	});
	it('should throw an exception when invalid parameters are given', function () {
		let trans = db.transaction(['INSERT INTO entries VALUES (?, ?, ?)']);
		
		expect(() =>
			trans.bind('foo', 25)
		).to.throw(RangeError);
		
		expect(() =>
			trans.bind('foo', 25, null, null)
		).to.throw(RangeError);
		
		expect(() =>
			trans.bind('foo', new Number(25), null)
		).to.throw(TypeError);
		
		expect(() =>
			trans.bind()
		).to.throw(RangeError);
		
		trans.bind('foo', 25, null);
		
		trans = db.transaction(['INSERT INTO entries VALUES (@a, @a, ?)']);
		
		expect(() =>
			trans.bind({ a: '123' })
		).to.throw(RangeError);
		
		expect(() =>
			trans.bind({ a: '123', 1: null })
		).to.throw(RangeError);
		
		expect(() =>
			trans.bind({ a: '123' }, null, null)
		).to.throw(RangeError);
		
		trans.bind({ a: '123' }, null);
		
		trans = db.transaction(['INSERT INTO entries VALUES (@a, @a, ?)']);
		trans.bind({ a: '123', b: null }, null);
	});
	it('should propagate exceptions thrown while accessing array/object members', function () {
		const arr = [22];
		const obj = {};
		const err = new TypeError('foobar');
		Object.defineProperty(arr, '0', { get: () => { throw err; } })
		Object.defineProperty(obj, 'baz', { get: () => { throw err; } })
		const trans1 = db.transaction(['INSERT INTO entries VALUES (NULL, ?, NULL)']);
		const trans2 = db.transaction(['INSERT INTO entries VALUES (NULL, @baz, NULL)']);
		expect(() => trans1.bind(arr)).to.throw(err);
		expect(() => trans2.bind(obj)).to.throw(err);
	});
});
