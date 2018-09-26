'use strict';
const { existsSync } = require('fs');
const Database = require('../.');

describe('new Database()', function () {
	it('should throw an exception when file path is not a string', function () {
		expect(() => new Database()).to.throw(TypeError);
		expect(() => new Database(null)).to.throw(TypeError);
		expect(() => new Database(0)).to.throw(TypeError);
		expect(() => new Database(123)).to.throw(TypeError);
		expect(() => new Database(new String(util.next()))).to.throw(TypeError);
		expect(() => new Database(() => {})).to.throw(TypeError);
		expect(() => new Database([util.next()])).to.throw(TypeError);
	});
	it('should throw an exception when file path is empty', function () {
		expect(() => new Database('')).to.throw(TypeError);
	});
	it('should not allow URI file paths', function () {
		expect(() => new Database(`file: ${util.next()}`)).to.throw(TypeError);
		expect(() => new Database(`file: ${util.next()}?mode=memory&cache=shared`)).to.throw(TypeError);
	});
	it('should not allow ":memory:" databases', function () {
		expect(() => new Database(':memory:')).to.throw(TypeError);
	});
	it('should allow disk-based databases to be created', function () {
		expect(existsSync(util.next())).to.be.false;
		const db = Database(util.current());
		expect(db.name).to.equal(util.current());
		expect(db.memory).to.be.false;
		expect(db.readonly).to.be.false;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
		expect(existsSync(util.current())).to.be.true;
	});
	it('should allow in-memory databases to be created', function () {
		expect(existsSync(util.next())).to.be.false;
		const db = new Database(util.current(), { memory: true });
		expect(db.name).to.equal(util.current());
		expect(db.memory).to.be.true;
		expect(db.readonly).to.be.false;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
		expect(existsSync(util.current())).to.be.false;
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
	it('should allow the "readonly" and "memory" options on the same connection', function () {
		expect(existsSync(util.next())).to.be.false;
		const db = new Database(util.current(), { memory: true, readonly: true });
		expect(db.name).to.equal(util.current());
		expect(db.memory).to.be.true;
		expect(db.readonly).to.be.true;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
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
	it('should ignore "fileMustExist" when the "memory" option is true', function () {
		expect(existsSync(util.next())).to.be.false;
		const db = new Database(util.current(), { memory: true, fileMustExist: true });
		expect(db.name).to.equal(util.current());
		expect(db.memory).to.be.true;
		expect(db.readonly).to.be.false;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
		expect(existsSync(util.current())).to.be.false;
	});
	it('should throw an Error if opening the database failed', function () {
		expect(existsSync(util.next())).to.be.false;
		expect(() => new Database(`temp/nonexistent/abcfoobar123/${util.current()}`)).to.throw(TypeError);
		expect(existsSync(util.current())).to.be.false;
	})
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
