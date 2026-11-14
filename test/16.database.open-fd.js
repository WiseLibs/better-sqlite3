'use strict';
const fs = require('fs');
const os = require('os');
const path = require('path');
const { spawn, spawnSync } = require('child_process');
const Database = require('../.');

const isWindows = os.platform().startsWith('win');
const UNLINKED = /deleted or replaced/;

describe('new Database(fd)', function () {
	beforeEach(function () {
		this.fds = [];
		this.dbs = [];
		this.openFd = (filename, flags = 'r+') => {
			const fd = fs.openSync(filename, flags);
			this.fds.push(fd);
			return fd;
		};
		// Creates the database and journal files, like a parent process would.
		this.createFiles = (filename = util.next()) => {
			fs.closeSync(fs.openSync(filename, 'a'));
			fs.closeSync(fs.openSync(`${filename}-journal`, 'a'));
			return filename;
		};
		this.openDb = (...args) => {
			const db = new Database(...args);
			this.dbs.push(db);
			return db;
		};
		this.openFdDb = (filename = this.createFiles(), options = {}, flags = 'r+') => {
			return this.openDb(this.openFd(filename, flags), { journalFd: this.openFd(`${filename}-journal`, flags), ...options });
		};
	});
	afterEach(function () {
		for (const db of this.dbs) try { db.close(); } catch (_) {}
		for (const fd of this.fds) try { fs.closeSync(fd); } catch (_) {}
	});

	it('should throw when given invalid file descriptor numbers', function () {
		const filename = this.createFiles();
		const fd = this.openFd(filename);
		const journalFd = this.openFd(`${filename}-journal`);
		for (const bad of [-1, 1.5, NaN, Infinity, 2 ** 31, -0.5]) {
			expect(() => this.openDb(bad, { journalFd })).to.throw(TypeError);
			expect(() => this.openDb(fd, { journalFd: bad })).to.throw(TypeError);
		}
		expect(() => this.openDb(fd, { journalFd: String(journalFd) })).to.throw(TypeError);
	});
	it('should require the "journalFd" option', function () {
		const filename = this.createFiles();
		expect(() => this.openDb(this.openFd(filename))).to.throw(TypeError, /journalFd/);
		expect(() => this.openDb(this.openFd(filename), {})).to.throw(TypeError, /journalFd/);
		expect(() => this.openDb(filename, { journalFd: this.openFd(`${filename}-journal`) })).to.throw(TypeError, /journalFd/);
	});

	if (isWindows) {
		it('should throw on Windows', function () {
			expect(() => this.openFdDb()).to.throw(TypeError, /not supported on Windows/);
		});
		return;
	}

	it('should open a database from file descriptors', function () {
		const filename = this.createFiles();
		const fd = this.openFd(filename);
		const db = this.openDb(fd, { journalFd: this.openFd(`${filename}-journal`) });
		expect(db.name).to.equal(`fd:${fd}`);
		expect(db.memory).to.be.false;
		expect(db.readonly).to.be.false;
		expect(db.open).to.be.true;
		expect(db.inTransaction).to.be.false;
		db.exec('CREATE TABLE data (x); INSERT INTO data VALUES (1), (2), (3)');
		expect(db.prepare('SELECT sum(x) FROM data').pluck().get()).to.equal(6);
		db.close();
		expect(db.open).to.be.false;
		expect(this.openDb(filename, { readonly: true }).prepare('SELECT sum(x) FROM data').pluck().get()).to.equal(6);
	});
	it('should open an existing database', function () {
		const filename = util.next();
		this.openDb(filename).exec('CREATE TABLE data (x); INSERT INTO data VALUES (42)');
		this.createFiles(filename);
		expect(this.openFdDb(filename).prepare('SELECT x FROM data').pluck().get()).to.equal(42);
	});
	it('should not take ownership of the file descriptors', function () {
		const filename = this.createFiles();
		const fd = this.openFd(filename);
		const journalFd = this.openFd(`${filename}-journal`);
		this.openDb(fd, { journalFd }).close();
		expect(() => fs.fstatSync(fd)).to.not.throw();
		expect(() => fs.fstatSync(journalFd)).to.not.throw();
	});
	it('should throw when a file descriptor is not open', function () {
		const filename = this.createFiles();
		const closed = 1000000; // Not open (closing a real descriptor would let it be reused)
		expect(() => this.openDb(closed, { journalFd: this.openFd(`${filename}-journal`) })).to.throw(TypeError, /database file descriptor is not open/);
		expect(() => this.openDb(this.openFd(filename), { journalFd: closed })).to.throw(TypeError, /journal file descriptor is not open/);
	});
	it('should throw when a file descriptor is not a regular file', function () {
		const filename = this.createFiles();
		const dir = this.openFd(path.dirname(filename), 'r');
		expect(() => this.openDb(dir, { journalFd: this.openFd(`${filename}-journal`) })).to.throw(TypeError, /database .* regular file/);
		expect(() => this.openDb(this.openFd(filename), { journalFd: dir })).to.throw(TypeError, /journal .* regular file/);
	});
	it('should throw when a file descriptor is not readable', function () {
		const filename = this.createFiles();
		expect(() => this.openFdDb(filename, {}, 'w')).to.throw(TypeError, /reading/);
		expect(() => this.openDb(this.openFd(filename), { journalFd: this.openFd(`${filename}-journal`, 'w') })).to.throw(TypeError, /journal .* reading/);
	});
	it('should throw when a file descriptor is in append mode', function () {
		const filename = this.createFiles();
		expect(() => this.openFdDb(filename, {}, 'a+')).to.throw(TypeError, /append/);
		expect(() => this.openDb(this.openFd(filename), { journalFd: this.openFd(`${filename}-journal`, 'a+') })).to.throw(TypeError, /journal .* append/);
	});
	it('should throw when both file descriptors refer to the same file', function () {
		const filename = this.createFiles();
		expect(() => this.openDb(this.openFd(filename), { journalFd: this.openFd(filename) })).to.throw(TypeError, /same file/);
	});
	it('should throw when a file has already been deleted', function () {
		const filename = this.createFiles();
		const fd = this.openFd(filename);
		const journalFd = this.openFd(`${filename}-journal`);
		fs.unlinkSync(`${filename}-journal`);
		expect(() => this.openDb(fd, { journalFd })).to.throw(TypeError, /journal file has been deleted/);
		fs.unlinkSync(filename);
		expect(() => this.openDb(fd, { journalFd })).to.throw(TypeError, /database file has been deleted/);
	});
	it('should require the "readonly" option for read-only file descriptors', function () {
		const filename = util.next();
		this.openDb(filename).exec('CREATE TABLE data (x); INSERT INTO data VALUES (1)');
		this.createFiles(filename);
		expect(() => this.openFdDb(filename, {}, 'r')).to.throw(TypeError, /readonly/);
		expect(() => this.openDb(this.openFd(filename), { journalFd: this.openFd(`${filename}-journal`, 'r') })).to.throw(TypeError, /journal.*readonly/);
		const db = this.openFdDb(filename, { readonly: true }, 'r');
		expect(db.readonly).to.be.true;
		expect(db.prepare('SELECT x FROM data').pluck().get()).to.equal(1);
		expect(() => db.exec('INSERT INTO data VALUES (2)')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_READONLY');
	});
	it('should respect the "readonly" option for writable file descriptors', function () {
		const filename = util.next();
		this.openDb(filename).exec('CREATE TABLE data (x)');
		this.createFiles(filename);
		const db = this.openFdDb(filename, { readonly: true });
		expect(db.readonly).to.be.true;
		expect(() => db.exec('INSERT INTO data VALUES (1)')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_READONLY');
	});
	it('should throw when the database is in WAL mode', function () {
		const filename = util.next();
		this.openDb(filename).pragma('journal_mode = WAL');
		this.dbs.pop().close();
		this.createFiles(filename);
		expect(() => this.openFdDb(filename)).to.throw(TypeError, /WAL/);
	});
	it('should not allow WAL mode', function () {
		const db = this.openFdDb();
		expect(() => db.pragma('journal_mode = WAL')).to.throw(Database.SqliteError, /not supported/);
		expect(() => db.pragma('main.journal_mode = wal')).to.throw(Database.SqliteError, /not supported/);
		expect(db.pragma('journal_mode', { simple: true })).to.equal('delete');
	});
	it('should never delete the journal file', function () {
		const filename = this.createFiles();
		const journal = `${filename}-journal`;
		const db = this.openFdDb(filename);
		expect(db.pragma('journal_mode', { simple: true })).to.equal('delete');
		db.exec('CREATE TABLE data (x)');
		for (const mode of ['delete', 'truncate', 'persist']) {
			expect(db.pragma(`journal_mode = ${mode}`, { simple: true })).to.equal(mode);
			db.exec('INSERT INTO data VALUES (1)');
			expect(fs.existsSync(journal)).to.be.true;
			if (mode !== 'persist') expect(fs.statSync(journal).size).to.equal(0);
		}
		expect(fs.readdirSync(path.dirname(filename)).filter(x => x.startsWith(`${path.basename(filename)}-`))).to.deep.equal([path.basename(journal)]);
	});
	it('should support transactions and rollbacks', function () {
		const db = this.openFdDb();
		db.exec('CREATE TABLE data (x)');
		const insert = db.prepare('INSERT INTO data VALUES (?)');
		db.transaction(() => { insert.run(1); insert.run(2); })();
		expect(() => db.transaction(() => { insert.run(3); throw new Error('rollback'); })()).to.throw('rollback');
		db.transaction(() => {
			insert.run(4);
			try { db.transaction(() => { insert.run(5); throw new Error('nested'); })(); } catch (_) {}
		})();
		expect(db.prepare('SELECT x FROM data ORDER BY x').pluck().all()).to.deep.equal([1, 2, 4]);
		db.exec('VACUUM');
		expect(db.prepare('SELECT x FROM data ORDER BY x').pluck().all()).to.deep.equal([1, 2, 4]);
	});
	it('should allow attaching path-based databases', function () {
		const db = this.openFdDb();
		const attached = util.next();
		db.prepare('ATTACH ? AS other').run(attached);
		db.exec('CREATE TABLE other.data (x); INSERT INTO other.data VALUES (1)');
		db.exec('DETACH other');
		expect(this.openDb(attached).prepare('SELECT x FROM data').pluck().get()).to.equal(1);
	});
	it('should not allow transactions that write to multiple databases', function () {
		const db = this.openFdDb();
		db.prepare('ATTACH ? AS other').run(util.next());
		db.exec('CREATE TABLE main.a (x); CREATE TABLE other.b (x);');
		expect(() => db.transaction(() => {
			db.exec('INSERT INTO main.a VALUES (1); INSERT INTO other.b VALUES (1);');
		})()).to.throw(Database.SqliteError, /multiple databases/);
		expect(db.inTransaction).to.be.false;
		expect(db.prepare('SELECT count(*) FROM main.a').pluck().get()).to.equal(0);
		expect(db.prepare('SELECT count(*) FROM other.b').pluck().get()).to.equal(0);
	});
	it('should not allow attaching other file descriptor databases by name', function () {
		const other = this.openFdDb();
		other.exec('CREATE TABLE data (x)');
		const filename = other.prepare('SELECT file FROM pragma_database_list WHERE name = \'main\'').pluck().get();
		const db = this.openFdDb();
		expect(() => db.prepare('ATTACH ? AS other').run(filename)).to.throw(Database.SqliteError).with.property('code', 'SQLITE_CANTOPEN');
	});
	it('should not allow different journal files for the same database', function () {
		const filename = this.createFiles();
		this.openFdDb(filename);
		const otherJournal = util.next();
		fs.writeFileSync(otherJournal, '');
		expect(() => this.openDb(this.openFd(filename), { journalFd: this.openFd(otherJournal) }))
			.to.throw(Database.SqliteError, /different journal file/);
	});

	describe('when a file is deleted or replaced', function () {
		for (const which of ['database', 'journal']) {
			it(`should fail closed if the ${which} file is deleted`, function () {
				const filename = this.createFiles();
				const db = this.openFdDb(filename);
				db.exec('CREATE TABLE data (x); INSERT INTO data VALUES (1)');
				fs.unlinkSync(which === 'database' ? filename : `${filename}-journal`);
				for (const fn of [
					() => db.prepare('SELECT * FROM data').all(),
					() => db.exec('INSERT INTO data VALUES (2)'),
				]) {
					expect(fn).to.throw(Database.SqliteError, UNLINKED).with.property('code', 'SQLITE_CANTOPEN');
				}
				expect(db.inTransaction).to.be.false;
			});
			it(`should fail closed if the ${which} file is replaced`, function () {
				const filename = this.createFiles();
				const db = this.openFdDb(filename);
				db.exec('CREATE TABLE data (x); INSERT INTO data VALUES (1)');
				const target = which === 'database' ? filename : `${filename}-journal`;
				fs.writeFileSync(`${target}.tmp`, fs.readFileSync(target));
				fs.renameSync(`${target}.tmp`, target);
				expect(() => db.prepare('SELECT * FROM data').all()).to.throw(Database.SqliteError, UNLINKED);
			});
		}
		it('should fail closed if a path-based connection deletes the journal', function () {
			const filename = this.createFiles();
			const db = this.openFdDb(filename);
			db.exec('CREATE TABLE data (x)');
			this.openDb(filename).exec('INSERT INTO data VALUES (1)'); // Uses journal_mode=DELETE
			expect(fs.existsSync(`${filename}-journal`)).to.be.false;
			expect(() => db.prepare('SELECT * FROM data').all()).to.throw(Database.SqliteError, UNLINKED);
		});
		it('should fail closed if the journal is deleted during a read transaction', function () {
			const filename = this.createFiles();
			const db = this.openFdDb(filename);
			db.exec('CREATE TABLE data (x); INSERT INTO data VALUES (1)');
			db.pragma('journal_mode = TRUNCATE'); // SQLite keeps the journal open between transactions
			db.unsafeMode();
			const iterator = db.prepare('SELECT * FROM data').iterate();
			iterator.next(); // Holds a SHARED lock
			db.exec('INSERT INTO data VALUES (2)');
			// A path-based connection (with journal_mode=DELETE) in another
			// process can delete the journal, because our SHARED lock doesn't
			// conflict with its RESERVED lock.
			const script = `
				const Database = require(${JSON.stringify(path.join(__dirname, '..'))});
				new Database(${JSON.stringify(filename)}).exec('BEGIN IMMEDIATE; INSERT INTO data VALUES (3); ROLLBACK');
			`;
			const result = spawnSync(process.execPath, ['-e', script], { encoding: 'utf8' });
			expect(result.status, result.stderr).to.equal(0);
			expect(fs.existsSync(`${filename}-journal`)).to.be.false;
			expect(() => db.exec('INSERT INTO data VALUES (4)')).to.throw(Database.SqliteError, UNLINKED).with.property('code', 'SQLITE_CANTOPEN');
			iterator.return();
		});
		it('should not attach an unreported error message to an unrelated error', async function () {
			const filename = this.createFiles();
			const db = this.openFdDb(filename);
			db.exec('CREATE TABLE data (x); INSERT INTO data VALUES (1)');
			fs.unlinkSync(`${filename}-journal`);
			// Backup errors are reported through the destination connection,
			// so the VFS's message on the source connection is never used.
			let backupError;
			await db.backup(util.next()).catch((err) => { backupError = err; });
			expect(backupError).to.be.an.instanceof(Database.SqliteError);
			const missing = path.join(util.next(), 'missing.db');
			expect(() => db.prepare('ATTACH ? AS other').run(missing))
				.to.throw(Database.SqliteError, 'unable to open database: ' + missing)
				.with.property('code', 'SQLITE_CANTOPEN');
		});
	});

	describe('crash recovery', function () {
		// Simulates a process that crashes in the middle of a large write
		// transaction, after it has started overwriting the database file.
		const crash = (filename) => {
			const script = `
				const fs = require('fs');
				const Database = require(${JSON.stringify(path.join(__dirname, '..'))});
				const filename = ${JSON.stringify(filename)};
				const db = new Database(fs.openSync(filename, 'r+'), { journalFd: fs.openSync(filename + '-journal', 'r+') });
				db.pragma('cache_size = 2');
				db.exec('BEGIN');
				db.exec('UPDATE data SET x = -x');
				db.exec('INSERT INTO data SELECT x + 1000000 FROM data');
				process.kill(process.pid, 'SIGKILL');
			`;
			const result = spawnSync(process.execPath, ['-e', script], { encoding: 'utf8' });
			expect(result.stderr).to.equal('');
			expect(result.signal).to.equal('SIGKILL');
			expect(fs.statSync(`${filename}-journal`).size).to.be.above(0);
		};
		const setup = (filename) => {
			const db = new Database(filename);
			db.exec('CREATE TABLE data (x)');
			db.transaction(() => {
				const insert = db.prepare('INSERT INTO data VALUES (?)');
				for (let i = 1; i <= 2000; ++i) insert.run(i);
			})();
			db.close();
		};
		const check = (db) => {
			expect(db.pragma('integrity_check', { simple: true })).to.equal('ok');
			expect(db.prepare('SELECT count(*) AS count, min(x) AS min, max(x) AS max FROM data').get())
				.to.deep.equal({ count: 2000, min: 1, max: 2000 });
		};

		it('should be performed by file descriptor connections', function () {
			this.timeout(10000);
			const filename = util.next();
			setup(filename);
			this.createFiles(filename);
			crash(filename);
			check(this.openFdDb(filename));
			expect(fs.statSync(`${filename}-journal`).size).to.equal(0);
		});
		it('should be performed by path-based connections', function () {
			this.timeout(10000);
			const filename = util.next();
			setup(filename);
			this.createFiles(filename);
			crash(filename);
			check(this.openDb(filename));
		});
		it('should not be performed by readonly connections', function () {
			this.timeout(10000);
			const filename = util.next();
			setup(filename);
			this.createFiles(filename);
			crash(filename);
			const readonly = this.openFdDb(filename, { readonly: true }, 'r');
			expect(() => readonly.prepare('SELECT * FROM data').all()).to.throw(Database.SqliteError).with.property('code', 'SQLITE_READONLY_ROLLBACK');
			const pathReadonly = this.openDb(filename, { readonly: true });
			expect(() => pathReadonly.prepare('SELECT * FROM data').all()).to.throw(Database.SqliteError).with.property('code', 'SQLITE_READONLY_ROLLBACK');
			check(this.openFdDb(filename));
			check(readonly);
		});
	});

	describe('locking', function () {
		it('should coordinate between connections sharing file descriptors', function () {
			const filename = this.createFiles();
			const fd = this.openFd(filename);
			const journalFd = this.openFd(`${filename}-journal`);
			const db1 = this.openDb(fd, { journalFd, timeout: 0 });
			const db2 = this.openDb(fd, { journalFd, timeout: 0 });
			db1.exec('CREATE TABLE data (x); INSERT INTO data VALUES (1)');

			db2.exec('BEGIN EXCLUSIVE');
			expect(() => db1.prepare('SELECT * FROM data').all()).to.throw(Database.SqliteError).with.property('code', 'SQLITE_BUSY');
			db2.exec('COMMIT');

			const iterator = db2.prepare('SELECT * FROM data').iterate();
			iterator.next(); // Holds a SHARED lock
			expect(() => db1.exec('INSERT INTO data VALUES (2)')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_BUSY');
			iterator.return();
			db1.exec('INSERT INTO data VALUES (2)');
			db1.close();
			expect(db2.prepare('SELECT count(*) FROM data').pluck().get()).to.equal(2);
		});
		it('should allow writes after a read-only connection opens the database first', function () {
			const filename = this.createFiles();
			const reader = this.openFdDb(filename, { readonly: true }, 'r'); // Its lock descriptor is read-only
			const writer = this.openFdDb(filename, { timeout: 0 });
			writer.exec('CREATE TABLE data (x); INSERT INTO data VALUES (1)');
			const iterator = reader.prepare('SELECT * FROM data').iterate();
			iterator.next(); // The writer's SHARED lock piggybacks on this one
			writer.exec('BEGIN');
			writer.prepare('SELECT * FROM data').all();
			iterator.return();
			writer.exec('INSERT INTO data VALUES (2)');
			writer.exec('COMMIT');
			expect(reader.prepare('SELECT count(*) FROM data').pluck().get()).to.equal(2);
		});
		it('should coordinate with path-based connections in other processes', async function () {
			this.timeout(10000);
			const filename = this.createFiles();
			const db = this.openFdDb(filename, { timeout: 0 });
			db.exec('CREATE TABLE data (x)');
			const script = `
				const Database = require(${JSON.stringify(path.join(__dirname, '..'))});
				const db = new Database(${JSON.stringify(filename)});
				db.pragma('journal_mode = PERSIST');
				db.exec('BEGIN EXCLUSIVE');
				process.stdout.write('locked');
				process.stdin.once('data', () => { db.exec('COMMIT'); db.close(); process.exit(0); });
			`;
			const child = spawn(process.execPath, ['-e', script], { stdio: ['pipe', 'pipe', 'inherit'] });
			try {
				await new Promise((resolve, reject) => {
					child.stdout.once('data', resolve);
					child.once('exit', () => reject(new Error('Child process exited early')));
				});
				expect(() => db.prepare('SELECT * FROM data').all()).to.throw(Database.SqliteError).with.property('code', 'SQLITE_BUSY');
				const exited = new Promise(resolve => child.once('exit', resolve));
				child.stdin.write('\n');
				await exited;
				db.exec('INSERT INTO data VALUES (1)');
				expect(db.prepare('SELECT count(*) FROM data').pluck().get()).to.equal(1);
			} finally {
				child.kill();
			}
		});
		for (const shared of [false, true]) {
			const description = shared
				? 'file descriptors inherited from the same open() call'
				: 'separately opened file descriptors';
			it(`should coordinate between processes using ${description}`, async function () {
				this.timeout(10000);
				const filename = this.createFiles();
				// This connection must be closed, so that this process doesn't
				// already have a different descriptor for acquiring locks.
				this.openFdDb(filename).exec('CREATE TABLE data (x)');
				this.dbs.pop().close();
				const childFds = [this.openFd(filename), this.openFd(`${filename}-journal`)];
				const script = `
					const Database = require(${JSON.stringify(path.join(__dirname, '..'))});
					const db = new Database(3, { journalFd: 4 });
					db.exec('BEGIN EXCLUSIVE; INSERT INTO data VALUES (1)');
					process.stdout.write('locked');
					process.stdin.once('data', () => { db.exec('COMMIT'); db.close(); process.exit(0); });
				`;
				const child = spawn(process.execPath, ['-e', script], { stdio: ['pipe', 'pipe', 'inherit', ...childFds] });
				try {
					await new Promise((resolve, reject) => {
						child.stdout.once('data', resolve);
						child.once('exit', () => reject(new Error('Child process exited early')));
					});
					const db = shared
						? this.openDb(childFds[0], { journalFd: childFds[1], timeout: 0 })
						: this.openFdDb(filename, { timeout: 0 });
					expect(() => db.prepare('SELECT * FROM data').all()).to.throw(Database.SqliteError).with.property('code', 'SQLITE_BUSY');
					expect(() => db.exec('INSERT INTO data VALUES (2)')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_BUSY');
					const exited = new Promise(resolve => child.once('exit', resolve));
					child.stdin.write('\n');
					await exited;
					db.exec('INSERT INTO data VALUES (2)');
					expect(db.prepare('SELECT x FROM data ORDER BY x').pluck().all()).to.deep.equal([1, 2]);
				} finally {
					child.kill();
				}
			});
		}
	});
});
