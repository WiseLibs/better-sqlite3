var expect = require('chai').expect;
var Database = require('../.');

describe('Database PRAGMA modification', function () {
	describe('.pragma()', function () {
		it('should throw an exception if used before the database is open', function () {
			var db = new Database('temp/11.1.db');
			expect(function () {db.pragma('cache_size');}).to.throw(Error);
		})
		it('should throw an exception if a string is not provided', function (done) {
			var db = new Database('temp/11.2.db');
			db.on('open', function () {
				expect(function () {db.pragma(123);}).to.throw(TypeError);
				expect(function () {db.pragma(0);}).to.throw(TypeError);
				expect(function () {db.pragma(null);}).to.throw(TypeError);
				expect(function () {db.pragma();}).to.throw(TypeError);
				expect(function () {db.pragma(new String('cache_size'));}).to.throw(TypeError);
				done();
			});
		})
		it('should throw an exception if invalid/redundant SQL is provided', function (done) {
			var db = new Database('temp/11.3.db');
			db.on('open', function () {
				expect(function () {db.pragma('PRAGMA cache_size');}).to.throw(Error);
				done();
			});
		})
		it('should execute the pragma, returning rows of strings', function (done) {
			var db = new Database('temp/11.4.db');
			db.on('open', function () {
				var rows = db.pragma('cache_size');
				expect(rows[0].cache_size).to.be.a('string');
				expect(+rows[0].cache_size).to.equal(-16000);
				done();
			});
		});
		it('should optionally return simpler results', function (done) {
			var db = new Database('temp/11.5.db');
			db.on('open', function () {
				var cache_size = db.pragma('cache_size', true);
				expect(cache_size).to.be.a('string');
				expect(cache_size).to.equal('-16000');
				done();
			});
		});
		it('should obey PRAGMA changes', function (done) {
			var db = new Database('temp/11.6.db');
			db.on('open', function () {
				expect(db.pragma('cache_size', true)).to.equal('-16000');
				db.pragma('cache_size = -8000');
				expect(db.pragma('cache_size', true)).to.equal('-8000');
				done();
			});
		});
	});
	describe('"wal" option', function () {
		it('should default to true', function (done) {
			var db = new Database('temp/11.7.db');
			db.on('open', function () {
				expect(db.pragma('journal_mode', true)).to.equal('wal');
				expect(db.pragma('synchronous', true)).to.equal('1');
				done();
			});
		});
		it('should be optionally turned off', function (done) {
			var db = new Database('temp/11.8.db', {wal: false});
			db.on('open', function () {
				expect(db.pragma('journal_mode', true)).to.equal('delete');
				expect(db.pragma('synchronous', true)).to.equal('2');
				done();
			});
		});
	});
});
