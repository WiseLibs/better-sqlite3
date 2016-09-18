var expect = require('chai').expect;
var fs = require('fs');
var Database = require('../.');
var db;

before(function (done) {
	db = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.db');
	db.on('open', function () {
		db.pragma('journal_mode = WAL');
		db.prepare('CREATE TABLE entries (a TEXT, b INTEGER)').run();
		done();
	});
});

describe('Database#checkpoint()', function () {
	describe('before a checkpoint', function () {
		it('every insert should increase the size of the WAL file', function () {
			var size1, size2;
			for (var i=0; i<10; ++i) {
				size1 = fs.statSync(db.name + '-wal').size;
				db.prepare('INSERT INTO entries VALUES (?, ?)').run('bar', 999);
				size2 = fs.statSync(db.name + '-wal').size;
				expect(size2).to.be.above(size1);
			}
		});
	});
	describe('after a checkpoint', function () {
		it('inserts should NOT increase the size of the WAL file', function () {
			expect(db.checkpoint()).to.equal(1);
			var size1, size2;
			for (var i=0; i<10; ++i) {
				size1 = fs.statSync(db.name + '-wal').size;
				db.prepare('INSERT INTO entries VALUES (?, ?)').run('bar', 999);
				size2 = fs.statSync(db.name + '-wal').size;
				expect(size2).to.be.equal(size1);
			}
		});
	});
});
