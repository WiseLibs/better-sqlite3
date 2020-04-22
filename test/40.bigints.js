'use strict';
const Database = require('../.');

describe('BigInts', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
		this.db.prepare('CREATE TABLE entries (a INTEGER, b REAL, c TEXT)').run();
	});
	afterEach(function () {
		this.db.close();
	});

	it('should bind to prepared statements', function () {
		const int = BigInt('1006028374637854687');
		this.db.prepare('INSERT INTO entries VALUES (?, ?, ?)').run(int, int, int);
		this.db.prepare('INSERT INTO entries VALUES (?, ?, ?)').bind(int, int, int).run();

		const db2 = new Database(util.next());
		try {
			db2.prepare('CREATE TABLE entries (a INTEGER, b REAL, c TEXT)').run();
			db2.prepare('INSERT INTO entries VALUES (?, ?, ?)').run(int, int, int);
			db2.prepare('INSERT INTO entries VALUES (?, ?, ?)').bind(int, int, int).run();
		} finally {
			db2.close();
		}
	});
	it('should be allowed as a return value in user-defined functions', function () {
		this.db.function('returnsInteger', a => BigInt(a + a));
		expect(this.db.prepare('SELECT returnsInteger(?)').pluck().get(42)).to.equal(84);
	});
	it('should get returned by operations after setting .safeIntegers()', function () {
		const int = BigInt('1006028374637854687');
		this.db.prepare('INSERT INTO entries VALUES (?, ?, ?)').run(int, int, int);
		this.db.prepare('INSERT INTO entries VALUES (?, ?, ?)').run(int, int, int);

		let stmt = this.db.prepare('SELECT a FROM entries').pluck();
		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt.safeIntegers().get()).to.deep.equal(int);
		expect(stmt.get()).to.deep.equal(int);
		expect(stmt.safeIntegers(false).get()).to.equal(1006028374637854700);
		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt.safeIntegers(true).get()).to.deep.equal(int);
		expect(stmt.get()).to.deep.equal(int);

		stmt = this.db.prepare('SELECT b FROM entries').pluck();
		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt.safeIntegers().get()).to.equal(1006028374637854700);

		stmt = this.db.prepare('SELECT c FROM entries').pluck();
		expect(stmt.get()).to.equal('1006028374637854687');
		expect(stmt.safeIntegers().get()).to.equal('1006028374637854687');

		let lastRowid = this.db.prepare('SELECT rowid FROM entries ORDER BY rowid DESC').pluck().get();
		stmt = this.db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		expect(stmt.run(int, int, int).lastInsertRowid).to.equal(++lastRowid);
		expect(stmt.safeIntegers().run(int, int, int).lastInsertRowid).to.deep.equal(BigInt(++lastRowid));
		expect(stmt.run(int, int, int).lastInsertRowid).to.deep.equal(BigInt(++lastRowid));
		expect(stmt.safeIntegers(false).run(int, int, int).lastInsertRowid).to.equal(++lastRowid);
	});
	it('should get passed to functions defined with the "safeIntegers" option', function () {
		this.db.function('customfunc', { safeIntegers: true }, (a) => { return (typeof a) + a; });
		expect(this.db.prepare('SELECT customfunc(?)').pluck().get(2)).to.equal('number2');
		expect(this.db.prepare('SELECT customfunc(?)').pluck().get(BigInt(2))).to.equal('bigint2');
	});
	it('should respect the default setting on the database', function () {
		let arg;
		const int = BigInt('1006028374637854687');
		const customFunctionArg = (name, options, dontDefine) => {
			dontDefine || this.db.function(name, options, (a) => { arg = a; });
			this.db.prepare(`SELECT ${name}(?)`).get(int);
			return arg;
		};
		this.db.prepare('INSERT INTO entries VALUES (?, ?, ?)').run(int, int, int);
		this.db.defaultSafeIntegers(true);

		const stmt = this.db.prepare('SELECT a FROM entries').pluck();
		expect(stmt.get()).to.deep.equal(int);
		expect(stmt.safeIntegers(false).get()).to.equal(1006028374637854700);
		expect(customFunctionArg('a1')).to.deep.equal(int);
		expect(customFunctionArg('a2', { safeIntegers: false })).to.equal(1006028374637854700);

		this.db.defaultSafeIntegers(false);

		const stmt2 = this.db.prepare('SELECT a FROM entries').pluck();
		expect(stmt2.get()).to.equal(1006028374637854700);
		expect(stmt2.safeIntegers().get()).to.deep.equal(int);
		expect(customFunctionArg('a3')).to.equal(1006028374637854700);
		expect(customFunctionArg('a4', { safeIntegers: true })).to.deep.equal(int);

		this.db.defaultSafeIntegers();

		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt2.get()).to.deep.equal(int);
		expect(customFunctionArg('a1', {}, true)).to.deep.equal(int);
		expect(customFunctionArg('a2', {}, true)).to.equal(1006028374637854700);
		expect(customFunctionArg('a3', {}, true)).to.equal(1006028374637854700);
		expect(customFunctionArg('a4', {}, true)).to.deep.equal(int);

		const stmt3 = this.db.prepare('SELECT a FROM entries').pluck();
		expect(stmt3.get()).to.deep.equal(int);
		expect(stmt3.safeIntegers(false).get()).to.equal(1006028374637854700);
		expect(customFunctionArg('a5')).to.deep.equal(int);
		expect(customFunctionArg('a6', { safeIntegers: false })).to.equal(1006028374637854700);
	});
});
