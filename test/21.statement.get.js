'use strict';
const Database = require('../.');

describe('Statement#get()', function () {
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
		expect(() => stmt.get()).to.throw(TypeError);

		stmt = this.db.prepare("CREATE TABLE IF NOT EXISTS entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)");
		expect(stmt.reader).to.be.false;
		expect(() => stmt.get()).to.throw(TypeError);

		stmt = this.db.prepare("BEGIN TRANSACTION");
		expect(stmt.reader).to.be.false;
		expect(() => stmt.get()).to.throw(TypeError);
	});
	it('should return the first matching row', function () {
		let stmt = this.db.prepare("SELECT * FROM entries ORDER BY rowid");
		expect(stmt.reader).to.be.true;
		expect(stmt.get()).to.deep.equal({ a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null });

		stmt = this.db.prepare("SELECT * FROM entries WHERE b > 5 ORDER BY rowid");
		expect(stmt.get()).to.deep.equal({ a: 'foo', b: 6, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null });
	});
	it('should obey the current pluck and expand settings', function () {
		const stmt = this.db.prepare("SELECT *, 2 + 3.5 AS c FROM entries ORDER BY rowid");
		const expanded = { entries: { a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null }, $: { c: 5.5 } };
		const row = { ...expanded.entries, ...expanded.$ };
		const plucked = expanded.entries.a;
		expect(stmt.get()).to.deep.equal(row);
		expect(stmt.pluck(true).get()).to.equal(plucked);
		expect(stmt.get()).to.equal(plucked);
		expect(stmt.pluck(false).get()).to.deep.equal(row);
		expect(stmt.get()).to.deep.equal(row);
		expect(stmt.pluck().get()).to.equal(plucked);
		expect(stmt.get()).to.equal(plucked);
		expect(stmt.expand().get()).to.deep.equal(expanded);
		expect(stmt.get()).to.deep.equal(expanded);
		expect(stmt.expand(false).get()).to.deep.equal(row);
		expect(stmt.get()).to.deep.equal(row);
		expect(stmt.expand(true).get()).to.deep.equal(expanded);
		expect(stmt.get()).to.deep.equal(expanded);
		expect(stmt.pluck(true).get()).to.equal(plucked);
		expect(stmt.get()).to.equal(plucked);
	});
	it('should return undefined when no rows were found', function () {
		const stmt = this.db.prepare("SELECT * FROM entries WHERE b == 999");
		expect(stmt.get()).to.be.undefined;
		expect(stmt.pluck().get()).to.be.undefined;
	});
	it('should accept bind parameters', function () {
		const row = { a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null };
		const SQL1 = 'SELECT * FROM entries WHERE a=? AND b=? AND c=? AND d=? AND e IS ?';
		const SQL2 = 'SELECT * FROM entries WHERE a=@a AND b=@b AND c=@c AND d=@d AND e IS @e';
		let result = this.db.prepare(SQL1).get('foo', 1, 3.14, Buffer.alloc(4).fill(0xdd), null);
		expect(result).to.deep.equal(row);

		result = this.db.prepare(SQL1).get(['foo', 1, 3.14, Buffer.alloc(4).fill(0xdd), null]);
		expect(result).to.deep.equal(row);

		result = this.db.prepare(SQL1).get(['foo', 1], [3.14], Buffer.alloc(4).fill(0xdd), [,]);
		expect(result).to.deep.equal(row);

		result = this.db.prepare(SQL2).get({ a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: undefined });
		expect(result).to.deep.equal(row);

		result = this.db.prepare(SQL2).get({ a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xaa), e: undefined });
		expect(result).to.be.undefined;

		expect(() =>
			this.db.prepare(SQL2).get({ a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd) })
		).to.throw(RangeError);

		expect(() =>
			this.db.prepare(SQL1).get()
		).to.throw(RangeError);

		expect(() =>
			this.db.prepare(SQL2).get({})
		).to.throw(RangeError);
	});
});
