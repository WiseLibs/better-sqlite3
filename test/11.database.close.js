'use strict';
const { existsSync } = require('fs');
const Database = require('../.');

describe('Database#close()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
	});
	afterEach(function () {
		this.db.close();
	});

	it('should cause db.open to return false', function () {
		expect(this.db.open).to.be.true;
		this.db.close();
		expect(this.db.open).to.be.false;
	});
	it('should return the database object', function () {
		expect(this.db.open).to.be.true;
		expect(this.db.close()).to.equal(this.db);
		expect(this.db.open).to.be.false;
		expect(this.db.close()).to.equal(this.db);
		expect(this.db.open).to.be.false;
	});
	it('should prevent any further database operations', function () {
		this.db.close();
		expect(() => this.db.exec('CREATE TABLE people (name TEXT)')).to.throw(TypeError);
		expect(() => this.db.prepare('CREATE TABLE cats (name TEXT)')).to.throw(TypeError);
		expect(() => this.db.transaction(() => {})).to.throw(TypeError);
		expect(() => this.db.pragma('cache_size')).to.throw(TypeError);
		expect(() => this.db.function('foo', () => {})).to.throw(TypeError);
		expect(() => this.db.aggregate('foo', { step: () => {} })).to.throw(TypeError);
		expect(() => this.db.table('foo', () => {})).to.throw(TypeError);
	});
	it('should prevent any existing statements from running', function () {
		this.db.prepare('CREATE TABLE people (name TEXT)').run();
		const stmt1 = this.db.prepare('SELECT * FROM people');
		const stmt2 = this.db.prepare("INSERT INTO people VALUES ('foobar')");

		this.db.prepare('SELECT * FROM people').bind();
		this.db.prepare("INSERT INTO people VALUES ('foobar')").bind();
		this.db.prepare('SELECT * FROM people').get();
		this.db.prepare('SELECT * FROM people').all();
		this.db.prepare('SELECT * FROM people').iterate().return();
		this.db.prepare("INSERT INTO people VALUES ('foobar')").run();

		this.db.close();

		expect(() => stmt1.bind()).to.throw(TypeError);
		expect(() => stmt2.bind()).to.throw(TypeError);
		expect(() => stmt1.get()).to.throw(TypeError);
		expect(() => stmt1.all()).to.throw(TypeError);
		expect(() => stmt1.iterate()).to.throw(TypeError);
		expect(() => stmt2.run()).to.throw(TypeError);
	});
	it('should delete the database\'s associated temporary files', function () {
		expect(existsSync(util.current())).to.be.true;
		this.db.pragma('journal_mode = WAL');
		this.db.prepare('CREATE TABLE people (name TEXT)').run();
		this.db.prepare('INSERT INTO people VALUES (?)').run('foobar');
		expect(existsSync(`${util.current()}-wal`)).to.be.true;

		this.db.close();

		expect(existsSync(util.current())).to.be.true;
		expect(existsSync(`${util.current()}-wal`)).to.be.false;
	});
});
