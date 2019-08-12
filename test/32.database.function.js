'use strict';
const Database = require('../.');

describe('Database#function()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
		this.get = (SQL, ...args) => this.db.prepare(`SELECT ${SQL}`).pluck().get(args);
	});
	afterEach(function () {
		this.db.close();
	});

	it('should throw an exception if the correct arguments are not provided', function () {
		expect(() => this.db.function()).to.throw(TypeError);
		expect(() => this.db.function(null)).to.throw(TypeError);
		expect(() => this.db.function('a')).to.throw(TypeError);
		expect(() => this.db.function({})).to.throw(TypeError);
		expect(() => this.db.function(() => {})).to.throw(TypeError);
		expect(() => this.db.function(function b() {})).to.throw(TypeError);
		expect(() => this.db.function({}, function c() {})).to.throw(TypeError);
		expect(() => this.db.function('d', {})).to.throw(TypeError);
		expect(() => this.db.function('e', { fn: function e() {} })).to.throw(TypeError);
		expect(() => this.db.function('f', Object.create(Function.prototype))).to.throw(TypeError);
		expect(() => this.db.function({ name: 'g' }, function g() {})).to.throw(TypeError);
		expect(() => this.db.function(new String('h'), function h() {})).to.throw(TypeError);
	});
	it('should throw an exception if boolean options are provided as non-booleans', function () {
		expect(() => this.db.function('a', { varargs: undefined }, () => {})).to.throw(TypeError);
		expect(() => this.db.function('b', { deterministic: undefined }, () => {})).to.throw(TypeError);
		expect(() => this.db.function('c', { safeIntegers: undefined }, () => {})).to.throw(TypeError);
	});
	it('should throw an exception if the provided name is empty', function () {
		expect(() => this.db.function('', function a() {})).to.throw(TypeError);
		expect(() => this.db.function('', { name: 'b' }, function b() {})).to.throw(TypeError);
	});
	it('should throw an exception if function.length is invalid', function () {
		const length = x => Object.defineProperty(() => {}, 'length', { value: x });
		expect(() => this.db.function('a', length(undefined))).to.throw(TypeError);
		expect(() => this.db.function('b', length(null))).to.throw(TypeError);
		expect(() => this.db.function('c', length('2'))).to.throw(TypeError);
		expect(() => this.db.function('d', length(NaN))).to.throw(TypeError);
		expect(() => this.db.function('e', length(Infinity))).to.throw(TypeError);
		expect(() => this.db.function('f', length(2.000000001))).to.throw(TypeError);
		expect(() => this.db.function('g', length(-0.000000001))).to.throw(TypeError);
		expect(() => this.db.function('h', length(-2))).to.throw(TypeError);
		expect(() => this.db.function('i', length(100.000000001))).to.throw(TypeError);
		expect(() => this.db.function('j', length(101))).to.throw(RangeError);
	});
	it('should register the given function and return the database object', function () {
		expect(this.db.function('a', () => {})).to.equal(this.db);
		expect(this.db.function('b', {}, () => {})).to.equal(this.db);
		expect(this.db.function('c', function x() {})).to.equal(this.db);
		expect(this.db.function('d', {}, function y() {})).to.equal(this.db);
	});
	it('should enable the registered function to be executed from SQL', function () {
		// numbers and strings
		this.db.function('a', (a, b, c) => a + b + c);
		expect(this.get('a(?, ?, ?)', 2, 10, 50)).to.equal(62);
		expect(this.get('a(?, ?, ?)', 2, 10, null)).to.equal(12);
		expect(this.get('a(?, ?, ?)', 'foo', 'z', 12)).to.equal('fooz12');

		// undefined is interpreted as null
		this.db.function('b', (a, b) => null);
		this.db.function('c', (a, b) => {});
		expect(this.get('b(?, ?)', 2, 10)).to.equal(null);
		expect(this.get('c(?, ?)', 2, 10)).to.equal(null);

		// buffers
		this.db.function('d', function foo(x) { return x; });
		const input = Buffer.alloc(8).fill(0xdd);
		const output = this.get('d(?)', input);
		expect(input).to.not.equal(output);
		expect(input.equals(output)).to.be.true;
		expect(output.equals(Buffer.alloc(8).fill(0xdd))).to.be.true;

		// should not register based on function.name
		expect(() => this.get('foo(?)', input)).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');

		// zero arguments
		this.db.function('e', () => 12);
		expect(this.get('e()')).to.equal(12);
	});
	it('should use a strict number of arguments by default', function () {
		this.db.function('fn', (a, b) => {});
		expect(() => this.get('fn()')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(() => this.get('fn(?)', 4)).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(() => this.get('fn(?, ?, ?)', 4, 8, 3)).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		this.get('fn(?, ?)', 4, 8);
	});
	it('should accept a "varargs" option', function () {
		const fn = (...args) => args.reduce((a, b) => a * b, 1);
		Object.defineProperty(fn, 'length', { value: '-2' });
		this.db.function('fn', { varargs: true }, fn);
		expect(this.get('fn()')).to.equal(1);
		expect(this.get('fn(?)', 7)).to.equal(7);
		expect(this.get('fn(?, ?)', 4, 8)).to.equal(32);
		expect(this.get('fn(?, ?, ?, ?, ?, ?)', 2, 3, 4, 5, 6, 7)).to.equal(5040);
	});
	it('should cause the function to throw when returning an invalid value', function () {
		this.db.function('fn', x => ({}));
		expect(() => this.get('fn(?)', 42)).to.throw(TypeError);
	});
	it('should propagate exceptions thrown in the registered function', function () {
		const expectError = (name, exception) => {
			this.db.function(name, () => { throw exception; });
			try {
				this.get(name + '()');
			} catch (ex) {
				expect(ex).to.equal(exception);
				return;
			}
			throw new TypeError('Expected function to throw an exception');
		};
		expectError('a', new TypeError('foobar'));
		expectError('b', new Error('baz'));
		expectError('c', { yup: 'ok' });
		expectError('d', 'foobarbazqux');
		expectError('e', '');
		expectError('f', null);
		expectError('g', 123.4);
	});
	it('should close a statement iterator that caused its function to throw', function () {
		this.db.prepare('CREATE TABLE iterable (value INTEGER)').run();
		this.db.prepare('INSERT INTO iterable WITH RECURSIVE temp(x) AS (SELECT 1 UNION ALL SELECT x * 2 FROM temp LIMIT 10) SELECT * FROM temp').run();

		let i = 0;
		const err = new Error('foo');
		this.db.function('fn', (x) => { if (++i >= 5) throw err; return x; });
		const iterator = this.db.prepare('SELECT fn(value) FROM iterable').pluck().iterate();

		let total = 0;
		expect(() => {
			for (const value of iterator) {
				total += value;
				expect(() => this.db.exec('SELECT fn(value) FROM iterable LIMIT 4')).to.throw(TypeError);
			}
		}).to.throw(err);

		expect(total).to.equal(1 + 2 + 4 + 8);
		expect(iterator.next()).to.deep.equal({ value: undefined, done: true });
		expect(total).to.equal(1 + 2 + 4 + 8);

		i = 0;
		this.db.exec('SELECT fn(value) FROM iterable LIMIT 4');
		expect(i).to.equal(4);
	});
	it('should be able to register multiple functions with the same name', function () {
		this.db.function('fn', () => 0);
		this.db.function('fn', (a) => 1);
		this.db.function('fn', (a, b) => 2);
		this.db.function('fn', (a, b, c) => 3);
		this.db.function('fn', (a, b, c, d) => 4);
		expect(this.get('fn()')).to.equal(0);
		expect(this.get('fn(555)')).to.equal(1);
		expect(this.get('fn(555, 555)')).to.equal(2);
		expect(this.get('fn(555, 555, 555)')).to.equal(3);
		expect(this.get('fn(555, 555, 555, 555)')).to.equal(4);
		this.db.function('fn', (a, b) => 'foobar');
		expect(this.get('fn()')).to.equal(0);
		expect(this.get('fn(555)')).to.equal(1);
		expect(this.get('fn(555, 555)')).to.equal('foobar');
		expect(this.get('fn(555, 555, 555)')).to.equal(3);
		expect(this.get('fn(555, 555, 555, 555)')).to.equal(4);
	});
	it('should not be able to affect bound buffers mid-query', function () {
		const input = Buffer.alloc(1024 * 8).fill(0xbb);
		let ranOnce = false;
		this.db.function('fn', () => {
			ranOnce = true;
			input[0] = 2;
		});
		const output = this.get('?, fn()', input);
		expect(ranOnce).to.be.true;
		expect(output.equals(Buffer.alloc(1024 * 8).fill(0xbb))).to.be.true;
	});
	describe('should not affect external environment', function () {
		specify('busy state', function () {
			this.db.function('fn', (x) => {
				expect(() => this.db.exec('SELECT 555')).to.throw(TypeError);
				return x * 2;
			});
			let ranOnce = false;
			for (const x of this.db.prepare('SELECT fn(555)').pluck().iterate()) {
				ranOnce = true;
				expect(x).to.equal(1110);
				expect(() => this.db.exec('SELECT 555')).to.throw(TypeError);
			}
			expect(ranOnce).to.be.true;
			this.db.exec('SELECT 555');
		});
		specify('was_js_error state', function () {
			this.db.prepare('CREATE TABLE data (value INTEGER)').run();
			const stmt = this.db.prepare('SELECT value FROM data');
			this.db.prepare('DROP TABLE data').run();

			const err = new Error('foo');
			this.db.function('fn', () => { throw err; });

			expect(() => this.db.prepare('SELECT fn()').get()).to.throw(err);
			try { stmt.get(); } catch (ex) {
				expect(ex).to.be.an.instanceof(Error);
				expect(ex).to.not.equal(err);
				expect(ex.message).to.not.equal(err.message);
				expect(ex).to.be.an.instanceof(Database.SqliteError);
				return;
			}
			throw new TypeError('Expected the statement to throw an exception');
		});
	});
});
