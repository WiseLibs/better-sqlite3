'use strict';
const { expect } = require('chai');
const Database = require('../.');
const db = new Database(require('./util').next());

before(function () {
	db.prepare('CREATE TABLE data (x)').run();
	db.prepare('CREATE TABLE empty (x)').run();
	db.prepare('INSERT INTO data VALUES (?)').run(3);
	db.prepare('INSERT INTO data VALUES (?)').run(5);
	db.prepare('INSERT INTO data VALUES (?)').run(7);
	db.prepare('INSERT INTO data VALUES (?)').run(11);
	db.prepare('INSERT INTO data VALUES (?)').run(13);
	db.prepare('INSERT INTO data VALUES (?)').run(17);
	db.prepare('INSERT INTO data VALUES (?)').run(19);
});

function register() {
	expect(db.register(...arguments)).to.equal(db);
}
function exec(SQL, ...args) {
	return db.prepare(`SELECT ${SQL}`).pluck().get(args);
}

describe('Database#register()', function () {
	it('should throw if a function is not provided', function () {
		expect(() => db.register()).to.throw(TypeError);
		expect(() => db.register(null)).to.throw(TypeError);
		expect(() => db.register({})).to.throw(TypeError);
		expect(() => db.register('foobar')).to.throw(TypeError);
	});
	it('should throw if the function name is empty', function () {
		expect(() => db.register(function () {})).to.throw(TypeError);
	});
	it('should register the given function', function () {
		register(function a1() {});
	});
	it('should execute the registered function in SQL', function () {
		// numbers and strings
		register(function b1(a, b, c) { return a + b + c; });
		expect(exec('b1(?, ?, ?)', 2, 10, 50)).to.equal(62);
		expect(exec('b1(?, ?, ?)', 2, 10, null)).to.equal(12);
		expect(exec('b1(?, ?, ?)', 'foo', 'z', 12)).to.equal('fooz12');
		
		// undefined is interpreted as null
		register(function b2(a, b) { return null; });
		register(function b3(a, b) {});
		expect(exec('b2(?, ?)', 2, 10)).to.equal(null);
		expect(exec('b3(?, ?)', 2, 10)).to.equal(null);
		
		// buffers
		register(function b4(a) { return a; });
		const buffer = exec('b4(?)', Buffer.alloc(8).fill(0xdd));
		expect(buffer.equals(Buffer.alloc(8).fill(0xdd))).to.be.ok;
		
		// zero arguments
		register(function b5() { return 12; });
		expect(exec('b5()')).to.equal(12);
	});
	it('should have a strict number of arguments by default', function () {
		register(function c1(a, b) {});
		expect(() => exec('c1()')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(() => exec('c1(?)', 4)).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(() => exec('c1(?, ?, ?)', 4, 8, 3)).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		exec('c1(?, ?)', 4, 8);
	});
	it('should accept a "name" option', function () {
		register({ name: 'd1' }, function (a, b) { return a - b; });
		register({ name: 'd2' }, function sdnfjlsd(a, b) { return a * b; });
		expect(exec('d1(?, ?)', 2, 10)).to.equal(-8);
		expect(exec('d2(?, ?)', 2, 10)).to.equal(20);
		expect(() => exec('sdnfjlsd(?, ?)', 2, 10)).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
	});
	it('should accept a "varargs" option', function () {
		register({ varargs: true }, function f1(...args) {
			return args.reduce((a, b) => a * b, 1);
		});
		expect(exec('f1()')).to.equal(1);
		expect(exec('f1(?)', 7)).to.equal(7);
		expect(exec('f1(?, ?)', 4, 8)).to.equal(32);
		expect(exec('f1(?, ?, ?, ?, ?, ?)', 2, 3, 4, 5, 6, 7)).to.equal(5040);
	});
	it('should throw if name is not a valid string', function () {
		expect(() => db.register({ name: '' }, function () {})).to.throw(TypeError);
		expect(() => db.register({ name: 123 }, function () {})).to.throw(TypeError);
		expect(() => db.register({ name: {} }, function xa1() {})).to.throw(TypeError);
		expect(() => db.register({ name: new String('abc') }, function xa2() {})).to.throw(TypeError);
	});
	it('should throw if function.length is not a positive integer', function () {
		function length(n, fn) {
			Object.defineProperty(fn, 'length', { value: n });
			return fn;
		}
		expect(() => db.register(length(-1, function xb1() {}))).to.throw(TypeError);
		expect(() => db.register(length(1.2, function xb2() {}))).to.throw(TypeError);
		expect(() => db.register(length(Infinity, function xb3() {}))).to.throw(TypeError);
		expect(() => db.register(length(NaN, function xb4() {}))).to.throw(TypeError);
		expect(() => db.register(length('2', function xb5() {}))).to.throw(TypeError);
	});
	it('should throw if function.length is larger than 127', function () {
		function length(n, fn) {
			Object.defineProperty(fn, 'length', { value: n });
			return fn;
		}
		expect(() => db.register(length(128, function xc1() {}))).to.throw(RangeError);
		expect(() => db.register(length(0xe0000000f, function xc2() {}))).to.throw(RangeError);
		db.register(length(127, function ya1() {}));
	});
	it('should throw if the database is busy', function () {
		let ranOnce = false;
		for (const a of db.prepare('SELECT 2').pluck().iterate()) {
			expect(a).to.equal(2);
			ranOnce = true;
			expect(() => db.register(function xd1() {})).to.throw(TypeError);
		}
		expect(ranOnce).to.be.true;
		db.register(function xd2() {});
	});
	it('should cause the database to become busy when executing the function', function () {
		let ranOnce = false;
		register(function g1() {
			ranOnce = true;
			expect(() => db.prepare('SELECT 555')).to.throw(TypeError);
			expect(() => db.pragma('cache_size')).to.throw(TypeError);
			expect(() => db.register(function xe1() {})).to.throw(TypeError);
		});
		expect(exec('g1()')).to.equal(null);
		expect(ranOnce).to.be.true;
		db.prepare('SELECT 555');
		db.pragma('cache_size');
		db.register(function xe2() {});
	});
	it('should throw if the function returns an invalid value', function () {
		register(function h1(a) { return {}; });
		expect(() => exec('h1(?)', 42)).to.throw(TypeError);
	});
	it('should propagate exceptions thrown in the registered function', function () {
		function expectError(name, exception) {
			register({ name }, function () { throw exception; });
			try {
				exec(name + '()');
			} catch (ex) {
				expect(ex).to.equal(exception);
				return;
			}
			throw new TypeError('Expected registered function to throw an exception');
		}
		expectError('i1', new TypeError('foobar'));
		expectError('i2', new Error('baz'));
		expectError('i3', { yup: 'ok' });
		expectError('i4', 'foobarbazqux');
		expectError('i5', '');
		expectError('i6', null);
		expectError('i7', 123.4);
	});
	it('should close a statement iterator that caused its function to throw', function () {
		const err = new Error('foo');
		let i = 0;
		register(function throwsIterator1(x) { if (++i >= 5) throw err; return x; });
		db.prepare('CREATE TABLE iterable (value INTEGER)').run();
		db.prepare('INSERT INTO iterable WITH RECURSIVE temp(a) AS (SELECT 1 UNION ALL SELECT a * 2 FROM temp LIMIT 10) SELECT * FROM temp').run();
		const iterator = db.prepare('SELECT throwsIterator1(value) FROM iterable').pluck().iterate();
		let total = 0;
		expect(() => {
			for (const value of iterator) {
				total += value;
				expect(() => db.prepare('SELECT throwsIterator1(value) FROM iterable')).to.throw(TypeError);
			}
		}).to.throw(err);
		expect(total).to.equal(1 + 2 + 4 + 8);
		expect(iterator.next()).to.deep.equal({ value: undefined, done: true });
		db.prepare('SELECT throwsIterator1(value) FROM iterable').pluck().iterate().return();
		expect(total).to.equal(1 + 2 + 4 + 8);
	});
	it('should be able to register multiple functions with the same name', function () {
		register(function ia1() { return 0; });
		register(function ia1(a) { return 1; });
		register(function ia1(a, b) { return 2; });
		register(function ia1(a, b, c) { return 3; });
		register(function ia1(a, b, c, d) { return 4; });
		expect(exec('ia1()')).to.equal(0);
		expect(exec('ia1(555)')).to.equal(1);
		expect(exec('ia1(555, 555)')).to.equal(2);
		expect(exec('ia1(555, 555, 555)')).to.equal(3);
		expect(exec('ia1(555, 555, 555, 555)')).to.equal(4);
		register(function ia1(a, b) { return 'foobar'; });
		expect(exec('ia1()')).to.equal(0);
		expect(exec('ia1(555)')).to.equal(1);
		expect(exec('ia1(555, 555)')).to.equal('foobar');
		expect(exec('ia1(555, 555, 555)')).to.equal(3);
		expect(exec('ia1(555, 555, 555, 555)')).to.equal(4);
	});
	it('should not be able to affect bound buffers mid-query', function () {
		const buffer = Buffer.alloc(1024 * 8).fill(0xbb);
		let ranOnce = false;
		register(function j1() {
			ranOnce = true;
			buffer[0] = 2;
		});
		const returned = exec('?, j1()', buffer);
		expect(ranOnce).to.be.true;
		expect(returned.equals(Buffer.alloc(1024 * 8).fill(0xbb))).to.be.ok;
	});
	describe('should not affect external environment', function () {
		specify('busy state', function () {
			let ranOnce = false;
			register(function k1(n) {
				expect(() => db.prepare('SELECT 555')).to.throw(TypeError);
				return n * 2;
			});
			for (const n of db.prepare('SELECT k1(555)').pluck().iterate()) {
				ranOnce = true;
				expect(n).to.equal(1110);
				expect(() => db.prepare('SELECT 555')).to.throw(TypeError);
			}
			expect(ranOnce).to.be.true;
			db.prepare('SELECT 555');
		});
		specify('was_js_error state', function () {
			db.prepare('CREATE TABLE abcxyz (value INTEGER)').run();
			const stmt = db.prepare('SELECT value FROM abcxyz');
			db.prepare('DROP TABLE abcxyz').run();
			const err = new Error('foobarbaz');
			register(function m1() { throw err; });
			expect(() => db.prepare('SELECT m1()').get()).to.throw(err);
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
	describe('should be able to register aggregate functions', function () {
		describe('while registering', function () {
			it('should register the given generator function', function () {
				register(function* zb1() {
					yield () => {};
				});
			});
			it('should throw if the yielded function.length is not a positive integer', function () {
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
			it('should throw if the yielded function.length is larger than 127', function () {
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
			it('should throw if the generator function never yields', function () {
				expect(() => register(function* zf1() {
					// no yield
				})).to.throw(TypeError);
			});
			it('should throw if a non-function is yielded', function () {
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
			it('should throw if the generator function yields twice', function () {
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
			it('should throw if the generator function never yields', function () {
				let first = true;
				register(function* zj1() {
					if (first) {
						first = false;
						yield (x) => {};
					}
				});
				expect(() => exec('zj1(x) FROM data')).to.throw(TypeError);
			});
			it('should throw if a non-function is yielded', function () {
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
			it('should throw if the generator function yields twice', function () {
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
			it('should throw if the yielded function.length is inconsistent', function () {
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
			it('should throw if the generator function returns an invalid value', function () {
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
});
