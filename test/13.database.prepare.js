'use strict';
const Database = require('../.');

describe('Database#prepare()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
	});
	afterEach(function () {
		this.db.close();
	});

	function assertStmt(stmt, source, db, reader) {
		expect(stmt.source).to.equal(source);
		expect(stmt.constructor.name).to.equal('Statement');
		expect(stmt.database).to.equal(db);
		expect(stmt.reader).to.equal(reader);
		expect(() => new stmt.constructor(source)).to.throw(TypeError);
	}

	it('should throw an exception if a string is not provided', function () {
		expect(() => this.db.prepare(123)).to.throw(TypeError);
		expect(() => this.db.prepare(0)).to.throw(TypeError);
		expect(() => this.db.prepare(null)).to.throw(TypeError);
		expect(() => this.db.prepare()).to.throw(TypeError);
		expect(() => this.db.prepare(new String('CREATE TABLE people (name TEXT)'))).to.throw(TypeError);
	});
	it('should throw an exception if invalid SQL is provided', function () {
		expect(() => this.db.prepare('CREATE TABLE people (name TEXT')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(() => this.db.prepare('INSERT INTO people VALUES (?)')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
	});
	it('should throw an exception if no statements are provided', function () {
		expect(() => this.db.prepare('')).to.throw(RangeError);
		expect(() => this.db.prepare(';')).to.throw(RangeError);
	});
	it('should throw an exception if more than one statement is provided', function () {
		expect(() => this.db.prepare('CREATE TABLE people (name TEXT);CREATE TABLE animals (name TEXT)')).to.throw(RangeError);
		expect(() => this.db.prepare('CREATE TABLE people (name TEXT);/')).to.throw(RangeError);
		expect(() => this.db.prepare('CREATE TABLE people (name TEXT);-')).to.throw(RangeError);
	});
	it('should create a prepared Statement object', function () {
		const stmt1 = this.db.prepare('CREATE TABLE people (name TEXT) ');
		const stmt2 = this.db.prepare('CREATE TABLE people (name TEXT); ');
		assertStmt(stmt1, 'CREATE TABLE people (name TEXT) ', this.db, false);
		assertStmt(stmt2, 'CREATE TABLE people (name TEXT); ', this.db, false);
		expect(stmt1).to.not.equal(stmt2);
		expect(stmt1).to.not.equal(this.db.prepare('CREATE TABLE people (name TEXT) '));
	});
	it('should create a prepared Statement object with just an expression', function () {
		const stmt = this.db.prepare('SELECT 555');
		assertStmt(stmt, 'SELECT 555', this.db, true);
	});
});
