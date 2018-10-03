'use strict';
const Database = require('../.');

describe('Database#transaction()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
		this.db.prepare('CREATE TABLE data (x)').run();
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
			let ranOnce = false;
			const trx = this.db.transaction((arg) => {
				expect(arg).to.equal('foo');
				this.db.prepare('INSERT INTO data VALUES (100)').run();
				expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3, 100]);
				expect(other.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3]);
				ranOnce = true;
				return 'bar';
			});
			expect(ranOnce).to.be.false;
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3]);
			expect(other.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3]);
			expect(trx('foo')).to.equal('bar');
			expect(ranOnce).to.be.true;
			expect(this.db.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3, 100]);
			expect(other.prepare('SELECT x FROM data').pluck().all()).to.deep.equal([1, 2, 3, 100]);
			other.close();
		});
		// TODO
		it('should rollback the transaction if an exception is thrown');
		it('should work when the transaction is rollbed back internally');
		it('should work when nested within other transaction functions');
		// TODO: fix integer package property descriptors
	});
});
