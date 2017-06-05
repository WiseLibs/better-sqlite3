var expect = require('chai').expect;
var Database = require('../.');
var util = (function () {
	var path = require('path');
	var dbId = 0;
	var obj;
	return obj = {
		current: function () {
			return 'temp/' + path.basename(__filename).split('.')[0] + '.' + dbId + '.db';
		},
		next: function () {++dbId; return obj.current();}
	};
}());

describe('Database#prepare()', function () {
	function assertStmt(stmt, source, db, returnsData) {
		expect(stmt.source).to.equal(source);
		expect(stmt.constructor.name).to.equal('Statement');
		expect(stmt.database).to.equal(db);
		expect(stmt.returnsData).to.equal(returnsData);
		expect(function () {
			new stmt.constructor(source);
		}).to.throw(TypeError);
	}
	it('should throw an exception if a string is not provided', function () {
		var db = new Database(util.next());
		expect(function () {db.prepare(123);}).to.throw(TypeError);
		expect(function () {db.prepare(0);}).to.throw(TypeError);
		expect(function () {db.prepare(null);}).to.throw(TypeError);
		expect(function () {db.prepare();}).to.throw(TypeError);
		expect(function () {db.prepare(new String('CREATE TABLE people (name TEXT)'));}).to.throw(TypeError);
	});
	it('should throw an exception if invalid SQL is provided', function () {
		var db = new Database(util.next());
		expect(function () {db.prepare('CREATE TABLE people (name TEXT');}).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(function () {db.prepare('INSERT INTO people VALUES (?)');}).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
	});
	it('should throw an exception if no statements are provided', function () {
		var db = new Database(util.next());
		expect(function () {db.prepare('');}).to.throw(RangeError);
		expect(function () {db.prepare(';');}).to.throw(RangeError);
	});
	it('should throw an exception if more than one statement is provided', function () {
		var db = new Database(util.next());
		expect(function () {db.prepare('CREATE TABLE people (name TEXT);CREATE TABLE animals (name TEXT)');}).to.throw(RangeError);
		expect(function () {db.prepare('CREATE TABLE people (name TEXT); ');}).to.throw(RangeError);
		expect(function () {db.prepare('CREATE TABLE people (name TEXT);;');}).to.throw(RangeError);
	});
	it('should create a prepared Statement object', function () {
		var db = new Database(util.next());
		var stmt1 = db.prepare('CREATE TABLE people (name TEXT)');
		var stmt2 = db.prepare('CREATE TABLE people (name TEXT);');
		assertStmt(stmt1, 'CREATE TABLE people (name TEXT)', db, false);
		assertStmt(stmt2, 'CREATE TABLE people (name TEXT);', db, false);
		expect(stmt1).to.not.equal(stmt2);
		expect(stmt1).to.not.equal(db.prepare('CREATE TABLE people (name TEXT)'));
	});
	it('should create a prepared Statement object with just an expression', function () {
		var db = new Database(util.next());
		var stmt = db.prepare('SELECT 555');
		assertStmt(stmt, 'SELECT 555', db, true);
	});
});
