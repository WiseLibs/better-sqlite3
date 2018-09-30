'use strict';
const { existsSync } = require('fs');
const Database = require('../.');

describe('new Database()', function () {
	it('should throw when file path is not a string', function () {
		expect(() => new Database()).to.throw(TypeError);
		expect(() => new Database(null)).to.throw(TypeError);
		expect(() => new Database(0)).to.throw(TypeError);
		expect(() => new Database(123)).to.throw(TypeError);
		expect(() => new Database(new String(util.next()))).to.throw(TypeError);
		expect(() => new Database(() => util.next())).to.throw(TypeError);
		expect(() => new Database([util.next()])).to.throw(TypeError);
	});
	it('should throw when file path is empty', function () {
		expect(() => new Database('')).to.throw(TypeError);
	});
	it('should throw when boolean options are provided as non-booleans', function () {
		expect(() => new Database(util.next(), { readOnly: false })).to.throw(TypeError);
		expect(() => new Database(util.next(), { readonly: undefined })).to.throw(TypeError);
		expect(() => new Database(util.next(), { memory: undefined })).to.throw(TypeError);
		expect(() => new Database(util.next(), { fileMustExist: undefined })).to.throw(TypeError);
	});
	it('should not allow URI file paths', function () {
		expect(() => new Database(`FILE:${util.next()}`)).to.throw(TypeError);
		expect(() => new Database(`file:${util.next()}`)).to.throw(TypeError);
		expect(() => new Database(`file:${util.next()}?mode=memory&cache=shared`)).to.throw(TypeError);
	});
	it('should allow disk-bound databases to be created', function () {
		expect(existsSync(util.next())).to.be.false;
		const db = Database(util.current());
		expect(db.name).to.equal(util.current());
		expect(db.memory).to.be.false;
		expect(db.readonly).to.be.false;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
		expect(existsSync(util.current())).to.be.true;
	});
	it('should allow named in-memory databases to be created', function () {
		expect(existsSync(util.next())).to.be.false;
		const db = new Database(util.current(), { memory: true });
		expect(db.name).to.equal(util.current());
		expect(db.memory).to.be.true;
		expect(db.readonly).to.be.false;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
		expect(existsSync(util.current())).to.be.false;
	});
	it('should allow anonymous in-memory databases to be created', function () {
		const db = new Database(':memory:');
		expect(db.name).to.equal(':memory:');
		expect(db.memory).to.be.true;
		expect(db.readonly).to.be.false;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
		expect(existsSync(':memory:')).to.be.false;
	});
	it('should not allow conflicting in-memory options', function () {
		expect(() => new Database(':memory:', { memory: false })).to.throw(TypeError);
		(new Database(':memory:', { memory: true })).close();
	});
	it('should allow readonly database connections to be created', function () {
		expect(existsSync(util.next())).to.be.false;
		expect(() => new Database(util.current(), { readonly: true })).to.throw(Database.SqliteError).with.property('code', 'SQLITE_CANTOPEN');
		(new Database(util.current())).close();
		expect(existsSync(util.current())).to.be.true;
		const db = new Database(util.current(), { readonly: true });
		expect(db.name).to.equal(util.current());
		expect(db.memory).to.be.false;
		expect(db.readonly).to.be.true;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
		expect(existsSync(util.current())).to.be.true;
	});
	it('should not allow the "readonly" option for in-memory databases', function () {
		expect(existsSync(util.next())).to.be.false;
		expect(() => new Database(util.current(), { memory: true, readonly: true })).to.throw(TypeError);
		expect(() => new Database(':memory:', { readonly: true })).to.throw(TypeError);
		expect(existsSync(util.current())).to.be.false;
	});
	it('should accept the "fileMustExist" option', function () {
		expect(existsSync(util.next())).to.be.false;
		expect(() => new Database(util.current(), { fileMustExist: true })).to.throw(Database.SqliteError).with.property('code', 'SQLITE_CANTOPEN');
		(new Database(util.current())).close();
		expect(existsSync(util.current())).to.be.true;
		const db = new Database(util.current(), { fileMustExist: true });
		expect(db.name).to.equal(util.current());
		expect(db.memory).to.be.false;
		expect(db.readonly).to.be.false;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
		expect(existsSync(util.current())).to.be.true;
	});
	it('should throw an Error if opening the database failed', function () {
		expect(existsSync(util.next())).to.be.false;
		expect(() => new Database(`temp/nonexistent/abcfoobar123/${util.current()}`)).to.throw(TypeError);
		expect(existsSync(util.current())).to.be.false;
	});
	it('should have a proper prototype chain', function () {
		const db = new Database(util.next());
		expect(db).to.be.an.instanceof(Database);
		expect(db.constructor).to.equal(Database);
		expect(Database.prototype.constructor).to.equal(Database);
		expect(Database.prototype.close).to.be.a('function');
		expect(Database.prototype.close).to.equal(db.close);
		expect(Database.prototype).to.equal(Object.getPrototypeOf(db));
	});
});
