'use strict';
const { expect } = require('chai');
const Database = require('../.');
const db = new Database(require('./util').next());

describe('Statement#all()', function () {
	it('should throw an exception when used on a statement that returns no data', function () {
		db.prepare('CREATE TABLE entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)').run();
		
		var stmt = db.prepare("INSERT INTO entries VALUES ('foo', 1, 3.14, x'dddddddd', NULL)");
		expect(stmt.returnsData).to.be.false;
		expect(function () {stmt.all();}).to.throw(TypeError);
		
		var stmt = db.prepare("CREATE TABLE IF NOT EXISTS entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)");
		expect(stmt.returnsData).to.be.false;
		expect(function () {stmt.all();}).to.throw(TypeError);
		
		var stmt = db.prepare("BEGIN TRANSACTION");
		expect(stmt.returnsData).to.be.false;
		expect(function () {stmt.all();}).to.throw(TypeError);
	});
	it('should return an array of every matching row', function () {
		db.prepare("INSERT INTO entries WITH RECURSIVE temp(a, b, c, d, e) AS (SELECT 'foo', 1, 3.14, x'dddddddd', NULL UNION ALL SELECT a, b + 1, c, d, e FROM temp LIMIT 10) SELECT * FROM temp").run();
		var row = {a: 'foo', b: 1, c: 3.14, d: bufferOfSize(4).fill(0xdd), e: null};
		
		var stmt = db.prepare("SELECT * FROM entries ORDER BY rowid");
		expect(stmt.returnsData).to.be.true;
		matchesFrom(stmt.all(), 1);
		
		stmt = db.prepare("SELECT * FROM entries WHERE b > 5 ORDER BY rowid");
		matchesFrom(stmt.all(), 6);
		
		function matchesFrom(rows, i) {
			for (var index = 0; i<=10; ++i, ++index) {
				row.b = i;
				expect(rows[index]).to.deep.equal(row);
			}
			expect(index).to.equal(rows.length);
		}
	});
	it('should obey the current pluck setting', function () {
		var stmt = db.prepare("SELECT * FROM entries");
		var plucked = new Array(10).fill('foo');
		expect(stmt.all()).to.not.deep.equal(plucked);
		expect(stmt.pluck(true).all()).to.deep.equal(plucked);
		expect(stmt.all()).to.deep.equal(plucked);
		expect(stmt.pluck(false).all()).to.not.deep.equal(plucked);
		expect(stmt.all()).to.not.deep.equal(plucked);
		expect(stmt.pluck().all()).to.deep.equal(plucked);
		expect(stmt.all()).to.deep.equal(plucked);
	});
	it('should return an empty array when no rows were found', function () {
		var stmt = db.prepare("SELECT * FROM entries WHERE b == 999");
		expect(stmt.all()).to.deep.equal([]);
		expect(stmt.pluck().all()).to.deep.equal([]);
	});
	it('should accept bind parameters', function () {
		var rows = [{a: 'foo', b: 1, c: 3.14, d: bufferOfSize(4).fill(0xdd), e: null}];
		var SQL1 = 'SELECT * FROM entries WHERE a=? AND b=? AND c=? AND d=? AND e IS ?';
		var SQL2 = 'SELECT * FROM entries WHERE a=@a AND b=@b AND c=@c AND d=@d AND e IS @e';
		var result = db.prepare(SQL1).all('foo', 1, 3.14, bufferOfSize(4).fill(0xdd), null);
		expect(result).to.deep.equal(rows);
		
		result = db.prepare(SQL1).all(['foo', 1, 3.14, bufferOfSize(4).fill(0xdd), null]);
		expect(result).to.deep.equal(rows);
		
		result = db.prepare(SQL1).all(['foo', 1], [3.14], bufferOfSize(4).fill(0xdd), [,]);
		expect(result).to.deep.equal(rows);
		
		result = db.prepare(SQL2).all({a: 'foo', b: 1, c: 3.14, d: bufferOfSize(4).fill(0xdd), e: undefined});
		expect(result).to.deep.equal(rows);
		
		result = db.prepare(SQL2).all({a: 'foo', b: 1, c: 3.14, d: bufferOfSize(4).fill(0xaa), e: undefined});
		expect(result).to.deep.equal([]);
		
		expect(function () {
			db.prepare(SQL2).all({a: 'foo', b: 1, c: 3.14, d: bufferOfSize(4).fill(0xdd)});
		}).to.throw(RangeError);
		
		expect(function () {
			db.prepare(SQL1).all();
		}).to.throw(RangeError);
		
		expect(function () {
			db.prepare(SQL2).all({});
		}).to.throw(RangeError);
	});
});

function bufferOfSize(size) {
	return Buffer.alloc ? Buffer.alloc(+size) : new Buffer(+size);
}
