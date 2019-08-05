'use strict';
const Database = require('../.');
const { Integer } = Database;

describe('verbose mode', function () {
	afterEach(function () {
		if (this.db) this.db.close();
	});

	it('should throw when not given a function or null/undefined', function () {
		expect(() => (this.db = new Database(util.next(), { verbose: false }))).to.throw(TypeError);
		expect(() => (this.db = new Database(util.next(), { verbose: true }))).to.throw(TypeError);
		expect(() => (this.db = new Database(util.next(), { verbose: 123 }))).to.throw(TypeError);
		expect(() => (this.db = new Database(util.next(), { verbose: 'null' }))).to.throw(TypeError);
		expect(() => (this.db = new Database(util.next(), { verbose: {} }))).to.throw(TypeError);
		expect(() => (this.db = new Database(util.next(), { verbose: [] }))).to.throw(TypeError);
	});
	it('should allow explicit null or undefined as a no-op', function () {
		for (const verbose of [undefined, null]) {
			const db = this.db = new Database(util.next(), { verbose });
			db.exec('select 5');
			db.close();
		}
	});
	it('should invoke the given function with all executed SQL', function () {
		let calls = [];
		function verbose(...args) {
			calls.push([this, ...args]);
		}
		const db = this.db = new Database(util.next(), { verbose });
		const stmt = db.prepare('select ?');
		db.exec('select 5');
		db.prepare('create table data (x)').run();
		stmt.get(Integer(10));
		stmt.all(Integer(15));
		stmt.iterate(Integer(20)).return();
		for (const x of stmt.iterate(Integer(25))) {}
		db.pragma('cache_size');
		db.prepare("insert into data values ('hi')").run();
		db.prepare("insert into data values ('bye')").run();
		expect(Array.from(db.prepare('select x from data order by rowid').pluck().iterate()))
			.to.deep.equal(['hi', 'bye']);
		expect(calls).to.deep.equal([
			[undefined, 'select 5'],
			[undefined, 'create table data (x)'],
			[undefined, 'select 10'],
			[undefined, 'select 15'],
			[undefined, 'select 25'],
			[undefined, 'PRAGMA cache_size'],
			[undefined, "insert into data values ('hi')"],
			[undefined, "insert into data values ('bye')"],
			[undefined, 'select x from data order by rowid'],
		]);
	});
	it('should not fully expand very long bound parameter', function () {
		let calls = [];
		function verbose(...args) {
			calls.push([this, ...args]);
		}
		const db = this.db = new Database(util.next(), { verbose });
		const stmt = db.prepare('select ?');
		stmt.get('this is a fairly short parameter');
		stmt.get('this is a slightly longer parameter');
		stmt.get('this is surely a very long bound parameter value that doesnt need to be logged in its entirety');
		expect(calls).to.deep.equal([
			[undefined, "select 'this is a fairly short parameter'"],
			[undefined, "select 'this is a slightly longer parame'/*+3 bytes*/"],
			[undefined, "select 'this is surely a very long bound'/*+62 bytes*/"],
		]);
	});
	it('should abort the execution if the logger function throws', function () {
		let fail = false;
		let failures = 0;
		const err = new Error('foo');
		const db = this.db = new Database(util.next(), { verbose: () => { if (fail) throw err; } });
		db.prepare('create table data (x)').run();
		db.function('fn', (value) => {
			if (fail) failures += 1;
			return value;
		});
		const shouldThrow = (fn) => {
			expect(fn).to.not.throw();
			expect(fn).to.not.throw();
			fail = true;
			try {
				expect(fn).to.throw(err);
			} finally {
				fail = false;
			}
			expect(fn).to.not.throw();
			expect(failures).to.equal(0);
		};
		const use = (stmt, fn) => () => fn(stmt);
		shouldThrow(() => db.exec('select fn(5)'));
		shouldThrow(use(db.prepare('insert into data values (fn(5))'), stmt => stmt.run()));
		shouldThrow(use(db.prepare('insert into data values (fn(?))'), stmt => stmt.run(5)));
		shouldThrow(use(db.prepare('select fn(?)'), stmt => stmt.get(5)));
		shouldThrow(use(db.prepare('select fn(?)'), stmt => stmt.all(5)));
		shouldThrow(use(db.prepare('select fn(?)'), stmt => Array.from(stmt.iterate(5))));
	});
});
