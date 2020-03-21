'use strict';
const fs = require('fs');
const path = require('path');
const Database = require('../.');

describe('Database#loadExtension()', function () {
	const extensions = ['test_extension', 'test_extension_custom_entry_point'];
	let filepath = {};
	before(function () {
		extensions.forEach(function(extensionName){
			const releaseFilepath = path.join(__dirname, '..', 'build', 'Release', extensionName + '.node');
			const debugFilepath = path.join(__dirname, '..', 'build', 'Debug', extensionName + '.node');
			try {
				fs.accessSync(releaseFilepath);
				filepath[extensionName] = releaseFilepath;
			} catch (_) {
				fs.accessSync(debugFilepath);
				filepath[extensionName] = debugFilepath;
			}
		});
	});
	beforeEach(function () {
		this.db = new Database(util.next());
	});
	afterEach(function () {
		this.db.close();
	});

	it('should throw an exception if a string argument is not given', function () {
		expect(() => this.db.loadExtension()).to.throw(TypeError);
		expect(() => this.db.loadExtension(undefined)).to.throw(TypeError);
		expect(() => this.db.loadExtension(null)).to.throw(TypeError);
		expect(() => this.db.loadExtension(123)).to.throw(TypeError);
		expect(() => this.db.loadExtension(new String(filepath.test_extension))).to.throw(TypeError);
		expect(() => this.db.loadExtension([filepath.test_extension])).to.throw(TypeError);
	});
	it('should throw an exception if the database is busy', function () {
		let invoked = false;
		for (const value of this.db.prepare('select 555').pluck().iterate()) {
			expect(value).to.equal(555);
			expect(() => this.db.loadExtension(filepath.test_extension)).to.throw(TypeError);
			invoked = true;
		}
		expect(invoked).to.be.true;
	});
	it('should throw an exception if the extension is not found', function () {
		try {
			this.db.loadExtension(filepath.test_extension + 'x');
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
		expect(this.db.loadExtension(filepath.test_extension)).to.equal(this.db);
		expect(this.db.prepare('SELECT testExtensionFunction(NULL, 123, 99, 2)').pluck().get()).to.equal(4);
		expect(this.db.prepare('SELECT testExtensionFunction(NULL, 2)').pluck().get()).to.equal(2);
	});
	it('should register the specified extension when specifying the standard entry_point', function () {
		expect(this.db.loadExtension(filepath.test_extension, 'sqlite3_extension_init')).to.equal(this.db);
		expect(this.db.prepare('SELECT testExtensionFunction(NULL, 123, 99, 2)').pluck().get()).to.equal(4);
		expect(this.db.prepare('SELECT testExtensionFunction(NULL, 2)').pluck().get()).to.equal(2);
	});
	it('should throw an exception if the entry_point is not found', function () {
		try {
			this.db.loadExtension(filepath.test_extension, 'invalid_entry_point');
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
	it('should not allow registering extensions with SQL', function () {
		expect(() => this.db.prepare('SELECT load_extension(?)').get(filepath.test_extension)).to.throw(Database.SqliteError);
		expect(this.db.loadExtension(filepath.test_extension)).to.equal(this.db);
		expect(() => this.db.prepare('SELECT load_extension(?)').get(filepath.test_extension)).to.throw(Database.SqliteError);
		this.db.close();
		this.db = new Database(util.next());
		try {
			this.db.loadExtension(filepath.test_extension + 'x');
		} catch (err) {
			expect(() => this.db.prepare('SELECT load_extension(?)').get(filepath.test_extension)).to.throw(Database.SqliteError);
			return;
		}
		throw new Error('This code should not have been reached');
	});
	it('should register the specified extension when specifying a non-standard entry_point', function () {
		expect(this.db.loadExtension(filepath.test_extension_custom_entry_point, 'custom_extension_init')).to.equal(this.db);
		expect(this.db.prepare('SELECT testExtensionFunction(NULL, 123, 99, 2)').pluck().get()).to.equal(4);
		expect(this.db.prepare('SELECT testExtensionFunction(NULL, 2)').pluck().get()).to.equal(2);
	});
});
