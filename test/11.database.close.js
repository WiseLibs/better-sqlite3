'use strict';
const { existsSync } = require('fs');
const Database = require('../.');

describe('Database#close()', function () {
	it('should cause db.open to return false', function () {
		const db = new Database(util.next());
		expect(db.open).to.be.true;
		db.close();
		expect(db.open).to.be.false;
	});
	it('should return the database object', function () {
		const db = new Database(util.next());
		expect(db.open).to.be.true;
		expect(db.close()).to.equal(db);
		expect(db.open).to.be.false;
		expect(db.close()).to.equal(db);
		expect(db.open).to.be.false;
	});
	it('should prevent any further database operations', function () {
		const db = new Database(util.next());
		db.close();
		expect(() => db.exec('CREATE TABLE people (name TEXT)')).to.throw(TypeError);
		expect(() => db.prepare('CREATE TABLE cats (name TEXT)')).to.throw(TypeError);
		expect(() => db.transaction(() => {})).to.throw(TypeError);
		expect(() => db.pragma('cache_size')).to.throw(TypeError);
		expect(() => db.checkpoint()).to.throw(TypeError);
		expect(() => db.function('foo', () => {})).to.throw(TypeError);
		expect(() => db.aggregate('foo', { step: () => {} })).to.throw(TypeError);
	});
	it('should prevent any existing statements from running', function () {
		const db = new Database(util.next());
		
		db.prepare('CREATE TABLE people (name TEXT)').run();
		const stmt1 = db.prepare('SELECT * FROM people');
		const stmt2 = db.prepare("INSERT INTO people VALUES ('foobar')");
		
		db.prepare('SELECT * FROM people').bind();
		db.prepare("INSERT INTO people VALUES ('foobar')").bind();
		db.prepare('SELECT * FROM people').get();
		db.prepare('SELECT * FROM people').all();
		db.prepare('SELECT * FROM people').iterate().return();
		db.prepare("INSERT INTO people VALUES ('foobar')").run();
		
		db.close();
		
		expect(() => stmt1.bind()).to.throw(TypeError);
		expect(() => stmt2.bind()).to.throw(TypeError);
		expect(() => stmt1.get()).to.throw(TypeError);
		expect(() => stmt1.all()).to.throw(TypeError);
		expect(() => stmt1.iterate()).to.throw(TypeError);
		expect(() => stmt2.run()).to.throw(TypeError);
	});
	it('should delete the database\'s associated temporary files', function () {
		const db = new Database(util.next());
		
		expect(existsSync(util.current())).to.be.true;
		db.pragma('journal_mode = WAL');
		db.prepare('CREATE TABLE people (name TEXT)').run();
		db.prepare('INSERT INTO people VALUES (?)').run('foobar');
		expect(existsSync(`${util.current()}-wal`)).to.be.true;
		
		db.close();
		
		expect(existsSync(util.current())).to.be.true;
		expect(existsSync(`${util.current()}-wal`)).to.be.false;
	});
});
