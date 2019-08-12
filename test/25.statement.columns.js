'use strict';
const Database = require('../.');

describe('Statement#columns()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
		this.db.prepare('CREATE TABLE entries (a TEXT, b INTEGER, c WHATthe)').run();
	});
	afterEach(function () {
		this.db.close();
	});

	it('should throw an exception if invoked on a non-reader statement', function () {
		const stmt = this.db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		expect(() => stmt.columns()).to.throw(TypeError);
	});
	it('should return an array of column descriptors', function () {
		expect(this.db.prepare('SELECT 5.0 as d, * FROM entries').columns()).to.deep.equal([
			{ name: 'd', column: null, table: null, database: null, type: null },
			{ name: 'a', column: 'a', table: 'entries', database: 'main', type: 'TEXT' },
			{ name: 'b', column: 'b', table: 'entries', database: 'main', type: 'INTEGER' },
			{ name: 'c', column: 'c', table: 'entries', database: 'main', type: 'WHATthe' },
		]);
		expect(this.db.prepare('SELECT a, c as b, b FROM entries').columns()).to.deep.equal([
			{ name: 'a', column: 'a', table: 'entries', database: 'main', type: 'TEXT' },
			{ name: 'b', column: 'c', table: 'entries', database: 'main', type: 'WHATthe' },
			{ name: 'b', column: 'b', table: 'entries', database: 'main', type: 'INTEGER' },
		]);
	});
	it('should not return stale column descriptors after being recompiled', function () {
		const stmt = this.db.prepare('SELECT * FROM entries');
		expect(stmt.columns()).to.deep.equal([
			{ name: 'a', column: 'a', table: 'entries', database: 'main', type: 'TEXT' },
			{ name: 'b', column: 'b', table: 'entries', database: 'main', type: 'INTEGER' },
			{ name: 'c', column: 'c', table: 'entries', database: 'main', type: 'WHATthe' },
		]);
		this.db.prepare('ALTER TABLE entries ADD COLUMN d FOOBAR').run();
		stmt.get(); // Recompile
		expect(stmt.columns()).to.deep.equal([
			{ name: 'a', column: 'a', table: 'entries', database: 'main', type: 'TEXT' },
			{ name: 'b', column: 'b', table: 'entries', database: 'main', type: 'INTEGER' },
			{ name: 'c', column: 'c', table: 'entries', database: 'main', type: 'WHATthe' },
			{ name: 'd', column: 'd', table: 'entries', database: 'main', type: 'FOOBAR' },
		]);
	});
});
