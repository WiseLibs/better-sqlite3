'use strict';
var expect = require('chai').expect;
var Database = require('../.');
var util = require('../tools/test-util.js');
var db;

before(function (done) {
	db = new Database(util.next());
	db.on('open', done);
});

describe('Statement#get()', function () {
	it('should throw an exception when used on a write statement', function () {
		db.prepare('CREATE TABLE entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)').run();
		var stmt = db.prepare("INSERT INTO entries VALUES ('foo', 1, 3.14, x'dddddddd', NULL)");
		expect(stmt.readonly).to.be.false;
		expect(function () {stmt.get();}).to.throw(TypeError);
	});
	it('should return the first matching row', function () {
		db.prepare("INSERT INTO entries WITH RECURSIVE temp(a, b, c, d, e) AS (SELECT 'foo', 1, 3.14, x'dddddddd', NULL UNION ALL SELECT a, b + 1, c, d, e FROM temp LIMIT 10) SELECT * FROM temp").run();
		
		var stmt = db.prepare("SELECT * FROM entries");
		expect(stmt.readonly).to.be.true;
		expect(stmt.get()).to.deep.equal({a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null});
		
		stmt = db.prepare("SELECT * FROM entries WHERE b > 5");
		expect(stmt.get()).to.deep.equal({a: 'foo', b: 6, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null});
	});
	it('should obey the current pluck setting', function () {
		var stmt = db.prepare("SELECT * FROM entries");
		var row = {a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null};
		expect(stmt.get()).to.deep.equal(row);
		expect(stmt.pluck(true).get()).to.equal('foo');
		expect(stmt.get()).to.equal('foo');
		expect(stmt.pluck(false).get()).to.deep.equal(row);
		expect(stmt.get()).to.deep.equal(row);
		expect(stmt.pluck().get()).to.equal('foo');
		expect(stmt.get()).to.equal('foo');
	});
	it('should return undefined when no rows were found', function () {
		var stmt = db.prepare("SELECT * FROM entries WHERE b == 999");
		expect(stmt.get()).to.be.undefined;
		expect(stmt.pluck().get()).to.be.undefined;
	});
	it('should accept bind parameters', function () {
		var row = {a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null};
		var SQL1 = 'SELECT * FROM entries WHERE a=? AND b=? AND c=? AND d=? AND e IS ?';
		var SQL2 = 'SELECT * FROM entries WHERE a=@a AND b=@b AND c=@c AND d=@d AND e IS @e';
		var result = db.prepare(SQL1).get('foo', 1, 3.14, Buffer.alloc(4).fill(0xdd), null);
		expect(result).to.deep.equal(row);
		
		result = db.prepare(SQL1).get(['foo', 1, 3.14, Buffer.alloc(4).fill(0xdd), null]);
		expect(result).to.deep.equal(row);
		
		result = db.prepare(SQL1).get(['foo', 1], [3.14], Buffer.alloc(4).fill(0xdd), [,]);
		expect(result).to.deep.equal(row);
		
		result = db.prepare(SQL2).get({a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: undefined});
		expect(result).to.deep.equal(row);
		
		result = db.prepare(SQL2).get({a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xaa), e: undefined});
		expect(result).to.be.undefined;
		
		expect(function () {
			db.prepare(SQL2).get({a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd)});
		}).to.throw(Error);
		
		expect(function () {
			db.prepare(SQL1).get();
		}).to.throw(Error);
		
		expect(function () {
			db.prepare(SQL2).get({});
		}).to.throw(Error);
	});
});
