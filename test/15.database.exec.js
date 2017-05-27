var expect = require('chai').expect;
var Database = require('../.');
var db;

before(function () {
	db = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.db');
});

describe('Database#exec()', function () {
	it('should throw an exception if a string is not provided', function () {
		expect(function () {db.exec(123);}).to.throw(TypeError);
		expect(function () {db.exec(0);}).to.throw(TypeError);
		expect(function () {db.exec(null);}).to.throw(TypeError);
		expect(function () {db.exec();}).to.throw(TypeError);
		expect(function () {db.exec(new String('CREATE TABLE entries (a TEXT, b INTEGER)'));}).to.throw(TypeError);
	});
	it('should throw an exception if invalid SQL is provided', function () {
		expect(function () {db.exec('CREATE TABLE entries (a TEXT, b INTEGER');}).to.throw(Error).with.property('code', 'SQLITE_ERROR');
	});
	it('should obey the restrictions of readonly mode', function () {
		var db2 = new Database(db.name, {readonly: true});
		expect(function () {db2.exec('CREATE TABLE people (name TEXT)');}).to.throw(Error).with.property('code', 'SQLITE_READONLY');
		db2.exec('SELECT 555');
	});
	it('should execute the SQL, returning the database object itself', function () {
		var returnValues = [];
		
		var r1 = db.exec('CREATE TABLE entries (a TEXT, b INTEGER)');
		var r2 = db.exec('INSERT INTO entries VALUES (\'foobar\', 44); INSERT INTO entries VALUES (\'baz\', NULL);');
		var r3 = db.exec('SELECT * FROM entries');
		
		expect(r1).to.equal(db);
		expect(r2).to.equal(db);
		expect(r3).to.equal(db);
		
		var rows = db.prepare('SELECT * FROM entries ORDER BY rowid').all();
		expect(rows.length).to.equal(2);
		expect(rows[0].a).to.equal('foobar');
		expect(rows[0].b).to.equal(44);
		expect(rows[1].a).to.equal('baz');
		expect(rows[1].b).to.equal(null);
	});
});
