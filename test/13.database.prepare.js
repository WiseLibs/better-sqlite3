'use strict';
const { expect } = require('chai');
const Database = require('../.');
const util = require('./util');

describe('Database#prepare()', function () {
	const assertStmt = (stmt, source, db, returnsData) => {
		expect(stmt.source).to.equal(source);
		expect(stmt.constructor.name).to.equal('Statement');
		expect(stmt.database).to.equal(db);
		expect(stmt.returnsData).to.equal(returnsData);
		expect(() => new stmt.constructor(source)).to.throw(TypeError);
	};
	it('should throw an exception if a string is not provided', function () {
		const db = new Database(util.next());
		expect(() => db.prepare(123)).to.throw(TypeError);
		expect(() => db.prepare(0)).to.throw(TypeError);
		expect(() => db.prepare(null)).to.throw(TypeError);
		expect(() => db.prepare()).to.throw(TypeError);
		expect(() => db.prepare(new String('CREATE TABLE people (name TEXT)'))).to.throw(TypeError);
	});
	it('should throw an exception if invalid SQL is provided', function () {
		const db = new Database(util.next());
		expect(() => db.prepare('CREATE TABLE people (name TEXT')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(() => db.prepare('INSERT INTO people VALUES (?)')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
	});
	it('should throw an exception if no statements are provided', function () {
		const db = new Database(util.next());
		expect(() => db.prepare('')).to.throw(RangeError);
		expect(() => db.prepare(';')).to.throw(RangeError);
	});
	it('should throw an exception if more than one statement is provided', function () {
		const db = new Database(util.next());
		expect(() => db.prepare('CREATE TABLE people (name TEXT);CREATE TABLE animals (name TEXT)')).to.throw(RangeError);
		expect(() => db.prepare('CREATE TABLE people (name TEXT); ')).to.throw(RangeError);
		expect(() => db.prepare('CREATE TABLE people (name TEXT);;')).to.throw(RangeError);
	});
	it('should create a prepared Statement object', function () {
		const db = new Database(util.next());
		const stmt1 = db.prepare('CREATE TABLE people (name TEXT)');
		const stmt2 = db.prepare('CREATE TABLE people (name TEXT);');
		assertStmt(stmt1, 'CREATE TABLE people (name TEXT)', db, false);
		assertStmt(stmt2, 'CREATE TABLE people (name TEXT);', db, false);
		expect(stmt1).to.not.equal(stmt2);
		expect(stmt1).to.not.equal(db.prepare('CREATE TABLE people (name TEXT)'));
	});
	it('should create a prepared Statement object with just an expression', function () {
		const db = new Database(util.next());
		const stmt = db.prepare('SELECT 555');
		assertStmt(stmt, 'SELECT 555', db, true);
	});
});
