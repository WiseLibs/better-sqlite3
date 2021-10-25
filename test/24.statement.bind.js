'use strict';
const Database = require('../.');

describe('Statement#bind()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
		this.db.prepare('CREATE TABLE entries (a TEXT, b INTEGER, c BLOB)').run();
	});
	afterEach(function () {
		this.db.close();
	});

	it('should permanently bind the given parameters', function () {
		const stmt = this.db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		const buffer = Buffer.alloc(4).fill(0xdd);
		stmt.bind('foobar', 25, buffer)
		stmt.run();
		buffer.fill(0xaa);
		stmt.run();
		const row1 = this.db.prepare('SELECT * FROM entries WHERE rowid=1').get();
		const row2 = this.db.prepare('SELECT * FROM entries WHERE rowid=2').get();
		expect(row1.a).to.equal(row2.a);
		expect(row1.b).to.equal(row2.b);
		expect(row1.c).to.deep.equal(row2.c);
	});
	it('should not allow you to bind temporary parameters afterwards', function () {
		const stmt = this.db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		const buffer = Buffer.alloc(4).fill(0xdd);
		stmt.bind('foobar', 25, buffer)
		expect(() => stmt.run(null)).to.throw(TypeError);
		expect(() => stmt.run(buffer)).to.throw(TypeError);
		expect(() => stmt.run('foobar', 25, buffer)).to.throw(TypeError);
	});
	it('should throw an exception when invoked twice on the same statement', function () {
		let stmt = this.db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		stmt.bind('foobar', 25, null);
		expect(() => stmt.bind('foobar', 25, null)).to.throw(TypeError);
		expect(() => stmt.bind()).to.throw(TypeError);

		stmt = this.db.prepare('SELECT * FROM entries');
		stmt.bind();
		expect(() => stmt.bind()).to.throw(TypeError);
	});
	it('should throw an exception when invalid parameters are given', function () {
		let stmt = this.db.prepare('INSERT INTO entries VALUES (?, ?, ?)');

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

		stmt = this.db.prepare('INSERT INTO entries VALUES (@a, @a, ?)');

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

		stmt = this.db.prepare('INSERT INTO entries VALUES (@a, @a, ?)');
		stmt.bind({ a: '123', b: null }, null);
	});
	it('should propagate exceptions thrown while accessing array/object members', function () {
		const arr = [22];
		const obj = {};
		const err = new TypeError('foobar');
		Object.defineProperty(arr, '0', { get: () => { throw err; } })
		Object.defineProperty(obj, 'baz', { get: () => { throw err; } })
		const stmt1 = this.db.prepare('SELECT ?');
		const stmt2 = this.db.prepare('SELECT @baz');
		expect(() => stmt1.bind(arr)).to.throw(err);
		expect(() => stmt2.bind(obj)).to.throw(err);
	});
	it('should properly bind empty buffers', function () {
		this.db.prepare('INSERT INTO entries (c) VALUES (?)').bind(Buffer.alloc(0)).run();
		const result = this.db.prepare('SELECT c FROM entries').pluck().get();
		expect(result).to.be.an.instanceof(Buffer);
		expect(result.length).to.equal(0);
	});
	it('should properly bind empty strings', function () {
		this.db.prepare('INSERT INTO entries (a) VALUES (?)').bind('').run();
		const result = this.db.prepare('SELECT a FROM entries').pluck().get();
		expect(result).to.be.a('string');
		expect(result.length).to.equal(0);
	});
});
