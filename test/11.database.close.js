var expect = require('chai').expect;
var Database = require('../.');
var util = (function () {
	var path = require('path');
	var dbId = 0;
	var obj;
	return obj = {
		current: function () {
			return 'temp/' + path.basename(__filename).split('.')[0] + '.' + dbId + '.db';
		},
		next: function () {++dbId; return obj.current();}
	};
}());

describe('Database#close()', function () {
	it('should cause db.open to return false', function () {
		var db = new Database(util.next());
		expect(db.open).to.be.true;
		db.close();
		expect(db.open).to.be.false;
	});
	it('should return the database object', function () {
		var db = new Database(util.next());
		expect(db.open).to.be.true;
		expect(db.close()).to.equal(db);
		expect(db.open).to.be.false;
		expect(db.close()).to.equal(db);
		expect(db.open).to.be.false;
	});
	it('should prevent any further database operations', function () {
		var db = new Database(util.next());
		db.close();
		expect(function () {db.prepare('CREATE TABLE people (name TEXT)');}).to.throw(TypeError);
		expect(function () {db.transaction(['CREATE TABLE people (name TEXT)']);}).to.throw(TypeError);
		expect(function () {db.pragma('cache_size');}).to.throw(TypeError);
		expect(function () {db.checkpoint();}).to.throw(TypeError);
	});
});
