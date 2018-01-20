'use strict';
const { expect } = require('chai');
const Database = require('../.');
const db = new Database(require('./util').next());

describe('Statement#iterate()', function () {
	it('should throw an exception when used on a statement that returns no data', function () {
		db.prepare('CREATE TABLE entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)').run();
		
		var stmt = db.prepare("INSERT INTO entries VALUES ('foo', 1, 3.14, x'dddddddd', NULL)");
		expect(stmt.returnsData).to.be.false;
		expect(function () {stmt.iterate();}).to.throw(TypeError);
		
		var stmt = db.prepare("CREATE TABLE IF NOT EXISTS entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)");
		expect(stmt.returnsData).to.be.false;
		expect(function () {stmt.iterate();}).to.throw(TypeError);
		
		var stmt = db.prepare("BEGIN TRANSACTION");
		expect(stmt.returnsData).to.be.false;
		expect(function () {stmt.iterate();}).to.throw(TypeError);
		
		db.prepare("INSERT INTO entries WITH RECURSIVE temp(a, b, c, d, e) AS (SELECT 'foo', 1, 3.14, x'dddddddd', NULL UNION ALL SELECT a, b + 1, c, d, e FROM temp LIMIT 10) SELECT * FROM temp").run();
	});
	it('should return an iterator over each matching row', function () {
		var row = {a: 'foo', b: 1, c: 3.14, d: bufferOfSize(4).fill(0xdd), e: null};
		
		var count = 0;
		var stmt = db.prepare("SELECT * FROM entries ORDER BY rowid");
		expect(stmt.returnsData).to.be.true;
		
		var iterator = stmt.iterate();
		expect(iterator).to.not.be.null;
		expect(typeof iterator).to.equal('object');
		expect(iterator.next).to.be.a('function');
		expect(iterator.return).to.be.a('function');
		expect(iterator.throw).to.not.be.a('function');
		expect(iterator[Symbol.iterator]).to.be.a('function');
		expect(iterator[Symbol.iterator]()).to.equal(iterator);
		
		for (var data of iterator) {
			row.b = ++count;
			expect(data).to.deep.equal(row);
		}
		expect(count).to.equal(10);
		
		count = 0;
		stmt = db.prepare("SELECT * FROM entries WHERE b > 5 ORDER BY rowid");
		var iterator2 = stmt.iterate();
		expect(iterator).to.not.equal(iterator2);
		for (var data of iterator2) {
			row.b = ++count + 5;
			expect(data).to.deep.equal(row);
		}
		expect(count).to.equal(5);
	});
	it('should obey the current pluck setting', function () {
		var row = {a: 'foo', b: 1, c: 3.14, d: bufferOfSize(4).fill(0xdd), e: null};
		var stmt = db.prepare("SELECT * FROM entries ORDER BY rowid");
		shouldHave(row);
		stmt.pluck(true);
		shouldHave('foo');
		shouldHave('foo');
		stmt.pluck(false);
		shouldHave(row);
		shouldHave(row);
		stmt.pluck();
		shouldHave('foo');
		shouldHave('foo');
		
		function shouldHave(desiredData) {
			var i = 0;
			for (var data of stmt.iterate()) {
				++i;
				if (typeof desiredData === 'object' && desiredData !== null) {
					desiredData.b = i;
				}
				expect(data).to.deep.equal(desiredData);
			}
			expect(i).to.equal(10);
		}
	});
	it('should not be able to invoke .pluck() while the database is busy', function () {
		var stmt1 = db.prepare("SELECT * FROM entries");
		var stmt2 = db.prepare("SELECT * FROM entries LIMIT 2");
		var i = 0;
		for (var data of stmt1.iterate()) {
			++i;
			expect(function () {stmt1.pluck();}).to.throw(TypeError);
			expect(function () {stmt2.pluck();}).to.throw(TypeError);
			expect(function () {stmt1.pluck(false);}).to.throw(TypeError);
			expect(function () {stmt2.pluck(false);}).to.throw(TypeError);
		}
		expect(i).to.equal(10);
	});
	it('should close the iterator when throwing in a for-of loop', function () {
		var err = new Error('foobar');
		var stmt = db.prepare("SELECT * FROM entries");
		var iterator = stmt.iterate();
		var count = 0;
		expect(function () {
			for (var row of iterator) {++count; throw err;}
		}).to.throw(err);
		expect(count).to.equal(1);
		expect(iterator.next()).to.deep.equal({value: undefined, done: true});
		for (var row of iterator) {++count;}
		expect(count).to.equal(1);
		for (var row of stmt.iterate()) {++count;}
		expect(count).to.equal(11);
	});
	it('should close the iterator when using break in a for-of loop', function () {
		var stmt = db.prepare("SELECT * FROM entries");
		var iterator = stmt.iterate();
		var count = 0;
		for (var row of iterator) {++count; break;}
		expect(count).to.equal(1);
		expect(iterator.next()).to.deep.equal({value: undefined, done: true});
		for (var row of iterator) {++count;}
		expect(count).to.equal(1);
		for (var row of stmt.iterate()) {++count;}
		expect(count).to.equal(11);
	});
	it('should return an empty iterator when no rows were found', function () {
		var stmt = db.prepare("SELECT * FROM entries WHERE b == 999");
		expect(stmt.iterate().next()).to.deep.equal({value: undefined, done: true});
		for (var data of stmt.pluck().iterate()) {
			throw new Error('This callback should not have been invoked');
		}
	});
	it('should not allow other database operations to execute while open', function () {
		var stmt1 = db.prepare('SELECT * FROM entries');
		var stmt2 = db.prepare('CREATE TABLE numbers (number INTEGER)');
		var trans = db.transaction(['CREATE TABLE numbers (number INTEGER)']);
		var count = 0;
		for (var row of db.prepare('SELECT * FROM entries').iterate()) {
			++count;
			expect(function () {
				db.close();
			}).to.throw(TypeError);
			expect(function () {
				db.pragma('cache_size');
			}).to.throw(TypeError);
			expect(function () {
				db.checkpoint();
			}).to.throw(TypeError);
			expect(function () {
				db.prepare('SELECT * FROM entries');
			}).to.throw(TypeError);
			expect(function () {
				db.transaction(['CREATE TABLE numbers (number INTEGER)']);
			}).to.throw(TypeError);
			expect(function () {
				stmt1.get();
			}).to.throw(TypeError);
			expect(function () {
				stmt1.all();
			}).to.throw(TypeError);
			expect(function () {
				stmt1.iterate();
			}).to.throw(TypeError);
			expect(function () {
				stmt2.run();
			}).to.throw(TypeError);
			expect(function () {
				trans.run();
			}).to.throw(TypeError);
		}
		expect(count).to.equal(10);
	});
	it('should allow database operations after closing the iterator', function () {
		var row = {a: 'foo', b: 1, c: 3.14, d: bufferOfSize(4).fill(0xdd), e: null};
		var stmt = db.prepare("SELECT * FROM entries");
		db.prepare('SELECT 555');
		var iterator = stmt.iterate();
		expect(function () {db.prepare('SELECT 555');}).to.throw(TypeError);
		expect(iterator.next()).to.deep.equal({value: row, done: false});
		row.b += 1;
		expect(function () {db.prepare('SELECT 555');}).to.throw(TypeError);
		expect(iterator.next()).to.deep.equal({value: row, done: false});
		row.b += 1;
		expect(function () {db.prepare('SELECT 555');}).to.throw(TypeError);
		expect(iterator.next()).to.deep.equal({value: row, done: false});
		expect(function () {db.prepare('SELECT 555');}).to.throw(TypeError);
		expect(iterator.return()).to.deep.equal({value: undefined, done: true});
		db.prepare('SELECT 555');
		expect(iterator.next()).to.deep.equal({value: undefined, done: true});
		db.prepare('SELECT 555');
		expect(iterator.return()).to.deep.equal({value: undefined, done: true});
		db.prepare('SELECT 555');
		expect(iterator.next()).to.deep.equal({value: undefined, done: true});
		db.prepare('SELECT 555');
	});
	it('should accept bind parameters', function () {
		var row = {a: 'foo', b: 1, c: 3.14, d: bufferOfSize(4).fill(0xdd), e: null};
		var SQL1 = 'SELECT * FROM entries WHERE a=? AND b=? AND c=? AND d=? AND e IS ?';
		var SQL2 = 'SELECT * FROM entries WHERE a=@a AND b=@b AND c=@c AND d=@d AND e IS @e';
		
		shouldHave(SQL1, row, ['foo', 1, 3.14, bufferOfSize(4).fill(0xdd), null])
		shouldHave(SQL1, row, [['foo', 1, 3.14, bufferOfSize(4).fill(0xdd), null]])
		shouldHave(SQL1, row, [['foo', 1], [3.14], bufferOfSize(4).fill(0xdd), [,]])
		shouldHave(SQL2, row, [{a: 'foo', b: 1, c: 3.14, d: bufferOfSize(4).fill(0xdd), e: undefined}])
		
		for (var data of db.prepare(SQL2).iterate({a: 'foo', b: 1, c: 3.14, d: bufferOfSize(4).fill(0xaa), e: undefined})) {
			throw new Error('This callback should not have been invoked');
		}
		
		expect(function () {
			db.prepare(SQL2).iterate(row, function () {});
		}).to.throw(TypeError);
		
		expect(function () {
			db.prepare(SQL2).iterate({a: 'foo', b: 1, c: 3.14, d: bufferOfSize(4).fill(0xdd)});
		}).to.throw(RangeError);
		
		expect(function () {
			db.prepare(SQL1).iterate();
		}).to.throw(RangeError);
		
		expect(function () {
			db.prepare(SQL2).iterate();
		}).to.throw(TypeError);
		
		expect(function () {
			db.prepare(SQL2).iterate(row, {});
		}).to.throw(TypeError);
		
		expect(function () {
			db.prepare(SQL2).iterate({});
		}).to.throw(RangeError);
		
		db.prepare(SQL1).iterate('foo', 1, 3.14, bufferOfSize(4).fill(0xdd), null).return();
		expect(function () {
			db.prepare(SQL1).iterate('foo', 1, new (function(){})(), bufferOfSize(4).fill(0xdd), null);
		}).to.throw(TypeError);
		
		function shouldHave(SQL, desiredData, args) {
			var i = 0;
			var stmt = db.prepare(SQL);
			for (var data of stmt.iterate.apply(stmt, args)) {
				desiredData.b = ++i;
				expect(data).to.deep.equal(desiredData);
			}
			expect(i).to.equal(1);
		}
	});
});

function bufferOfSize(size) {
	return Buffer.alloc ? Buffer.alloc(+size) : new Buffer(+size);
}
