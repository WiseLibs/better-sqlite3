'use strict';
const { expect } = require('chai');
const Database = require('../.');
const db = new Database(require('./util').next());

describe('Statement#bind()', function () {
	it('should permanently bind the given parameters', function () {
		db.prepare('CREATE TABLE entries (a TEXT, b INTEGER, c BLOB)').run();
		const stmt = db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		const buffer = Buffer.alloc(4).fill(0xdd);
		stmt.bind('foobar', 25, buffer)
		stmt.run();
		buffer.fill(0xaa);
		stmt.run();
		const row1 = db.prepare('SELECT * FROM entries WHERE rowid=1').get();
		const row2 = db.prepare('SELECT * FROM entries WHERE rowid=2').get();
		expect(row1.a).to.equal(row2.a);
		expect(row1.b).to.equal(row2.b);
		expect(row1.c).to.deep.equal(row2.c);
	});
	it('should not allow you to bind temporary parameters afterwards', function () {
		const stmt = db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		const buffer = Buffer.alloc(4).fill(0xdd);
		stmt.bind('foobar', 25, buffer)
		expect(() => stmt.run(null)).to.throw(TypeError);
		expect(() => stmt.run(buffer)).to.throw(TypeError);
		expect(() => stmt.run('foobar', 25, buffer)).to.throw(TypeError);
	});
	it('should throw an exception when invoked twice on the same statement', function () {
		let stmt = db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		stmt.bind('foobar', 25, null);
		expect(() => stmt.bind('foobar', 25, null)).to.throw(TypeError);
		expect(() => stmt.bind()).to.throw(TypeError);
		
		stmt = db.prepare('SELECT * FROM entries');
		stmt.bind();
		expect(() => stmt.bind()).to.throw(TypeError);
	});
	it('should throw an exception when invalid parameters are given', function () {
		let stmt = db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		
		expect(() =>
			stmt.bind('foo', 25)
		).to.throw(RangeError);
		
		expect(() =>
			stmt.bind('foo', 25, null, null)
		).to.throw(RangeError);
		
		expect(() =>
			stmt.bind('foo', new Number(25), null)
		).to.throw(TypeError);
		
		expect(() =>
			stmt.bind()
		).to.throw(RangeError);
		
		stmt.bind('foo', 25, null);
		
		stmt = db.prepare('INSERT INTO entries VALUES (@a, @a, ?)');
		
		expect(() =>
			stmt.bind({ a: '123' })
		).to.throw(RangeError);
		
		expect(() =>
			stmt.bind({ a: '123', 1: null })
		).to.throw(RangeError);
		
		expect(() =>
			stmt.bind({ a: '123' }, null, null)
		).to.throw(RangeError);
		
		stmt.bind({ a: '123' }, null);
		
		stmt = db.prepare('INSERT INTO entries VALUES (@a, @a, ?)');
		stmt.bind({ a: '123', b: null }, null);
	});
	it('should propagate exceptions thrown while accessing array/object members', function () {
		const arr = [22];
		const obj = {};
		const err = new TypeError('foobar');
		Object.defineProperty(arr, '0', { get: () => { throw err; } })
		Object.defineProperty(obj, 'baz', { get: () => { throw err; } })
		const stmt1 = db.prepare('SELECT ?');
		const stmt2 = db.prepare('SELECT @baz');
		expect(() => stmt1.bind(arr)).to.throw(err);
		expect(() => stmt2.bind(obj)).to.throw(err);
	});
});
