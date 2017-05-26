var expect = require('chai').expect;
var Database = require('../.');
var Int64 = Database.Int64;
var db;
var db2;

before(function () {
	db = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.1.db');
	db2 = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.2.db');
	db.prepare('CREATE TABLE entries (a INTEGER, b REAL, c TEXT)').run();
	db2.prepare('CREATE TABLE entries (a INTEGER, b REAL, c TEXT)').run();
});

describe('Int64', function () {
	it('should throw if the low and high components are not numbers', function () {
		expect(function () {new Int64()}).to.throw(TypeError);
		expect(function () {new Int64('123', '123')}).to.throw(TypeError);
		expect(function () {new Int64('123')}).to.throw(TypeError);
		expect(function () {new Int64(null, null)}).to.throw(TypeError);
		expect(function () {new Int64(new Number(123), new Number(123))}).to.throw(TypeError);
		expect(function () {new Int64(123, undefined)}).to.throw(TypeError);
		expect(function () {Int64()}).to.throw(TypeError);
		expect(function () {Int64('123', '123')}).to.throw(TypeError);
		expect(function () {Int64('123')}).to.throw(TypeError);
		expect(function () {Int64(null, null)}).to.throw(TypeError);
		expect(function () {Int64(new Number(123), new Number(123))}).to.throw(TypeError);
		expect(function () {Int64(123, undefined)}).to.throw(TypeError);
		new Int64(123, 123);
		Int64(123, 123);
	});
	it('should throw if the low and high components are not 32-bit integers', function () {
		expect(function () {new Int64(123, 12.2)}).to.throw(TypeError);
		expect(function () {new Int64(123, 2147483648)}).to.throw(TypeError);
		expect(function () {new Int64(123, -2147483649)}).to.throw(TypeError);
		expect(function () {new Int64(12.2, 123)}).to.throw(TypeError);
		expect(function () {new Int64(2147483648, 123)}).to.throw(TypeError);
		expect(function () {new Int64(-2147483649, 123)}).to.throw(TypeError);
		expect(function () {new Int64(NaN, 123)}).to.throw(TypeError);
		expect(function () {new Int64(Infinity, 123)}).to.throw(TypeError);
		expect(function () {new Int64(-Infinity, 123)}).to.throw(TypeError);
		expect(function () {Int64(123, 12.2)}).to.throw(TypeError);
		expect(function () {Int64(123, 2147483648)}).to.throw(TypeError);
		expect(function () {Int64(123, -2147483649)}).to.throw(TypeError);
		expect(function () {Int64(12.2, 123)}).to.throw(TypeError);
		expect(function () {Int64(2147483648, 123)}).to.throw(TypeError);
		expect(function () {Int64(-2147483649, 123)}).to.throw(TypeError);
		expect(function () {Int64(NaN, 123)}).to.throw(TypeError);
		expect(function () {Int64(Infinity, 123)}).to.throw(TypeError);
		expect(function () {Int64(-Infinity, 123)}).to.throw(TypeError);
	});
	it('should expose the low and high components via getters', function () {
		var int = new Int64(123, 123);
		expect(int.low).to.equal(123);
		expect(int.high).to.equal(123);
		int.low = 22;
		int.high = 22;
		expect(int.low).to.equal(123);
		expect(int.high).to.equal(123);
	});
	it('should default the high component to zero, if not provided', function () {
		var int = new Int64(123);
		expect(int.low).to.equal(123);
		expect(int.high).to.equal(0);
	});
	it('should reveal the full value when cast to a string', function () {
		expect(String(new Int64(123))).to.equal('123');
		expect(String(new Int64(123, 123))).to.equal('528280977531');
		expect(String(new Int64(123, -123))).to.equal('-528280977285');
		expect(String(new Int64(4243423, 234234234))).to.equal('1006028374637854687');
	});
	it('should cast to its full value when the number is a safe number', function () {
		expect(+(new Int64(123))).to.equal(123);
		expect(+(new Int64(123, 123))).to.equal(528280977531);
		expect(+(new Int64(123, -123))).to.equal(-528280977285);
	});
	it('should throw a RangeError when casting to a number is not safe', function () {
		expect(function () {+(new Int64(4243423, 234234234))}).to.throw(RangeError);
	});
	it('should compare to other Int64s and other values via .equals()', function () {
		var int = new Int64(123, 123);
		expect(int.equals(int)).to.be.true;
		expect(int.equals(new Int64(123, 123))).to.be.true;
		expect(int.equals({low: 123, high: 123})).to.be.true;
		expect(int.equals(528280977531)).to.be.true;
		expect(int.equals('528280977531')).to.be.true;
		int = new Int64(4243436, 234234234);
		expect(int.equals(new Int64(4243436, 234234234))).to.be.true;
		expect(int.equals(String(int))).to.be.true;
		expect(int.equals(+String(int))).to.be.false;
	});
	it('should bind to statements and transactions', function () {
		var int = new Int64(4243423, 234234234);
		db.prepare('INSERT INTO entries VALUES (?, ?, ?)').run(int, int, int);
		db.transaction(['INSERT INTO entries VALUES (?, ?, ?)']).run(int, int, int);
		db.prepare('INSERT INTO entries VALUES (?, ?, ?)').bind(int, int, int).run();
		db.transaction(['INSERT INTO entries VALUES (?, ?, ?)']).bind(int, int, int).run();
		
		db2.prepare('INSERT INTO entries VALUES (?, ?, ?)').run(int, int, int);
		db2.transaction(['INSERT INTO entries VALUES (?, ?, ?)']).run(int, int, int);
		db2.prepare('INSERT INTO entries VALUES (?, ?, ?)').bind(int, int, int).run();
		db2.transaction(['INSERT INTO entries VALUES (?, ?, ?)']).bind(int, int, int).run();
	});
	it('should be allowed as a return value in registered functions', function () {
		db.register(function returnsInt64(a) {return new Int64(a + a);});
		expect(db.prepare('SELECT returnsInt64(?)').pluck().get(42)).to.equal(84);
	});
	it('should get returned by operations after setting .safeIntegers()', function () {
		var int = new Int64(4243423, 234234234);
		var stmt = db.prepare('SELECT a FROM entries').pluck();
		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt.safeIntegers().get()).to.deep.equal(int);
		expect(stmt.get()).to.deep.equal(int);
		expect(stmt.safeIntegers(false).get()).to.equal(1006028374637854700);
		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt.safeIntegers(true).get()).to.deep.equal(int);
		expect(stmt.get()).to.deep.equal(int);
		
		stmt = db.prepare('SELECT b FROM entries').pluck();
		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt.safeIntegers().get()).to.equal(1006028374637854700);
		
		stmt = db.prepare('SELECT c FROM entries').pluck();
		expect(stmt.get()).to.equal('1006028374637854687');
		expect(stmt.safeIntegers().get()).to.equal('1006028374637854687');
		
		var lastRowid = db.prepare('SELECT rowid FROM entries ORDER BY rowid DESC').pluck().get();
		stmt = db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		expect(stmt.run(int, int, int).lastInsertROWID).to.equal(++lastRowid);
		expect(stmt.safeIntegers().run(int, int, int).lastInsertROWID).to.deep.equal(new Int64(++lastRowid));
		expect(stmt.run(int, int, int).lastInsertROWID).to.deep.equal(new Int64(++lastRowid));
		expect(stmt.safeIntegers(false).run(int, int, int).lastInsertROWID).to.equal(++lastRowid);
		
		var trans = db.transaction(['INSERT INTO entries VALUES (?, ?, ?)']);
		expect(trans.run(int, int, int).lastInsertROWID).to.equal(++lastRowid);
		expect(trans.safeIntegers().run(int, int, int).lastInsertROWID).to.deep.equal(new Int64(++lastRowid));
		expect(trans.run(int, int, int).lastInsertROWID).to.deep.equal(new Int64(++lastRowid));
		expect(trans.safeIntegers(false).run(int, int, int).lastInsertROWID).to.equal(++lastRowid);
	});
	it('should get passed to functions registered with the "safeIntegers" option', function () {
		db.register({safeIntegers: true}, function customfunc(a) {return a.low;});
		expect(db.prepare('SELECT customfunc(?)').pluck().get(2)).to.equal(null);
		expect(db.prepare('SELECT customfunc(?)').pluck().get(new Int64(2, 2))).to.equal(2);
	});
	it('should be able to change the default setting on the database', function () {
		var arg;
		var int = new Int64(4243423, 234234234);
		function customFunctionArg(options, dontRegister) {
			dontRegister || db.register(options, function (a) {arg = a;});
			db.prepare('SELECT ' + options.name + '(?)').get(int);
			return arg;
		}
		db.defaultSafeIntegers(true);
		
		var stmt = db.prepare('SELECT a FROM entries').pluck();
		expect(stmt.get()).to.deep.equal(int);
		expect(stmt.safeIntegers(false).get()).to.equal(1006028374637854700);
		expect(customFunctionArg({name: 'a1'})).to.deep.equal(int);
		expect(customFunctionArg({name: 'a2', safeIntegers: false})).to.equal(1006028374637854700);
		
		db.defaultSafeIntegers(false);
		
		var stmt2 = db.prepare('SELECT a FROM entries').pluck();
		expect(stmt2.get()).to.equal(1006028374637854700);
		expect(stmt2.safeIntegers().get()).to.deep.equal(int);
		expect(customFunctionArg({name: 'a3'})).to.equal(1006028374637854700);
		expect(customFunctionArg({name: 'a4', safeIntegers: true})).to.deep.equal(int);
		
		db.defaultSafeIntegers();
		
		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt2.get()).to.deep.equal(int);
		expect(customFunctionArg({name: 'a1'}, true)).to.deep.equal(int);
		expect(customFunctionArg({name: 'a2'}, true)).to.equal(1006028374637854700);
		expect(customFunctionArg({name: 'a3'}, true)).to.equal(1006028374637854700);
		expect(customFunctionArg({name: 'a4'}, true)).to.deep.equal(int);
		
		var stmt3 = db.prepare('SELECT a FROM entries').pluck();
		expect(stmt3.get()).to.deep.equal(int);
		expect(stmt3.safeIntegers(false).get()).to.equal(1006028374637854700);
		expect(customFunctionArg({name: 'a5'})).to.deep.equal(int);
		expect(customFunctionArg({name: 'a6', safeIntegers: false})).to.equal(1006028374637854700);
	});
	it('should not be able to invoke .safeIntegers() while the database is busy', function () {
		var ranOnce = false;
		var stmt1 = db.prepare('SELECT * FROM entries LIMIT 10');
		var stmt2 = db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		stmt1.each(function () {
			ranOnce = true;
			expect(function () {stmt1.safeIntegers();}).to.throw(TypeError);
			expect(function () {stmt2.safeIntegers();}).to.throw(TypeError);
			expect(function () {stmt1.safeIntegers(false);}).to.throw(TypeError);
			expect(function () {stmt2.safeIntegers(false);}).to.throw(TypeError);
		});
		expect(ranOnce).to.be.true;
	});
});
