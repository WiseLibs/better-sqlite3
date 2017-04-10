var expect = require('chai').expect;
var Database = require('../.');
var Int64 = Database.Int64;
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
	it('should throw an exception if a function is not provided', function () {
		expect(function () {db.register()}).to.throw(TypeError);
		expect(function () {db.register(null)}).to.throw(TypeError);
		expect(function () {db.register({})}).to.throw(TypeError);
		expect(function () {db.register('foobar')}).to.throw(TypeError);
	});
	it('should throw an exception if the function name is empty', function () {
		expect(function () {db.register(function () {})}).to.throw(TypeError);
	});
	it('should register the given function', function () {
		register(function a() {});
	});
	it('should execute the registered function in SQL', function () {
		register(function b(a, b, c) {return a + b + c;});
		expect(exec('b(?, ?, ?)', 2, 10, 50)).to.equal(62);
		expect(exec('b(?, ?, ?)', 2, 10, null)).to.equal(12);
		expect(exec('b(?, ?, ?)', 'foo', 'z', 12)).to.equal('fooz12');
		
		register(function c() {});
		expect(exec('c(?, ?)', 2, 10)).to.equal(null);
		
		register(function d(a) {return a;});
		var buffer = exec('d(?, ?)', Buffer.alloc(8).fill(0xdd), 'foo');
		expect(buffer.equals(Buffer.alloc(8).fill(0xdd))).to.be.ok;
		
		register(function e(a) {return new Int64(a + a);});
		expect(exec('e(?)', 42)).to.equal(84);
		
		register(function e2() {return 12;});
		expect(exec('e2()')).to.equal(12);
	});
	it('should accept a "name" option', function () {
		register({name: 'f'}, function (a, b) {return a - b;});
		register({name: 'g'}, function sdnfjlsd(a, b) {return a * b;});
		expect(exec('f(?, ?)', 2, 10)).to.equal(-8);
		expect(exec('g(?, ?)', 2, 10)).to.equal(20);
		expect(function () {exec('sdnfjlsd(?, ?)', 2, 10);}).to.throw(Error);
	});
	it('should accept a "safeIntegers" option', function () {
		register({safeIntegers: true}, function h(a) {return a.low;});
		expect(exec('h(?)', 2)).to.equal(null);
		expect(exec('h(?)', new Int64(2, 2))).to.equal(2);
	});
	it('should accept an "argCount" option', function () {
		register({argCount: 2}, function i(a, b) {return a * b;});
		expect(exec('i(?, ?)', 4, 8)).to.equal(32);
		expect(function () {exec('i(?, ?, ?)', 4, 8, 3);}).to.throw(Error);
		expect(function () {exec('i(?)', 4);}).to.throw(Error);
	});
	it('should throw an exception if name is not a valid string', function () {
		expect(function () {db.register({name: ''}, function () {})}).to.throw(TypeError);
		expect(function () {db.register({name: 123}, function () {})}).to.throw(TypeError);
		expect(function () {db.register({name: {}}, function xa() {})}).to.throw(TypeError);
		expect(function () {db.register({name: new String('abc')}, function xb() {})}).to.throw(TypeError);
	});
	it('should throw an exception if argCount is not a positive integer', function () {
		expect(function () {db.register({argCount: -1}, function xc() {})}).to.throw(TypeError);
		expect(function () {db.register({argCount: 1.2}, function xd() {})}).to.throw(TypeError);
		expect(function () {db.register({argCount: Infinity}, function xe() {})}).to.throw(TypeError);
		expect(function () {db.register({argCount: NaN}, function xf() {})}).to.throw(TypeError);
	});
	it('should throw an exception if argCount is larger than 127', function () {
		expect(function () {db.register({argCount: 128}, function xg() {})}).to.throw(TypeError);
		expect(function () {db.register({argCount: 0xe0000000f}, function xh() {})}).to.throw(TypeError);
	});
	it('should throw an exception if the database is busy', function () {
		var ranOnce = false;
		db.prepare('SELECT 2').pluck().each(function (a) {
			expect(a).to.equal(2);
			ranOnce = true;
			expect(function () {db.register(function xi() {});}).to.throw(TypeError);
		});
		expect(ranOnce).to.be.true;
		db.register(function xi() {});
	});
	it('should cause the database to become busy when executing the function', function () {
		var ranOnce = false;
		register(function j() {
			ranOnce = true;
			expect(function () {db.prepare('SELECT 555');}).to.throw(TypeError);
			expect(function () {db.pragma('cache_size');}).to.throw(TypeError);
			expect(function () {db.register(function xj() {});}).to.throw(TypeError);
		});
		expect(exec('j()')).to.equal(null);
		expect(ranOnce).to.be.true;
		db.prepare('SELECT 555');
		db.pragma('cache_size');
		db.register(function xj() {});
	});
	it('should throw an exception if the function returns an invalid value', function () {
		register(function k(a) {return {};});
		expect(function () {exec('k(?)', 42);}).to.throw(Error);
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
		expectError('l', new TypeError('foobar'));
		expectError('m', new Error('baz'));
		expectError('n', {yup: 'ok'});
		expectError('o', 'foobarbazqux');
		expectError('p', '');
		expectError('q', null);
		expectError('r', 123.4);
	});
	it('should not be able to affect bound buffers mid-query', function () {
		var buffer = Buffer.alloc(1024 * 8).fill(0xbb);
		var ranOnce = false;
		register(function s() {
			ranOnce = true;
			buffer[0] = 2;
		});
		var returned = exec('?, s()', buffer);
		expect(ranOnce).to.be.true;
		expect(returned.equals(Buffer.alloc(1024 * 8).fill(0xbb))).to.be.ok;
	});
	describe('should not affect external environment', function () {
		specify('busy state', function () {
			register(function t(n) {
				expect(function () {db.prepare('SELECT 555');}).to.throw(TypeError);
				return n * 2;
			});
			var ranOnce = false;
			db.prepare('SELECT t(555)').pluck().each(function (n) {
				ranOnce = true;
				expect(n).to.equal(1110);
				expect(function () {db.prepare('SELECT 555');}).to.throw(TypeError);
			});
			expect(ranOnce).to.be.true;
			db.prepare('SELECT 555');
		});
		specify('safeIntegers state');
		specify('was_js_error state');
	});
});
