'use strict';
const Database = require('../.');

describe('Statement#iterate()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
		this.db.prepare("CREATE TABLE entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)").run();
		this.db.prepare("INSERT INTO entries WITH RECURSIVE temp(a, b, c, d, e) AS (SELECT 'foo', 1, 3.14, x'dddddddd', NULL UNION ALL SELECT a, b + 1, c, d, e FROM temp LIMIT 10) SELECT * FROM temp").run();
	});
	afterEach(function () {
		this.db.close();
	});

	it('should throw an exception when used on a statement that returns no data', function () {
		let stmt = this.db.prepare("INSERT INTO entries VALUES ('foo', 1, 3.14, x'dddddddd', NULL)");
		expect(stmt.reader).to.be.false;
		expect(() => stmt.iterate()).to.throw(TypeError);

		stmt = this.db.prepare("CREATE TABLE IF NOT EXISTS entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)");
		expect(stmt.reader).to.be.false;
		expect(() => stmt.iterate()).to.throw(TypeError);

		stmt = this.db.prepare("BEGIN TRANSACTION");
		expect(stmt.reader).to.be.false;
		expect(() => stmt.iterate()).to.throw(TypeError);

		this.db.prepare("INSERT INTO entries WITH RECURSIVE temp(a, b, c, d, e) AS (SELECT 'foo', 1, 3.14, x'dddddddd', NULL UNION ALL SELECT a, b + 1, c, d, e FROM temp LIMIT 10) SELECT * FROM temp").run();
	});
	it('should return an iterator over each matching row', function () {
		const row = { a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null };

		let count = 0;
		let stmt = this.db.prepare("SELECT * FROM entries ORDER BY rowid");
		expect(stmt.reader).to.be.true;

		const iterator = stmt.iterate();
		expect(iterator).to.not.be.null;
		expect(typeof iterator).to.equal('object');
		expect(iterator.next).to.be.a('function');
		expect(iterator.return).to.be.a('function');
		expect(iterator.throw).to.not.be.a('function');
		expect(iterator[Symbol.iterator]).to.be.a('function');
		expect(iterator[Symbol.iterator]()).to.equal(iterator);

		for (const data of iterator) {
			row.b = ++count;
			expect(data).to.deep.equal(row);
		}
		expect(count).to.equal(10);

		count = 0;
		stmt = this.db.prepare("SELECT * FROM entries WHERE b > 5 ORDER BY rowid");
		const iterator2 = stmt.iterate();
		expect(iterator).to.not.equal(iterator2);
		for (const data of iterator2) {
			row.b = ++count + 5;
			expect(data).to.deep.equal(row);
		}
		expect(count).to.equal(5);
	});
	it('should obey the current pluck and expand settings', function () {
		const shouldHave = (desiredData) => {
			let i = 0;
			for (const data of stmt.iterate()) {
				i += 1;
				if (typeof desiredData === 'object' && desiredData !== null) {
					if (Array.isArray(desiredData)) {
						desiredData[1] = i;
					} else if (typeof desiredData.entries === 'object' && desiredData.entries !== null) {
						desiredData.entries.b = i;
					} else {
						desiredData.b = i;
					}
				}
				expect(data).to.deep.equal(desiredData);
			}
			expect(i).to.equal(10);
		};
		const expanded = {
			entries: { a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null },
			$: { c: 5.5 },
		};
		const row = Object.assign({}, expanded.entries, expanded.$);
		const plucked = expanded.entries.a;
		const raw = Object.values(expanded.entries).concat(expanded.$.c);
		const stmt = this.db.prepare("SELECT *, 2 + 3.5 AS c FROM entries ORDER BY rowid");
		shouldHave(row);
		stmt.pluck(true);
		shouldHave(plucked);
		shouldHave(plucked);
		stmt.pluck(false);
		shouldHave(row);
		shouldHave(row);
		stmt.pluck();
		shouldHave(plucked);
		shouldHave(plucked);
		stmt.expand();
		shouldHave(expanded);
		shouldHave(expanded);
		stmt.expand(false);
		shouldHave(row);
		shouldHave(row);
		stmt.expand(true);
		shouldHave(expanded);
		shouldHave(expanded);
		stmt.pluck(true);
		shouldHave(plucked);
		shouldHave(plucked);
		stmt.raw();
		shouldHave(raw);
		shouldHave(raw);
		stmt.raw(false);
		shouldHave(row);
		shouldHave(row);
		stmt.raw(true);
		shouldHave(raw);
		shouldHave(raw);
		stmt.expand(true);
		shouldHave(expanded);
		shouldHave(expanded);
	});
	it('should close the iterator when throwing in a for-of loop', function () {
		const err = new Error('foobar');
		const stmt = this.db.prepare("SELECT * FROM entries ORDER BY rowid");
		const iterator = stmt.iterate();
		let count = 0;
		expect(() => {
			for (const row of iterator) { ++count; throw err; }
		}).to.throw(err);
		expect(count).to.equal(1);
		expect(iterator.next()).to.deep.equal({ value: undefined, done: true });
		for (const row of iterator) ++count;
		expect(count).to.equal(1);
		for (const row of stmt.iterate()) ++count;
		expect(count).to.equal(11);
	});
	it('should close the iterator when using break in a for-of loop', function () {
		const stmt = this.db.prepare("SELECT * FROM entries ORDER BY rowid");
		const iterator = stmt.iterate();
		let count = 0;
		for (const row of iterator) { ++count; break; }
		expect(count).to.equal(1);
		expect(iterator.next()).to.deep.equal({ value: undefined, done: true });
		for (const row of iterator) ++count;
		expect(count).to.equal(1);
		for (const row of stmt.iterate()) ++count;
		expect(count).to.equal(11);
	});
	it('should return an empty iterator when no rows were found', function () {
		const stmt = this.db.prepare("SELECT * FROM entries WHERE b == 999");
		expect(stmt.iterate().next()).to.deep.equal({ value: undefined, done: true });
		for (const data of stmt.pluck().iterate()) {
			throw new Error('This callback should not have been invoked');
		}
	});
	it('should accept bind parameters', function () {
		const shouldHave = (SQL, desiredData, args) => {
			let i = 0;
			const stmt = this.db.prepare(SQL);
			for (const data of stmt.iterate(...args)) {
				desiredData.b = ++i;
				expect(data).to.deep.equal(desiredData);
			}
			expect(i).to.equal(1);
		};

		const row = { a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null };
		const SQL1 = 'SELECT * FROM entries WHERE a=? AND b=? AND c=? AND d=? AND e IS ?';
		const SQL2 = 'SELECT * FROM entries WHERE a=@a AND b=@b AND c=@c AND d=@d AND e IS @e';

		shouldHave(SQL1, row, ['foo', 1, 3.14, Buffer.alloc(4).fill(0xdd), null]);
		shouldHave(SQL1, row, [['foo', 1, 3.14, Buffer.alloc(4).fill(0xdd), null]]);
		shouldHave(SQL1, row, [['foo', 1], [3.14], Buffer.alloc(4).fill(0xdd), [,]]);
		shouldHave(SQL2, row, [{ a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: undefined }]);

		for (const data of this.db.prepare(SQL2).iterate({ a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xaa), e: undefined })) {
			throw new Error('This callback should not have been invoked');
		}

		expect(() =>
			this.db.prepare(SQL2).iterate(row, () => {})
		).to.throw(TypeError);

		expect(() =>
			this.db.prepare(SQL2).iterate({ a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd) })
		).to.throw(RangeError);

		expect(() =>
			this.db.prepare(SQL1).iterate()
		).to.throw(RangeError);

		expect(() =>
			this.db.prepare(SQL2).iterate()
		).to.throw(TypeError);

		expect(() =>
			this.db.prepare(SQL2).iterate(row, {})
		).to.throw(TypeError);

		expect(() =>
			this.db.prepare(SQL2).iterate({})
		).to.throw(RangeError);

		this.db.prepare(SQL1).iterate('foo', 1, 3.14, Buffer.alloc(4).fill(0xdd), null).return();
		expect(() =>
			this.db.prepare(SQL1).iterate('foo', 1, new (function(){})(), Buffer.alloc(4).fill(0xdd), null)
		).to.throw(TypeError);
	});
});
