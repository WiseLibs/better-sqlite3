var expect = require('chai').expect;
var Database = require('../.');

describe('Closing a database', function () {
	describe('before opening it', function () {
		it('should never emit the "open" event', function (done) {
			var db = new Database('temp/12.1.db');
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
	describe('because of a failed open attempt', function (done) {
		it('should have an Error object as its first parameter', function () {
			var db = new Database('temp/nonexistent/abcfoobar123/12.2.db');
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
			var db = new Database('temp/12.3.db');
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
		it('should prevent further PRAGMA executions', function (done) {
			var db = new Database('temp/12.4.db');
			db.on('open', function () {
				expect(db.pragma('cache_size', true)).to.equal('-16000');
				db.close();
				expect(function () {db.pragma('cache_size', true)}).to.throw(Error);
				db.on('close', function (err) {
					expect(err).to.be.null;
					expect(function () {db.pragma('cache_size', true)}).to.throw(Error);
					done();
				});
			});
		});
	});
});
