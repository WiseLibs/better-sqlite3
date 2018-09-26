'use strict';
const Database = require('../.');

describe('Database#pragma()', function () {
	it('should throw an exception if a string is not provided', function () {
		const db = new Database(util.next());
		expect(() => db.pragma(123)).to.throw(TypeError);
		expect(() => db.pragma(0)).to.throw(TypeError);
		expect(() => db.pragma(null)).to.throw(TypeError);
		expect(() => db.pragma()).to.throw(TypeError);
		expect(() => db.pragma(new String('cache_size'))).to.throw(TypeError);
	});
	it('should throw an exception if invalid/redundant SQL is provided', function () {
		const db = new Database(util.next());
		expect(() => db.pragma('PRAGMA cache_size')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(() => db.pragma('cache_size; PRAGMA cache_size')).to.throw(RangeError);
	});
	it('should execute the pragma, returning rows of results', function () {
		const db = new Database(util.next());
		const rows = db.pragma('cache_size');
		expect(rows).to.be.an('array');
		expect(rows[0]).to.be.an('object');
		expect(rows[0].cache_size).to.be.a('number');
		expect(rows[0].cache_size).to.equal(-16000);
	});
	it('should optionally return simpler results', function () {
		const db = new Database(util.next());
		expect(db.pragma('cache_size', { simple: false })).to.be.an('array');
		const cache_size = db.pragma('cache_size', { simple: true });
		expect(cache_size).to.be.a('number');
		expect(cache_size).to.equal(-16000);
		expect(() => db.pragma('cache_size', true)).to.throw(TypeError);
		expect(() => db.pragma('cache_size', 123)).to.throw(TypeError);
		expect(() => db.pragma('cache_size', function () {})).to.throw(TypeError);
		expect(() => db.pragma('cache_size', NaN)).to.throw(TypeError);
		expect(() => db.pragma('cache_size', 'true')).to.throw(TypeError);
	});
	it('should obey PRAGMA changes', function () {
		const db = new Database(util.next());
		expect(db.pragma('cache_size', { simple: true })).to.equal(-16000);
		db.pragma('cache_size = -8000');
		expect(db.pragma('cache_size', { simple: true })).to.equal(-8000);
		expect(db.pragma('journal_mode', { simple: true })).to.equal('delete');
		db.pragma('journal_mode = wal');
		expect(db.pragma('journal_mode', { simple: true })).to.equal('wal');
	});
	it('should respect readonly connections', function () {
		(new Database(util.next())).close();
		const db = new Database(util.current(), { readonly: true, fileMustExist: true });
		expect(db.pragma('cache_size', { simple: true })).to.equal(-16000);
		db.pragma('cache_size = -8000');
		expect(db.pragma('cache_size', { simple: true })).to.equal(-8000);
		expect(db.pragma('journal_mode', { simple: true })).to.equal('delete');
		expect(() => db.pragma('journal_mode = wal')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_READONLY');
		expect(db.pragma('journal_mode', { simple: true })).to.equal('delete');
	});
	it('should return undefined if no rows exist and simpler results are desired', function () {
		const db = new Database(util.next());
		expect(db.pragma('table_info', { simple: true })).to.be.undefined;
	});
});
