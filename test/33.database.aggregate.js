'use strict';
const Database = require('../.');

describe('Database#aggregate()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
		this.db.prepare('CREATE TABLE empty (_)').run();
		this.db.prepare('CREATE TABLE ints (_)').run();
		this.db.prepare('CREATE TABLE texts (_)').run();
		this.db.prepare('INSERT INTO ints VALUES (?), (?), (?), (?), (?), (?), (?)').run(3, 5, 7, 11, 13, 17, 19);
		this.db.prepare('INSERT INTO texts VALUES (?), (?), (?), (?), (?), (?), (?)').run('a', 'b', 'c', 'd', 'e', 'f', 'g');
		this.get = (SQL, ...args) => this.db.prepare(`SELECT ${SQL}`).pluck().get(args);
		this.all = (SQL, ...args) => this.db.prepare(`SELECT ${SQL} WINDOW win AS (ORDER BY rowid ROWS BETWEEN 1 PRECEDING AND 1 FOLLOWING) ORDER BY rowid`).pluck().all(args);
	});
	afterEach(function () {
		this.db.close();
	});

	it('should throw an exception if the correct arguments are not provided', function () {
		expect(() => this.db.aggregate()).to.throw(TypeError);
		expect(() => this.db.aggregate(null)).to.throw(TypeError);
		expect(() => this.db.aggregate('a')).to.throw(TypeError);
		expect(() => this.db.aggregate({})).to.throw(TypeError);
		expect(() => this.db.aggregate({ step: () => {} })).to.throw(TypeError);
		expect(() => this.db.aggregate({ name: 'b', step: function b() {} })).to.throw(TypeError);
		expect(() => this.db.aggregate(() => {})).to.throw(TypeError);
		expect(() => this.db.aggregate(function c() {})).to.throw(TypeError);
		expect(() => this.db.aggregate({}, function d() {})).to.throw(TypeError);
		expect(() => this.db.aggregate({ name: 'e', step: function e() {} }, function e() {})).to.throw(TypeError);
		expect(() => this.db.aggregate('f')).to.throw(TypeError);
		expect(() => this.db.aggregate('g', null)).to.throw(TypeError);
		expect(() => this.db.aggregate('h', {})).to.throw(TypeError);
		expect(() => this.db.aggregate('i', function i() {})).to.throw(TypeError);
		expect(() => this.db.aggregate('j', {}, function j() {})).to.throw(TypeError);
		expect(() => this.db.aggregate('k', { name: 'k' }, function k() {})).to.throw(TypeError);
		expect(() => this.db.aggregate('l', { inverse: function l() {} })).to.throw(TypeError);
		expect(() => this.db.aggregate('m', { result: function m() {} })).to.throw(TypeError);
		expect(() => this.db.aggregate(new String('n'), { step: function n() {} })).to.throw(TypeError);
	});
	it('should throw an exception if boolean options are provided as non-booleans', function () {
		expect(() => this.db.aggregate('a', { step: () => {}, varargs: undefined })).to.throw(TypeError);
		expect(() => this.db.aggregate('b', { step: () => {}, deterministic: undefined })).to.throw(TypeError);
		expect(() => this.db.aggregate('c', { step: () => {}, safeIntegers: undefined })).to.throw(TypeError);
	});
	it('should throw an exception if function options are provided as non-fns', function () {
		expect(() => this.db.aggregate('a', { step: undefined })).to.throw(TypeError);
		expect(() => this.db.aggregate('b', { step: null })).to.throw(TypeError);
		expect(() => this.db.aggregate('c', { step: false })).to.throw(TypeError);
		expect(() => this.db.aggregate('d', { step: true })).to.throw(TypeError);
		expect(() => this.db.aggregate('e', { step: Object.create(Function.prototype) })).to.throw(TypeError);
		expect(() => this.db.aggregate('f', { step: () => {}, inverse: false })).to.throw(TypeError);
		expect(() => this.db.aggregate('g', { step: () => {}, inverse: true })).to.throw(TypeError);
		expect(() => this.db.aggregate('h', { step: () => {}, inverse: Object.create(Function.prototype) })).to.throw(TypeError);
		expect(() => this.db.aggregate('i', { step: () => {}, result: false })).to.throw(TypeError);
		expect(() => this.db.aggregate('j', { step: () => {}, result: true })).to.throw(TypeError);
		expect(() => this.db.aggregate('k', { step: () => {}, result: Object.create(Function.prototype) })).to.throw(TypeError);
	});
	it('should throw an exception if the provided name is empty', function () {
		expect(() => this.db.aggregate('', { step: () => {} })).to.throw(TypeError);
		expect(() => this.db.aggregate('', { name: 'a', step: () => {} })).to.throw(TypeError);
		expect(() => this.db.aggregate('', { name: 'b', step: function b() {} })).to.throw(TypeError);
	});
	it('should throw an exception if step.length or inverse.length is invalid', function () {
		const length = x => Object.defineProperty(() => {}, 'length', { value: x });
		expect(() => this.db.aggregate('a', { step: length(undefined) })).to.throw(TypeError);
		expect(() => this.db.aggregate('b', { step: length(null) })).to.throw(TypeError);
		expect(() => this.db.aggregate('c', { step: length('2') })).to.throw(TypeError);
		expect(() => this.db.aggregate('d', { step: length(NaN) })).to.throw(TypeError);
		expect(() => this.db.aggregate('e', { step: length(Infinity) })).to.throw(TypeError);
		expect(() => this.db.aggregate('f', { step: length(2.000000001) })).to.throw(TypeError);
		expect(() => this.db.aggregate('g', { step: length(-0.000000001) })).to.throw(TypeError);
		expect(() => this.db.aggregate('h', { step: length(-2) })).to.throw(TypeError);
		expect(() => this.db.aggregate('i', { step: length(100.000000001) })).to.throw(TypeError);
		expect(() => this.db.aggregate('j', { step: length(102) })).to.throw(RangeError);
		expect(() => this.db.aggregate('aa', { step: () => {}, inverse: length(undefined) })).to.throw(TypeError);
		expect(() => this.db.aggregate('bb', { step: () => {}, inverse: length(null) })).to.throw(TypeError);
		expect(() => this.db.aggregate('cc', { step: () => {}, inverse: length('2') })).to.throw(TypeError);
		expect(() => this.db.aggregate('dd', { step: () => {}, inverse: length(NaN) })).to.throw(TypeError);
		expect(() => this.db.aggregate('ee', { step: () => {}, inverse: length(Infinity) })).to.throw(TypeError);
		expect(() => this.db.aggregate('ff', { step: () => {}, inverse: length(2.000000001) })).to.throw(TypeError);
		expect(() => this.db.aggregate('gg', { step: () => {}, inverse: length(-0.000000001) })).to.throw(TypeError);
		expect(() => this.db.aggregate('hh', { step: () => {}, inverse: length(-2) })).to.throw(TypeError);
		expect(() => this.db.aggregate('ii', { step: () => {}, inverse: length(100.000000001) })).to.throw(TypeError);
		expect(() => this.db.aggregate('jj', { step: () => {}, inverse: length(102) })).to.throw(RangeError);
	});
	it('should register an aggregate function and return the database object', function () {
		const length = x => Object.defineProperty(() => {}, 'length', { value: x });
		expect(this.db.aggregate('a', { step: () => {} })).to.equal(this.db);
		expect(this.db.aggregate('b', { step: function x() {} })).to.equal(this.db);
		expect(this.db.aggregate('c', { step: length(1) })).to.equal(this.db);
		expect(this.db.aggregate('d', { step: length(101) })).to.equal(this.db);
	});
	it('should enable the registered aggregate function to be executed from SQL', function () {
		// numbers
		this.db.aggregate('a', { step: (ctx, a, b) => a * b + ctx });
		expect(this.get('a(_, ?) FROM ints', 2)).to.equal(150);

		// strings
		this.db.aggregate('b', { step: (ctx, a, b) => a + b + ctx });
		expect(this.get('b(_, ?) FROM texts', '!')).to.equal('g!f!e!d!c!b!a!null');

		// starting value is null
		this.db.aggregate('c', { step: (ctx, x) => null });
		this.db.aggregate('d', { step: (ctx, x) => ctx });
		this.db.aggregate('e', { step: (ctx, x) => {} });
		expect(this.get('c(_) FROM ints')).to.equal(null);
		expect(this.get('d(_) FROM ints')).to.equal(null);
		expect(this.get('e(_) FROM ints')).to.equal(null);

		// buffers
		this.db.aggregate('f', { step: (ctx, x) => x });
		const input = Buffer.alloc(8).fill(0xdd);
		const output = this.get('f(?)', input);
		expect(input).to.not.equal(output);
		expect(input.equals(output)).to.be.true;
		expect(output.equals(Buffer.alloc(8).fill(0xdd))).to.be.true;

		// zero arguments
		this.db.aggregate('g', { step: (ctx) => 'z' + ctx });
		this.db.aggregate('h', { step: (ctx) => 12 });
		this.db.aggregate('i', { step: () => 44 });
		expect(this.get('g()')).to.equal('znull');
		expect(this.get('h()')).to.equal(12);
		expect(this.get('i()')).to.equal(44);
		expect(this.get('g() FROM empty')).to.equal(null);
		expect(this.get('h() FROM empty')).to.equal(null);
		expect(this.get('i() FROM empty')).to.equal(null);
		expect(this.get('g() FROM ints')).to.equal('zzzzzzznull');
		expect(this.get('h() FROM ints')).to.equal(12);
		expect(this.get('i() FROM ints')).to.equal(44);
		expect(this.get('g(*) FROM ints')).to.equal('zzzzzzznull');
		expect(this.get('h(*) FROM ints')).to.equal(12);
		expect(this.get('i(*) FROM ints')).to.equal(44);
	});
	it('should use a strict number of arguments by default', function () {
		this.db.aggregate('agg', { step: (ctx, a, b) => {} });
		expect(() => this.get('agg()')).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(() => this.get('agg(?)', 4)).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(() => this.get('agg(?, ?, ?)', 4, 8, 3)).to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		this.get('agg(?, ?)', 4, 8);
	});
	it('should accept a "varargs" option', function () {
		const step = (ctx, ...args) => args.reduce((a, b) => a * b, 1) + ctx;
		Object.defineProperty(step, 'length', { value: '-2' });
		this.db.aggregate('agg', { varargs: true, step });
		expect(this.get('agg()')).to.equal(1);
		expect(this.get('agg(?)', 7)).to.equal(7);
		expect(this.get('agg(?, ?)', 4, 8)).to.equal(32);
		expect(this.get('agg(?, ?, ?, ?, ?, ?)', 2, 3, 4, 5, 6, 7)).to.equal(5040);
	});
	it('should accept an optional start value', function () {
		this.db.aggregate('a', { start: 10000, step: (ctx, a, b) => a * b + ++ctx });
		expect(this.get('a(_, ?) FROM ints', 2)).to.equal(10157);
		expect(this.get('a(_, ?) FROM ints', 2)).to.equal(10157);

		this.db.aggregate('b', { start: { foo: 1000 }, step: (ctx, a, b) => a * b + (ctx.foo ? ++ctx.foo : ++ctx) });
		expect(this.get('b(_, ?) FROM ints', 2)).to.equal(1157);
		expect(this.get('b(_, ?) FROM ints', 2)).to.equal(1158);

		let ranOnce = false;
		this.db.aggregate('c', { start: undefined, step: (ctx, a, b) => {
			if (ranOnce) expect(ctx).to.be.NaN;
			else expect(ctx).to.be.undefined;
			ranOnce = true;
			return a * b + ++ctx;
		} });
		expect(this.get('c(_, ?) FROM ints', 2)).to.equal(null);
		expect(ranOnce).to.be.true;
		ranOnce = false;
		expect(this.get('c(_, ?) FROM ints', 2)).to.equal(null);
		expect(ranOnce).to.be.true;
	});
	it('should accept an optional start() function', function () {
		let start = 10000;

		this.db.aggregate('a', { start: () => start++, step: (ctx, a, b) => a * b + ctx });
		expect(this.get('a(_, ?) FROM ints', 2)).to.equal(10150);
		expect(this.get('a(_, ?) FROM ints', 2)).to.equal(10151);
		expect(this.get('a(_, ?) FROM ints', 2)).to.equal(10152);

		this.db.aggregate('b', { start: () => ({ foo: start-- }), step: (ctx, a, b) => a * b + (ctx.foo || ctx) });
		expect(this.get('b(_, ?) FROM ints', 2)).to.equal(10153);
		expect(this.get('b(_, ?) FROM ints', 2)).to.equal(10152);
		expect(this.get('b(_, ?) FROM ints', 2)).to.equal(10151);

		let ranOnce = false;
		this.db.aggregate('c', { start: () => undefined, step: (ctx, a, b) => {
			if (ranOnce) expect(ctx).to.be.NaN;
			else expect(ctx).to.be.undefined;
			ranOnce = true;
			return a * b + ++ctx;
		} });
		expect(this.get('c(_, ?) FROM ints', 2)).to.equal(null);
		expect(ranOnce).to.be.true;
		ranOnce = false;
		expect(this.get('c(_, ?) FROM ints', 2)).to.equal(null);
		expect(ranOnce).to.be.true;
	});
	it('should not change the aggregate value when step() returns undefined', function () {
		this.db.aggregate('a', { start: 10000, step: (ctx, a, b) => a === 11 ? undefined : a * b + ctx });
		expect(this.get('a(_, ?) FROM ints', 2)).to.equal(10128);
		this.db.aggregate('b', { start: () => 1000, step: (ctx, a, b) => {} });
		expect(this.get('b(_, ?) FROM ints', 2)).to.equal(1000);
		this.db.aggregate('c', { start: () => 1000, step: (ctx, a, b) => null });
		expect(this.get('c(_, ?) FROM ints', 2)).to.equal(null);
	});
	it('should accept a result() transformer function', function () {
		this.db.aggregate('a', {
			start: 10000,
			step: (ctx, a, b) => a * b + ctx,
			result: ctx => ctx / 2,
		});
		expect(this.get('a(_, ?) FROM ints', 2)).to.equal(5075);
		this.db.aggregate('b', {
			start: () => ({ foo: 1000 }),
			step: (ctx, a, b) => { ctx.foo += a * b; },
			result: ctx => ctx.foo,
		});
		expect(this.get('b(_, ?) FROM ints', 2)).to.equal(1150);
		expect(this.get('b(_, ?) FROM ints', 2)).to.equal(1150); // should play well when ran multiple times
		this.db.aggregate('c', {
			start: () => ({ foo: 1000 }),
			step: (ctx, a, b) => { ctx.foo += 1; },
			result: ctx => ctx.foo,
		});
		expect(this.get('c(_, ?) FROM empty', 2)).to.equal(1000);
	});
	it('should interpret undefined as null within a result() function', function () {
		this.db.aggregate('agg', {
			start: 10000,
			step: (ctx, a, b) => a * b + ctx,
			result: () => {},
		});
		expect(this.get('agg(_, ?) FROM ints', 2)).to.equal(null);
	});
	it('should accept an inverse() function to support aggregate window functions', function () {
		this.db.aggregate('agg', {
			start: () => 10000,
			step: (ctx, a, b) => a * b + ctx,
		});
		expect(() => this.all('agg(_, ?) OVER win FROM ints', 2))
			.to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		this.db.aggregate('wn', {
			start: () => 10000,
			step: (ctx, a, b) => a * b + ctx,
			inverse: (ctx, a, b) => ctx - a * b,
		});
		expect(this.all('wn(_, ?) OVER win FROM ints', 2))
			.to.deep.equal([10016, 10030, 10046, 10062, 10082, 10098, 10072]);
	});
	it('should not change the aggregate value when inverse() returns undefined', function () {
		this.db.aggregate('a', {
			start: () => 10000,
			step: (ctx, a, b) => a * b + ctx,
			inverse: (ctx, a, b) => a === 11 ? undefined : ctx - a * b,
		});
		expect(this.all('a(_, ?) OVER win FROM ints', 2))
			.to.deep.equal([10016, 10030, 10046, 10062, 10082, 10120, 10094]);
		this.db.aggregate('b', {
			start: () => 10000,
			step: (ctx, a, b) => ctx ? a * b + ctx : null,
			inverse: (ctx, a, b) => null,
		});
		expect(this.all('b(_, ?) OVER win FROM ints', 2))
			.to.deep.equal([10016, 10030, null, null, null, null, null]);
	});
	it('should potentially call result() multiple times for window functions', function () {
		let startCount = 0;
		let stepCount = 0;
		let inverseCount = 0;
		let resultCount = 0;
		this.db.aggregate('wn', {
			start: () => {
				startCount += 1;
				return { foo: 1000, results: 0 };
			},
			step: (ctx, a, b) => {
				stepCount += 1;
				ctx.foo += a * b;
			},
			inverse: (ctx, a, b) => {
				inverseCount += 1;
				ctx.foo -= a * b;
			},
			result: (ctx) => {
				resultCount += 1;
				return ctx.foo + ctx.results++ * 10000;
			},
		});
		expect(this.all('wn(_, ?) OVER win FROM ints', 2))
			.to.deep.equal([1016, 11030, 21046, 31062, 41082, 51098, 61072]);
		expect(startCount).to.equal(1);
		expect(stepCount).to.equal(7);
		expect(inverseCount).to.equal(5);
		expect(resultCount).to.equal(7);
		expect(this.all('wn(_, ?) OVER win FROM ints', 2)) // should play well when ran multiple times
			.to.deep.equal([1016, 11030, 21046, 31062, 41082, 51098, 61072]);
		expect(startCount).to.equal(2);
		expect(stepCount).to.equal(14);
		expect(inverseCount).to.equal(10);
		expect(resultCount).to.equal(14);
		expect(this.all('wn(_, ?) OVER win FROM empty', 2))
			.to.deep.equal([]);
		expect(startCount).to.equal(2);
		expect(stepCount).to.equal(14);
		expect(inverseCount).to.equal(10);
		expect(resultCount).to.equal(14);
	});
	it('should infer argument count from the greater of step() and inverse()', function () {
		this.db.aggregate('a', {
			start: () => 10000,
			step: (ctx, a) => a + ctx,
			inverse: (ctx, a, b) => ctx - a,
		});
		expect(this.all('a(_, ?) OVER win FROM ints', 2))
			.to.deep.equal([10008, 10015, 10023, 10031, 10041, 10049, 10036]);
		expect(() => this.all('a(_) OVER win FROM ints'))
			.to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		this.db.aggregate('b', {
			start: () => 10000,
			step: (ctx, a, b) => a + ctx,
			inverse: (ctx, a) => ctx - a,
		});
		expect(this.all('b(_, ?) OVER win FROM ints', 2))
			.to.deep.equal([10008, 10015, 10023, 10031, 10041, 10049, 10036]);
		expect(() => this.all('b(_) OVER win FROM ints'))
			.to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		this.db.aggregate('c', {
			start: (a, b, c, d, e) => 10000,
			step: () => {},
			inverse: (ctx, a) => --ctx,
			result: (ctx, a, b, c, d, e) => ctx,
		});
		expect(this.all('c(_) OVER win FROM ints'))
			.to.deep.equal([10000, 10000, 9999, 9998, 9997, 9996, 9995]);
		expect(() => this.all('c() OVER win FROM ints'))
			.to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(() => this.all('c(*) OVER win FROM ints'))
			.to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
		expect(() => this.all('c(_, ?) OVER win FROM ints', 2))
			.to.throw(Database.SqliteError).with.property('code', 'SQLITE_ERROR');
	});
	it('should throw an exception if the database is busy', function () {
		let ranOnce = false;
		for (const x of this.db.prepare('SELECT 2').pluck().iterate()) {
			expect(x).to.equal(2);
			ranOnce = true;
			expect(() => this.db.aggregate('a', { step: () => {} })).to.throw(TypeError);
		}
		expect(ranOnce).to.be.true;
		this.db.aggregate('b', { step: () => {} });
	});
	it('should cause the database to become busy when executing the aggregate', function () {
		let checkCount = 0;
		const expectBusy = () => {
			expect(() => this.db.exec('SELECT a()')).to.throw(TypeError);
			expect(() => this.db.prepare('SELECT 555')).to.throw(TypeError);
			expect(() => this.db.pragma('cache_size')).to.throw(TypeError);
			expect(() => this.db.function('x', () => {})).to.throw(TypeError);
			expect(() => this.db.aggregate('y', { step: () => {} })).to.throw(TypeError);
			checkCount += 1;
		};
		this.db.aggregate('a', { step: () => {} });
		this.db.aggregate('b', { start: expectBusy, step: expectBusy, inverse: expectBusy, result: expectBusy });

		expect(this.all('b(*) OVER win FROM ints')).to.deep.equal([null, null, null, null, null, null, null]);
		expect(checkCount).to.equal(20);
		checkCount = 0;

		expect(this.db.exec('SELECT b(*) OVER win FROM ints WINDOW win AS (ORDER BY rowid ROWS BETWEEN 1 PRECEDING AND 1 FOLLOWING) ORDER BY rowid')).to.equal(this.db);
		expect(checkCount).to.equal(20);

		this.db.exec('SELECT a()');
		this.db.prepare('SELECT 555');
		this.db.pragma('cache_size');
		this.db.function('xx', () => {});
		this.db.aggregate('yy', { step: () => {} });
	});
	it('should cause the aggregate to throw when returning an invalid value', function () {
		this.db.aggregate('a', {
			start: () => ({}),
			step: () => ({}),
			inverse: () => ({}),
			result: () => 42,
		});
		this.db.aggregate('b', {
			start: () => 42,
			step: () => 42,
			inverse: () => 42,
			result: () => ({}),
		});
		this.db.aggregate('c', {
			step: () => {},
			result: () => 42,
		});
		this.db.aggregate('d', {
			step: () => {},
			result: () => ({}),
		});
		expect(this.all('a(*) OVER win FROM ints')).to.deep.equal([42, 42, 42, 42, 42, 42, 42]);
		expect(() => this.all('b(*) OVER win FROM ints')).to.throw(TypeError);
		expect(this.get('c(*) FROM ints')).to.equal(42);
		expect(this.get('c(*) FROM empty')).to.equal(42);
		expect(() => this.get('d(*) FROM ints')).to.throw(TypeError);
		expect(() => this.get('d(*) FROM empty')).to.throw(TypeError);
	});
	it('should close a statement iterator that caused its aggregate to throw', function () {
		this.db.prepare('CREATE TABLE iterable (value INTEGER)').run();
		this.db.prepare('INSERT INTO iterable WITH RECURSIVE temp(x) AS (SELECT 1 UNION ALL SELECT x * 2 FROM temp LIMIT 10) SELECT * FROM temp').run();

		let i = 0;
		const err = new Error('foo');
		this.db.aggregate('wn', {
			step: (ctx, x) => { if (++i >= 5) throw err; return x; },
			inverse: () => {},
		});
		const iterator = this.db.prepare('SELECT wn(value) OVER (ROWS CURRENT ROW) FROM iterable').pluck().iterate();

		let total = 0;
		expect(() => {
			for (const value of iterator) {
				total += value;
				expect(() => this.db.exec('SELECT wn(value) OVER (ROWS CURRENT ROW) FROM iterable LIMIT 4')).to.throw(TypeError);
			}
		}).to.throw(err);

		expect(total).to.equal(1 + 2 + 4 + 8);
		expect(iterator.next()).to.deep.equal({ value: undefined, done: true });
		expect(total).to.equal(1 + 2 + 4 + 8);

		i = 0;
		this.db.exec('SELECT wn(value) OVER (ROWS CURRENT ROW) FROM iterable LIMIT 4');
		expect(i).to.equal(4);
	});
	it('should be able to register multiple aggregates with the same name', function () {
		this.db.aggregate('agg', { step: (ctx) => 0 });
		this.db.aggregate('agg', { step: (ctx, a) => 1 });
		this.db.aggregate('agg', { step: (ctx, a, b) => 2 });
		this.db.aggregate('agg', { step: (ctx, a, b, c) => 3, inverse: () => {} });
		this.db.aggregate('agg', { step: (ctx, a, b, c, d) => 4 });
		expect(this.get('agg()')).to.equal(0);
		expect(this.get('agg(555)')).to.equal(1);
		expect(this.get('agg(555, 555)')).to.equal(2);
		expect(this.get('agg(555, 555, 555)')).to.equal(3);
		expect(this.get('agg(555, 555, 555, 555)')).to.equal(4);
		this.db.aggregate('agg', { step: (ctx, a, b) => 'foo', inverse: () => {} });
		this.db.aggregate('agg', { step: (ctx, a, b, c) => 'bar' });
		expect(this.get('agg()')).to.equal(0);
		expect(this.get('agg(555)')).to.equal(1);
		expect(this.get('agg(555, 555)')).to.equal('foo');
		expect(this.get('agg(555, 555, 555)')).to.equal('bar');
		expect(this.get('agg(555, 555, 555, 555)')).to.equal(4);
	});
	it('should not be able to affect bound buffers mid-query', function () {
		const input = Buffer.alloc(1024 * 8).fill(0xbb);
		let startCalled = false;
		let stepCalled = false;
		this.db.aggregate('agg', {
			start: () => {
				startCalled = true;
				input[0] = 2;
			},
			step: () => {
				stepCalled = true;
				input[0] = 2;
			},
		});
		const output = this.get('?, agg(*) FROM ints', input);
		expect(startCalled).to.be.true;
		expect(stepCalled).to.be.true;
		expect(output.equals(Buffer.alloc(1024 * 8).fill(0xbb))).to.be.true;
	});
	describe('should propagate exceptions', function () {
		const exceptions = [new TypeError('foobar'), new Error('baz'), { yup: 'ok' }, 'foobarbazqux', '', null, 123.4];
		const expectError = (exception, fn) => {
			try { fn(); } catch (ex) {
				expect(ex).to.equal(exception);
				return;
			}
			throw new TypeError('Expected aggregate to throw an exception');
		};

		specify('thrown in the start() function', function () {
			exceptions.forEach((exception, index) => {
				const calls = [];
				this.db.aggregate(`wn${index}`, {
					start: () => { calls.push('a'); throw exception; },
					step: () => { calls.push('b'); },
					inverse: () => { calls.push('c'); },
					result: () => { calls.push('d'); },
				});
				expectError(exception, () => this.get(`wn${index}() FROM empty`));
				expect(calls.splice(0)).to.deep.equal(['a']);
				expectError(exception, () => this.get(`wn${index}() FROM ints`));
				expect(calls.splice(0)).to.deep.equal(['a']);
				expectError(exception, () => this.all(`wn${index}() OVER win FROM ints`));
				expect(calls.splice(0)).to.deep.equal(['a']);
			});
		});
		specify('thrown in the step() function', function () {
			exceptions.forEach((exception, index) => {
				const calls = [];
				this.db.aggregate(`wn${index}`, {
					start: () => { calls.push('a'); },
					step: () => { calls.push('b'); throw exception; },
					inverse: () => { calls.push('c'); },
					result: () => { calls.push('d'); },
				});
				expect(this.get(`wn${index}() FROM empty`)).to.equal(null);
				expect(calls.splice(0)).to.deep.equal(['a', 'd']);
				expectError(exception, () => this.get(`wn${index}() FROM ints`));
				expect(calls.splice(0)).to.deep.equal(['a', 'b']);
				expectError(exception, () => this.all(`wn${index}() OVER win FROM ints`));
				expect(calls.splice(0)).to.deep.equal(['a', 'b']);
			});
		});
		specify('thrown in the inverse() function', function () {
			exceptions.forEach((exception, index) => {
				const calls = [];
				this.db.aggregate(`wn${index}`, {
					start: () => { calls.push('a'); },
					step: () => { calls.push('b'); },
					inverse: () => { calls.push('c'); throw exception; },
					result: () => { calls.push('d'); },
				});
				expect(this.get(`wn${index}() FROM empty`)).to.equal(null);
				expect(calls.splice(0)).to.deep.equal(['a', 'd']);
				expect(this.get(`wn${index}() FROM ints`)).to.equal(null);
				expect(calls.splice(0)).to.deep.equal(['a', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'd']);
				expectError(exception, () => this.all(`wn${index}() OVER win FROM ints`));
				expect(calls.length).to.be.above(2);
				expect(calls.indexOf('c')).to.equal(calls.length - 1);
			});
		});
		specify('thrown in the result() function', function () {
			exceptions.forEach((exception, index) => {
				const calls = [];
				this.db.aggregate(`wn${index}`, {
					start: () => { calls.push('a'); },
					step: () => { calls.push('b'); },
					inverse: () => { calls.push('c'); },
					result: () => { calls.push('d'); throw exception; },
				});
				expectError(exception, () => this.get(`wn${index}() FROM empty`));
				expect(calls.splice(0)).to.deep.equal(['a', 'd']);
				expectError(exception, () => this.get(`wn${index}() FROM ints`));
				expect(calls.splice(0)).to.deep.equal(['a', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'd']);
				expectError(exception, () => this.all(`wn${index}() OVER win FROM ints`));
				expect(calls.splice(0)).to.deep.equal(['a', 'b', 'b', 'd']);
			});
		});
		specify('thrown due to returning an invalid value', function () {
			const calls = [];
			this.db.aggregate('wn', {
				start: () => { calls.push('a'); },
				step: () => { calls.push('b'); },
				inverse: () => { calls.push('c'); },
				result: () => { calls.push('d'); return {}; },
			});
			expect(() => this.get('wn() FROM empty')).to.throw(TypeError);
			expect(calls.splice(0)).to.deep.equal(['a', 'd']);
			expect(() => this.get('wn() FROM ints')).to.throw(TypeError);;
			expect(calls.splice(0)).to.deep.equal(['a', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'd']);
			expect(() => this.all('wn() OVER win FROM ints')).to.throw(TypeError);;
			expect(calls.splice(0)).to.deep.equal(['a', 'b', 'b', 'd']);
		});
	});
	describe('should not affect external environment', function () {
		specify('busy state', function () {
			this.db.aggregate('agg', { step: (ctx, x) => {
				expect(() => this.db.exec('SELECT 555')).to.throw(TypeError);
				return x * 2 + ctx;
			} });
			let ranOnce = false;
			for (const x of this.db.prepare('SELECT agg(555)').pluck().iterate()) {
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
			this.db.aggregate('agg', { step: () => { throw err; } });

			expect(() => this.db.prepare('SELECT agg()').get()).to.throw(err);
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
