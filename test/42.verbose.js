'use strict';
const Database = require('../.');
const { Integer } = Database;

describe('verbose mode', function () {
	it('should throw when not given a function or null/undefined', function () {
		expect(() => new Database(util.next(), { verbose: false })).to.throw(TypeError);
		expect(() => new Database(util.next(), { verbose: true })).to.throw(TypeError);
		expect(() => new Database(util.next(), { verbose: 123 })).to.throw(TypeError);
		expect(() => new Database(util.next(), { verbose: 'null' })).to.throw(TypeError);
		expect(() => new Database(util.next(), { verbose: {} })).to.throw(TypeError);
		expect(() => new Database(util.next(), { verbose: [] })).to.throw(TypeError);
	});
	it('should allow explicit null or undefined as a no-op', function () {
		for (const verbose of [undefined, null]) {
			const db = new Database(util.next(), { verbose });
			db.exec('select 5');
			db.close();
		}
	});
	it('should invoke the given function with all executed SQL', async function () {
		let calls = [];
		function verbose(...args) {
			calls.push([this, ...args]);
		}
		const db = new Database(util.next(), { verbose });
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
		await new Promise(fn => process.nextTick(fn));
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
		db.close();
	});
	it('should not invoke the function within the current event loop tick', async function () {
		let calls = [];
		function verbose(...args) {
			calls.push([this, ...args]);
		}
		const db = new Database(util.next(), { verbose });
		const stmt = db.prepare('select ?');
		db.exec('select 5');
		stmt.get(Integer(10));
		db.pragma('cache_size');
		expect(calls).to.deep.equal([]);
		await new Promise(fn => process.nextTick(fn));
		expect(calls).to.deep.equal([
			[undefined, 'select 5'],
			[undefined, 'select 10'],
			[undefined, 'PRAGMA cache_size'],
		]);
		db.close();
	});
	it('should not fully expand very long bound parameter', async function () {
		let calls = [];
		function verbose(...args) {
			calls.push([this, ...args]);
		}
		const db = new Database(util.next(), { verbose });
		const stmt = db.prepare('select ?');
		stmt.get('this is a fairly short parameter');
		stmt.get('this is a slightly longer parameter');
		stmt.get('this is surely a very long bound parameter value that doesnt need to be logged in its entirety');
		await new Promise(fn => process.nextTick(fn));
		expect(calls).to.deep.equal([
			[undefined, "select 'this is a fairly short parameter'"],
			[undefined, "select 'this is a slightly longer parame'/*+3 bytes*/"],
			[undefined, "select 'this is surely a very long bound'/*+62 bytes*/"],
		]);
		db.close();
	});
});
