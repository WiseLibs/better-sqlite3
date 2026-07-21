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
	it('should not treat class instances as plain objects', function () {
		const stmt = this.db.prepare('INSERT INTO entries VALUES (@a, @a, ?)');
		expect(() => stmt.bind(new (class { get a() { return "123"; } })(), null)).to.throw(TypeError);
		expect(() => stmt.bind(Object.assign(new Date(), { a: 123 }), null)).to.throw(TypeError);
		expect(() => stmt.bind(Object.assign(new Number(123), { a: 123 }), null)).to.throw(TypeError);
		expect(() => stmt.bind(Object.assign(() => {}, { a: 123 }), null)).to.throw(TypeError);
	});
	it('should not treat class instances from other realms as plain objects', function () {
		const vm = require('vm');
		const context = vm.createContext({});

		// A class instance from another realm is not a plain object, so passing it
		// where named parameters are expected must throw.
		const foreignInstance = vm.runInContext('(new (class { get a() { return "123"; } })())', context);
		const stmt = this.db.prepare('INSERT INTO entries VALUES (@a, @a, ?)');
		expect(() => stmt.bind(foreignInstance, null)).to.throw(TypeError);
	});
	it('should recognize plain objects created in other realms', function () {
		const vm = require('vm');
		const context = vm.createContext({});

		// A plain object created in another realm has a different Object.prototype
		// identity, but should still be recognized as a plain object.
		const foreignPlainObject = vm.runInContext('({ a: "123", b: null })', context);
		expect(Object.getPrototypeOf(foreignPlainObject)).to.not.equal(Object.prototype);

		const stmt = this.db.prepare('INSERT INTO entries VALUES (@a, @a, ?)');
		stmt.bind(foreignPlainObject, null);
		stmt.run();
		const row = this.db.prepare('SELECT * FROM entries WHERE rowid=1').get();
		expect(row.a).to.equal('123');

		// An object created via Object.create(null) in another realm is plain too.
		const foreignNullProtoObject = vm.runInContext('Object.assign(Object.create(null), { a: "456", b: null })', context);
		const stmt2 = this.db.prepare('INSERT INTO entries VALUES (@a, @a, ?)');
		stmt2.bind(foreignNullProtoObject, null);
		stmt2.run();
		const row2 = this.db.prepare('SELECT * FROM entries WHERE rowid=2').get();
		expect(row2.a).to.equal('456');
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
