'use strict';
const Database = require('../.');

describe('Database hooks', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
	});
	afterEach(function () {
		this.db.close();
	});

	it('should invoke the correct callbacks when changes are successfully committed', function () {
		const updates = [];
		let commits = 0;
		let rollbacks = 0;

		this.db.updateHook((op, dbName, tableName, rowid) => {
			updates.push({ op, dbName, tableName, rowid });
		});
		this.db.commitHook(() => {
			++commits;
			return true;
		});
		this.db.rollbackHook(() => {
			++rollbacks;
		});

		this.db.exec('CREATE TABLE entries (a TEXT, b INTEGER)');
		expect(updates).to.have.lengthOf(0);
		expect(commits).to.be.equal(1);
		expect(rollbacks).to.be.equal(0);

		this.db.exec("INSERT INTO entries VALUES ('foobar', 44)");
		expect(updates).to.have.lengthOf(1);
		expect(updates[0].op).to.equal('SQLITE_INSERT');
		expect(updates[0].dbName).to.equal('main');
		expect(updates[0].tableName).to.equal('entries');
		expect(updates[0].rowid).to.be.equal(1n);
		expect(commits).to.be.equal(2);
		expect(rollbacks).to.be.equal(0);

		this.db.exec("UPDATE entries SET b = 99 WHERE a = 'foobar'");
		expect(updates).to.have.lengthOf(2);
		expect(updates[1].op).to.equal('SQLITE_UPDATE');
		expect(updates[1].dbName).to.equal('main');
		expect(updates[1].tableName).to.equal('entries');
		expect(updates[1].rowid).to.be.equal(1n);
		expect(commits).to.be.equal(3);
		expect(rollbacks).to.be.equal(0);

		this.db.exec('DELETE FROM entries WHERE b = 99');
		expect(updates).to.have.lengthOf(3);
		expect(updates[2].op).to.equal('SQLITE_DELETE');
		expect(updates[2].dbName).to.equal('main');
		expect(updates[2].tableName).to.equal('entries');
		expect(updates[2].rowid).to.be.equal(1n);
		expect(commits).to.be.equal(4);
		expect(rollbacks).to.be.equal(0);
	});

	it('should correctly handle rollbacks', function () {
		let attemptedCommits = 0;
		let rollbacks = 0;

		this.db.commitHook(() => {
			return ++attemptedCommits <= 1;
		});
		this.db.rollbackHook(() => {
			++rollbacks;
		});

		this.db.exec('CREATE TABLE entries (a TEXT, b INTEGER)');
		expect(attemptedCommits).to.be.equal(1);
		expect(rollbacks).to.be.equal(0);

		expect(() => {
			this.db.exec("INSERT INTO entries VALUES ('foobar', 44)");
		}).to.throw(Database.SqliteError, 'constraint failed');
		expect(attemptedCommits).to.be.equal(2);
		expect(rollbacks).to.be.equal(1);
	});

	it('should turn exceptions in commit hooks into rollbacks and propagate errors', function () {
		let attemptedCommits = 0;
		let rollbacks = 0;

		const commitError = new Error('commit error');
		this.db.commitHook(() => {
			if (++attemptedCommits > 1) {
				throw commitError;
			}
			return true;
		});
		this.db.rollbackHook(() => {
			++rollbacks;
		});

		this.db.exec('CREATE TABLE entries (a TEXT, b INTEGER)');
		expect(attemptedCommits).to.be.equal(1);
		expect(rollbacks).to.be.equal(0);

		expect(() => {
			this.db.exec("INSERT INTO entries VALUES ('foobar', 44)");
		}).to.throw(commitError);
		expect(attemptedCommits).to.be.equal(2);
		expect(rollbacks).to.be.equal(1);
	});

	it('should allow changing hooks', function () {
		const updatesA = [];
		let commitsA = 0;
		let rollbacksA = 0;

		this.db.exec('CREATE TABLE entries (a TEXT, b INTEGER)');

		this.db.updateHook((op, dbName, tableName, rowid) => {
			updatesA.push({ op, dbName, tableName, rowid });
		});
		this.db.commitHook(() => {
			++commitsA;
			return true;
		});
		this.db.rollbackHook(() => {
			++rollbacksA;
		});
		this.db.exec("INSERT INTO entries VALUES ('foobar', 44)");

		expect(updatesA).to.have.lengthOf(1);
		expect(updatesA[0].op).to.equal('SQLITE_INSERT');
		expect(updatesA[0].dbName).to.equal('main');
		expect(updatesA[0].tableName).to.equal('entries');
		expect(updatesA[0].rowid).to.be.equal(1n);

		expect(commitsA).to.be.equal(1);
		expect(rollbacksA).to.be.equal(0);

		const updatesB = [];
		let attemptedCommitsB = 0;
		let rollbacksB = 0;

		this.db.updateHook((op, dbName, tableName, rowid) => {
			updatesB.push({ op, dbName, tableName, rowid });
		});
		this.db.commitHook(() => {
			++attemptedCommitsB;
			return false;
		});
		this.db.rollbackHook(() => {
			++rollbacksB;
		});
		expect(() => {
			this.db.exec("INSERT INTO entries VALUES ('bazquux', 99)");
		}).to.throw(Database.SqliteError, 'constraint failed');

		expect(updatesB).to.have.lengthOf(1);
		expect(updatesB[0].op).to.equal('SQLITE_INSERT');
		expect(updatesB[0].dbName).to.equal('main');
		expect(updatesB[0].tableName).to.equal('entries');
		expect(updatesB[0].rowid).to.be.equal(2n);

		expect(commitsA).to.be.equal(1);
		expect(rollbacksA).to.be.equal(0);

		expect(attemptedCommitsB).to.be.equal(1);
		expect(rollbacksB).to.be.equal(1);
	});

	it('should allow removing hooks', function () {
		const updates = [];
		let commits = 0;
		let rollbacks = 0;

		this.db.exec('CREATE TABLE entries (a TEXT, b INTEGER)');

		this.db.updateHook((op, dbName, tableName, rowid) => {
			updates.push({ op, dbName, tableName, rowid });
		});
		this.db.commitHook(() => {
			++commits;
			return true;
		});
		this.db.rollbackHook(() => {
			++rollbacks;
		});
		this.db.exec("INSERT INTO entries VALUES ('foobar', 44)");

		expect(updates).to.have.lengthOf(1);
		expect(updates[0].op).to.equal('SQLITE_INSERT');
		expect(updates[0].dbName).to.equal('main');
		expect(updates[0].tableName).to.equal('entries');
		expect(updates[0].rowid).to.be.equal(1n);

		expect(commits).to.be.equal(1);
		expect(rollbacks).to.be.equal(0);

		this.db.updateHook(null);
		this.db.commitHook(undefined);
		this.db.rollbackHook();
		this.db.exec("INSERT INTO entries VALUES ('bazquux', 99)");

		expect(updates).to.have.lengthOf(1);
		expect(commits).to.be.equal(1);
		expect(rollbacks).to.be.equal(0);
	});
});
