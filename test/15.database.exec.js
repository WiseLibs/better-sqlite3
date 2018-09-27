'use strict';
const Database = require('../.');

describe('Database#exec()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
	});
	afterEach(function () {
		this.db.close();
	});
	
	it('should throw an exception if a string is not provided', function () {
		expect(() => this.db.exec(123)).to.throw(TypeError);
		expect(() => this.db.exec(0)).to.throw(TypeError);
		expect(() => this.db.exec(null)).to.throw(TypeError);
		expect(() => this.db.exec()).to.throw(TypeError);
		expect(() => this.db.exec(new String('CREATE TABLE entries (a TEXT, b INTEGER)'))).to.throw(TypeError);
	});
	it('should throw an exception if invalid SQL is provided', function () {
		expect(() => this.db.exec('CREATE TABLE entries (a TEXT, b INTEGER')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
	});
	it('should obey the restrictions of readonly mode', function () {
		this.db.close();
		this.db = new Database(util.current(), { readonly: true });
		expect(() => this.db.exec('CREATE TABLE people (name TEXT)')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_READONLY');
		this.db.exec('SELECT 555');
	});
	it('should execute the SQL, returning the database object itself', function () {
		const returnValues = [];
		
		const r1 = this.db.exec('CREATE TABLE entries (a TEXT, b INTEGER)');
		const r2 = this.db.exec('INSERT INTO entries VALUES (\'foobar\', 44); INSERT INTO entries VALUES (\'baz\', NULL);');
		const r3 = this.db.exec('SELECT * FROM entries');
		
		expect(r1).to.equal(this.db);
		expect(r2).to.equal(this.db);
		expect(r3).to.equal(this.db);
		
		const rows = this.db.prepare('SELECT * FROM entries ORDER BY rowid').all();
		expect(rows.length).to.equal(2);
		expect(rows[0].a).to.equal('foobar');
		expect(rows[0].b).to.equal(44);
		expect(rows[1].a).to.equal('baz');
		expect(rows[1].b).to.equal(null);
	});
});
