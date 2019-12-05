'use strict';
const { existsSync, writeFileSync, readFileSync } = require('fs');
const Database = require('../.');

describe('Database#backup()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
		this.db.prepare("CREATE TABLE entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)").run();
		this.db.prepare("INSERT INTO entries WITH RECURSIVE temp(a, b, c, d, e) AS (SELECT 'foo', 1, 3.14, x'dddddddd', NULL UNION ALL SELECT a, b + 1, c, d, e FROM temp LIMIT 5) SELECT * FROM temp").run();
	});
	afterEach(function () {
		this.db.close();
	});

	const fulfillsWith = (value, p) => p.then(v => void expect(v).to.deep.equal(value));
	const rejectsWith = (type, p) => {
		const shouldReject = () => { throw new Error('Promise should have been rejected') };
		const reasonIs = (reason) => { if (!(reason instanceof type)) throw reason; }
		return p.then(shouldReject, reasonIs);
	};

	it('should be rejected when destination is not a string', async function () {
		await rejectsWith(TypeError, this.db.backup());
		await rejectsWith(TypeError, this.db.backup(null));
		await rejectsWith(TypeError, this.db.backup(0));
		await rejectsWith(TypeError, this.db.backup(123));
		await rejectsWith(TypeError, this.db.backup(new String(util.next())));
		await rejectsWith(TypeError, this.db.backup(() => util.next()));
		await rejectsWith(TypeError, this.db.backup([util.next()]));
	});
	it('should not allow an empty destination string', async function () {
		await rejectsWith(TypeError, this.db.backup(''));
		await rejectsWith(TypeError, this.db.backup(' \t\n '));
	});
	it('should not allow a URI file path', async function () {
		await rejectsWith(TypeError, this.db.backup(`FILE:${util.next()}`));
		await rejectsWith(TypeError, this.db.backup(`file:${util.next()}`));
		await rejectsWith(TypeError, this.db.backup(`file:${util.next()}?mode=memory&cache=shared`));
	});
	it('should not allow a :memory: destination', async function () {
		await rejectsWith(TypeError, this.db.backup(':memory:'));
		expect(existsSync(':memory:')).to.be.false;
	});
	it('should backup the database and fulfill the returned promise', async function () {
		expect(existsSync(this.db.name)).to.be.true;
		expect(existsSync(util.next())).to.be.false;
		const promise = this.db.backup(util.current());
		expect(existsSync(util.current())).to.be.false;
		await fulfillsWith({ totalPages: 2, remainingPages: 0 }, promise);
		expect(existsSync(this.db.name)).to.be.true;
		expect(existsSync(util.current())).to.be.true;
		const rows = this.db.prepare('SELECT * FROM entries').all();
		this.db.close();
		this.db = new Database(util.current());
		expect(this.db.prepare('SELECT * FROM entries').all()).to.deep.equal(rows);
	});
	it('should be rejected if the directory does not exist', async function () {
		expect(existsSync(util.next())).to.be.false;
		const filepath = `temp/nonexistent/abcfoobar123/${util.current()}`;
		await rejectsWith(TypeError, this.db.backup(filepath));
		expect(existsSync(filepath)).to.be.false;
		expect(existsSync(util.current())).to.be.false;
	});
	it('should be rejected if a database cannot be opened at the destination', async function () {
		writeFileSync(util.next(), 'not a database file');
		await rejectsWith(Database.SqliteError, this.db.backup(util.current()));
		expect(readFileSync(util.current(), 'utf8')).to.equal('not a database file');
	});
	it('should accept the "attached" option', async function () {
		const source = this.db.name;
		const destination = util.next();
		let promise;
		this.db.close();
		this.db = new Database(':memory:');
		this.db.prepare('ATTACH ? AS cool_db').run(source);
		expect(existsSync(source)).to.be.true;
		expect(existsSync(destination)).to.be.false;
		await fulfillsWith({ totalPages: 2, remainingPages: 0 },
			this.db.backup(destination, { attached: 'cool_db' }));
		expect(existsSync(source)).to.be.true;
		expect(existsSync(destination)).to.be.true;
		const rows = this.db.prepare('SELECT * FROM cool_db.entries').all();
		this.db.close();
		this.db = new Database(destination);
		expect(this.db.prepare('SELECT * FROM main.entries').all()).to.deep.equal(rows);
	});
	it('should accept the "progress" option', async function () {
		expect(existsSync(this.db.name)).to.be.true;
		expect(existsSync(util.next())).to.be.false;
		const calls = [];
		const promise = this.db.backup(util.current(), { progress(...args) {
			calls.push([this, ...args]);
		} });
		expect(existsSync(util.current())).to.be.false;
		await fulfillsWith({ totalPages: 2, remainingPages: 0 }, promise);
		expect(existsSync(this.db.name)).to.be.true;
		expect(existsSync(util.current())).to.be.true;
		const rows = this.db.prepare('SELECT * FROM entries').all();
		this.db.close();
		this.db = new Database(util.current());
		expect(this.db.prepare('SELECT * FROM entries').all()).to.deep.equal(rows);
		expect(calls).to.deep.equal([[undefined, { totalPages: 2, remainingPages: 2 }]]);
	});
	it('should allow control over transfer sizes via the progress callback', async function () {
		let transferSize = 0;
		const expected = [];
		const actual = [];
		const promise = this.db.backup(util.next(), { progress(state) {
			actual.push(state);
			return transferSize;
		} });
		promise.catch(() => {});
		expect(actual).to.deep.equal(expected);
		while (!actual.length) await new Promise(setImmediate);
		expected.push({ totalPages: 2, remainingPages: 2 });
		expect(actual).to.deep.equal(expected);
		await new Promise(setImmediate);
		transferSize = 1;
		await new Promise(setImmediate);
		expected.push({ totalPages: 2, remainingPages: 2 });
		expected.push({ totalPages: 2, remainingPages: 2 });
		expect(actual).to.deep.equal(expected);
		await new Promise(setImmediate);
		expected.push({ totalPages: 2, remainingPages: 1 });
		expect(actual).to.deep.equal(expected);
		const payload = Buffer.alloc(4096 * 5).fill(0x7a).toString();
		this.db.prepare('INSERT INTO entries (a, b) VALUES (?, 999)').run(payload);
		transferSize = Infinity;
		await new Promise(setImmediate);
		expected.push({ totalPages: 7, remainingPages: 5 });
		expect(actual).to.deep.equal(expected);
		await new Promise(setImmediate);
		expect(actual).to.deep.equal(expected);
		await fulfillsWith({ totalPages: 7, remainingPages: 0 }, promise);
		this.db.close();
		this.db = new Database(util.current());
		expect(this.db.prepare('SELECT a FROM entries WHERE b = 999').pluck().get()).to.deep.equal(payload);
	});
	it('should be aborted if an error is thrown inside the progress callback', async function () {
		const promise = this.db.backup(util.next(), { progress: () => { throw new SyntaxError('foo'); } });
		await rejectsWith(SyntaxError, promise);
	});
	it('should be aborted if the progress callback returns a non-number', async function () {
		const backup = x => this.db.backup(util.next(), { progress: () => x });
		await rejectsWith(TypeError, backup(null));
		await rejectsWith(TypeError, backup(new Number(1)));
		await rejectsWith(TypeError, backup(() => 1));
		await rejectsWith(TypeError, backup([1]));
		await rejectsWith(TypeError, backup('1'));
	});
	it('should rollback an aborted backup file if it was not newly created', async function () {
		const otherDb = new Database(util.next());
		try {
			otherDb.prepare('CREATE TABLE foo (bar)').run()
			otherDb.prepare('INSERT INTO foo VALUES (2), (8)').run();
		} finally {
			otherDb.close();
		}
		let error;
		let transferSize = 0;
		const expected = [];
		const actual = [];
		const promise = this.db.backup(util.current(), { progress(state) {
			actual.push(state);
			if (error) throw error;
			return transferSize;
		} });
		promise.catch(() => {});
		expect(actual).to.deep.equal(expected);
		while (!actual.length) await new Promise(setImmediate);
		expected.push({ totalPages: 2, remainingPages: 2 });
		expect(actual).to.deep.equal(expected);
		transferSize = 1;
		await new Promise(setImmediate);
		expected.push({ totalPages: 2, remainingPages: 2 });
		expect(actual).to.deep.equal(expected);
		transferSize = 0;
		await new Promise(setImmediate);
		expected.push({ totalPages: 2, remainingPages: 1 });
		expect(actual).to.deep.equal(expected);
		error = new SyntaxError('foo');
		await new Promise(setImmediate);
		expected.push({ totalPages: 2, remainingPages: 1 });
		expect(actual).to.deep.equal(expected);
		await rejectsWith(SyntaxError, promise);
		expect(actual).to.deep.equal(expected);
		expect(existsSync(util.current())).to.be.true;
		this.db.close();
		this.db = new Database(util.current());
		expect(this.db.prepare('SELECT bar FROM foo').pluck().all()).to.deep.equal([2, 8]);
	});
	it('should delete an aborted backup file if it was newly created', async function () {
		let error;
		let transferSize = 0;
		const expected = [];
		const actual = [];
		const promise = this.db.backup(util.next(), { progress(state) {
			actual.push(state);
			if (error) throw error;
			return transferSize;
		} });
		promise.catch(() => {});
		expect(actual).to.deep.equal(expected);
		while (!actual.length) await new Promise(setImmediate);
		expected.push({ totalPages: 2, remainingPages: 2 });
		expect(actual).to.deep.equal(expected);
		transferSize = 1;
		await new Promise(setImmediate);
		expected.push({ totalPages: 2, remainingPages: 2 });
		expect(actual).to.deep.equal(expected);
		transferSize = 0;
		await new Promise(setImmediate);
		expected.push({ totalPages: 2, remainingPages: 1 });
		expect(actual).to.deep.equal(expected);
		error = new SyntaxError('foo');
		await new Promise(setImmediate);
		expected.push({ totalPages: 2, remainingPages: 1 });
		expect(actual).to.deep.equal(expected);
		await rejectsWith(SyntaxError, promise);
		expect(actual).to.deep.equal(expected);
		expect(existsSync(util.current())).to.be.false;
	});
	it('should be aborted if the connection is closed during a backup', async function () {
		let transferSize = 0;
		const calls = [];
		const promise = this.db.backup(util.next(), { progress(state) {
			calls.push(state);
			return transferSize;
		} });
		promise.catch(() => {});
		while (!calls.length) await new Promise(setImmediate);
		transferSize = 1;
		await new Promise(setImmediate);
		await new Promise(setImmediate);
		this.db.close();
		expect(this.db.open).to.be.false;
		await rejectsWith(TypeError, promise);
		expect(calls).to.deep.equal([
			{ totalPages: 2, remainingPages: 2 },
			{ totalPages: 2, remainingPages: 2 },
			{ totalPages: 2, remainingPages: 1 },
		]);
		expect(existsSync(util.current())).to.be.false;
	});
});
