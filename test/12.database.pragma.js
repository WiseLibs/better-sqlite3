'use strict';
const Database = require('../.');

describe('Database#pragma()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
	});
	afterEach(function () {
		this.db.close();
	});

	it('should throw an exception if a string is not provided', function () {
		expect(() => this.db.pragma(123)).to.throw(TypeError);
		expect(() => this.db.pragma(0)).to.throw(TypeError);
		expect(() => this.db.pragma(null)).to.throw(TypeError);
		expect(() => this.db.pragma()).to.throw(TypeError);
		expect(() => this.db.pragma(new String('cache_size'))).to.throw(TypeError);
	});
	it('should throw an exception if boolean options are provided as non-booleans', function () {
		expect(() => this.db.pragma('cache_size', { simple: undefined })).to.throw(TypeError);
	});
	it('should throw an exception if invalid/redundant SQL is provided', function () {
		expect(() => this.db.pragma('PRAGMA cache_size')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(() => this.db.pragma('cache_size; PRAGMA cache_size')).to.throw(RangeError);
	});
	it('should execute the pragma, returning rows of results', function () {
		const rows = this.db.pragma('cache_size');
		expect(rows).to.be.an('array');
		expect(rows[0]).to.be.an('object');
		expect(rows[0].cache_size).to.be.a('number');
		expect(rows[0].cache_size).to.equal(-16000);
	});
	it('should optionally return simpler results', function () {
		expect(this.db.pragma('cache_size', { simple: false })).to.be.an('array');
		const cache_size = this.db.pragma('cache_size', { simple: true });
		expect(cache_size).to.be.a('number');
		expect(cache_size).to.equal(-16000);
		expect(() => this.db.pragma('cache_size', true)).to.throw(TypeError);
		expect(() => this.db.pragma('cache_size', 123)).to.throw(TypeError);
		expect(() => this.db.pragma('cache_size', function () {})).to.throw(TypeError);
		expect(() => this.db.pragma('cache_size', NaN)).to.throw(TypeError);
		expect(() => this.db.pragma('cache_size', 'true')).to.throw(TypeError);
	});
	it('should obey PRAGMA changes', function () {
		expect(this.db.pragma('cache_size', { simple: true })).to.equal(-16000);
		this.db.pragma('cache_size = -8000');
		expect(this.db.pragma('cache_size', { simple: true })).to.equal(-8000);
		expect(this.db.pragma('journal_mode', { simple: true })).to.equal('delete');
		this.db.pragma('journal_mode = wal');
		expect(this.db.pragma('journal_mode', { simple: true })).to.equal('wal');
	});
	it('should respect readonly connections', function () {
		this.db.close();
		this.db = new Database(util.current(), { readonly: true, fileMustExist: true });
		expect(this.db.pragma('cache_size', { simple: true })).to.equal(-16000);
		this.db.pragma('cache_size = -8000');
		expect(this.db.pragma('cache_size', { simple: true })).to.equal(-8000);
		expect(this.db.pragma('journal_mode', { simple: true })).to.equal('delete');
		expect(() => this.db.pragma('journal_mode = wal')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_READONLY');
		expect(this.db.pragma('journal_mode', { simple: true })).to.equal('delete');
	});
	it('should return undefined if no rows exist and simpler results are desired', function () {
		expect(this.db.pragma('table_info', { simple: true })).to.be.undefined;
	});
});
