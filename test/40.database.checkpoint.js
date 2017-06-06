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

function fillWall(count, expectation) {
	[db1, db2].forEach(function (db) {
		var size1, size2;
		for (var i=0; i<count; ++i) {
			size1 = fs.statSync(db.name + '-wal').size;
			db.prepare('INSERT INTO entries VALUES (?, ?)').run('bar', 999);
			size2 = fs.statSync(db.name + '-wal').size;
			expectation(size2, size1, db);
		}
	});
}

describe('Database#checkpoint()', function () {
	describe('when used without a specified database', function () {
		specify('every insert should increase the size of the WAL file', function () {
			fillWall(10, function (b, a) {expect(b).to.be.above(a);});
		});
		specify('inserts after a checkpoint should NOT increase the size of the WAL file', function () {
			db1.prepare('ATTACH \'' + db2.name + '\' AS foobar').run();
			expect(db1.checkpoint()).to.deep.equal(db1);
			fillWall(10, function (b, a) {expect(b).to.equal(a);});
		});
	});
	describe('when used on a specific database', function () {
		specify('every insert should increase the size of the WAL file', function () {
			db1.prepare('DETACH foobar').run();
			db1.close();
			db2.close();
			db1 = new Database(db1.name);
			db2 = new Database(db2.name);
			db1.prepare('CREATE TABLE _unused (a TEXT, b INTEGER)').run();
			db2.prepare('CREATE TABLE _unused (a TEXT, b INTEGER)').run();
			fillWall(10, function (b, a) {expect(b).to.be.above(a);});
		});
		specify('inserts after a checkpoint should NOT increase the size of the WAL file', function () {
			db1.prepare('ATTACH \'' + db2.name + '\' AS bazqux').run();
			expect(db1.checkpoint('bazqux')).to.equal(db1);
			fillWall(10, function (b, a, db) {
				if (db === db1) {
					expect(b).to.be.above(a);
				} else {
					expect(b).to.be.equal(a);
				}
			});
		});
	});
});
