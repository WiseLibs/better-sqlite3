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
	describe('before opening it', function () {
		it('should never emit the "open" event', function (done) {
			var db = new Database(util.next());
			expect(db.open).to.be.false;
			db.on('open', function () {
				done(new Error('This event should not have been fired.'));
			});
			db.on('close', function (err) {
				expect(err).to.be.null;
				expect(db.open).to.be.false;
				done();
			});
			expect(db.close()).to.equal(db);
			expect(db.open).to.be.false;
		});
	});
	describe('because of a failed open attempt', function () {
		it('should have an Error object as its first parameter', function (done) {
			var db = new Database('temp/nonexistent/abcfoobar123/' + util.next());
			expect(db.open).to.be.false;
			db.on('open', function () {
				done(new Error('This event should not have been fired.'));
			});
			db.on('close', function (err) {
				expect(err).to.be.an.instanceof(Error);
				expect(db.open).to.be.false;
				done();
			});
		})
	});
	describe('after opening it', function () {
		it('should emit the close event as normal', function (done) {
			var db = new Database(util.next());
			expect(db.open).to.be.false;
			db.on('open', function () {
				expect(db.open).to.be.true;
				db.close();
				expect(db.open).to.be.false;
				db.on('close', function (err) {
					expect(err).to.be.null;
					expect(db.open).to.be.false;
					done();
				});
			});
		});
		it('should prevent any further database operations', function (done) {
			var db = new Database(util.next());
			db.on('open', function () {
				expect(db.open).to.be.true;
				db.close();
				db.on('close', function (err) {
					expect(err).to.be.null;
					expect(db.open).to.be.false;
					expect(function () {db.prepare('CREATE TABLE people (name TEXT)');}).to.throw(Error);
					expect(function () {db.transaction(['CREATE TABLE people (name TEXT)']);}).to.throw(Error);
					expect(function () {db.pragma('cache_size');}).to.throw(Error);
					expect(function () {db.checkpoint();}).to.throw(Error);
					done();
				});
			});
		});
	});
});
