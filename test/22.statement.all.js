'use strict';
const Database = require('../.');

describe('Statement#all()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
		this.db.prepare('CREATE TABLE entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)').run();
		this.db.prepare("INSERT INTO entries WITH RECURSIVE temp(a, b, c, d, e) AS (SELECT 'foo', 1, 3.14, x'dddddddd', NULL UNION ALL SELECT a, b + 1, c, d, e FROM temp LIMIT 10) SELECT * FROM temp").run();
	});
	afterEach(function () {
		this.db.close();
	});
	
	it('should throw an exception when used on a statement that returns no data', function () {
		let stmt = this.db.prepare("INSERT INTO entries VALUES ('foo', 1, 3.14, x'dddddddd', NULL)");
		expect(stmt.reader).to.be.false;
		expect(() => stmt.all()).to.throw(TypeError);
		
		stmt = this.db.prepare("CREATE TABLE IF NOT EXISTS entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)");
		expect(stmt.reader).to.be.false;
		expect(() => stmt.all()).to.throw(TypeError);
		
		stmt = this.db.prepare("BEGIN TRANSACTION");
		expect(stmt.reader).to.be.false;
		expect(() => stmt.all()).to.throw(TypeError);
	});
	it('should return an array of every matching row', function () {
		const row = { a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null };
		
		let stmt = this.db.prepare("SELECT * FROM entries ORDER BY rowid");
		expect(stmt.reader).to.be.true;
		matchesFrom(stmt.all(), 1);
		
		stmt = this.db.prepare("SELECT * FROM entries WHERE b > 5 ORDER BY rowid");
		matchesFrom(stmt.all(), 6);
		
		function matchesFrom(rows, i) {
			let index = 0;
			for (; i <= 10; ++i, ++index) {
				row.b = i;
				expect(rows[index]).to.deep.equal(row);
			}
			expect(index).to.equal(rows.length);
		}
	});
	it('should obey the current pluck setting', function () {
		const stmt = this.db.prepare("SELECT * FROM entries");
		const plucked = new Array(10).fill('foo');
		expect(stmt.all()).to.not.deep.equal(plucked);
		expect(stmt.pluck(true).all()).to.deep.equal(plucked);
		expect(stmt.all()).to.deep.equal(plucked);
		expect(stmt.pluck(false).all()).to.not.deep.equal(plucked);
		expect(stmt.all()).to.not.deep.equal(plucked);
		expect(stmt.pluck().all()).to.deep.equal(plucked);
		expect(stmt.all()).to.deep.equal(plucked);
	});
	it('should return an empty array when no rows were found', function () {
		const stmt = this.db.prepare("SELECT * FROM entries WHERE b == 999");
		expect(stmt.all()).to.deep.equal([]);
		expect(stmt.pluck().all()).to.deep.equal([]);
	});
	it('should accept bind parameters', function () {
		const rows = [{ a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null }];
		const SQL1 = 'SELECT * FROM entries WHERE a=? AND b=? AND c=? AND d=? AND e IS ?';
		const SQL2 = 'SELECT * FROM entries WHERE a=@a AND b=@b AND c=@c AND d=@d AND e IS @e';
		let result = this.db.prepare(SQL1).all('foo', 1, 3.14, Buffer.alloc(4).fill(0xdd), null);
		expect(result).to.deep.equal(rows);
		
		result = this.db.prepare(SQL1).all(['foo', 1, 3.14, Buffer.alloc(4).fill(0xdd), null]);
		expect(result).to.deep.equal(rows);
		
		result = this.db.prepare(SQL1).all(['foo', 1], [3.14], Buffer.alloc(4).fill(0xdd), [,]);
		expect(result).to.deep.equal(rows);
		
		result = this.db.prepare(SQL2).all({ a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: undefined });
		expect(result).to.deep.equal(rows);
		
		result = this.db.prepare(SQL2).all({ a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xaa), e: undefined });
		expect(result).to.deep.equal([]);
		
		expect(() =>
			this.db.prepare(SQL2).all({ a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd) })
		).to.throw(RangeError);
		
		expect(() =>
			this.db.prepare(SQL1).all()
		).to.throw(RangeError);
		
		expect(() =>
			this.db.prepare(SQL2).all({})
		).to.throw(RangeError);
	});
});
