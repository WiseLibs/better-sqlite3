'use strict';
const Database = require('../lib');

describe('Database#explain()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
		this.db.exec('CREATE TABLE entries (a TEXT, b INTEGER, c REAL)');
		this.db.exec("INSERT INTO entries VALUES ('foo', 1, 3.14), ('bar', 2, 2.71)");
	});
	afterEach(function () {
		this.db.close();
	});

	it('should throw an exception if a string is not provided', function () {
		expect(() => this.db.explain(123)).to.throw(TypeError);
		expect(() => this.db.explain(0)).to.throw(TypeError);
		expect(() => this.db.explain(null)).to.throw(TypeError);
		expect(() => this.db.explain()).to.throw(TypeError);
		expect(() => this.db.explain(new String('SELECT * FROM entries'))).to.throw(TypeError);
	});

	it('should execute a simple EXPLAIN query without parameters', function () {
		const plan = this.db.explain('SELECT * FROM entries');
		expect(plan).to.be.an('array');
		expect(plan.length).to.be.greaterThan(0);
		expect(plan[0]).to.be.an('object');
		expect(plan[0]).to.have.property('opcode');
	});

	it('should work with EXPLAIN already in the SQL', function () {
		const plan1 = this.db.explain('SELECT * FROM entries');
		const plan2 = this.db.explain('EXPLAIN SELECT * FROM entries');
		expect(plan1).to.deep.equal(plan2);
	});

	it('should work with EXPLAIN QUERY PLAN', function () {
		const plan = this.db.explain("EXPLAIN QUERY PLAN SELECT * FROM entries WHERE a = 'foo'");
		expect(plan).to.be.an('array');
		expect(plan.length).to.be.greaterThan(0);
		expect(plan[0]).to.be.an('object');
	});

	it('should handle queries with parameters without throwing errors', function () {
		const plan1 = this.db.explain('SELECT * FROM entries WHERE a = ?');
		expect(plan1).to.be.an('array');
		expect(plan1.length).to.be.greaterThan(0);

		const plan2 = this.db.explain('SELECT * FROM entries WHERE a = :name AND b = :value');
		expect(plan2).to.be.an('array');
		expect(plan2.length).to.be.greaterThan(0);
	});

	it('should handle complex queries with multiple parameters', function () {
		const plan = this.db.explain('SELECT * FROM entries WHERE a = ? AND b > ? AND c < ?');
		expect(plan).to.be.an('array');
		expect(plan.length).to.be.greaterThan(0);
	});

	it('should work with JOIN queries', function () {
		this.db.exec('CREATE TABLE users (id INTEGER, name TEXT)');
		const plan = this.db.explain('SELECT * FROM entries JOIN users ON entries.b = users.id WHERE users.name = ?');
		expect(plan).to.be.an('array');
		expect(plan.length).to.be.greaterThan(0);
	});

	it('should throw an exception for invalid SQL', function () {
		expect(() => this.db.explain('INVALID SQL')).to.throw(Database.SqliteError);
		expect(() => this.db.explain('SELECT * FROM nonexistent')).to.throw(Database.SqliteError);
	});

	it('should work with case insensitive EXPLAIN', function () {
		const plan1 = this.db.explain('explain SELECT * FROM entries');
		const plan2 = this.db.explain('ExPlAiN SELECT * FROM entries');
		const plan3 = this.db.explain('EXPLAIN SELECT * FROM entries');
		expect(plan1.length).to.equal(plan2.length);
		expect(plan2.length).to.equal(plan3.length);
	});

	it('should respect readonly connections', function () {
		this.db.close();
		this.db = new Database(util.current(), { readonly: true, fileMustExist: true });
		const plan = this.db.explain('SELECT * FROM entries WHERE a = ?');
		expect(plan).to.be.an('array');
		expect(plan.length).to.be.greaterThan(0);
	});
});

