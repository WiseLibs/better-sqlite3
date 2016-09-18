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
	it('should throw if the low and high components are not numbers');
	it('should throw if the low and high components are not 32-bit integers');
	it('should default the high component to zero, if not provided');
	it('should expose the low and high components via getters');
	it('should reveal the full value via .toString()');
	it('should cast to its full value when the number is a safe number');
	it('should cast to a NaN when the number is not a safe number');
	it('should compare to other Int64s or other values via .equals()');
	it('should bind to statements and transactions');
	it('should get returned by operations after setting .safeIntegers()');
	it('should react to changing settings inside an .each() callback');
	it('should be safe from other databases inside an .each() callback');
	it('should be able to change the default setting on the database');
	it('should return fully accurate round-trip results');
});
