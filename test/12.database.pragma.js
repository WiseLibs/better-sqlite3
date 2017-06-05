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
		expect(function () {db.pragma('PRAGMA cache_size');}).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(function () {db.pragma('cache_size; PRAGMA cache_size');}).to.throw(RangeError);
	});
	it('should execute the pragma, returning rows of results', function () {
		var db = new Database(util.next());
		var rows = db.pragma('cache_size');
		expect(rows[0].cache_size).to.be.a('number');
		expect(rows[0].cache_size).to.equal(-16000);
	});
	it('should optionally return simpler results', function () {
		var db = new Database(util.next());
		var cache_size = db.pragma('cache_size', true);
		expect(cache_size).to.be.a('number');
		expect(cache_size).to.equal(-16000);
		expect(function () {db.pragma('cache_size', undefined)}).to.throw(TypeError);
		expect(function () {db.pragma('cache_size', null)}).to.throw(TypeError);
		expect(function () {db.pragma('cache_size', 123)}).to.throw(TypeError);
		expect(function () {db.pragma('cache_size', function () {})}).to.throw(TypeError);
		expect(function () {db.pragma('cache_size', NaN)}).to.throw(TypeError);
		expect(function () {db.pragma('cache_size', 'true')}).to.throw(TypeError);
	});
	it('should obey PRAGMA changes', function () {
		var db = new Database(util.next());
		expect(db.pragma('cache_size', true)).to.equal(-16000);
		db.pragma('cache_size = -8000');
		expect(db.pragma('cache_size', true)).to.equal(-8000);
		expect(db.pragma('journal_mode', true)).to.equal('delete');
		db.pragma('journal_mode = wal');
		expect(db.pragma('journal_mode', true)).to.equal('wal');
	});
	it('should respect readonly connections', function () {
		(new Database(util.next())).close();
		var db = new Database(util.current(), {readonly: true});
		expect(db.pragma('cache_size', true)).to.equal(-16000);
		db.pragma('cache_size = -8000');
		expect(db.pragma('cache_size', true)).to.equal(-8000);
		expect(db.pragma('journal_mode', true)).to.equal('delete');
		expect(function () {db.pragma('journal_mode = wal');}).to.throw(Database.SqliteError).with.property('code', 'SQLITE_READONLY');
		expect(db.pragma('journal_mode', true)).to.equal('delete');
	});
	it('should return undefined if no rows exist and simpler results are desired', function () {
		var db = new Database(util.next());
		expect(db.pragma('table_info', true)).to.be.undefined;
	});
});
