'use strict';
var expect = require('chai').expect;
var Database = require('../.');
var db;

before(function (done) {
	db = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.db');
	db.on('open', done);
});

describe('Statement#each()', function () {
	it('should throw an exception when used on a write statement', function () {
		db.prepare('CREATE TABLE entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)').run();
		var stmt = db.prepare("INSERT INTO entries VALUES ('foo', 1, 3.14, x'dddddddd', NULL)");
		expect(stmt.readonly).to.be.false;
		expect(function () {stmt.each(function () {});}).to.throw(TypeError);
		db.prepare("INSERT INTO entries WITH RECURSIVE temp(a, b, c, d, e) AS (SELECT 'foo', 1, 3.14, x'dddddddd', NULL UNION ALL SELECT a, b + 1, c, d, e FROM temp LIMIT 10) SELECT * FROM temp").run();
	});
	it('should throw an exception when the last argument is not a function', function () {
		var stmt = db.prepare('SELECT * FROM entries');
		expect(function () {stmt.each();}).to.throw(TypeError);
		expect(function () {stmt.each({});}).to.throw(TypeError);
		expect(function () {stmt.each(function () {}, 123);}).to.throw(TypeError);
		stmt.each(function () {});
	});
	it('should invoke the callback for each matching row', function () {
		var row = {a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null};
		
		var count = 0;
		var stmt = db.prepare("SELECT * FROM entries");
		expect(stmt.readonly).to.be.true;
		var ret = stmt.each(function (data) {
			row.b = ++count;
			expect(data).to.deep.equal(row);
		});
		expect(count).to.equal(10);
		expect(ret).to.be.undefined;
		
		count = 0;
		stmt = db.prepare("SELECT * FROM entries WHERE b > 5");
		ret = stmt.each(function (data) {
			row.b = ++count + 5;
			expect(data).to.deep.equal(row);
		});
		expect(count).to.equal(5);
		expect(ret).to.be.undefined;
	});
	it('should obey the current pluck setting', function () {
		var row = {a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null};
		var stmt = db.prepare("SELECT * FROM entries");
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
			stmt.each(function (data) {
				++i;
				if (typeof desiredData === 'object' && desiredData !== null) {
					desiredData.b = i;
				}
				expect(data).to.deep.equal(desiredData);
			});
			expect(i).to.equal(10);
		}
	});
	it('should obey the pluck setting even if it changed inside the callback', function () {
		var i = 0;
		var stmt = db.prepare("SELECT * FROM entries");
		stmt.each(function (data) {
			if (++i % 2) {
				expect(data).to.be.an('object');
			} else {
				expect(data).to.be.a('string');
			}
			stmt.pluck(i % 2 ? true : false);
		});
		expect(i).to.equal(10);
	});
	it('should propagate exceptions thrown inside the callback', function () {
		var err = new Error('foobar');
		var stmt = db.prepare("SELECT * FROM entries");
		var count = 0;
		expect(function () {
			stmt.each(function () {++count; throw err;})
		}).to.throw(err);
		expect(count).to.equal(1);
	});
	it('should not invoke the callback when no rows were found', function () {
		var stmt = db.prepare("SELECT * FROM entries WHERE b == 999");
		stmt.each(function () {
			throw new Error('This callback should not have been invoked.')
		});
		stmt.pluck().each(function () {
			throw new Error('This callback should not have been invoked.')
		});
	});
	it('should not allow other database operations to execute in the callback', function () {
		var stmt1 = db.prepare('SELECT * FROM entries');
		var stmt2 = db.prepare('CREATE TABLE numbers (number INTEGER)');
		var trans = db.transaction(['CREATE TABLE numbers (number INTEGER)']);
		var count = 0;
		db.prepare('SELECT * FROM entries').each(function () {
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
				stmt1.each(function () {});
			}).to.throw(TypeError);
			expect(function () {
				stmt2.run();
			}).to.throw(TypeError);
			expect(function () {
				trans.run();
			}).to.throw(TypeError);
		});
		expect(count).to.equal(10);
	});
	it('should accept bind parameters', function () {
		var row = {a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null};
		var SQL1 = 'SELECT * FROM entries WHERE a=? AND b=? AND c=? AND d=? AND e IS ?';
		var SQL2 = 'SELECT * FROM entries WHERE a=@a AND b=@b AND c=@c AND d=@d AND e IS @e';
		
		shouldHave(SQL1, row, ['foo', 1, 3.14, Buffer.alloc(4).fill(0xdd), null])
		shouldHave(SQL1, row, [['foo', 1, 3.14, Buffer.alloc(4).fill(0xdd), null]])
		shouldHave(SQL1, row, [['foo', 1], [3.14], Buffer.alloc(4).fill(0xdd), [,]])
		shouldHave(SQL2, row, [{a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: undefined}])
		
		db.prepare(SQL2).each({a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xaa), e: undefined}, function () {
			throw new Error('This callback should not have been invoked.');
		});
		
		expect(function () {
			db.prepare(SQL2).each({a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd)}, function () {});
		}).to.throw(Error);
		
		expect(function () {
			db.prepare(SQL1).each();
		}).to.throw(TypeError);
		
		expect(function () {
			db.prepare(SQL1).each(function () {});
		}).to.throw(Error);
		
		expect(function () {
			db.prepare(SQL2).each({});
		}).to.throw(TypeError);
		
		expect(function () {
			db.prepare(SQL2).each({}, function () {});
		}).to.throw(Error);
		
		function shouldHave(SQL, desiredData, args) {
			var i = 0;
			var stmt = db.prepare(SQL);
			stmt.each.apply(stmt, args.concat(function (data) {
				desiredData.b = ++i;
				expect(data).to.deep.equal(desiredData);
			}));
			expect(i).to.equal(1);
		}
	});
});
