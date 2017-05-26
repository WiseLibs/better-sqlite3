var expect = require('chai').expect;
var fs = require('fs');
var Database = require('../.');
var db1, db2;

before(function () {
	db1 = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.db');
	db1.pragma('journal_mode = WAL');
	db1.prepare('CREATE TABLE entries (a TEXT, b INTEGER)').run();
	db2 = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '2.db');
	db2.pragma('journal_mode = WAL');
	db2.prepare('CREATE TABLE entries (a TEXT, b INTEGER)').run();
});

describe('Database#checkpoint()', function () {
	describe('before a checkpoint', function () {
		it('every insert should increase the size of the WAL file', function () {
			[db1, db2].forEach(function (db) {
				var size1, size2;
				for (var i=0; i<10; ++i) {
					size1 = fs.statSync(db.name + '-wal').size;
					db.prepare('INSERT INTO entries VALUES (?, ?)').run('bar', 999);
					size2 = fs.statSync(db.name + '-wal').size;
					expect(size2).to.be.above(size1);
				}
			});
		});
	});
	describe('after a checkpoint', function () {
		it('inserts should NOT increase the size of the WAL file', function () {
			db1.prepare('ATTACH \'' + db2.name + '\' AS foobar').run();
			expect(db1.checkpoint()).to.deep.equal({main: 1, foobar: 1});
			[db1, db2].forEach(function (db) {
				var size1, size2;
				for (var i=0; i<10; ++i) {
					size1 = fs.statSync(db.name + '-wal').size;
					db.prepare('INSERT INTO entries VALUES (?, ?)').run('bar', 999);
					size2 = fs.statSync(db.name + '-wal').size;
					expect(size2).to.be.equal(size1);
				}
			});
		});
		it('obeys the "only" option', function () {
			expect(db1.checkpoint({only: 'foobar'})).to.equal(1);
		});
	});
});
