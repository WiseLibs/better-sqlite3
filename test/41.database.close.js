'use strict';
const { expect } = require('chai');
const fs = require('fs');
const Database = require('../.');
const util = require('./util');

describe('Database#close()', function () {
	it('should prevent statements and transactions from operating', function () {
		const db = new Database(util.next());
		db.prepare('CREATE TABLE people (name TEXT)').run();
		const stmt1 = db.prepare('SELECT * FROM people');
		const stmt2 = db.prepare("INSERT INTO people VALUES ('foobar')");
		const trans = db.transaction(["INSERT INTO people VALUES ('foobar')"]);
		
		db.prepare('SELECT * FROM people').bind();
		db.prepare("INSERT INTO people VALUES ('foobar')").bind();
		db.transaction(["INSERT INTO people VALUES ('foobar')"]).bind();
		db.prepare('SELECT * FROM people').get();
		db.prepare('SELECT * FROM people').all();
		db.prepare('SELECT * FROM people').iterate().return();
		db.prepare("INSERT INTO people VALUES ('foobar')").run();
		db.transaction(["INSERT INTO people VALUES ('foobar')"]).run();
		
		db.close();
		
		expect(() => stmt1.bind()).to.throw(TypeError);
		expect(() => stmt2.bind()).to.throw(TypeError);
		expect(() => trans.bind()).to.throw(TypeError);
		expect(() => stmt1.get()).to.throw(TypeError);
		expect(() => stmt1.all()).to.throw(TypeError);
		expect(() => stmt1.iterate()).to.throw(TypeError);
		expect(() => stmt2.run()).to.throw(TypeError);
		expect(() => trans.run()).to.throw(TypeError);
	});
	it('should delete the database\'s associated temporary files', function () {
		const db = new Database(util.next());
		fs.accessSync(util.current());
		db.pragma('journal_mode = WAL');
		db.prepare('CREATE TABLE people (name TEXT)').run();
		db.prepare('INSERT INTO people VALUES (?)').run('foobar');
		fs.accessSync(`${util.current()}-wal`);
		
		db.close();
		
		fs.accessSync(util.current());
		expect(() =>
			fs.accessSync(util.current() + '-wal')
		).to.throw();
	});
});
