'use strict';
const Database = require('../.');

describe('Database#table()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
	});
	afterEach(function () {
		this.db.close();
	});

	it('should throw an exception if the correct arguments are not provided', function () {
		expect(() => this.db.table()).to.throw(TypeError);
		expect(() => this.db.table(null)).to.throw(TypeError);
		expect(() => this.db.table('a')).to.throw(TypeError);
		expect(() => this.db.table({})).to.throw(TypeError);
		expect(() => this.db.table({ rows: function*(){}, columns: ['x'] })).to.throw(TypeError);
		expect(() => this.db.table({ name: 'b', rows: function*(){}, columns: ['x'] })).to.throw(TypeError);
		expect(() => this.db.table(() => {})).to.throw(TypeError);
		expect(() => this.db.table(function* c() {})).to.throw(TypeError);
		expect(() => this.db.table({}, function d() {})).to.throw(TypeError);
		expect(() => this.db.table({ name: 'e', rows: function* e() {}, columns: ['x'] }, function e() {})).to.throw(TypeError);
		expect(() => this.db.table('f')).to.throw(TypeError);
		expect(() => this.db.table('g', null)).to.throw(TypeError);
		expect(() => this.db.table('h', {})).to.throw(TypeError);
		expect(() => this.db.table('i', Object.create(Function.prototype))).to.throw(TypeError);
		expect(() => this.db.table('j', { columns: ['x'] }, function j() {})).to.throw(TypeError);
		expect(() => this.db.table('k', { name: 'k', columns: ['x'] }, function* k() {})).to.throw(TypeError);
		expect(() => this.db.table('l', { name: 'l', rows: function* l() {} })).to.throw(TypeError);
		expect(() => this.db.table(new String('m'), { columns: ['x'], rows: function* m() {} })).to.throw(TypeError);
		expect(() => this.db.table(new String('n'), () => {})).to.throw(TypeError);
	});
	it('should throw an exception if boolean options are provided as non-booleans', function () {
		expect(() => this.db.table('a', { columns: ['x'], rows: function*(){}, directOnly: undefined })).to.throw(TypeError);
		expect(() => this.db.table('b', { columns: ['x'], rows: function*(){}, safeIntegers: undefined })).to.throw(TypeError);
	});
	it('should throw an exception if the "columns" option is invalid', function () {
		expect(() => this.db.table('a', { rows: function*(){} })).to.throw(TypeError);
		expect(() => this.db.table('b', { columns: undefined, rows: function*(){} })).to.throw(TypeError);
		expect(() => this.db.table('c', { columns: 'x', rows: function*(){} })).to.throw(TypeError);
		expect(() => this.db.table('d', { columns: { length: 1, 0: 'x', [Symbol.iterator]: () => ['x'].values() }, rows: function*(){} })).to.throw(TypeError);
		expect(() => this.db.table('e', { columns: ['x',, 'y'], rows: function*(){} })).to.throw(TypeError);
		expect(() => this.db.table('f', { columns: ['x', new String('y')], rows: function*(){} })).to.throw(TypeError);
		expect(() => this.db.table('g', { columns: ['x', 'x'], rows: function*(){} })).to.throw(TypeError);
		expect(() => this.db.table('h', { columns: [], rows: function*(){} })).to.throw(RangeError);
	});
	it('should throw an exception if the "parameters" option is invalid', function () {
		expect(() => this.db.table('a', { parameters: undefined, columns: ['foo'], rows: function*(){} })).to.throw(TypeError);
		expect(() => this.db.table('b', { parameters: 'x', columns: ['foo'], rows: function*(){} })).to.throw(TypeError);
		expect(() => this.db.table('c', { parameters: { length: 1, 0: 'x', [Symbol.iterator]: () => ['x'].values() }, columns: ['foo'], rows: function*(){} })).to.throw(TypeError);
		expect(() => this.db.table('d', { parameters: ['x',, 'y'], columns: ['foo'], rows: function*(){} })).to.throw(TypeError);
		expect(() => this.db.table('e', { parameters: ['x', new String('y')], columns: ['foo'], rows: function*(){} })).to.throw(TypeError);
		expect(() => this.db.table('f', { parameters: ['x', 'x'], columns: ['foo'], rows: function*(){} })).to.throw(TypeError);
		expect(() => this.db.table('g', { parameters: ['x'], columns: ['x'], rows: function*(){} })).to.throw(TypeError);
		expect(() => this.db.table('h', { parameters: [...Array(33)].map((_, i) => `p${i}`), columns: ['foo'], rows: function*(){} })).to.throw(RangeError);
	});
	it('should throw an exception if the "rows" option is invalid', function () {
		expect(() => this.db.table('a', { columns: ['x'] })).to.throw(TypeError);
		expect(() => this.db.table('b', { columns: ['x'], rows: undefined })).to.throw(TypeError);
		expect(() => this.db.table('c', { columns: ['x'], rows: {} })).to.throw(TypeError);
		expect(() => this.db.table('d', { columns: ['x'], rows: () => {} })).to.throw(TypeError);
		expect(() => this.db.table('e', { columns: ['x'], rows: function () {} })).to.throw(TypeError);
		expect(() => this.db.table('f', { columns: ['x'], rows: Object.create(Function.prototype) })).to.throw(TypeError);
		expect(() => this.db.table('g', { columns: ['x'], rows: Object.create(Object.getPrototypeOf(function*(){})) })).to.throw(TypeError);
		expect(() => this.db.table('h', { columns: ['x'], rows: Object.setPrototypeOf(() => {}, Object.create(Object.getPrototypeOf(function*(){}))) })).to.throw(TypeError);
	});
	it('should throw an exception if the provided name is empty', function () {
		expect(() => this.db.table('', { columns: ['x'], rows: function* () {} })).to.throw(TypeError);
		expect(() => this.db.table('', { name: 'a', columns: ['x'], rows: function* () {} })).to.throw(TypeError);
		expect(() => this.db.table('', { name: 'b', columns: ['x'], rows: function* b() {} })).to.throw(TypeError);
		expect(() => this.db.table('', function c() {})).to.throw(TypeError);
	});
	it('should throw an exception if generator.length is invalid', function () {
		const length = x => Object.defineProperty(function*(){}, 'length', { value: x });
		expect(() => this.db.table('a', { columns: ['x'], rows: length(undefined) })).to.throw(TypeError);
		expect(() => this.db.table('b', { columns: ['x'], rows: length(null) })).to.throw(TypeError);
		expect(() => this.db.table('c', { columns: ['x'], rows: length('1') })).to.throw(TypeError);
		expect(() => this.db.table('d', { columns: ['x'], rows: length(NaN) })).to.throw(TypeError);
		expect(() => this.db.table('e', { columns: ['x'], rows: length(Infinity) })).to.throw(TypeError);
		expect(() => this.db.table('f', { columns: ['x'], rows: length(1.000000001) })).to.throw(TypeError);
		expect(() => this.db.table('g', { columns: ['x'], rows: length(-0.000000001) })).to.throw(TypeError);
		expect(() => this.db.table('h', { columns: ['x'], rows: length(-1) })).to.throw(TypeError);
		expect(() => this.db.table('i', { columns: ['x'], rows: length(32.000000001) })).to.throw(TypeError);
		expect(() => this.db.table('j', { columns: ['x'], rows: length(33) })).to.throw(RangeError);
	});
	it('should register a virtual table and return the database object', function () {
		const length = x => Object.defineProperty(function*(){}, 'length', { value: x });
		expect(this.db.table('a', { columns: ['x'], rows: function* () {} })).to.equal(this.db);
		expect(this.db.table('b', { columns: ['x'], rows: length(1) })).to.equal(this.db);
		expect(this.db.table('c', { columns: ['x'], rows: length(32) })).to.equal(this.db);
	});
	it('should enable the registered virtual table to be queried from SQL', function () {
		const rows = [
			{ a: null, b: 123, c: 456.789, d: 'foo', e: Buffer.from('bar') },
			{ a: null, b: 987, c: 654.321, d: 'oof', e: Buffer.from('rab') },
		];
		this.db.table('vtab', {
			columns: ['a', 'b', 'c', 'd', 'e'],
			*rows() {
				for (const obj of rows) {
					yield Object.values(obj);
				}
			},
		});
		expect(this.db.prepare('SELECT * FROM vtab').all()).to.deep.equal(rows);
		expect(this.db.prepare('SELECT * FROM vtab WHERE b < 500').all()).to.deep.equal(rows.slice(0, 1));
		expect(this.db.prepare('SELECT * FROM vtab ORDER BY d DESC').all()).to.deep.equal(rows.slice().reverse());
	});
	it('should infer parameters for the virtual table', function () {
		this.db.table('vtab', {
			columns: ['a', 'b'],
			*rows(x, y) {
				yield [x, y];
				yield [x * 2, y * 3];
			},
		});
		expect(this.db.prepare('SELECT * FROM vtab(?, ?)').all(2, 3))
			.to.deep.equal([{ a: 2, b: 3 }, { a: 4, b: 9 }]);
		expect(this.db.prepare('SELECT * FROM vtab WHERE "$1" = ? AND "$2" = ?').all(2, 3))
			.to.deep.equal([{ a: 2, b: 3 }, { a: 4, b: 9 }]);
		expect(() => this.db.prepare('SELECT * FROM vtab(?, ?, ?)'))
			.to.throw(Database.SqliteError);
		expect(() => this.db.prepare('SELECT * FROM vtab WHERE "$1" = ? AND "$2" = ? AND "$3" = ?'))
			.to.throw(Database.SqliteError);
	});
	it('should accept explicit parameters for the virtual table', function () {
		this.db.table('vtab', {
			columns: ['a', 'b'],
			parameters: ['x', 'y', 'z'],
			*rows(p1, p2, p3, p4) {
				yield [arguments[0], arguments[1] + arguments[2]];
				yield [arguments[0] * 2, (arguments[1] + arguments[2]) * 3];
			},
		});
		expect(this.db.prepare('SELECT * FROM vtab(?, ?, ?)').all(2, 3, 4))
			.to.deep.equal([{ a: 2, b: 7 }, { a: 4, b: 21 }]);
		expect(this.db.prepare('SELECT * FROM vtab WHERE x = ? AND y = ? AND z = ?').all(2, 3, 4))
			.to.deep.equal([{ a: 2, b: 7 }, { a: 4, b: 21 }]);
		expect(() => this.db.prepare('SELECT * FROM vtab(?, ?, ?, ?)'))
			.to.throw(Database.SqliteError);
		expect(() => this.db.prepare('SELECT * FROM vtab WHERE "$1" = ? AND "$2" = ? AND "$3" = ?'))
			.to.throw(Database.SqliteError);
	});
	it('should accept a large number of parameters for the virtual table', function () {
		const args = ['foo', 'bar', 1, -2, Buffer.from('hello'), 5, -10, 'baz', 99.9, -0.5];
		this.db.table('vtab', {
			columns: ['x'],
			*rows(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10) {
				yield [p10];
				yield [p9];
				yield [p8];
				yield [p7];
				yield [p6];
				yield [p5];
				yield [p4];
				yield [p3];
				yield [p2];
				yield [p1];
			},
		});
		expect(this.db.prepare('SELECT * FROM vtab(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)').pluck().all(args))
			.to.deep.equal(args.slice().reverse());
		expect(this.db.prepare('SELECT * FROM vtab(?, ?, ?, ?, ?, ?, ?, ?, ?)').pluck().all(args.slice(0, -1)))
			.to.deep.equal([null].concat(args.slice(0, -1).reverse()));
		expect(() => this.db.prepare('SELECT * FROM vtab(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)'))
			.to.throw(Database.SqliteError);
	});
	it('should correctly handle arguments even when used out of order', function () {
		const calls = [];
		this.db.table('vtab', {
			columns: ['x', 'y'],
			*rows(x, y) {
				calls.push([...arguments]);
				yield { x, y };
			},
		});
		expect(this.db.prepare('SELECT * FROM vtab WHERE "$1" = ? AND "$2" = ?').get(10, 5))
			.to.deep.equal({ x: 10, y: 5 });
		expect(calls.splice(0)).to.deep.equal([[10, 5]]);
		expect(this.db.prepare('SELECT * FROM vtab WHERE "$2" = ? AND "$1" = ?').get(5, 10))
			.to.deep.equal({ x: 10, y: 5 });
		expect(calls.splice(0)).to.deep.equal([[10, 5]]);
		expect(this.db.prepare('SELECT * FROM vtab WHERE "$2" = ? AND "$2" = ? AND "$1" = ?').get(5, 5, 10))
			.to.deep.equal({ x: 10, y: 5 });
		expect(calls.splice(0)).to.deep.equal([[10, 5]]);
		expect(this.db.prepare('SELECT * FROM vtab WHERE "$2" = ? AND "$2" = ? AND "$1" = ?').get(5, 9, 10))
			.to.be.undefined;
		expect(calls.splice(0)).to.deep.equal([[10, 5]]);
		expect(this.db.prepare('SELECT * FROM vtab WHERE "$2" = ? AND "$2" = ? AND "$1" = ?').get(9, 5, 10))
			.to.be.undefined;
		expect(calls.splice(0)).to.deep.equal([[10, 9]]);
	});
	it.skip('should correctly handle arguments that are constrained to other arguments', function () {
		// This test case fails due to a bug in SQLite (as of May 2021):
		// https://sqlite.org/forum/forumpost/830d37b928
		const calls = [];
		this.db.table('vtab', {
			columns: ['x', 'y'],
			*rows(x, y) {
				calls.push([...arguments]);
				yield { x, y };
			},
		});
		expect(this.db.prepare('SELECT * FROM vtab WHERE "$1" = ? AND "$2" = "$1"').get(10))
			.to.deep.equal({ x: 10, y: 10 });
		expect(calls.splice(0)).to.deep.equal([[10, 10]]);
		expect(this.db.prepare('SELECT * FROM vtab WHERE "$2" = "$1" AND "$1" = ?').get(10))
			.to.deep.equal({ x: 10, y: 10 });
		expect(calls.splice(0)).to.deep.equal([[10, 10]]);
		expect(this.db.prepare('SELECT * FROM vtab WHERE "$2" = ? AND "$2" = "$1" AND "$1" = ?').get(10, 10))
			.to.deep.equal({ x: 10, y: 10 });
		expect(calls.splice(0)).to.deep.equal([[10, 10]]);
		expect(this.db.prepare('SELECT * FROM vtab WHERE "$2" = ? AND "$2" = "$1" AND "$1" = ?').get(5, 10))
			.to.be.undefined;
		expect(calls.splice(0)).to.deep.equal([[10, 5]]);
		expect(this.db.prepare('SELECT * FROM vtab WHERE "$2" = "$1" AND "$2" = ? AND "$1" = ?').get(5, 10))
			.to.be.undefined;
		expect(calls.splice(0)).to.deep.equal([[10, 10]]);
	});
	it('should throw an exception if the database is busy', function () {
		let ranOnce = false;
		for (const x of this.db.prepare('SELECT 2').pluck().iterate()) {
			expect(x).to.equal(2);
			ranOnce = true;
			expect(() => this.db.table('a', { columns: ['x'], rows: function* () {} })).to.throw(TypeError);
		}
		expect(ranOnce).to.be.true;
		this.db.table('b', { columns: ['x'], rows: function* () {} });
	});
	it('should cause the database to become busy when querying the virtual table', function () {
		let checkCount = 0;
		const expectBusy = function* () {
			for (let i = 0; i < 3; ++i) {
				expect(() => this.db.exec('SELECT * FROM a')).to.throw(TypeError);
				expect(() => this.db.prepare('SELECT 555')).to.throw(TypeError);
				expect(() => this.db.pragma('cache_size')).to.throw(TypeError);
				expect(() => this.db.function('x', () => {})).to.throw(TypeError);
				expect(() => this.db.table('y', { columns: ['x'], rows: function* () {} })).to.throw(TypeError);
				checkCount += 1;
				yield [i];
			}
		};
		this.db.table('a', { columns: ['x'], rows: function* () {} });
		this.db.table('b', { columns: ['x'], rows: expectBusy });

		expect(this.db.prepare('SELECT * FROM b').pluck().all()).to.deep.equal([0, 1, 2]);
		expect(checkCount).to.equal(3);

		this.db.exec('SELECT * FROM a');
		this.db.prepare('SELECT 555');
		this.db.pragma('cache_size');
		this.db.function('xx', () => {});
		this.db.table('yy', { columns: ['x'], rows: function* () {} })
	});
	it('should cause the virtual table to throw when yielding an invalid value', function () {
		this.db.table('a', {
			columns: ['x'],
			*rows() { yield [42]; }
		});
		this.db.table('b', {
			columns: ['x'],
			*rows() { yield 42; }
		});
		this.db.table('c', {
			columns: ['x'],
			*rows() { yield; }
		});
		this.db.table('d', {
			columns: ['x'],
			*rows() { yield null; }
		});
		expect(this.db.prepare('SELECT * FROM a').get()).to.deep.equal({ x: 42 });
		expect(() => this.db.prepare('SELECT * FROM b').get()).to.throw(TypeError);
		expect(() => this.db.prepare('SELECT * FROM c').get()).to.throw(TypeError);
		expect(() => this.db.prepare('SELECT * FROM d').get()).to.throw(TypeError);
	});
	it('should allow arrays to be yielded as rows', function () {
		const rows = [
			{ a: null, b: 123, c: 456.789, d: 'foo', e: Buffer.from('bar') },
			{ a: null, b: 987, c: 654.321, d: 'oof', e: Buffer.from('rab') },
		];
		this.db.table('vtab', {
			columns: ['a', 'b', 'c', 'd', 'e'],
			*rows() {
				for (const obj of rows) {
					yield Object.values(obj);
				}
			},
		});
		expect(this.db.prepare('SELECT * FROM vtab').all()).to.deep.equal(rows);
	});
	it('should allow objects to be yielded as rows', function () {
		const rows = [
			{ a: null, b: 123, c: 456.789, d: 'foo', e: Buffer.from('bar') },
			{ a: null, b: 987, c: 654.321, d: 'oof', e: Buffer.from('rab') },
			{ e: Buffer.from('hello'), d: 'world', c: 0.1, b: 10, a: null },
			{ d: 'old friend', c: -0.1, e: Buffer.from('goodbye'), a: null, b: -10 },
		];
		this.db.table('vtab', {
			columns: ['a', 'b', 'c', 'd', 'e'],
			*rows() {
				for (const obj of rows) {
					yield obj;
				}
			},
		});
		expect(this.db.prepare('SELECT * FROM vtab').all()).to.deep.equal(rows);
	});
	it('should throw an exception if an invalid array is yielded', function () {
		const tests = [
			[1, 2, 3, 4, 5],
			[1, 2, 3, 4, 5, 6],
			[1, 2, 3, 4],
			[],
			[1, 2, 3, 4, new Number(5)],
			[1, 2, 3, 4, [5]],
			[1, 2, 3, 4, new Date()],
		];
		this.db.table('vtab', {
			columns: ['a', 'b', 'c', 'd', 'e'],
			*rows(n) {
				yield tests[n];
			},
		});
		expect(this.db.prepare('SELECT * FROM vtab(?)').raw().all(0)).to.deep.equal([tests[0]]);
		expect(() => this.db.prepare('SELECT * FROM vtab(?)').all(1)).to.throw(TypeError);
		expect(() => this.db.prepare('SELECT * FROM vtab(?)').all(2)).to.throw(TypeError);
		expect(() => this.db.prepare('SELECT * FROM vtab(?)').all(3)).to.throw(TypeError);
		expect(() => this.db.prepare('SELECT * FROM vtab(?)').all(4)).to.throw(TypeError);
		expect(() => this.db.prepare('SELECT * FROM vtab(?)').all(5)).to.throw(TypeError);
		expect(() => this.db.prepare('SELECT * FROM vtab(?)').all(6)).to.throw(TypeError);
	});
	it('should throw an exception if an invalid object is yielded', function () {
		const tests = [
			{ a: 1, b: 2, c: 3, d: 4, e: 5 },
			{ a: 1, b: 2, c: 3, d: 4, e: 5, f: 6 },
			{ a: 1, b: 2, c: 3, d: 4 },
			{},
			{ a: 1, b: 2, c: 3, d: 4, e: new Number(5) },
			{ a: 1, b: 2, c: 3, d: 4, e: [5] },
			{ a: 1, b: 2, c: 3, d: 4, e: new Date() },
			{ a: 1, b: 2, c: 3, d: 4, f: 5 },
		];
		this.db.table('vtab', {
			columns: ['a', 'b', 'c', 'd', 'e'],
			*rows(n) {
				yield tests[n];
			},
		});
		expect(this.db.prepare('SELECT * FROM vtab(?)').all(0)).to.deep.equal([tests[0]]);
		expect(() => this.db.prepare('SELECT * FROM vtab(?)').all(1)).to.throw(TypeError);
		expect(() => this.db.prepare('SELECT * FROM vtab(?)').all(2)).to.throw(TypeError);
		expect(() => this.db.prepare('SELECT * FROM vtab(?)').all(3)).to.throw(TypeError);
		expect(() => this.db.prepare('SELECT * FROM vtab(?)').all(4)).to.throw(TypeError);
		expect(() => this.db.prepare('SELECT * FROM vtab(?)').all(5)).to.throw(TypeError);
		expect(() => this.db.prepare('SELECT * FROM vtab(?)').all(6)).to.throw(TypeError);
		expect(() => this.db.prepare('SELECT * FROM vtab(?)').all(7)).to.throw(TypeError);
	});
	it('should automatically assign rowids without affecting yielded objects', function () {
		let rows = [{ x: 5 }, { x: 10 }];
		this.db.table('a', {
			columns: ['x'],
			*rows() { yield* rows; },
		});
		expect(this.db.prepare('SELECT rowid, * FROM a').all())
			.to.deep.equal([{ rowid: 1, x: 5 }, { rowid: 2, x: 10 }]);
		expect(rows).to.deep.equal([{ x: 5 }, { x: 10 }]);

		rows = [{ rowid: 5 }, { rowid: 10 }];
		this.db.table('b', {
			columns: ['rowid'],
			*rows() { yield* rows; },
		});
		expect(this.db.prepare('SELECT oid AS oid, * FROM b').all())
			.to.deep.equal([{ oid: 1, rowid: 5 }, { oid: 2, rowid: 10 }]);
		expect(rows).to.deep.equal([{ rowid: 5 }, { rowid: 10 }]);
	});
	it('should be driven by stmt.iterate() one row at a time', function () {
		let state = 0;
		this.db.table('vtab', {
			columns: ['x'],
			*rows() {
				state += 1;
				yield ['foo'];
				state += 1;
				yield ['bar'];
				state += 1;
				yield ['baz'];
				state += 1;
				yield ['qux'];
				state += 1;
			},
		});
		const values = [];
		for (const value of this.db.prepare('SELECT * FROM vtab').pluck().iterate()) {
			values.push(value);
			if (value === 'baz') break;
		}
		expect(values).to.deep.equal(['foo', 'bar', 'baz']);
		expect(state).to.equal(3);
	});
	it('should throw an exception if preparing a statement that uses an unsupported operator on a parameter', function () {
		this.db.table('vtab', {
			columns: ['a', 'b'],
			parameters: ['x', 'y', 'z'],
			*rows(x, y, z) {
				yield [x, y + z];
				yield [x * 2, (y + z) * 3];
			},
		});
		expect(this.db.prepare('SELECT * FROM vtab(?, ?, ?)').all(2, 3, 4))
			.to.deep.equal([{ a: 2, b: 7 }, { a: 4, b: 21 }]);
		expect(this.db.prepare('SELECT * FROM vtab WHERE x = ? AND y = ? AND z = ?').all(2, 3, 4))
			.to.deep.equal([{ a: 2, b: 7 }, { a: 4, b: 21 }]);
		expect(() => this.db.prepare('SELECT * FROM vtab WHERE x = ? AND y = ? AND z > ?'))
			.to.throw(Database.SqliteError);
		expect(() => this.db.prepare('SELECT * FROM vtab WHERE x = ? AND y < ? AND z = ?'))
			.to.throw(Database.SqliteError);
		expect(() => this.db.prepare('SELECT * FROM vtab WHERE x IS ? AND y = ? AND z = ?'))
			.to.throw(Database.SqliteError);
	});
	it('should properly escape column and parameter names', function () {
		this.db.table('vtab', {
			columns: ['foo);'],
			parameters: ['x"); SELECT "y', 'y'],
			*rows(x, y) {
				yield [x];
				yield [y];
				yield [x + y];
			},
		});
		expect(this.db.prepare('SELECT "foo);" FROM vtab WHERE "x""); SELECT ""y" = ? AND y = ?').all(5, 10))
			.to.deep.equal([{ 'foo);': 5 }, { 'foo);': 10 }, { 'foo);': 15 }]);
	});
	it('should not allow CREATE VIRTUAL TABLE statements by default', function () {
		this.db.table('mod', {
			columns: ['x'],
			*rows() {},
		});
		expect(() => this.db.exec('CREATE VIRTUAL TABLE a USING mod')).to.throw(Database.SqliteError);
		expect(() => this.db.exec('CREATE VIRTUAL TABLE b USING mod()')).to.throw(Database.SqliteError);
		expect(() => this.db.exec('CREATE VIRTUAL TABLE c USING mod(foo)')).to.throw(Database.SqliteError);
	});
	it('should support CREATE VIRTUAL TABLE statements by accepting a factory function', function () {
		let table = '';
		this.db.table('mod', function (...args) {
			expect(this).to.deep.equal({ module: 'mod', database: 'main', table });
			return {
				columns: ['x'],
				*rows() { yield* args.map(x => [x]); },
			};
		});
		expect(() => this.db.prepare('SELECT * FROM mod')).to.throw(Database.SqliteError);
		table = 'foo';
		this.db.exec(`CREATE VIRTUAL TABLE ${table} USING mod(hello world, how are you?)`);
		table = 'bar';
		this.db.exec(`CREATE VIRTUAL TABLE ${table} USING mod(1, 2, 3)`);
		expect(this.db.prepare('SELECT x FROM foo').pluck().all()).to.deep.equal(['hello world', 'how are you?']);
		expect(this.db.prepare('SELECT x FROM bar').pluck().all()).to.deep.equal(['1', '2', '3']);
		expect(() => this.db.prepare('SELECT * FROM mod')).to.throw(Database.SqliteError);
	});
	it('should correctly handle omitted arguments in any order', function () {
		this.db.table('vtab', {
			columns: ['value'],
			parameters: ['x', 'y', 'z'],
			*rows(x = 100, y = 10, z = 1) {
				expect(arguments.length).to.equal(3);
				yield [x + y + z];
			},
		});
		expect(this.db.prepare('SELECT * FROM vtab(?, ?, ?)').pluck().get(2.2, 3.3, 4.4)).to.equal(9.9);
		expect(this.db.prepare('SELECT * FROM vtab(?, ?)').pluck().get(2.2, 3.3)).to.equal(6.5);
		expect(this.db.prepare('SELECT * FROM vtab(?)').pluck().get(2.2)).to.equal(13.2);
		expect(this.db.prepare('SELECT * FROM vtab').pluck().get()).to.equal(111);
		expect(this.db.prepare('SELECT * FROM vtab WHERE x = ? AND y = ? AND z = ?').pluck().get(2.2, 3.3, 4.4)).to.equal(9.9);
		expect(this.db.prepare('SELECT * FROM vtab WHERE x = ? AND y = ?').pluck().get(2.2, 3.3)).to.equal(6.5);
		expect(this.db.prepare('SELECT * FROM vtab WHERE x = ? AND z = ?').pluck().get(2.2, 3.3)).to.equal(15.5);
		expect(this.db.prepare('SELECT * FROM vtab WHERE y = ? AND z = ?').pluck().get(2.2, 3.3)).to.equal(105.5);
		expect(this.db.prepare('SELECT * FROM vtab WHERE x = ?').pluck().get(2.2)).to.equal(13.2);
		expect(this.db.prepare('SELECT * FROM vtab WHERE y = ?').pluck().get(2.2)).to.equal(103.2);
		expect(this.db.prepare('SELECT * FROM vtab WHERE z = ?').pluck().get(2.2)).to.equal(112.2);
	});
	it('should not call the generator function if any arguments are NULL', function () {
		let calls = 0;
		this.db.table('vtab', {
			columns: ['val'],
			parameters: ['x', 'y', 'z'],
			*rows(x = 0, y = 0, z = 0) {
				calls += 1;
				yield [x + y + z];
			},
		});
		expect(this.db.prepare('SELECT val FROM vtab(?, ?, ?)').pluck().all(1, 10, 100)).to.deep.equal([111]);
		expect(this.db.prepare('SELECT val FROM vtab(?, ?)').pluck().all(1, 10)).to.deep.equal([11]);
		expect(this.db.prepare('SELECT val FROM vtab(?, ?, ?)').pluck().all(1, 10, null)).to.deep.equal([]);
		expect(this.db.prepare('SELECT val FROM vtab(?, ?, ?)').pluck().all(1, null, 100)).to.deep.equal([]);
		expect(this.db.prepare('SELECT val FROM vtab(?, ?, ?)').pluck().all(null, 10, 100)).to.deep.equal([]);
		expect(this.db.prepare('SELECT val FROM vtab(?, ?)').pluck().all(1, null)).to.deep.equal([]);
		expect(calls).to.equal(2);
	});
	it('should close a statement iterator that caused a virtual table to throw', function () {
		this.db.prepare('CREATE TABLE iterable (x INTEGER)').run();
		this.db.prepare('INSERT INTO iterable WITH RECURSIVE temp(x) AS (SELECT 1 UNION ALL SELECT x * 2 FROM temp LIMIT 10) SELECT * FROM temp').run();

		let i = 0;
		const err = new Error('foo');
		this.db.table('vtab', {
			columns: ['value'],
			parameters: ['x'],
			*rows(x) {
				if (++i >= 5) throw err;
				yield [x];
			},
		});
		const iterator = this.db.prepare('SELECT value FROM vtab JOIN iterable USING (x)').pluck().iterate();

		let total = 0;
		expect(() => {
			for (const value of iterator) {
				total += value;
				expect(() => this.db.exec('SELECT value FROM vtab JOIN iterable USING (x) LIMIT 4')).to.throw(TypeError);
			}
		}).to.throw(err);

		expect(total).to.equal(1 + 2 + 4 + 8);
		expect(iterator.next()).to.deep.equal({ value: undefined, done: true });
		expect(total).to.equal(1 + 2 + 4 + 8);

		i = 0;
		this.db.exec('SELECT value FROM vtab JOIN iterable USING (x) LIMIT 4');
		expect(i).to.equal(4);
	});
	it('should not be able to affect bound buffers mid-query', function () {
		const input = Buffer.alloc(1024 * 8).fill(0xbb);
		let called = false;
		this.db.table('vtab', {
			columns: ['x'],
			*rows(arg) {
				called = true;
				input[0] = 2;
				arg[0] = 2;
				yield [123];
			},
		});
		const [output, arg, num] = this.db.prepare('SELECT :input, "$1", x FROM vtab(:input)').raw().get({ input });
		expect(called).to.be.true;
		expect(output.equals(Buffer.alloc(1024 * 8).fill(0xbb))).to.be.true;
		expect(arg.equals(Buffer.alloc(1024 * 8).fill(0xbb))).to.be.true;
		expect(num).to.equal(123);
	});
	describe('should propagate exceptions', function () {
		const exceptions = [new TypeError('foobar'), new Error('baz'), { yup: 'ok' }, 'foobarbazqux', '', null, 123.4];
		const expectError = (exception, fn) => {
			try { fn(); } catch (ex) {
				expect(ex).to.equal(exception);
				return;
			}
			throw new TypeError('Expected table to throw an exception');
		};

		specify('thrown in the factory function', function () {
			exceptions.forEach((exception, index) => {
				const calls = [];
				this.db.table(`mod${index}`, () => {
					calls.push('a');
					throw exception;
					calls.push('b');
					return {
						columns: ['x'],
						*rows() {
							calls.push('c');
							yield [42];
							calls.push('d');
						},
					};
				});
				expect(calls.splice(0)).to.deep.equal([]);
				expectError(exception, () => this.db.exec(`CREATE VIRTUAL TABLE vtab${index} USING mod${index}()`));
				expect(calls.splice(0)).to.deep.equal(['a']);
				expect(() => this.db.prepare(`SELECT * FROM vtab${index}`)).to.throw(Database.SqliteError);
				expect(calls.splice(0)).to.deep.equal([]);
			});
		});
		specify('thrown in the rows() function', function () {
			exceptions.forEach((exception, index) => {
				const calls = [];
				this.db.table(`mod${index}`, () => {
					calls.push('a');
					return {
						columns: ['x'],
						*rows() {
							calls.push('b');
							yield [42];
							calls.push('c');
							throw exception;
							calls.push('d');
						},
					};
				});
				expect(calls.splice(0)).to.deep.equal([]);
				this.db.exec(`CREATE VIRTUAL TABLE vtab${index} USING mod${index}()`);
				expect(calls.splice(0)).to.deep.equal(['a']);
				expect(this.db.prepare(`SELECT * FROM vtab${index}`).pluck().get()).to.equal(42);
				expect(calls.splice(0)).to.deep.equal(['b']);
				expectError(exception, () => this.db.prepare(`SELECT * FROM vtab${index}`).pluck().all());
				expect(calls.splice(0)).to.deep.equal(['b', 'c']);
			});
		});
		specify('thrown due to yielding an invalid value', function () {
			const calls = [];
			this.db.table('mod', () => {
				calls.push('a');
				return {
					columns: ['x'],
					*rows() {
						calls.push('b');
						yield [42];
						calls.push('c');
						yield [new Number(42)];
						calls.push('d');
					},
				};
			});
			expect(calls.splice(0)).to.deep.equal([]);
			this.db.exec('CREATE VIRTUAL TABLE vtab USING mod()');
			expect(calls.splice(0)).to.deep.equal(['a']);
			expect(this.db.prepare('SELECT * FROM vtab').pluck().get()).to.equal(42);
			expect(calls.splice(0)).to.deep.equal(['b']);
			expect(() => this.db.prepare('SELECT * FROM vtab').pluck().all()).to.throw(TypeError);
			expect(calls.splice(0)).to.deep.equal(['b', 'c']);
		});
	});
	describe('should not affect external environment', function () {
		specify('busy state', function () {
			this.db.table('vtab', {
				columns: ['x'],
				*rows(arg) {
					expect(() => this.db.exec('SELECT 555')).to.throw(TypeError);
					yield [arg * 2];
				},
			});
			let ranOnce = false;
			for (const x of this.db.prepare('SELECT * FROM vtab(555)').pluck().iterate()) {
				ranOnce = true;
				expect(x).to.equal(1110);
				expect(() => this.db.exec('SELECT 555')).to.throw(TypeError);
			}
			expect(ranOnce).to.be.true;
			this.db.exec('SELECT 555');
		});
		specify('was_js_error state', function () {
			this.db.prepare('CREATE TABLE data (value INTEGER)').run();
			const stmt = this.db.prepare('SELECT value FROM data');
			this.db.prepare('DROP TABLE data').run();

			const err = new Error('foo');
			this.db.table('vtab', {
				columns: ['x'],
				*rows() { throw err; },
			});

			expect(() => this.db.prepare('SELECT * FROM vtab').get()).to.throw(err);
			try { stmt.get(); } catch (ex) {
				expect(ex).to.be.an.instanceof(Error);
				expect(ex).to.not.equal(err);
				expect(ex.message).to.not.equal(err.message);
				expect(ex).to.be.an.instanceof(Database.SqliteError);
				return;
			}
			throw new TypeError('Expected the statement to throw an exception');
		});
	});
});
