'use strict';
const Database = require('../.');
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
	beforeEach(function () {
		this.db = new Database(util.next());
	});
	afterEach(function () {
		this.db.close();
	});
	it('should throw if a string argument is not given', function () {
		expect(() => this.db.loadExtension()).to.throw(TypeError);
		expect(() => this.db.loadExtension(undefined)).to.throw(TypeError);
		expect(() => this.db.loadExtension(null)).to.throw(TypeError);
		expect(() => this.db.loadExtension(123)).to.throw(TypeError);
		expect(() => this.db.loadExtension(new String(filepath))).to.throw(TypeError);
		expect(() => this.db.loadExtension([filepath])).to.throw(TypeError);
	});
	it('should throw if the database is closed', function () {
		this.db.close();
		expect(() => this.db.loadExtension(filepath)).to.throw(TypeError);
	});
	it('should throw if the database is busy', function () {
		let invoked = false;
		for (const value of this.db.prepare('select 555').pluck().iterate()) {
			expect(value).to.equal(555);
			expect(() => this.db.loadExtension(filepath)).to.throw(TypeError);
			invoked = true;
		}
		expect(invoked).to.be.true;
	});
	it('should throw if the extension is not found', function () {
		try {
			this.db.loadExtension(filepath + 'x');
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
		expect(this.db.loadExtension(filepath)).to.equal(this.db);
		expect(this.db.prepare('SELECT testExtensionFunction(NULL, 123, 99, 2)').pluck().get()).to.equal(4);
		expect(this.db.prepare('SELECT testExtensionFunction(NULL, 2)').pluck().get()).to.equal(2);
	});
	it('should not allow registering extensions with SQL', function () {
		expect(() => this.db.prepare('SELECT load_extension(?)').get(filepath)).to.throw(Database.SqliteError);
		expect(this.db.loadExtension(filepath)).to.equal(this.db);
		expect(() => this.db.prepare('SELECT load_extension(?)').get(filepath)).to.throw(Database.SqliteError);
		this.db.close();
		this.db = new Database(util.next());
		try {
			this.db.loadExtension(filepath + 'x');
		} catch (err) {
			expect(() => this.db.prepare('SELECT load_extension(?)').get(filepath)).to.throw(Database.SqliteError);
			return;
		}
		throw new Error('This code should not have been reached');
	});
});
