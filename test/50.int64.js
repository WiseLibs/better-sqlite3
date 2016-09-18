var expect = require('chai').expect;
var Database = require('../.');
var Int64 = Database.Int64;
var db;
var db2;

before(function (done) {
	db = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.1.db');
	db2 = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.2.db');
	var openCount = 0;
	db.on('open', opened);
	db2.on('open', opened);
	function opened() {
		if (++openCount === 2) {
			db.prepare('CREATE TABLE entries (a INTEGER, b REAL, c TEXT)').run();
			db2.prepare('CREATE TABLE entries (a INTEGER, b REAL, c TEXT)').run();
			done();
		}
	}
});

describe('Int64', function () {
	it('should throw if the low and high components are not numbers', function () {
		expect(function () {new Int64()}).to.throw(TypeError);
		expect(function () {new Int64('123', '123')}).to.throw(TypeError);
		expect(function () {new Int64('123')}).to.throw(TypeError);
		expect(function () {new Int64(null, null)}).to.throw(TypeError);
		expect(function () {new Int64(new Number(123), new Number(123))}).to.throw(TypeError);
		expect(function () {new Int64(123, undefined)}).to.throw(TypeError);
		new Int64(123, 123);
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
	it('should cast to a NaN when the number is not a safe number', function () {
		expect(+(new Int64(4243423, 234234234))).to.be.NaN;
	});
	it('should compare to other Int64s and other values via .equals()', function () {
		var int = new Int64(123, 123);
		expect(int.equals(int)).to.be.true;
		expect(int.equals(new Int64(123, 123))).to.be.true;
		expect(int.equals({low: 123, high: 123})).to.be.false;
		expect(int.equals(528280977531)).to.be.true;
		expect(int.equals('528280977531')).to.be.true;
		int = new Int64(4243423, 234234234);
		expect(int.equals(new Int64(4243423, 234234234))).to.be.true;
		expect(int.equals(String(int))).to.be.true;
		expect(int.equals(+String(int))).to.be.false;
		expect(int.equals(+int)).to.be.false;
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
	});
	it('should react to changing settings inside an .each() callback', function () {
		var int = new Int64(4243423, 234234234);
		var stmt = db.prepare('SELECT * FROM entries');
		var count = 0;
		stmt.each(function (row) {
			expect(row.b).to.equal(1006028374637854700);
			expect(row.c).to.equal('1006028374637854687');
			if (++count % 2) {
				expect(row.a).to.equal(1006028374637854700);
			} else {
				expect(row.a).to.deep.equal(int);
			}
			stmt.safeIntegers(count % 2 ? true : false);
		});
		expect(count).to.equal(4);
	});
	it('should be safe from other databases inside an .each() callback', function () {
		var int = new Int64(4243423, 234234234);
		var stmt = db.prepare('SELECT a FROM entries').safeIntegers();
		var stmt2 = db2.prepare('SELECT a FROM entries');
		var count = 0;
		stmt.each(function (row) {
			++count;
			expect(row.a).to.deep.equal(int);
			
			var subcount = 0;
			stmt2.safeIntegers(false).each(function (row) {
				++subcount;
				expect(row.a).to.equal(1006028374637854700);
			});
			expect(subcount).to.equal(4);
			
		});
		expect(count).to.equal(4);
	});
	it('should be able to change the default setting on the database', function () {
		db.defaultSafeIntegers(true);
		var int = new Int64(4243423, 234234234);
		
		var stmt = db.prepare('SELECT a FROM entries').pluck();
		expect(stmt.get()).to.deep.equal(int);
		expect(stmt.safeIntegers(false).get()).to.equal(1006028374637854700);
		
		db.defaultSafeIntegers(false);
		
		var stmt2 = db.prepare('SELECT a FROM entries').pluck();
		expect(stmt2.get()).to.equal(1006028374637854700);
		expect(stmt2.safeIntegers().get()).to.deep.equal(int);
		
		db.defaultSafeIntegers(true);
		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt2.get()).to.deep.equal(int);
	});
});
