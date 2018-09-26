'use strict';
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
		expect(() => db.prepare('CREATE TABLE people (name TEXT)')).to.throw(TypeError);
		expect(() => db.transaction(['CREATE TABLE people (name TEXT)'])).to.throw(TypeError);
		expect(() => db.pragma('cache_size')).to.throw(TypeError);
		expect(() => db.checkpoint()).to.throw(TypeError);
	});
});
