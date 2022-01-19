'use strict';
const fs = require('fs');
const path = require('path');
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
			expect(fs.existsSync('')).to.be.false;
			expect(fs.existsSync('null')).to.be.false;
			expect(fs.existsSync('undefined')).to.be.false;
			expect(fs.existsSync('[object Object]')).to.be.false;
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
		expect(fs.existsSync(':memory:')).to.be.false;
	});
	it('should allow disk-bound databases to be created', function () {
		expect(fs.existsSync(util.next())).to.be.false;
		const db = this.db = new Database(util.current());
		expect(db.name).to.equal(util.current());
		expect(db.memory).to.be.false;
		expect(db.readonly).to.be.false;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
		expect(fs.existsSync(util.current())).to.be.true;
	});
	it('should allow readonly database connections to be created', function () {
		expect(fs.existsSync(util.next())).to.be.false;
		expect(() => (this.db = new Database(util.current(), { readonly: true }))).to.throw(Database.SqliteError).with.property('code', 'SQLITE_CANTOPEN');
		(new Database(util.current())).close();
		expect(fs.existsSync(util.current())).to.be.true;
		const db = this.db = new Database(util.current(), { readonly: true });
		expect(db.name).to.equal(util.current());
		expect(db.memory).to.be.false;
		expect(db.readonly).to.be.true;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
		expect(fs.existsSync(util.current())).to.be.true;
	});
	it('should not allow the "readonly" option for in-memory databases', function () {
		expect(fs.existsSync(util.next())).to.be.false;
		expect(() => (this.db = new Database(':memory:', { readonly: true }))).to.throw(TypeError);
		expect(() => (this.db = new Database('', { readonly: true }))).to.throw(TypeError);
		expect(fs.existsSync(util.current())).to.be.false;
	});
	it('should accept the "fileMustExist" option', function () {
		expect(fs.existsSync(util.next())).to.be.false;
		expect(() => (this.db = new Database(util.current(), { fileMustExist: true }))).to.throw(Database.SqliteError).with.property('code', 'SQLITE_CANTOPEN');
		(new Database(util.current())).close();
		expect(fs.existsSync(util.current())).to.be.true;
		const db = this.db = new Database(util.current(), { fileMustExist: true });
		expect(db.name).to.equal(util.current());
		expect(db.memory).to.be.false;
		expect(db.readonly).to.be.false;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
		expect(fs.existsSync(util.current())).to.be.true;
	});
	util.itUnix('should accept the "timeout" option', function () {
		this.slow(4000);
		const testTimeout = (timeout) => {
			const db = new Database(util.current(), { timeout });
			try {
				const start = Date.now();
				expect(() => db.exec('BEGIN EXCLUSIVE')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_BUSY');
				const end = Date.now();
				expect(end - start).to.be.closeTo(timeout, 200);
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
	it('should accept the "nativeBinding" option', function () {
		this.slow(500);
		const oldBinding = require('bindings')({ bindings: 'better_sqlite3.node', path: true });
		const newBinding = path.join(path.dirname(oldBinding), 'test.node');
		expect(oldBinding).to.be.a('string');
		fs.copyFileSync(oldBinding, newBinding);
		const getBinding = db => db[Object.getOwnPropertySymbols(db)[0]].constructor;
		let db1;
		let db2;
		let db3;
		try {
			db1 = new Database('');
			db2 = new Database('', { nativeBinding: oldBinding });
			db3 = new Database('', { nativeBinding: newBinding });
			expect(db1.open).to.be.true;
			expect(db2.open).to.be.true;
			expect(db3.open).to.be.true;
			expect(getBinding(db1)).to.equal(getBinding(db2));
			expect(getBinding(db1)).to.not.equal(getBinding(db3));
			expect(getBinding(db2)).to.not.equal(getBinding(db3));
		} finally {
			if (db1) db1.close();
			if (db2) db2.close();
			if (db3) db3.close();
		}
	});
	it('should throw an Error if the directory does not exist', function () {
		expect(fs.existsSync(util.next())).to.be.false;
		const filepath = `temp/nonexistent/abcfoobar123/${util.current()}`;
		expect(() => (this.db = new Database(filepath))).to.throw(TypeError);
		expect(fs.existsSync(filepath)).to.be.false;
		expect(fs.existsSync(util.current())).to.be.false;
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
	it('should work properly when called as a function', function () {
		const db = this.db = Database(util.next());
		expect(db).to.be.an.instanceof(Database);
		expect(db.constructor).to.equal(Database);
		expect(Database.prototype.close).to.equal(db.close);
		expect(Database.prototype).to.equal(Object.getPrototypeOf(db));
	});
	it('should work properly when subclassed', function () {
		class MyDatabase extends Database {
			foo() {
				return 999;
			}
		}
		const db = this.db = new MyDatabase(util.next());
		expect(db).to.be.an.instanceof(Database);
		expect(db).to.be.an.instanceof(MyDatabase);
		expect(db.constructor).to.equal(MyDatabase);
		expect(Database.prototype.close).to.equal(db.close);
		expect(MyDatabase.prototype.close).to.equal(db.close);
		expect(Database.prototype.foo).to.be.undefined;
		expect(MyDatabase.prototype.foo).to.equal(db.foo);
		expect(Database.prototype).to.equal(Object.getPrototypeOf(MyDatabase.prototype));
		expect(MyDatabase.prototype).to.equal(Object.getPrototypeOf(db));
		expect(db.foo()).to.equal(999);
	});
});
