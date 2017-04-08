var expect = require('chai').expect;
var Database = require('../.');
var util = (function () {
	var path = require('path');
	var dbId = 0;
	var obj;
	return obj = {
		current: function () {
			return 'temp/' + path.basename(__filename).split('.')[0] + '.' + dbId + '.db';
		},
		next: function () {++dbId; return obj.current();}
	};
}());

describe('Database#pragma()', function () {
	it('should throw an exception if a string is not provided', function () {
		var db = new Database(util.next());
		expect(function () {db.pragma(123);}).to.throw(TypeError);
		expect(function () {db.pragma(0);}).to.throw(TypeError);
		expect(function () {db.pragma(null);}).to.throw(TypeError);
		expect(function () {db.pragma();}).to.throw(TypeError);
		expect(function () {db.pragma(new String('cache_size'));}).to.throw(TypeError);
	});
	it('should throw an exception if invalid/redundant SQL is provided', function () {
		var db = new Database(util.next());
		expect(function () {db.pragma('PRAGMA cache_size');}).to.throw(Error);
	});
	it('should execute the pragma, returning rows of strings', function () {
		var db = new Database(util.next());
		var rows = db.pragma('cache_size');
		expect(rows[0].cache_size).to.be.a('string');
		expect(rows[0].cache_size).to.equal('-16000');
	});
	it('should optionally return simpler results', function () {
		var db = new Database(util.next());
		var cache_size = db.pragma('cache_size', true);
		expect(cache_size).to.be.a('string');
		expect(cache_size).to.equal('-16000');
	});
	it('should accept any truthy value to simplify results', function () {
		var db = new Database(util.next());
		expect(db.pragma('cache_size', {})).to.equal('-16000');
		expect(db.pragma('cache_size', 123)).to.equal('-16000');
		expect(db.pragma('cache_size', function () {})).to.equal('-16000');
		expect(db.pragma('cache_size', NaN)).to.deep.equal([{cache_size: '-16000'}]);
	});
	it('should obey PRAGMA changes', function () {
		var db = new Database(util.next());
		expect(db.pragma('cache_size', true)).to.equal('-16000');
		db.pragma('cache_size = -8000');
		expect(db.pragma('cache_size', true)).to.equal('-8000');
	});
	it('should be available to readonly connections', function () {
		var db = new Database(util.next(), {readonly: true});
		expect(db.pragma('cache_size', true)).to.equal('-16000');
		db.pragma('cache_size = -8000');
		expect(db.pragma('cache_size', true)).to.equal('-8000');
	});
	it('should return undefined if no rows exist and simpler results are desired', function () {
		var db = new Database(util.next());
		expect(db.pragma('table_info', true)).to.be.undefined;
	});
});
