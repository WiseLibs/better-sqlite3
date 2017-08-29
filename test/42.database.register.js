var expect = require('chai').expect;
var Database = require('../.');
var db;

before(function () {
	db = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.db');
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
	expect(db.register.apply(db, arguments)).to.equal(db);
}
function exec(SQL) {
	return db.prepare('SELECT ' + SQL).pluck().get([].slice.call(arguments, 1));
}

describe('Database#register()', function () {
	it('should throw if a function is not provided', function () {
		expect(function () {db.register()}).to.throw(TypeError);
		expect(function () {db.register(null)}).to.throw(TypeError);
		expect(function () {db.register({})}).to.throw(TypeError);
		expect(function () {db.register('foobar')}).to.throw(TypeError);
	});
	it('should throw if the function name is empty', function () {
		expect(function () {db.register(function () {})}).to.throw(TypeError);
	});
	it('should register the given function', function () {
		register(function a1() {});
	});
	it('should execute the registered function in SQL', function () {
		// numbers and strings
		register(function b1(a, b, c) {return a + b + c;});
		expect(exec('b1(?, ?, ?)', 2, 10, 50)).to.equal(62);
		expect(exec('b1(?, ?, ?)', 2, 10, null)).to.equal(12);
		expect(exec('b1(?, ?, ?)', 'foo', 'z', 12)).to.equal('fooz12');
		
		// undefined is interpreted as null
		register(function b2(a, b) {return null;});
		register(function b3(a, b) {});
		expect(exec('b2(?, ?)', 2, 10)).to.equal(null);
		expect(exec('b3(?, ?)', 2, 10)).to.equal(null);
		
		// buffers
		register(function b4(a) {return a;});
		var buffer = exec('b4(?)', bufferOfSize(8).fill(0xdd));
		expect(buffer.equals(bufferOfSize(8).fill(0xdd))).to.be.ok;
		
		// zero arguments
		register(function b5() {return 12;});
		expect(exec('b5()')).to.equal(12);
	});
	it('should have a strict number of arguments by default', function () {
		register(function c1(a, b) {});
		expect(function () {exec('c1()');}).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(function () {exec('c1(?)', 4);}).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(function () {exec('c1(?, ?, ?)', 4, 8, 3);}).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		exec('c1(?, ?)', 4, 8);
	});
	it('should accept a "name" option', function () {
		register({name: 'd1'}, function (a, b) {return a - b;});
		register({name: 'd2'}, function sdnfjlsd(a, b) {return a * b;});
		expect(exec('d1(?, ?)', 2, 10)).to.equal(-8);
		expect(exec('d2(?, ?)', 2, 10)).to.equal(20);
		expect(function () {exec('sdnfjlsd(?, ?)', 2, 10);}).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
	});
	it('should accept a "varargs" option', function () {
		register({varargs: true}, function f1() {
			return [].slice.call(arguments).reduce(function (a, b) {return a * b;}, 1);
		});
		expect(exec('f1()')).to.equal(1);
		expect(exec('f1(?)', 7)).to.equal(7);
		expect(exec('f1(?, ?)', 4, 8)).to.equal(32);
		expect(exec('f1(?, ?, ?, ?, ?, ?)', 2, 3, 4, 5, 6, 7)).to.equal(5040);
	});
	it('should throw if name is not a valid string', function () {
		expect(function () {db.register({name: ''}, function () {})}).to.throw(TypeError);
		expect(function () {db.register({name: 123}, function () {})}).to.throw(TypeError);
		expect(function () {db.register({name: {}}, function xa1() {})}).to.throw(TypeError);
		expect(function () {db.register({name: new String('abc')}, function xa2() {})}).to.throw(TypeError);
	});
	it('should throw if function.length is not a positive integer', function () {
		function length(n, fn) {
			Object.defineProperty(fn, 'length', {value: n});
			return fn;
		}
		expect(function () {db.register(length(-1, function xb1() {}))}).to.throw(TypeError);
		expect(function () {db.register(length(1.2, function xb2() {}))}).to.throw(TypeError);
		expect(function () {db.register(length(Infinity, function xb3() {}))}).to.throw(TypeError);
		expect(function () {db.register(length(NaN, function xb4() {}))}).to.throw(TypeError);
		expect(function () {db.register(length('2', function xb5() {}))}).to.throw(TypeError);
	});
	it('should throw if function.length is larger than 127', function () {
		function length(n, fn) {
			Object.defineProperty(fn, 'length', {value: n});
			return fn;
		}
		expect(function () {db.register(length(128, function xc1() {}))}).to.throw(RangeError);
		expect(function () {db.register(length(0xe0000000f, function xc2() {}))}).to.throw(RangeError);
		db.register(length(127, function ya1() {}));
	});
	it('should throw if the database is busy', function () {
		var ranOnce = false;
		for (var a of db.prepare('SELECT 2').pluck().iterate()) {
			expect(a).to.equal(2);
			ranOnce = true;
			expect(function () {db.register(function xd1() {});}).to.throw(TypeError);
		}
		expect(ranOnce).to.be.true;
		db.register(function xd2() {});
	});
	it('should cause the database to become busy when executing the function', function () {
		var ranOnce = false;
		register(function g1() {
			ranOnce = true;
			expect(function () {db.prepare('SELECT 555');}).to.throw(TypeError);
			expect(function () {db.pragma('cache_size');}).to.throw(TypeError);
			expect(function () {db.register(function xe1() {});}).to.throw(TypeError);
		});
		expect(exec('g1()')).to.equal(null);
		expect(ranOnce).to.be.true;
		db.prepare('SELECT 555');
		db.pragma('cache_size');
		db.register(function xe2() {});
	});
	it('should throw if the function returns an invalid value', function () {
		register(function h1(a) {return {};});
		expect(function () {exec('h1(?)', 42);}).to.throw(TypeError);
	});
	it('should propagate exceptions thrown in the registered function', function () {
		function expectError(name, exception) {
			register({name: name}, function () {throw exception;});
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
		expectError('i3', {yup: 'ok'});
		expectError('i4', 'foobarbazqux');
		expectError('i5', '');
		expectError('i6', null);
		expectError('i7', 123.4);
	});
	it('should close a statement iterator that caused its function to throw', function () {
		var i = 0;
		var err = new Error('foo');
		register(function throwsIterator1(x) {if (++i >= 5) throw err; return x});
		db.prepare('CREATE TABLE iterable (value INTEGER)').run();
		db.prepare('INSERT INTO iterable WITH RECURSIVE temp(a) AS (SELECT 1 UNION ALL SELECT a * 2 FROM temp LIMIT 10) SELECT * FROM temp').run();
		var iterator = db.prepare('SELECT throwsIterator1(value) FROM iterable').pluck().iterate();
		var total = 0;
		expect(function () {
			for (var value of iterator) {
				total += value;
				expect(function () {db.prepare('SELECT throwsIterator1(value) FROM iterable');}).to.throw(TypeError);
			}
		}).to.throw(err);
		expect(total).to.equal(1 + 2 + 4 + 8);
		expect(iterator.next()).to.deep.equal({value: undefined, done: true});
		db.prepare('SELECT throwsIterator1(value) FROM iterable').pluck().iterate().return();
		expect(total).to.equal(1 + 2 + 4 + 8);
	});
	it('should be able to register multiple functions with the same name', function () {
		register(function ia1() {return 0;});
		register(function ia1(a) {return 1;});
		register(function ia1(a, b) {return 2;});
		register(function ia1(a, b, c) {return 3;});
		register(function ia1(a, b, c, d) {return 4;});
		expect(exec('ia1()')).to.equal(0);
		expect(exec('ia1(555)')).to.equal(1);
		expect(exec('ia1(555, 555)')).to.equal(2);
		expect(exec('ia1(555, 555, 555)')).to.equal(3);
		expect(exec('ia1(555, 555, 555, 555)')).to.equal(4);
		register(function ia1(a, b) {return 'foobar';});
		expect(exec('ia1()')).to.equal(0);
		expect(exec('ia1(555)')).to.equal(1);
		expect(exec('ia1(555, 555)')).to.equal('foobar');
		expect(exec('ia1(555, 555, 555)')).to.equal(3);
		expect(exec('ia1(555, 555, 555, 555)')).to.equal(4);
	});
	it('should not be able to affect bound buffers mid-query', function () {
		var buffer = bufferOfSize(1024 * 8).fill(0xbb);
		var ranOnce = false;
		register(function j1() {
			ranOnce = true;
			buffer[0] = 2;
		});
		var returned = exec('?, j1()', buffer);
		expect(ranOnce).to.be.true;
		expect(returned.equals(bufferOfSize(1024 * 8).fill(0xbb))).to.be.ok;
	});
	describe('should not affect external environment', function () {
		specify('busy state', function () {
			var ranOnce = false;
			register(function k1(n) {
				expect(function () {db.prepare('SELECT 555');}).to.throw(TypeError);
				return n * 2;
			});
			for (var n of db.prepare('SELECT k1(555)').pluck().iterate()) {
				ranOnce = true;
				expect(n).to.equal(1110);
				expect(function () {db.prepare('SELECT 555');}).to.throw(TypeError);
			}
			expect(ranOnce).to.be.true;
			db.prepare('SELECT 555');
		});
		specify('was_js_error state', function () {
			db.prepare('CREATE TABLE abcxyz (value INTEGER)').run();
			var stmt = db.prepare('SELECT value FROM abcxyz');
			db.prepare('DROP TABLE abcxyz').run();
			var err = new Error('foobarbaz');
			register(function m1() {throw err;});
			expect(function () {db.prepare('SELECT m1()').get();}).to.throw(err);
			try {stmt.get();} catch (ex) {
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
					yield function () {};
				});
			});
			it('should throw if the yielded function.length is not a positive integer', function () {
				function length(n) {
					var fn = function () {};
					Object.defineProperty(fn, 'length', {value: n});
					return fn;
				}
				expect(function () {register(function* zc1() {
					yield length(-1);
				})}).to.throw(TypeError);
				expect(function () {register(function* zc2() {
					yield length(1.2);
				})}).to.throw(TypeError);
				expect(function () {register(function* zc3() {
					yield length(Infinity);
				})}).to.throw(TypeError);
				expect(function () {register(function* zc4() {
					yield length(NaN);
				})}).to.throw(TypeError);
				expect(function () {register(function* zc5() {
					yield length('2');
				})}).to.throw(TypeError);
			});
			it('should throw if the yielded function.length is larger than 127', function () {
				function length(n) {
					var fn = function () {};
					Object.defineProperty(fn, 'length', {value: n});
					return fn;
				}
				expect(function () {register(function* zd1() {
					yield length(128);
				})}).to.throw(RangeError);
				expect(function () {register(function* zd2() {
					yield length(0xe0000000f);
				})}).to.throw(RangeError);
				register(function* zd3() {yield length(127);})
			});
			it('should propagate exceptions thrown while getting function.length', function () {
				var err = new Error('foobar');
				expect(function () {
					register(function* ze1() {
						var fn = function () {};
						Object.defineProperty(fn, 'length', {get: function () {
							throw err;
						}});
						yield fn;
					});
				}).to.throw(err);
			});
			it('should throw if the generator function never yields', function () {
				expect(function () {register(function* zf1() {
					// no yield
				})}).to.throw(TypeError);
			});
			it('should throw if a non-function is yielded', function () {
				expect(function () {register(function* zf1() {
					yield;
				})}).to.throw(TypeError);
				expect(function () {register(function* zf1() {
					yield 123;
				})}).to.throw(TypeError);
				expect(function () {register(function* zf1() {
					yield 'foobar';
				})}).to.throw(TypeError);
				expect(function () {register(function* zf1() {
					yield {length: 0, name: ''};
				})}).to.throw(TypeError);
			});
			it('should throw if the generator function yields twice', function () {
				expect(function () {register(function* zg1() {
					var fn = function () {};
					yield fn;
					yield fn;
				})}).to.throw(TypeError);
			});
			it('should propagate exceptions thrown before yielding', function () {
				var err = new Error('foobar');
				expect(function () {
					register(function* zh1() {
						throw err;
						yield function () {};
					});
				}).to.throw(err);
			});
			it('should propagate exceptions thrown after yielding', function () {
				var err = new Error('foobar');
				expect(function () {
					register(function* zi1() {
						yield function () {};
						throw err;
					});
				}).to.throw(err);
			});
		});
		describe('before executing', function () {
			it('should throw if the generator function never yields', function () {
				var first = true;
				register(function* zj1() {
					if (first) {
						first = false;
						yield function (x) {};
					}
				});
				expect(function () {exec('zj1(x) FROM data');}).to.throw(TypeError);
			});
			it('should throw if a non-function is yielded', function () {
				function registerAggregate(name, value) {
					var first = true;
					register({name: name}, function* () {
						if (first) {
							first = false;
							yield function (x) {};
						} else {
							yield value;
						}
					});
				}
				registerAggregate('zk1');
				registerAggregate('zk2', 123);
				registerAggregate('zk3', 'foobar');
				registerAggregate('zk4', {length: 0, name: ''});
				registerAggregate('zk5', function (x) {});
				expect(function () {exec('zk1(x) FROM data');}).to.throw(TypeError);
				expect(function () {exec('zk2(x) FROM data');}).to.throw(TypeError);
				expect(function () {exec('zk3(x) FROM data');}).to.throw(TypeError);
				expect(function () {exec('zk4(x) FROM data');}).to.throw(TypeError);
				exec('zk5(x) FROM data');
			});
			it('should throw if the generator function yields twice', function () {
				var first = true;
				register(function* zl1() {
					if (first) {
						first = false;
						yield function (x) {};
					} else {
						yield function (x) {};
						yield function (x) {};
					}
				});
				expect(function () {exec('zl1(x) FROM data');}).to.throw(TypeError);
			});
			it('should propagate exceptions thrown before yielding', function () {
				var first = true;
				var err = new Error('foobar');
				register(function* zm1() {
					if (first) {
						first = false;
						yield function (x) {};
					} else {
						throw err;
						yield function (x) {};
					}
				});
				expect(function () {exec('zm1(x) FROM data');}).to.throw(err);
			});
			it('should propagate exceptions thrown after yielding', function () {
				var first = true;
				var err = new Error('foobar');
				register(function* zma1() {
					if (first) {
						first = false;
						yield function (x) {};
					} else {
						yield function (x) {};
						throw err;
					}
				});
				expect(function () {exec('zma1(x) FROM data');}).to.throw(err);
			});
			it('should propagate exceptions thrown while getting function.length', function () {
				var first = true;
				var err = new Error('foobar');
				register(function* zn1() {
					if (first) {
						first = false;
						yield function (x) {};
					} else {
						var fn = function (x) {};
						Object.defineProperty(fn, 'length', {get: function () {
							throw err;
						}});
						yield fn;
					}
				});
				expect(function () {exec('zn1(x) FROM data');}).to.throw(err);
			});
			it('should throw if the yielded function.length is inconsistent', function () {
				var first = true;
				register(function* zo1() {
					if (first) {
						first = false;
						yield function (x) {};
					} else {
						yield function (x, y) {};
					}
				});
				expect(function () {exec('zo1(x) FROM data');}).to.throw(TypeError);
			});
		});
		describe('while executing', function () {
			it('should propagate exceptions thrown in the yielded callback', function () {
				var err = new Error('foobar');
				register(function* zp1() {
					yield function (x) {throw err;};
				});
				expect(function () {exec('zp1(x) FROM data');}).to.throw(err);
			});
			it('should throw if the generator function returns an invalid value', function () {
				var err = new Error('foobar');
				register(function* zq1() {yield function (x) {}; return {};});
				register(function* zq2() {yield function (x) {}; return 123;});
				expect(function () {exec('zq1(x) FROM data');}).to.throw(TypeError);
				exec('zq2(x) FROM data');
			});
			it('should be invoked for each row', function () {
				register(function* zr1() {
					var result = 1;
					yield function (x) {result *= x;};
					return result + 5;
				});
				expect(exec('zr1(x) FROM data')).to.equal(4849850);
			})
			it('should result in the correct value when no rows are passed through', function () {
				register(function* zra1() {
					var result = 5;
					yield function (x) {result = 999;};
					return result + 2;
				});
				expect(exec('zra1(x) FROM empty')).to.equal(7);
			});
			it('should have a strict number of arguments by default', function () {
				register(function* zs1() {
					var result = 0;
					yield function (x, y) {result += x + y};
					return result;
				});
				expect(function () {exec('zs1() FROM data');}).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
				expect(function () {exec('zs1(x) FROM data');}).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
				expect(function () {exec('zs1(x, ?, ?) FROM data', 8, 3);}).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
				expect(exec('zs1(x, ?) FROM data', 2)).to.equal(89);
			});
			it('should accept a "varargs" option', function () {
				register({varargs: true}, function* zt1() {
					var result = 0;
					yield function () {
						result += [].slice.call(arguments).reduce(function (a, b) {return a + b;}, 0);
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
					var result = 1;
					yield function () {
						expect(arguments.length).to.equal(0);
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

function bufferOfSize(size) {
	return Buffer.alloc ? Buffer.alloc(+size) : new Buffer(+size);
}
