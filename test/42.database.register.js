var expect = require('chai').expect;
var Database = require('../.');
var db;

before(function () {
	db = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.db');
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
		var buffer = exec('b4(?)', Buffer.alloc(8).fill(0xdd));
		expect(buffer.equals(Buffer.alloc(8).fill(0xdd))).to.be.ok;
		
		// zero arguments
		register(function b5() {return 12;});
		expect(exec('b5()')).to.equal(12);
	});
	it('should have a strict number of arguments by default', function () {
		register(function c1(a, b) {});
		expect(function () {exec('c1()');}).to.throw(Error);
		expect(function () {exec('c1(?)', 4);}).to.throw(Error);
		expect(function () {exec('c1(?, ?, ?)', 4, 8, 3);}).to.throw(Error);
		exec('c1(?, ?)', 4, 8);
	});
	it('should accept a "name" option', function () {
		register({name: 'd1'}, function (a, b) {return a - b;});
		register({name: 'd2'}, function sdnfjlsd(a, b) {return a * b;});
		expect(exec('d1(?, ?)', 2, 10)).to.equal(-8);
		expect(exec('d2(?, ?)', 2, 10)).to.equal(20);
		expect(function () {exec('sdnfjlsd(?, ?)', 2, 10);}).to.throw(Error);
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
		db.prepare('SELECT 2').pluck().each(function (a) {
			expect(a).to.equal(2);
			ranOnce = true;
			expect(function () {db.register(function xd1() {});}).to.throw(TypeError);
		});
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
		expect(function () {exec('h1(?)', 42);}).to.throw(Error);
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
			throw new TypeError('Expected registered function to throw an exception.');
		}
		expectError('i1', new TypeError('foobar'));
		expectError('i2', new Error('baz'));
		expectError('i3', {yup: 'ok'});
		expectError('i4', 'foobarbazqux');
		expectError('i5', '');
		expectError('i6', null);
		expectError('i7', 123.4);
	});
	it('should not be able to affect bound buffers mid-query', function () {
		var buffer = Buffer.alloc(1024 * 8).fill(0xbb);
		var ranOnce = false;
		register(function j1() {
			ranOnce = true;
			buffer[0] = 2;
		});
		var returned = exec('?, j1()', buffer);
		expect(ranOnce).to.be.true;
		expect(returned.equals(Buffer.alloc(1024 * 8).fill(0xbb))).to.be.ok;
	});
	describe('should not affect external environment', function () {
		specify('busy state', function () {
			var ranOnce = false;
			register(function k1(n) {
				expect(function () {db.prepare('SELECT 555');}).to.throw(TypeError);
				return n * 2;
			});
			db.prepare('SELECT k1(555)').pluck().each(function (n) {
				ranOnce = true;
				expect(n).to.equal(1110);
				expect(function () {db.prepare('SELECT 555');}).to.throw(TypeError);
			});
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
				expect(ex.message.indexOf('SQLite: ')).to.equal(0);
				return;
			}
			throw new TypeError('Expected the statement to throw an exception.');
		});
	});
	describe('should accept the "aggregate" option', function () {
		describe('while registering', function () {
			it('should throw if a generator function is not used');
			it('should register the given generator function');
			it('should have a strict number of arguments by default');
			it('should accept a "varargs" option');
			it('should throw if the yielded function.length is not a positive integer');
			it('should throw if the yielded function.length is larger than 127');
			it('should propagate exceptions thrown while getting function.length');
			it('should throw if the generator function never yields');
			it('should throw if a non-function is yielded');
			it('should throw if the generator function yields twice');
			it('should propagate exceptions thrown before yielding');
			it('should propagate exceptions thrown after yielding');
		});
		describe('after registering', function () {
			it('should throw if the generator function never yields');
			it('should throw if a non-function is yielded');
			it('should throw if the generator function yields twice');
			it('should propagate exceptions thrown before yielding');
			it('should propagate exceptions thrown after yielding');
			it('should propagate exceptions thrown while getting function.length');
			it('should throw if the yielded function.length is inconsistent');
		});
		describe('while executing', function () {
			it('should propagate exceptions thrown in the yielded callback');
			it('should throw if the generator function returns an invalid value');
			it('should result in the correct value when no rows are passed through');
			it('should result in the correct when * is used as the argument');
		});
	});
});
