'use strict';
const Database = require('../.');

describe('Statement#toString()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
		this.db.prepare('CREATE TABLE entries (a TEXT, b INTEGER, c BLOB)').run();
	});
	afterEach(function () {
		this.db.close();
	});

	it('should return the source SQL for a statement with no parameters', function () {
		const source = 'SELECT * FROM entries';
		const stmt = this.db.prepare(source);
		expect(stmt.toString()).to.equal(source);
		expect(stmt.toString()).to.equal(stmt.source);
	});
	it('should return the source SQL when parameters have not been bound', function () {
		const source = 'SELECT * FROM entries WHERE a = ? AND b = ?';
		const stmt = this.db.prepare(source);
		expect(stmt.toString()).to.equal(source);
		expect(stmt.toString()).to.equal(stmt.source);
	});
	it('should not use temporary parameters passed to execution methods', function () {
		this.db.exec("INSERT INTO entries (a, b) VALUES ('foobar', 1), ('foobar', 2)");
		const source = 'SELECT b FROM entries WHERE a = ?';
		const stmt = this.db.prepare(source);
		const yielded = [];
		for (const { b } of stmt.iterate('foobar')) {
			yielded.push(b);
			expect(stmt.toString()).to.equal(source);
		}
		expect(stmt.toString()).to.equal(source);
		expect(yielded).to.deep.equal([1, 2]);
	});
	it('should return the expanded SQL after parameters are bound', function () {
		const stmt = this.db.prepare('SELECT * FROM entries WHERE a = ? AND b = ?');
		stmt.bind('foo', 25);
		expect(stmt.toString()).to.equal("SELECT * FROM entries WHERE a = 'foo' AND b = 25.0");
	});
	it('should expand NULL and blob parameters', function () {
		const stmt = this.db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		stmt.bind(null, 25, Buffer.from([0xde, 0xad]));
		expect(stmt.toString()).to.equal("INSERT INTO entries VALUES (NULL, 25.0, x'dead')");
	});
	it('should return the source SQL when bound with no parameters', function () {
		const source = 'SELECT 555';
		const stmt = this.db.prepare(source);
		stmt.bind();
		expect(stmt.toString()).to.equal(source);
	});
	it('should return the source SQL after the database is closed', function () {
		const source = 'SELECT * FROM entries WHERE a = ?';
		const stmt = this.db.prepare(source);
		stmt.bind('foobar');
		expect(stmt.toString()).to.equal("SELECT * FROM entries WHERE a = 'foobar'");
		this.db.close();
		expect(stmt.toString()).to.equal(source);
		expect(stmt.toString()).to.equal(stmt.source);
	});
	it('should be used when coercing a statement to a string', function () {
		const stmt = this.db.prepare('SELECT * FROM entries WHERE a = ? AND b = ?');
		expect(String(stmt)).to.equal('SELECT * FROM entries WHERE a = ? AND b = ?');
		expect(`${stmt}`).to.equal('SELECT * FROM entries WHERE a = ? AND b = ?');
		stmt.bind('foo', 25);
		expect('' + stmt).to.equal("SELECT * FROM entries WHERE a = 'foo' AND b = 25.0");
	});
});
