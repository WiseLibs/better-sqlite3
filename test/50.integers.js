'use strict';
const Database = require('../.');
const { Integer } = Database;

describe('64-bit integers', function () {
	let db1, db2;
	before(function () {
		db1 = new Database(util.next());
		db2 = new Database(util.next());
		db1.prepare('CREATE TABLE entries (a INTEGER, b REAL, c TEXT)').run();
		db2.prepare('CREATE TABLE entries (a INTEGER, b REAL, c TEXT)').run();
	});
	
	it('should bind to statements and transactions', function () {
		const int = Integer.fromBits(4243423, 234234234);
		db1.prepare('INSERT INTO entries VALUES (?, ?, ?)').run(int, int, int);
		db1.transaction(['INSERT INTO entries VALUES (?, ?, ?)']).run(int, int, int);
		db1.prepare('INSERT INTO entries VALUES (?, ?, ?)').bind(int, int, int).run();
		db1.transaction(['INSERT INTO entries VALUES (?, ?, ?)']).bind(int, int, int).run();
		
		db2.prepare('INSERT INTO entries VALUES (?, ?, ?)').run(int, int, int);
		db2.transaction(['INSERT INTO entries VALUES (?, ?, ?)']).run(int, int, int);
		db2.prepare('INSERT INTO entries VALUES (?, ?, ?)').bind(int, int, int).run();
		db2.transaction(['INSERT INTO entries VALUES (?, ?, ?)']).bind(int, int, int).run();
	});
	it('should be allowed as a return value in user-defined functions', function () {
		db1.function('returnsInteger', (a) => { return Integer(a + a); });
		expect(db1.prepare('SELECT returnsInteger(?)').pluck().get(42)).to.equal(84);
	});
	it('should get returned by operations after setting .safeIntegers()', function () {
		const int = Integer.fromBits(4243423, 234234234);
		let stmt = db1.prepare('SELECT a FROM entries').pluck();
		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt.safeIntegers().get()).to.deep.equal(int);
		expect(stmt.get()).to.deep.equal(int);
		expect(stmt.safeIntegers(false).get()).to.equal(1006028374637854700);
		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt.safeIntegers(true).get()).to.deep.equal(int);
		expect(stmt.get()).to.deep.equal(int);
		
		stmt = db1.prepare('SELECT b FROM entries').pluck();
		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt.safeIntegers().get()).to.equal(1006028374637854700);
		
		stmt = db1.prepare('SELECT c FROM entries').pluck();
		expect(stmt.get()).to.equal('1006028374637854687');
		expect(stmt.safeIntegers().get()).to.equal('1006028374637854687');
		
		let lastRowid = db1.prepare('SELECT rowid FROM entries ORDER BY rowid DESC').pluck().get();
		stmt = db1.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		expect(stmt.run(int, int, int).lastInsertRowid).to.equal(++lastRowid);
		expect(stmt.safeIntegers().run(int, int, int).lastInsertRowid).to.deep.equal(Integer(++lastRowid));
		expect(stmt.run(int, int, int).lastInsertRowid).to.deep.equal(Integer(++lastRowid));
		expect(stmt.safeIntegers(false).run(int, int, int).lastInsertRowid).to.equal(++lastRowid);
		
		const trans = db1.transaction(['INSERT INTO entries VALUES (?, ?, ?)']);
		expect(trans.run(int, int, int).lastInsertRowid).to.equal(++lastRowid);
		expect(trans.safeIntegers().run(int, int, int).lastInsertRowid).to.deep.equal(Integer(++lastRowid));
		expect(trans.run(int, int, int).lastInsertRowid).to.deep.equal(Integer(++lastRowid));
		expect(trans.safeIntegers(false).run(int, int, int).lastInsertRowid).to.equal(++lastRowid);
	});
	it('should get passed to functions defined with the "safeIntegers" option', function () {
		db1.function('customfunc', { safeIntegers: true }, (a) => { return a.low; });
		expect(db1.prepare('SELECT customfunc(?)').pluck().get(2)).to.equal(null);
		expect(db1.prepare('SELECT customfunc(?)').pluck().get(Integer.fromBits(2, 2))).to.equal(2);
	});
	it('should respect the default setting on the database', function () {
		let arg;
		const int = Integer.fromBits(4243423, 234234234);
		function customFunctionArg(name, options, dontDefine) {
			dontDefine || db1.function(name, options, (a) => { arg = a; });
			db1.prepare(`SELECT ${name}(?)`).get(int);
			return arg;
		}
		db1.defaultSafeIntegers(true);
		
		const stmt = db1.prepare('SELECT a FROM entries').pluck();
		expect(stmt.get()).to.deep.equal(int);
		expect(stmt.safeIntegers(false).get()).to.equal(1006028374637854700);
		expect(customFunctionArg('a1')).to.deep.equal(int);
		expect(customFunctionArg('a2', { safeIntegers: false })).to.equal(1006028374637854700);
		
		db1.defaultSafeIntegers(false);
		
		const stmt2 = db1.prepare('SELECT a FROM entries').pluck();
		expect(stmt2.get()).to.equal(1006028374637854700);
		expect(stmt2.safeIntegers().get()).to.deep.equal(int);
		expect(customFunctionArg('a3')).to.equal(1006028374637854700);
		expect(customFunctionArg('a4', { safeIntegers: true })).to.deep.equal(int);
		
		db1.defaultSafeIntegers();
		
		expect(stmt.get()).to.equal(1006028374637854700);
		expect(stmt2.get()).to.deep.equal(int);
		expect(customFunctionArg('a1', {}, true)).to.deep.equal(int);
		expect(customFunctionArg('a2', {}, true)).to.equal(1006028374637854700);
		expect(customFunctionArg('a3', {}, true)).to.equal(1006028374637854700);
		expect(customFunctionArg('a4', {}, true)).to.deep.equal(int);
		
		const stmt3 = db1.prepare('SELECT a FROM entries').pluck();
		expect(stmt3.get()).to.deep.equal(int);
		expect(stmt3.safeIntegers(false).get()).to.equal(1006028374637854700);
		expect(customFunctionArg('a5')).to.deep.equal(int);
		expect(customFunctionArg('a6', { safeIntegers: false })).to.equal(1006028374637854700);
	});
	it('should forbid invoking .safeIntegers() while the database is busy', function () {
		let ranOnce = false;
		const stmt1 = db1.prepare('SELECT * FROM entries LIMIT 10');
		const stmt2 = db1.prepare('INSERT INTO entries VALUES (?, ?, ?)');
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
