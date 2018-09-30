'use strict';
const Database = require('../.');

describe.only('Database#aggregate()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
		this.db.prepare('CREATE TABLE empty (x)').run();
		this.db.prepare('CREATE TABLE data (x)').run();
		this.db.prepare('INSERT INTO data VALUES (?), (?), (?), (?), (?), (?), (?)').run(3, 5, 7, 11, 13, 17, 19);
		this.get = (SQL, ...args) => this.db.prepare(`SELECT ${SQL}`).pluck().get(args);
	});
	afterEach(function () {
		this.db.close();
	});
	
	it('should throw an exception if the correct arguments are not provided', function () {
		expect(() => this.db.aggregate()).to.throw(TypeError);
		expect(() => this.db.aggregate(null)).to.throw(TypeError);
		expect(() => this.db.aggregate('a')).to.throw(TypeError);
		expect(() => this.db.aggregate({})).to.throw(TypeError);
		expect(() => this.db.aggregate({ step: () => {} })).to.throw(TypeError);
		expect(() => this.db.aggregate({ name: 'b', step: function b() {} })).to.throw(TypeError);
		expect(() => this.db.aggregate(() => {})).to.throw(TypeError);
		expect(() => this.db.aggregate(function c() {})).to.throw(TypeError);
		expect(() => this.db.aggregate({}, function d() {})).to.throw(TypeError);
		expect(() => this.db.aggregate({ name: 'e', step: function e() {} }, function e() {})).to.throw(TypeError);
		expect(() => this.db.aggregate('f')).to.throw(TypeError);
		expect(() => this.db.aggregate('g', null)).to.throw(TypeError);
		expect(() => this.db.aggregate('h', {})).to.throw(TypeError);
		expect(() => this.db.aggregate('i', function i() {})).to.throw(TypeError);
		expect(() => this.db.aggregate('j', {}, function j() {})).to.throw(TypeError);
		expect(() => this.db.aggregate('k', { name: 'k' }, function k() {})).to.throw(TypeError);
		expect(() => this.db.aggregate('l', { inverse: function l() {} })).to.throw(TypeError);
		expect(() => this.db.aggregate('m', { result: function m() {} })).to.throw(TypeError);
		expect(() => this.db.aggregate(new String('n'), { step: function n() {} })).to.throw(TypeError);
	});
	it('should throw an exception if boolean options are provided as non-booleans', function () {
		expect(() => this.db.aggregate('a', { step: () => {}, varargs: undefined })).to.throw(TypeError);
		expect(() => this.db.aggregate('b', { step: () => {}, deterministic: undefined })).to.throw(TypeError);
		expect(() => this.db.aggregate('c', { step: () => {}, safeIntegers: undefined })).to.throw(TypeError);
	});
	it('should throw an exception if function options are provided as non-fns', function () {
		expect(() => this.db.aggregate('a', { step: undefined })).to.throw(TypeError);
		expect(() => this.db.aggregate('b', { step: null })).to.throw(TypeError);
		expect(() => this.db.aggregate('c', { step: false })).to.throw(TypeError);
		expect(() => this.db.aggregate('d', { step: true })).to.throw(TypeError);
		expect(() => this.db.aggregate('e', { step: Object.create(Function.prototype) })).to.throw(TypeError);
		expect(() => this.db.aggregate('f', { step: () => {}, inverse: false })).to.throw(TypeError);
		expect(() => this.db.aggregate('g', { step: () => {}, inverse: true })).to.throw(TypeError);
		expect(() => this.db.aggregate('h', { step: () => {}, inverse: Object.create(Function.prototype) })).to.throw(TypeError);
		expect(() => this.db.aggregate('i', { step: () => {}, result: false })).to.throw(TypeError);
		expect(() => this.db.aggregate('j', { step: () => {}, result: true })).to.throw(TypeError);
		expect(() => this.db.aggregate('k', { step: () => {}, result: Object.create(Function.prototype) })).to.throw(TypeError);
	});
	it('should throw an exception if the provided name is empty', function () {
		expect(() => this.db.aggregate('', { step: () => {} })).to.throw(TypeError);
		expect(() => this.db.aggregate('', { name: 'a', step: () => {} })).to.throw(TypeError);
		expect(() => this.db.aggregate('', { name: 'b', step: function b() {} })).to.throw(TypeError);
	});
	it('should throw an exception if step.length or inverse.length is invalid', function () {
		const length = x => Object.defineProperty(() => {}, 'length', { value: x });
		expect(() => this.db.aggregate('a', { step: length(undefined) })).to.throw(TypeError);
		expect(() => this.db.aggregate('b', { step: length(null) })).to.throw(TypeError);
		expect(() => this.db.aggregate('c', { step: length('2') })).to.throw(TypeError);
		expect(() => this.db.aggregate('d', { step: length(NaN) })).to.throw(TypeError);
		expect(() => this.db.aggregate('e', { step: length(Infinity) })).to.throw(TypeError);
		expect(() => this.db.aggregate('f', { step: length(2.000000001) })).to.throw(TypeError);
		expect(() => this.db.aggregate('g', { step: length(-0.000000001) })).to.throw(TypeError);
		expect(() => this.db.aggregate('h', { step: length(-2) })).to.throw(TypeError);
		expect(() => this.db.aggregate('i', { step: length(100.000000001) })).to.throw(TypeError);
		expect(() => this.db.aggregate('j', { step: length(102) })).to.throw(RangeError);
		expect(() => this.db.aggregate('aa', { step: () => {}, inverse: length(undefined) })).to.throw(TypeError);
		expect(() => this.db.aggregate('bb', { step: () => {}, inverse: length(null) })).to.throw(TypeError);
		expect(() => this.db.aggregate('cc', { step: () => {}, inverse: length('2') })).to.throw(TypeError);
		expect(() => this.db.aggregate('dd', { step: () => {}, inverse: length(NaN) })).to.throw(TypeError);
		expect(() => this.db.aggregate('ee', { step: () => {}, inverse: length(Infinity) })).to.throw(TypeError);
		expect(() => this.db.aggregate('ff', { step: () => {}, inverse: length(2.000000001) })).to.throw(TypeError);
		expect(() => this.db.aggregate('gg', { step: () => {}, inverse: length(-0.000000001) })).to.throw(TypeError);
		expect(() => this.db.aggregate('hh', { step: () => {}, inverse: length(-2) })).to.throw(TypeError);
		expect(() => this.db.aggregate('ii', { step: () => {}, inverse: length(100.000000001) })).to.throw(TypeError);
		expect(() => this.db.aggregate('jj', { step: () => {}, inverse: length(102) })).to.throw(RangeError);
	});
	it('should register an aggregate function and return the database object', function () {
		const length = x => Object.defineProperty(() => {}, 'length', { value: x });
		expect(this.db.aggregate('a', { step: () => {} })).to.equal(this.db);
		expect(this.db.aggregate('b', { step: function x() {} })).to.equal(this.db);
		expect(this.db.aggregate('c', { step: length(1) })).to.equal(this.db);
		expect(this.db.aggregate('d', { step: length(101) })).to.equal(this.db);
	});
	it('should enable the registered aggregate function to be executed from SQL', function () {
		// numbers and strings
		this.db.aggregate('a', (a, b, c) => a + b + c);
		expect(this.get('a(?, ?, ?)', 2, 10, 50)).to.equal(62);
		expect(this.get('a(?, ?, ?)', 2, 10, null)).to.equal(12);
		expect(this.get('a(?, ?, ?)', 'foo', 'z', 12)).to.equal('fooz12');
		
		// undefined is interpreted as null
		this.db.aggregate('b', (a, b) => null);
		this.db.aggregate('c', (a, b) => {});
		expect(this.get('b(?, ?)', 2, 10)).to.equal(null);
		expect(this.get('c(?, ?)', 2, 10)).to.equal(null);
		
		// buffers
		this.db.aggregate('d', function foo(x) { return x; });
		const input = Buffer.alloc(8).fill(0xdd);
		const output = this.get('d(?)', input);
		expect(input).to.not.equal(output);
		expect(input.equals(output)).to.be.true;
		expect(output.equals(Buffer.alloc(8).fill(0xdd))).to.be.true;
		
		// should not register based on function.name
		expect(() => this.get('foo(?)', input)).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		
		// zero arguments
		this.db.aggregate('e', () => 12);
		expect(this.get('e()')).to.equal(12);
	});
	it('should use a strict number of arguments by default', function () {
		this.db.aggregate('fn', (a, b) => {});
		expect(() => this.get('fn()')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(() => this.get('fn(?)', 4)).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(() => this.get('fn(?, ?, ?)', 4, 8, 3)).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		this.get('fn(?, ?)', 4, 8);
	});
	it('should accept a "varargs" option', function () {
		const fn = (...args) => args.reduce((a, b) => a * b, 1);
		Object.defineProperty(fn, 'length', { value: '-2' });
		this.db.aggregate('fn', { varargs: true }, fn);
		expect(this.get('fn()')).to.equal(1);
		expect(this.get('fn(?)', 7)).to.equal(7);
		expect(this.get('fn(?, ?)', 4, 8)).to.equal(32);
		expect(this.get('fn(?, ?, ?, ?, ?, ?)', 2, 3, 4, 5, 6, 7)).to.equal(5040);
	});
	it('should throw an exception if the database is busy', function () {
		let ranOnce = false;
		for (const x of this.db.prepare('SELECT 2').pluck().iterate()) {
			expect(x).to.equal(2);
			ranOnce = true;
			expect(() => this.db.aggregate('fn', () => {})).to.throw(TypeError);
		}
		expect(ranOnce).to.be.true;
		this.db.aggregate('fn', () => {});
	});
	it('should cause the database to become busy when executing the function', function () {
		let ranOnce = false;
		this.db.aggregate('a', () => {
			ranOnce = true;
			expect(() => this.db.prepare('SELECT 555')).to.throw(TypeError);
			expect(() => this.db.pragma('cache_size')).to.throw(TypeError);
			expect(() => this.db.aggregate('b', () => {})).to.throw(TypeError);
		});
		expect(this.get('a()')).to.equal(null);
		expect(ranOnce).to.be.true;
		this.db.prepare('SELECT 555');
		this.db.pragma('cache_size');
		this.db.aggregate('b', () => {});
	});
	it('should cause the function to throw when returning an invalid value', function () {
		this.db.aggregate('fn', x => ({}));
		expect(() => this.get('fn(?)', 42)).to.throw(TypeError);
	});
	it('should propagate exceptions thrown in the registered function', function () {
		const expectError = (name, exception) => {
			this.db.aggregate(name, () => { throw exception; });
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
		this.db.aggregate('fn', (x) => { if (++i >= 5) throw err; return x; });
		const iterator = this.db.prepare('SELECT fn(value) FROM iterable').pluck().iterate();
		
		let total = 0;
		expect(() => {
			for (const value of iterator) {
				total += value;
				expect(() => this.db.prepare('SELECT fn(value) FROM iterable')).to.throw(TypeError);
			}
		}).to.throw(err);
		
		expect(total).to.equal(1 + 2 + 4 + 8);
		expect(iterator.next()).to.deep.equal({ value: undefined, done: true });
		this.db.prepare('SELECT fn(value) FROM iterable').pluck().iterate().return();
		expect(total).to.equal(1 + 2 + 4 + 8);
	});
	it('should be able to register multiple functions with the same name', function () {
		this.db.aggregate('fn', () => 0);
		this.db.aggregate('fn', (a) => 1);
		this.db.aggregate('fn', (a, b) => 2);
		this.db.aggregate('fn', (a, b, c) => 3);
		this.db.aggregate('fn', (a, b, c, d) => 4);
		expect(this.get('fn()')).to.equal(0);
		expect(this.get('fn(555)')).to.equal(1);
		expect(this.get('fn(555, 555)')).to.equal(2);
		expect(this.get('fn(555, 555, 555)')).to.equal(3);
		expect(this.get('fn(555, 555, 555, 555)')).to.equal(4);
		this.db.aggregate('fn', (a, b) => 'foobar');
		expect(this.get('fn()')).to.equal(0);
		expect(this.get('fn(555)')).to.equal(1);
		expect(this.get('fn(555, 555)')).to.equal('foobar');
		expect(this.get('fn(555, 555, 555)')).to.equal(3);
		expect(this.get('fn(555, 555, 555, 555)')).to.equal(4);
	});
	it('should not be able to affect bound buffers mid-query', function () {
		const input = Buffer.alloc(1024 * 8).fill(0xbb);
		let ranOnce = false;
		this.db.aggregate('fn', () => {
			ranOnce = true;
			input[0] = 2;
		});
		const output = this.get('?, fn()', input);
		expect(ranOnce).to.be.true;
		expect(output.equals(Buffer.alloc(1024 * 8).fill(0xbb))).to.be.true;
	});
	describe('should not affect external environment', function () {
		specify('busy state', function () {
			this.db.aggregate('fn', (x) => {
				expect(() => this.db.prepare('SELECT 555')).to.throw(TypeError);
				return x * 2;
			});
			let ranOnce = false;
			for (const x of this.db.prepare('SELECT fn(555)').pluck().iterate()) {
				ranOnce = true;
				expect(x).to.equal(1110);
				expect(() => this.db.prepare('SELECT 555')).to.throw(TypeError);
			}
			expect(ranOnce).to.be.true;
			this.db.prepare('SELECT 555');
		});
		specify('was_js_error state', function () {
			this.db.prepare('CREATE TABLE data (value INTEGER)').run();
			const stmt = this.db.prepare('SELECT value FROM data');
			this.db.prepare('DROP TABLE data').run();
			
			const err = new Error('foo');
			this.db.aggregate('fn', () => { throw err; });
			
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
	describe('while registering', function () {
		it('should register the given generator function', function () {
			register(function* zb1() {
				yield () => {};
			});
		});
		it('should throw an exception if the yielded function.length is not a positive integer', function () {
			function length(n) {
				const fn = () => {};
				Object.defineProperty(fn, 'length', { value: n });
				return fn;
			}
			expect(() => register(function* zc1() {
				yield length(-1);
			})).to.throw(TypeError);
			expect(() => register(function* zc2() {
				yield length(1.2);
			})).to.throw(TypeError);
			expect(() => register(function* zc3() {
				yield length(Infinity);
			})).to.throw(TypeError);
			expect(() => register(function* zc4() {
				yield length(NaN);
			})).to.throw(TypeError);
			expect(() => register(function* zc5() {
				yield length('2');
			})).to.throw(TypeError);
		});
		it('should throw an exception if the yielded function.length is larger than 127', function () {
			function length(n) {
				const fn = () => {};
				Object.defineProperty(fn, 'length', { value: n });
				return fn;
			}
			expect(() => register(function* zd1() {
				yield length(128);
			})).to.throw(RangeError);
			expect(() => register(function* zd2() {
				yield length(0xe0000000f);
			})).to.throw(RangeError);
			register(function* zd3() { yield length(127); })
		});
		it('should propagate exceptions thrown while getting function.length', function () {
			const err = new Error('foobar');
			expect(() =>
				register(function* ze1() {
					const fn = () => {};
					Object.defineProperty(fn, 'length', { get: () => { throw err; } });
					yield fn;
				})
			).to.throw(err);
		});
		it('should throw an exception if the generator function never yields', function () {
			expect(() => register(function* zf1() {
				// no yield
			})).to.throw(TypeError);
		});
		it('should throw an exception if a non-function is yielded', function () {
			expect(() => register(function* zf1() {
				yield;
			})).to.throw(TypeError);
			expect(() => register(function* zf1() {
				yield 123;
			})).to.throw(TypeError);
			expect(() => register(function* zf1() {
				yield 'foobar';
			})).to.throw(TypeError);
			expect(() => register(function* zf1() {
				yield { length: 0, name: '' };
			})).to.throw(TypeError);
		});
		it('should throw an exception if the generator function yields twice', function () {
			expect(() => register(function* zg1() {
				const fn = () => {};
				yield fn;
				yield fn;
			})).to.throw(TypeError);
		});
		it('should propagate exceptions thrown before yielding', function () {
			const err = new Error('foobar');
			expect(() =>
				register(function* zh1() {
					throw err;
					yield () => {};
				})
			).to.throw(err);
		});
		it('should propagate exceptions thrown after yielding', function () {
			const err = new Error('foobar');
			expect(() =>
				register(function* zi1() {
					yield () => {};
					throw err;
				})
			).to.throw(err);
		});
	});
	describe('before executing', function () {
		it('should throw an exception if the generator function never yields', function () {
			let first = true;
			register(function* zj1() {
				if (first) {
					first = false;
					yield (x) => {};
				}
			});
			expect(() => exec('zj1(x) FROM data')).to.throw(TypeError);
		});
		it('should throw an exception if a non-function is yielded', function () {
			function registerAggregate(name, value) {
				let first = true;
				register({ name }, function* () {
					if (first) {
						first = false;
						yield (x) => {};
					} else {
						yield value;
					}
				});
			}
			registerAggregate('zk1');
			registerAggregate('zk2', 123);
			registerAggregate('zk3', 'foobar');
			registerAggregate('zk4', { length: 0, name: '' });
			registerAggregate('zk5', function (x) {});
			expect(() => exec('zk1(x) FROM data')).to.throw(TypeError);
			expect(() => exec('zk2(x) FROM data')).to.throw(TypeError);
			expect(() => exec('zk3(x) FROM data')).to.throw(TypeError);
			expect(() => exec('zk4(x) FROM data')).to.throw(TypeError);
			exec('zk5(x) FROM data');
		});
		it('should throw an exception if the generator function yields twice', function () {
			let first = true;
			register(function* zl1() {
				if (first) {
					first = false;
					yield (x) => {};
				} else {
					yield (x) => {};
					yield (x) => {};
				}
			});
			expect(() => exec('zl1(x) FROM data')).to.throw(TypeError);
		});
		it('should propagate exceptions thrown before yielding', function () {
			let first = true;
			const err = new Error('foobar');
			register(function* zm1() {
				if (first) {
					first = false;
					yield (x) => {};
				} else {
					throw err;
					yield (x) => {};
				}
			});
			expect(() => exec('zm1(x) FROM data')).to.throw(err);
		});
		it('should propagate exceptions thrown after yielding', function () {
			let first = true;
			const err = new Error('foobar');
			register(function* zma1() {
				if (first) {
					first = false;
					yield (x) => {};
				} else {
					yield (x) => {};
					throw err;
				}
			});
			expect(() => exec('zma1(x) FROM data')).to.throw(err);
		});
		it('should propagate exceptions thrown while getting function.length', function () {
			let first = true;
			const err = new Error('foobar');
			register(function* zn1() {
				if (first) {
					first = false;
					yield (x) => {};
				} else {
					const fn = (x) => {};
					Object.defineProperty(fn, 'length', { get: () => { throw err; } });
					yield fn;
				}
			});
			expect(() => exec('zn1(x) FROM data')).to.throw(err);
		});
		it('should throw an exception if the yielded function.length is inconsistent', function () {
			let first = true;
			register(function* zo1() {
				if (first) {
					first = false;
					yield (x) => {};
				} else {
					yield (x, y) => {};
				}
			});
			expect(() => exec('zo1(x) FROM data')).to.throw(TypeError);
		});
	});
	describe('while executing', function () {
		it('should propagate exceptions thrown in the yielded callback', function () {
			const err = new Error('foobar');
			register(function* zp1() {
				yield (x) => { throw err; };
			});
			expect(() => exec('zp1(x) FROM data')).to.throw(err);
		});
		it('should throw an exception if the generator function returns an invalid value', function () {
			const err = new Error('foobar');
			register(function* zq1() { yield (x) => {}; return {}; });
			register(function* zq2() { yield (x) => {}; return 123; });
			expect(() => exec('zq1(x) FROM data')).to.throw(TypeError);
			exec('zq2(x) FROM data');
		});
		it('should be invoked for each row', function () {
			register(function* zr1() {
				let result = 1;
				yield (x) => { result *= x; };
				return result + 5;
			});
			expect(exec('zr1(x) FROM data')).to.equal(4849850);
		})
		it('should result in the correct value when no rows are passed through', function () {
			register(function* zra1() {
				let result = 5;
				yield (x) => { result = 999; };
				return result + 2;
			});
			expect(exec('zra1(x) FROM empty')).to.equal(7);
		});
		it('should have a strict number of arguments by default', function () {
			register(function* zs1() {
				let result = 0;
				yield (x, y) => { result += x + y };
				return result;
			});
			expect(() => exec('zs1() FROM data')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
			expect(() => exec('zs1(x) FROM data')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
			expect(() => exec('zs1(x, ?, ?) FROM data', 8, 3)).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
			expect(exec('zs1(x, ?) FROM data', 2)).to.equal(89);
		});
		it('should accept a "varargs" option', function () {
			register({ varargs: true }, function* zt1() {
				let result = 0;
				yield (...args) => {
					result += args.reduce((a, b) => a + b, 0);
				};
				return result;
			});
			expect(exec('zt1() FROM data')).to.equal(0);
			expect(exec('zt1(x) FROM data')).to.equal(75);
			expect(exec('zt1(x, x) FROM data')).to.equal(150);
			expect(exec('zt1(x, ?, ?, ?, ?, ?, ?) FROM data', 2, 3, 4, 5, 6, 7)).to.equal(264);
		});
		it('should result in the correct value when * is used as the argument', function () {
			register(function* zu1() {
				let result = 1;
				yield (...args) => {
					expect(args.length).to.equal(0);
					result += 2;
				};
				return result + 1000;
			});
			expect(exec('zu1(*) FROM data')).to.equal(1015);
			expect(exec('zu1() FROM data')).to.equal(1015);
			expect(exec('zu1(*) FROM empty')).to.equal(1001);
			expect(exec('zu1() FROM empty')).to.equal(1001);
		});
	});
});
