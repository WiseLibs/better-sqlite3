'use strict';
const { expect } = require('chai');
const Database = require('../.');
const util = require('./util');
const filepath = (() => {
	const fs = require('fs');
	const path = require('path');
	function exists(loc) { try { fs.readFileSync(loc); return true; } catch (_) { return false; } }
	const attempts = [
		'../build/Debug/test_extension.node',
		'../build/Release/test_extension.node',
	].map(loc => path.join(__dirname, loc));
	for (let i = 0; i < attempts.length; ++i) {
		if (exists(attempts[i])) return attempts[i];
	}
	throw new TypeError('Could not find test_extension.node');
})();

describe('Database#loadExtension()', function () {
	it('should throw if a string argument is not given', function () {
		const db = new Database(util.next());
		expect(() => db.loadExtension()).to.throw(TypeError);
		expect(() => db.loadExtension(undefined)).to.throw(TypeError);
		expect(() => db.loadExtension(null)).to.throw(TypeError);
		expect(() => db.loadExtension(123)).to.throw(TypeError);
		expect(() => db.loadExtension(new String(filepath))).to.throw(TypeError);
		expect(() => db.loadExtension([filepath])).to.throw(TypeError);
	});
	it('should throw if the database is closed', function () {
		const db = new Database(util.next());
		db.close();
		expect(() => db.loadExtension(filepath)).to.throw(TypeError);
	});
	it('should throw if the database is busy', function () {
		const db = new Database(util.next());
		let invoked = false;
		for (const value of db.prepare('select 555').pluck().iterate()) {
			expect(value).to.equal(555);
			expect(() => db.loadExtension(filepath)).to.throw(TypeError);
			invoked = true;
		}
		expect(invoked).to.be.true;
	});
	it('should throw if the extension is not found', function () {
		const db = new Database(util.next());
		try {
			db.loadExtension(filepath + 'x');
		} catch (err) {
			expect(err).to.be.an.instanceof(Database.SqliteError);
			expect(err.message).to.be.a('string');
			expect(err.message.length).to.be.above(0);
			expect(err.message).to.not.equal('not an error');
			expect(err.code).to.equal('SQLITE_ERROR');
			return;
		}
		throw new Error('This code should not have been reached');
	});
	it('should register the specified extension', function () {
		const db = new Database(util.next());
		expect(db.loadExtension(filepath)).to.equal(db);
		expect(db.prepare('SELECT testExtensionFunction(NULL, 123, 99, 2)').pluck().get()).to.equal(4);
		expect(db.prepare('SELECT testExtensionFunction(NULL, 2)').pluck().get()).to.equal(2);
	});
	it('should not allow registering extensions with SQL', function () {
		const db1 = new Database(util.next());
		expect(() => db1.prepare('SELECT load_extension(?)').get(filepath)).to.throw(Database.SqliteError);
		expect(db1.loadExtension(filepath)).to.equal(db1);
		expect(() => db1.prepare('SELECT load_extension(?)').get(filepath)).to.throw(Database.SqliteError);
		const db2 = new Database(util.next());
		try {
			db2.loadExtension(filepath + 'x');
		} catch (err) {
			expect(() => db2.prepare('SELECT load_extension(?)').get(filepath)).to.throw(Database.SqliteError);
			return;
		}
		throw new Error('This code should not have been reached');
	});
});
