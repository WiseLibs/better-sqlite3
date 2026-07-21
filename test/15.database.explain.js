'use strict';
const Database = require('../.');

describe('Database#explain()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
		this.db.prepare('CREATE TABLE entries (a TEXT, b INTEGER)').run();
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
	it('should throw an exception if invalid SQL is provided', function () {
		expect(() => this.db.explain('SELECT * FROM nonexistent')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(() => this.db.explain('CREATE TABLE entries (a TEXT')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
	});
	it('should return the bytecode program as an array of rows', function () {
		const program = this.db.explain('SELECT * FROM entries');
		expect(program).to.be.an('array');
		expect(program.length).to.be.above(0);
		for (const row of program) {
			expect(row).to.be.an('object');
			expect(row.addr).to.be.a('number');
			expect(row.opcode).to.be.a('string');
			expect(row).to.have.keys(['addr', 'opcode', 'p1', 'p2', 'p3', 'p4', 'p5', 'comment']);
		}
		expect(program.some(row => row.opcode === 'Halt')).to.be.true;
	});
	it('should explain statements with unbound parameters', function () {
		// A normal prepared statement cannot be executed without its parameters.
		expect(() => this.db.prepare('SELECT * FROM entries WHERE a = ?').all()).to.throw(RangeError);

		const program = this.db.explain('SELECT * FROM entries WHERE a = ?');
		expect(program).to.be.an('array');
		expect(program.length).to.be.above(0);
	});
	it('should explain statements with multiple unbound parameters', function () {
		const program = this.db.explain('SELECT * FROM entries WHERE a = ? AND b = @b');
		expect(program).to.be.an('array');
		expect(program.length).to.be.above(0);
	});
	it('should return the query plan when prefixed with QUERY PLAN', function () {
		const plan = this.db.explain('QUERY PLAN SELECT * FROM entries');
		expect(plan).to.be.an('array');
		expect(plan.length).to.be.above(0);
		for (const row of plan) {
			expect(row).to.be.an('object');
			expect(row).to.have.keys(['id', 'parent', 'notused', 'detail']);
			expect(row.detail).to.be.a('string');
		}
		expect(plan.some(row => /entries/.test(row.detail))).to.be.true;
	});
});
