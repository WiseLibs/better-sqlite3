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
	function opened() {++openCount === 2 && done();}
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
	it('should bind to statements and transactions');
	it('should get returned by operations after setting .safeIntegers()');
	it('should react to changing settings inside an .each() callback');
	it('should be safe from other databases inside an .each() callback');
	it('should be able to change the default setting on the database');
	it('should return fully accurate round-trip results');
});
