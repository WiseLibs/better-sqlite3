var expect = require('chai').expect;
var fs = require('fs');
var Database = require('../.');

describe('Opening a database', function () {
	it('should throw an exception when file path is not a string', function () {
		expect(function () {new Database();}).to.throw(TypeError);
		expect(function () {new Database(null);}).to.throw(TypeError);
		expect(function () {new Database(0);}).to.throw(TypeError);
		expect(function () {new Database(123);}).to.throw(TypeError);
		expect(function () {new Database(new String('temp/10.1.db'));}).to.throw(TypeError);
		expect(function () {new Database(function () {});}).to.throw(TypeError);
		expect(function () {new Database(['temp/10.2.db']);}).to.throw(TypeError);
	});
	it('should throw an exception when file path is empty', function () {
		expect(function () {new Database('');}).to.throw(TypeError);
	});
	it('should not allow URI file paths', function () {
		expect(function () {new Database('file:temp/10.3.db');}).to.throw(TypeError);
		expect(function () {new Database('file:temp/10.4.db?mode=memory');}).to.throw(TypeError);
	});
	it('should not allow ":memory:"" databases', function () {
		expect(function () {new Database(':memory:');}).to.throw(TypeError);
	});
	it('should allow disk-based databases to be created', function (done) {
		expect(function () {fs.accessSync('temp/10.5.db');}).to.throw(Error);
		var db = new Database('temp/10.5.db');
		expect(db.open).to.be.false;
		db.on('open', function () {
			fs.accessSync('temp/10.5.db');
			expect(db.open).to.be.true;
			done();
		});
	});
	it('should allow in-memory databases to be created', function (done) {
		expect(function () {fs.accessSync('temp/10.6.db');}).to.throw(Error);
		var db = new Database('temp/10.6.db', {memory: true});
		expect(db.open).to.be.false;
		db.on('open', function () {
			expect(function () {fs.accessSync('temp/10.6.db');}).to.throw(Error);
			expect(db.open).to.be.true;
			done();
		});
	});
	it('should have a proper prototype chain', function () {
		var db = new Database('temp/10.7.db');
		expect(db).to.be.an.instanceof(Database);
		expect(db.constructor).to.equal(Database);
		expect(Database.prototype.constructor).to.equal(Database);
		expect(Database.prototype.close).to.be.a('function');
		expect(Database.prototype.close).to.equal(db.close);
	});
});
