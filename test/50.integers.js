const { expect } = require('chai');
const Integer = require('integer');
const Database = require('../.');
const util = require('./util');

const db = new Database(util.next());
const db2 = new Database(util.next());

before(function () {
	db.prepare('CREATE TABLE entries (a INTEGER, b REAL, c TEXT)').run();
	db2.prepare('CREATE TABLE entries (a INTEGER, b REAL, c TEXT)').run();
});

describe('64-bit integers', function () {
	it('should bind to statements and transactions', function () {
		const int = Integer.fromBits(4243423, 234234234);
		db.prepare('INSERT INTO entries VALUES (?, ?, ?)').run(int, int, int);
		db.transaction(['INSERT INTO entries VALUES (?, ?, ?)']).run(int, int, int);
		db.prepare('INSERT INTO entries VALUES (?, ?, ?)').bind(int, int, int).run();
		db.transaction(['INSERT INTO entries VALUES (?, ?, ?)']).bind(int, int, int).run();
		
		db2.prepare('INSERT INTO entries VALUES (?, ?, ?)').run(int, int, int);
		db2.transaction(['INSERT INTO entries VALUES (?, ?, ?)']).run(int, int, int);
		db2.prepare('INSERT INTO entries VALUES (?, ?, ?)').bind(int, int, int).run();
		db2.transaction(['INSERT INTO entries VALUES (?, ?, ?)']).bind(int, int, int).run();
	});
	it('should be allowed as a return value in registered functions', function () {
		db.register(function returnsInteger(a) { return Integer(a + a); });
		expect(db.prepare('SELECT returnsInteger(?)').pluck().get(42)).to.equal(84);
	});
	it('should get returned by operations after setting .safeIntegers()', function () {
		const int = Integer.fromBits(4243423, 234234234);
		let stmt = db.prepare('SELECT a FROM entries').pluck();
		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt.safeIntegers().get()).to.deep.equal(int);
		expect(stmt.get()).to.deep.equal(int);
		expect(stmt.safeIntegers(false).get()).to.equal(1006028374637854700);
		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt.safeIntegers(true).get()).to.deep.equal(int);
		expect(stmt.get()).to.deep.equal(int);
		
		stmt = db.prepare('SELECT b FROM entries').pluck();
		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt.safeIntegers().get()).to.equal(1006028374637854700);
		
		stmt = db.prepare('SELECT c FROM entries').pluck();
		expect(stmt.get()).to.equal('1006028374637854687');
		expect(stmt.safeIntegers().get()).to.equal('1006028374637854687');
		
		let lastRowid = db.prepare('SELECT rowid FROM entries ORDER BY rowid DESC').pluck().get();
		stmt = db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		expect(stmt.run(int, int, int).lastInsertROWID).to.equal(++lastRowid);
		expect(stmt.safeIntegers().run(int, int, int).lastInsertROWID).to.deep.equal(Integer(++lastRowid));
		expect(stmt.run(int, int, int).lastInsertROWID).to.deep.equal(Integer(++lastRowid));
		expect(stmt.safeIntegers(false).run(int, int, int).lastInsertROWID).to.equal(++lastRowid);
		
		const trans = db.transaction(['INSERT INTO entries VALUES (?, ?, ?)']);
		expect(trans.run(int, int, int).lastInsertROWID).to.equal(++lastRowid);
		expect(trans.safeIntegers().run(int, int, int).lastInsertROWID).to.deep.equal(Integer(++lastRowid));
		expect(trans.run(int, int, int).lastInsertROWID).to.deep.equal(Integer(++lastRowid));
		expect(trans.safeIntegers(false).run(int, int, int).lastInsertROWID).to.equal(++lastRowid);
	});
	it('should get passed to functions registered with the "safeIntegers" option', function () {
		db.register({ safeIntegers: true }, function customfunc(a) { return a.low; });
		expect(db.prepare('SELECT customfunc(?)').pluck().get(2)).to.equal(null);
		expect(db.prepare('SELECT customfunc(?)').pluck().get(Integer.fromBits(2, 2))).to.equal(2);
	});
	it('should respect the default setting on the database', function () {
		let arg;
		const int = Integer.fromBits(4243423, 234234234);
		function customFunctionArg(options, dontRegister) {
			dontRegister || db.register(options, (a) => { arg = a; });
			db.prepare(`SELECT ${options.name}(?)`).get(int);
			return arg;
		}
		db.defaultSafeIntegers(true);
		
		const stmt = db.prepare('SELECT a FROM entries').pluck();
		expect(stmt.get()).to.deep.equal(int);
		expect(stmt.safeIntegers(false).get()).to.equal(1006028374637854700);
		expect(customFunctionArg({ name: 'a1' })).to.deep.equal(int);
		expect(customFunctionArg({ name: 'a2', safeIntegers: false })).to.equal(1006028374637854700);
		
		db.defaultSafeIntegers(false);
		
		const stmt2 = db.prepare('SELECT a FROM entries').pluck();
		expect(stmt2.get()).to.equal(1006028374637854700);
		expect(stmt2.safeIntegers().get()).to.deep.equal(int);
		expect(customFunctionArg({ name: 'a3' })).to.equal(1006028374637854700);
		expect(customFunctionArg({ name: 'a4', safeIntegers: true })).to.deep.equal(int);
		
		db.defaultSafeIntegers();
		
		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt2.get()).to.deep.equal(int);
		expect(customFunctionArg({ name: 'a1' }, true)).to.deep.equal(int);
		expect(customFunctionArg({ name: 'a2' }, true)).to.equal(1006028374637854700);
		expect(customFunctionArg({ name: 'a3' }, true)).to.equal(1006028374637854700);
		expect(customFunctionArg({ name: 'a4' }, true)).to.deep.equal(int);
		
		const stmt3 = db.prepare('SELECT a FROM entries').pluck();
		expect(stmt3.get()).to.deep.equal(int);
		expect(stmt3.safeIntegers(false).get()).to.equal(1006028374637854700);
		expect(customFunctionArg({ name: 'a5' })).to.deep.equal(int);
		expect(customFunctionArg({ name: 'a6', safeIntegers: false })).to.equal(1006028374637854700);
	});
	it('should forbid invoking .safeIntegers() while the database is busy', function () {
		let ranOnce = false;
		const stmt1 = db.prepare('SELECT * FROM entries LIMIT 10');
		const stmt2 = db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		for (const row of stmt1.iterate()) {
			ranOnce = true;
			expect(() => stmt1.safeIntegers()).to.throw(TypeError);
			expect(() => stmt2.safeIntegers()).to.throw(TypeError);
			expect(() => stmt1.safeIntegers(false)).to.throw(TypeError);
			expect(() => stmt2.safeIntegers(false)).to.throw(TypeError);
		}
		expect(ranOnce).to.be.true;
	});
});
