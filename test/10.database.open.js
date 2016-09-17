var expect = require('chai').expect;
var fs = require('fs');
var Database = require('../.');
var util = require('../tools/test-util.js');

describe('new Database()', function () {
	it('should throw an exception when file path is not a string', function () {
		expect(function () {new Database();}).to.throw(TypeError);
		expect(function () {new Database(null);}).to.throw(TypeError);
		expect(function () {new Database(0);}).to.throw(TypeError);
		expect(function () {new Database(123);}).to.throw(TypeError);
		expect(function () {new Database(new String(util.next()));}).to.throw(TypeError);
		expect(function () {new Database(function () {});}).to.throw(TypeError);
		expect(function () {new Database([util.next()]);}).to.throw(TypeError);
	});
	it('should throw an exception when file path is empty', function () {
		expect(function () {new Database('');}).to.throw(TypeError);
	});
	it('should not allow URI file paths', function () {
		expect(function () {new Database('file:' + util.next());}).to.throw(TypeError);
		expect(function () {new Database('file:' + util.next() + '?mode=memory&cache=shared');}).to.throw(TypeError);
	});
	it('should not allow ":memory:" databases', function () {
		expect(function () {new Database(':memory:');}).to.throw(TypeError);
	});
	it('should allow disk-based databases to be created', function (done) {
		expect(function () {fs.accessSync(util.next());}).to.throw(Error);
		var db = new Database(util.current());
		expect(db.name).to.equal(util.current());
		expect(db.memory).to.be.false;
		expect(db.open).to.be.false;
		db.on('open', function () {
			fs.accessSync(util.current());
			expect(db.open).to.be.true;
			done();
		});
	});
	it('should allow in-memory databases to be created', function (done) {
		expect(function () {fs.accessSync(util.next());}).to.throw(Error);
		var db = new Database(util.current(), {memory: true});
		expect(db.name).to.equal(util.current());
		expect(db.memory).to.be.true;
		expect(db.open).to.be.false;
		db.on('open', function () {
			expect(function () {fs.accessSync(util.current());}).to.throw(Error);
			expect(db.open).to.be.true;
			done();
		});
	});
	it('should not allow the database to be used before it opens', function (done) {
		var db = new Database(util.next());
		expect(db.open).to.be.false;
		expect(function () {db.prepare('CREATE TABLE people (name TEXT)');}).to.throw(Error);
		expect(function () {db.transaction(['CREATE TABLE people (name TEXT)']);}).to.throw(Error);
		expect(function () {db.pragma('cache_size');}).to.throw(Error);
		expect(function () {db.checkpoint();}).to.throw(Error);
		db.on('open', function () {
			expect(db.open).to.be.true;
			done();
		});
	});
	it('should have a proper prototype chain', function () {
		var db = new Database(util.next());
		expect(db).to.be.an.instanceof(Database);
		expect(db.constructor).to.equal(Database);
		expect(Database.prototype.constructor).to.equal(Database);
		expect(Database.prototype.close).to.be.a('function');
		expect(Database.prototype.close).to.equal(db.close);
	});
});
