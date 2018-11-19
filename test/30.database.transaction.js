'use strict';
const Database = require('../.');

describe('Database#transaction()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
		this.db.prepare('CREATE TABLE data (x UNIQUE)').run();
		this.db.prepare('INSERT INTO data VALUES (1), (2), (3)').run();
	});
	afterEach(function () {
		this.db.close();
	});

	it('should throw an exception if a function is not provided', function () {
		expect(() => this.db.transaction(123)).to.throw(TypeError);
		expect(() => this.db.transaction(0)).to.throw(TypeError);
		expect(() => this.db.transaction(null)).to.throw(TypeError);
		expect(() => this.db.transaction()).to.throw(TypeError);
		expect(() => this.db.transaction([])).to.throw(TypeError);
		expect(() => this.db.transaction('CREATE TABLE people (name TEXT)')).to.throw(TypeError);
		expect(() => this.db.transaction(['CREATE TABLE people (name TEXT)'])).to.throw(TypeError);
	});
	it('should return a new transaction function', function () {
		const fn = () => {};
		const trx = this.db.transaction(fn);
		expect(trx).to.not.equal(fn);
		expect(trx).to.be.a('function');
		expect(trx).to.equal(trx.default);
		const keys = ['default', 'deferred', 'immediate', 'exclusive'];
		for (const key of keys) {
			const nested = trx[key];
			expect(nested).to.not.equal(fn);
			expect(nested).to.be.a('function');
			expect(nested.database).to.equal(this.db);
			expect(nested.run).to.be.undefined;
			expect(nested.get).to.be.undefined;
			expect(nested.all).to.be.undefined;
			expect(nested.iterate).to.be.undefined;
			expect(nested.reader).to.be.undefined;
			expect(nested.source).to.be.undefined;
			for (const key of keys) expect(nested[key]).to.equal(trx[key]);
		}
	});
	describe('transaction function', function () {
		it('should execute the wrapped function', function () {
			const trx = this.db.transaction(function () { return [this, ...arguments]; });
			const obj = {};
			expect(trx.call(obj, 'foo', 'bar', 123, obj)).to.deep.equal([obj, 'foo', 'bar', 123, obj]);
		});
		it('should execute within an isolated transaction', function () {
			const other = new Database(util.current());
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3]);
			expect(other.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3]);
			expect(this.db.inTransaction).to.be.false;
			let ranOnce = false;
			const trx = this.db.transaction((arg) => {
				expect(this.db.inTransaction).to.be.true;
				expect(arg).to.equal('foo');
				this.db.prepare('INSERT INTO data VALUES (100)').run();
				expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3, 100]);
				expect(other.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3]);
				ranOnce = true;
				expect(this.db.inTransaction).to.be.true;
				return 'bar';
			});
			expect(ranOnce).to.be.false;
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3]);
			expect(other.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3]);
			expect(this.db.inTransaction).to.be.false;
			expect(trx('foo')).to.equal('bar');
			expect(this.db.inTransaction).to.be.false;
			expect(ranOnce).to.be.true;
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3, 100]);
			expect(other.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3, 100]);
			other.close();
		});
		it('should rollback the transaction if an exception is thrown', function () {
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3]);
			expect(this.db.inTransaction).to.be.false;
			const err = new Error('foobar');
			let ranOnce = false;
			const trx = this.db.transaction((arg) => {
				expect(this.db.inTransaction).to.be.true;
				expect(arg).to.equal('baz');
				this.db.prepare('INSERT INTO data VALUES (100)').run();
				expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3, 100]);
				ranOnce = true;
				expect(this.db.inTransaction).to.be.true;
				throw err;
			});
			expect(ranOnce).to.be.false;
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3]);
			expect(this.db.inTransaction).to.be.false;
			expect(() => trx('baz')).to.throw(err);
			expect(this.db.inTransaction).to.be.false;
			expect(ranOnce).to.be.true;
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3]);
		});
		it('should work when nested within other transaction functions', function () {
			const stmt = this.db.prepare('INSERT INTO data VALUES (?)');
			const insertOne = this.db.transaction(x => stmt.run(x));
			const insertMany = this.db.transaction((...values) => values.map(insertOne));
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3]);
			insertMany(10, 20, 30);
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3, 10, 20, 30]);
			expect(() => insertMany(40, 50, 3)).to.throw(Database.SqliteError).with.property('code', 'SQLITE_CONSTRAINT_UNIQUE');
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3, 10, 20, 30]);
		});
		it('should be able to perform partial rollbacks when nested', function () {
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3]);
			const stmt = this.db.prepare('INSERT INTO data VALUES (?)');
			const insertOne = this.db.transaction(x => stmt.run(x).changes);
			const insertMany = this.db.transaction((...values) => values.reduce((y, x) => y + insertOne(x), 0));
			expect(this.db.inTransaction).to.be.false;
			const trx = this.db.transaction(() => {
				expect(this.db.inTransaction).to.be.true;
				let count = 0;
				count += insertMany(10, 20, 30);
				expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3, 10, 20, 30]);
				try {
					insertMany(40, 50, 3, 60);
				} catch (_) {
					expect(this.db.inTransaction).to.be.true;
					count += insertOne(555);
				}
				expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3, 10, 20, 30, 555]);
				this.db.prepare('SAVEPOINT foo').run();
				insertOne(123);
				insertMany(456, 789);
				expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3, 10, 20, 30, 555, 123, 456, 789]);
				this.db.prepare('ROLLBACK TO foo').run();
				expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3, 10, 20, 30, 555]);
				count += insertMany(1000);
				expect(this.db.inTransaction).to.be.true;
				return count;
			});
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3]);
			expect(this.db.inTransaction).to.be.false;
			expect(trx()).to.equal(5);
			expect(this.db.inTransaction).to.be.false;
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3, 10, 20, 30, 555, 1000]);
		});
		it('should work when the transaction is rolled back internally', function () {
			const stmt = this.db.prepare('INSERT OR ROLLBACK INTO data VALUES (?)');
			const insertOne = this.db.transaction(x => stmt.run(x));
			const insertMany = this.db.transaction((...values) => values.map(insertOne));
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3]);
			insertMany(10, 20, 30);
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3, 10, 20, 30]);
			expect(() => insertMany(40, 50, 10)).to.throw(Database.SqliteError).with.property('code', 'SQLITE_CONSTRAINT_UNIQUE');
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3, 10, 20, 30]);
		});
	});
});
