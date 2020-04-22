'use strict';
const { existsSync } = require('fs');
const Database = require('../.');

describe('new Database()', function () {
	afterEach(function () {
		if (this.db) this.db.close();
	});

	it('should throw when given invalid argument types', function () {
		expect(() => (this.db = new Database('', ''))).to.throw(TypeError);
		expect(() => (this.db = new Database({}, ''))).to.throw(TypeError);
		expect(() => (this.db = new Database({}, {}))).to.throw(TypeError);
		expect(() => (this.db = new Database({}))).to.throw(TypeError);
		expect(() => (this.db = new Database(0))).to.throw(TypeError);
		expect(() => (this.db = new Database(123))).to.throw(TypeError);
		expect(() => (this.db = new Database(new String(util.next())))).to.throw(TypeError);
		expect(() => (this.db = new Database(() => util.next()))).to.throw(TypeError);
		expect(() => (this.db = new Database([util.next()]))).to.throw(TypeError);
	});
	it('should throw when boolean options are provided as non-booleans', function () {
		expect(() => (this.db = new Database(util.next(), { readOnly: false }))).to.throw(TypeError);
		expect(() => (this.db = new Database(util.next(), { readonly: undefined }))).to.throw(TypeError);
		expect(() => (this.db = new Database(util.next(), { fileMustExist: undefined }))).to.throw(TypeError);
	});
	it('should allow anonymous temporary databases to be created', function () {
		for (const args of [[''], [], [null], [undefined], ['', { timeout: 2000 }]]) {
			const db = this.db = new Database(...args);
			expect(db.name).to.equal('');
			expect(db.memory).to.be.true;
			expect(db.readonly).to.be.false;
			expect(db.open).to.be.true;
			expect(db.inTransaction).to.be.false;
			expect(existsSync('')).to.be.false;
			expect(existsSync('null')).to.be.false;
			expect(existsSync('undefined')).to.be.false;
			expect(existsSync('[object Object]')).to.be.false;
			db.close();
		}
	});
	it('should allow anonymous in-memory databases to be created', function () {
		const db = this.db = new Database(':memory:');
		expect(db.name).to.equal(':memory:');
		expect(db.memory).to.be.true;
		expect(db.readonly).to.be.false;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
		expect(existsSync(':memory:')).to.be.false;
	});
	it('should allow disk-bound databases to be created', function () {
		expect(existsSync(util.next())).to.be.false;
		const db = this.db = Database(util.current());
		expect(db.name).to.equal(util.current());
		expect(db.memory).to.be.false;
		expect(db.readonly).to.be.false;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
		expect(existsSync(util.current())).to.be.true;
	});
	it('should allow readonly database connections to be created', function () {
		expect(existsSync(util.next())).to.be.false;
		expect(() => (this.db = new Database(util.current(), { readonly: true }))).to.throw(Database.SqliteError).with.property('code', 'SQLITE_CANTOPEN');
		(new Database(util.current())).close();
		expect(existsSync(util.current())).to.be.true;
		const db = this.db = new Database(util.current(), { readonly: true });
		expect(db.name).to.equal(util.current());
		expect(db.memory).to.be.false;
		expect(db.readonly).to.be.true;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
		expect(existsSync(util.current())).to.be.true;
	});
	it('should not allow the "readonly" option for in-memory databases', function () {
		expect(existsSync(util.next())).to.be.false;
		expect(() => (this.db = new Database(':memory:', { readonly: true }))).to.throw(TypeError);
		expect(() => (this.db = new Database('', { readonly: true }))).to.throw(TypeError);
		expect(existsSync(util.current())).to.be.false;
	});
	it('should accept the "fileMustExist" option', function () {
		expect(existsSync(util.next())).to.be.false;
		expect(() => (this.db = new Database(util.current(), { fileMustExist: true }))).to.throw(Database.SqliteError).with.property('code', 'SQLITE_CANTOPEN');
		(new Database(util.current())).close();
		expect(existsSync(util.current())).to.be.true;
		const db = this.db = new Database(util.current(), { fileMustExist: true });
		expect(db.name).to.equal(util.current());
		expect(db.memory).to.be.false;
		expect(db.readonly).to.be.false;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
		expect(existsSync(util.current())).to.be.true;
	});
	util.itUnix('should accept the "timeout" option', function () {
		this.slow(4000);
		const testTimeout = (timeout) => {
			const db = new Database(util.current(), { timeout });
			try {
				const start = Date.now();
				expect(() => db.exec('BEGIN EXCLUSIVE')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_BUSY');
				const end = Date.now();
				expect(end - start).to.be.closeTo(timeout, 100);
			} finally {
				db.close();
			}
		};
		const blocker = this.db = new Database(util.next(), { timeout: 0x7fffffff });
		blocker.exec('BEGIN EXCLUSIVE');
		testTimeout(0);
		testTimeout(1000);
		blocker.close();
		expect(() => (this.db = new Database(util.current(), { timeout: undefined }))).to.throw(TypeError);
		expect(() => (this.db = new Database(util.current(), { timeout: null }))).to.throw(TypeError);
		expect(() => (this.db = new Database(util.current(), { timeout: NaN }))).to.throw(TypeError);
		expect(() => (this.db = new Database(util.current(), { timeout: '75' }))).to.throw(TypeError);
		expect(() => (this.db = new Database(util.current(), { timeout: -1 }))).to.throw(TypeError);
		expect(() => (this.db = new Database(util.current(), { timeout: 75.01 }))).to.throw(TypeError);
		expect(() => (this.db = new Database(util.current(), { timeout: 0x80000000 }))).to.throw(RangeError);
	});
	it('should throw an Error if the directory does not exist', function () {
		expect(existsSync(util.next())).to.be.false;
		const filepath = `temp/nonexistent/abcfoobar123/${util.current()}`;
		expect(() => (this.db = new Database(filepath))).to.throw(TypeError);
		expect(existsSync(filepath)).to.be.false;
		expect(existsSync(util.current())).to.be.false;
	});
	it('should have a proper prototype chain', function () {
		const db = this.db = new Database(util.next());
		expect(db).to.be.an.instanceof(Database);
		expect(db.constructor).to.equal(Database);
		expect(Database.prototype.constructor).to.equal(Database);
		expect(Database.prototype.close).to.be.a('function');
		expect(Database.prototype.close).to.equal(db.close);
		expect(Database.prototype).to.equal(Object.getPrototypeOf(db));
	});
});
