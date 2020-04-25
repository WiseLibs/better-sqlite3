'use strict';
const Database = require('../.');

describe('Database#unsafeMode()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
		this.db.exec('create table foo (x)');
		this.read = this.db.prepare('select 5');
		this.write = this.db.prepare('insert into foo values (0)');
	});
	afterEach(function () {
		this.db.close();
	});

	it('should not allow unsafe operations by default', function () {
		let hadRow = false;
		for (const row of this.read.iterate()) {
			expect(() => this.write.run()).to.throw(TypeError);
			expect(() => this.db.exec('select 5')).to.throw(TypeError);
			expect(() => this.db.pragma('cache_size')).to.throw(TypeError);
			hadRow = true;
		}
		expect(hadRow).to.be.true;

		this.db.pragma('journal_mode = OFF');
		this.db.pragma('writable_schema = ON');
		expect(this.db.pragma('journal_mode', { simple: true })).to.equal('delete');
		expect(() => this.db.exec("update sqlite_master set name = 'bar' where name = 'foo'")).to.throw(Database.SqliteError);
	});
	it('should allow unsafe operations when toggled on', function () {
		this.db.unsafeMode();

		let hadRow = false;
		for (const row of this.read.iterate()) {
			this.write.run();
			this.db.exec('select 5');
			this.db.pragma('cache_size');
			hadRow = true;
		}
		expect(hadRow).to.be.true;

		this.db.pragma('journal_mode = OFF');
		this.db.pragma('writable_schema = ON');
		expect(this.db.pragma('journal_mode', { simple: true })).to.equal('off');
		this.db.exec("update sqlite_master set name = 'bar' where name = 'foo'");

		this.db.unsafeMode(false);
		expect(() => this.db.exec("update sqlite_master set name = 'foo' where name = 'bar'")).to.throw(Database.SqliteError);
		this.db.unsafeMode(true);
		this.db.exec("update sqlite_master set name = 'foo' where name = 'bar'");
	});
});
