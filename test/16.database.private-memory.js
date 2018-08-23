'use strict';
const { expect } = require('chai');
const fs = require('fs');
const Database = require('../.');

describe('Database(":memory:")', function () {
	function tableCount(db) {
		return db.prepare('SELECT COUNT(1) AS n FROM sqlite_master').get().n;
	}
	it('should not actually touch a file called :memory:', function () {
		expect(fs.existsSync(':memory:')).to.be.false;
		new Database(':memory:');
		expect(fs.existsSync(':memory:')).to.be.false;
	});
	it('should be isolated', function () {
		const db0 = new Database(':memory:');
		const db1 = new Database(':memory:');
		db0.prepare('CREATE TABLE tab (col)').run();
		expect(tableCount(db0)).to.equal(1);
		expect(tableCount(db1)).to.equal(0);
		db0.close();
		db1.close();
		const db2 = new Database(':memory:');
		expect(tableCount(db2)).to.equal(0);
	});
	it('should be shared among databases with "memory" set to true', function () {
		const db0 = new Database(':memory:', { memory: true });
		const db1 = new Database(':memory:', { memory: true });
		const db2 = new Database(':memory:');
		db0.prepare('CREATE TABLE tab (col)').run();
		expect(tableCount(db0)).to.equal(1);
		expect(tableCount(db1)).to.equal(1);
		expect(tableCount(db2)).to.equal(0);
	});
	it('should obey the restrictions of readonly mode', function () {
		const db = new Database(':memory:', {readonly: true});
		const stmt = db.prepare('CREATE TABLE tab (col)');
		expect(() => stmt.run()).to.throw(Database.SqliteError).with.property('code', 'SQLITE_READONLY');
	});
	it('should ignore "fileMustExist"', function () {
		new Database(':memory:', { readonly: true, fileMustExist: true });
	});
});
