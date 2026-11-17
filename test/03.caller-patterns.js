'use strict';
const path = require('path');
const util = require('../lib/util');

// These tests characterize the *structural* contract that callers depend on:
// how a Database is constructed, what its prototype and instance surfaces look
// like, how it behaves under subclassing and prototype patching, and how the
// nine entrypoints relate to one another.
//
// Query behavior is covered thoroughly elsewhere. What is not covered elsewhere
// is the construction machinery itself, which is exactly what an internal
// refactor of lib/database.js would put at risk. Every assertion here should
// survive any such refactor; if one of them has to change, that change is a
// breaking change to callers and belongs in release notes.
//
// The native addon is deliberately not required. lib/database.js accepts an
// addon object via the `nativeBinding` option, so the JS construction layer can
// be exercised in isolation. That keeps these tests fast, platform-independent,
// and focused on the layer being characterized.

const ENTRYPOINTS = [
	'linux-x64',
	'linux-arm64',
	'linuxmusl-x64',
	'linuxmusl-arm64',
	'darwin-x64',
	'darwin-arm64',
	'win32-x64',
	'win32-arm64',
];

/**
 * The set of methods every Database prototype is expected to expose.
 *
 * Locking this list down is the point: a refactor that silently drops or
 * renames a prototype member is a breaking change for callers, and a refactor
 * that moves a member from the prototype onto the instance changes what
 * `Object.keys()`, spread, and prototype patching see.
 */
const PROTOTYPE_METHODS = [
	'prepare',
	'transaction',
	'pragma',
	'explain',
	'backup',
	'serialize',
	'function',
	'aggregate',
	'table',
	'loadExtension',
	'exec',
	'close',
	'defaultSafeIntegers',
	'unsafeMode',
];

/**
 * The enumerable own accessors installed on every instance, in installation
 * order. Order matters because it is observable through `Object.keys()`.
 */
const INSTANCE_GETTERS = ['name', 'open', 'inTransaction', 'readonly', 'memory'];

/**
 * Builds a stand-in for the native addon, satisfying the contract that
 * lib/database.js expects of `better_sqlite3.node`.
 *
 * Only the surface touched during construction and simple delegation is
 * implemented; anything requiring real SQLite is out of scope here.
 *
 * @returns {object} An addon object suitable for the `nativeBinding` option.
 *
 * @example
 * const db = new Database(':memory:', { nativeBinding: fakeAddon() });
 * expect(db.open).to.be.true;
 */
function fakeAddon() {
	return {
		isInitialized: false,
		initializeCalls: 0,
		initialize(...args) {
			this.initializeCalls += 1;
			this.initializeArgs = args;
		},
		Database: class FakeNativeDatabase {
			constructor(...args) {
				this.constructorArgs = args;
				this.name = args[1];
				this.open = true;
				this.inTransaction = false;
				this.readonly = args[3];
				this.memory = args[2];
			}
			exec() {}
			close() { this.open = false; }
			prepare() { return {}; }
			loadExtension() {}
			defaultSafeIntegers() {}
			unsafeMode() {}
		},
	};
}

/**
 * Constructs a Database backed by a fake addon.
 *
 * @param {Function} Ctor The Database constructor under test.
 * @param {string} [filename] Database filename; defaults to an anonymous db.
 * @returns {object} A constructed Database instance.
 */
function build(Ctor, filename = ':memory:') {
	return new Ctor(filename, { nativeBinding: fakeAddon() });
}

describe('caller patterns', function () {
	const Database = require('../lib/index');

	describe('construction forms', function () {
		it('constructs with new', function () {
			const db = build(Database);
			expect(db).to.be.an.instanceof(Database);
		});

		it('constructs without new', function () {
			const db = Database(':memory:', { nativeBinding: fakeAddon() });
			expect(db).to.be.an.instanceof(Database);
		});

		it('produces identical shapes with and without new', function () {
			const withNew = build(Database);
			const withoutNew = Database(':memory:', { nativeBinding: fakeAddon() });
			expect(Object.getPrototypeOf(withNew)).to.equal(Object.getPrototypeOf(withoutNew));
			expect(Object.keys(withNew)).to.deep.equal(Object.keys(withoutNew));
		});

		it('exposes the constructor on instances', function () {
			expect(build(Database).constructor).to.equal(Database);
		});

		it('places instances directly on Database.prototype', function () {
			expect(Object.getPrototypeOf(build(Database))).to.equal(Database.prototype);
		});

		it('keeps the prototype chain exactly one link from Object.prototype', function () {
			// An extra link is observable, and puts one more hop on every
			// method lookup. If this ever has to change, it should be a
			// deliberate, reviewed decision rather than a silent side effect.
			let links = 0;
			let proto = Object.getPrototypeOf(build(Database));
			while (proto !== null && proto !== Object.prototype) {
				links += 1;
				proto = Object.getPrototypeOf(proto);
			}
			expect(links).to.equal(1);
		});

		it('constructs an anonymous temporary database from an empty filename', function () {
			// Documented behavior: an empty string means a temporary database.
			const db = build(Database, '');
			expect(db[util.cppdb].constructorArgs[2]).to.be.true; // anonymous
		});
	});

	describe('prototype surface', function () {
		it('exposes exactly the expected method names', function () {
			const actual = Object.getOwnPropertyNames(Database.prototype)
				.filter((key) => key !== 'constructor')
				.sort();
			expect(actual).to.deep.equal([...PROTOTYPE_METHODS].sort());
		});

		it('exposes every method as a function', function () {
			for (const method of PROTOTYPE_METHODS) {
				expect(Database.prototype[method], method).to.be.a('function');
			}
		});

		it('exposes the custom inspect symbol on the prototype', function () {
			expect(Database.prototype[util.inspect]).to.be.a('function');
		});

		it('keeps methods off the instance', function () {
			const db = build(Database);
			for (const method of PROTOTYPE_METHODS) {
				expect(Object.prototype.hasOwnProperty.call(db, method), method).to.be.false;
			}
		});

		it('reaches prototype methods through the instance', function () {
			const db = build(Database);
			for (const method of PROTOTYPE_METHODS) {
				expect(db[method], method).to.equal(Database.prototype[method]);
			}
		});

		it('keeps prototype methods non-enumerable in for..in over the prototype', function () {
			// Assigned via `Database.prototype.x = fn`, so these are enumerable
			// on the prototype but absent from Object.keys(instance).
			const db = build(Database);
			const inherited = [];
			for (const key in db) {
				if (!Object.prototype.hasOwnProperty.call(db, key)) inherited.push(key);
			}
			expect(inherited.sort()).to.deep.equal([...PROTOTYPE_METHODS].sort());
		});
	});

	describe('instance surface', function () {
		it('exposes exactly the expected enumerable own keys, in order', function () {
			expect(Object.keys(build(Database))).to.deep.equal(INSTANCE_GETTERS);
		});

		it('installs the getters as enumerable own accessors', function () {
			const db = build(Database);
			for (const key of INSTANCE_GETTERS) {
				const descriptor = Object.getOwnPropertyDescriptor(db, key);
				expect(descriptor, key).to.be.an('object');
				expect(descriptor.get, key).to.be.a('function');
				expect(descriptor.set, key).to.be.undefined;
				expect(descriptor.enumerable, key).to.be.true;
			}
		});

		it('survives object spread', function () {
			const spread = { ...build(Database) };
			expect(Object.keys(spread)).to.deep.equal(INSTANCE_GETTERS);
		});

		it('survives JSON round-tripping of enumerable state', function () {
			expect(Object.keys(JSON.parse(JSON.stringify(build(Database))))).to.deep.equal(INSTANCE_GETTERS);
		});

		it('hides the internal addon handle from enumeration', function () {
			const db = build(Database);
			const descriptor = Object.getOwnPropertyDescriptor(db, util.cppdb);
			expect(descriptor).to.be.an('object');
			expect(descriptor.enumerable).to.be.false;
			expect(Object.keys(db)).to.not.include(util.cppdb);
		});

		it('reports getter values through the addon', function () {
			const db = build(Database, ':memory:');
			expect(db.open).to.be.true;
			expect(db.readonly).to.be.false;
			expect(db.inTransaction).to.be.false;
		});
	});

	describe('subclassing', function () {
		it('supports class extends', function () {
			class Sub extends Database {}
			const db = build(Sub);
			expect(db).to.be.an.instanceof(Sub);
			expect(db).to.be.an.instanceof(Database);
		});

		it('exposes subclass methods', function () {
			class Sub extends Database {
				extra() { return 42; }
			}
			expect(build(Sub).extra()).to.equal(42);
		});

		it('inherits base methods into the subclass', function () {
			class Sub extends Database {}
			const db = build(Sub);
			for (const method of PROTOTYPE_METHODS) {
				expect(db[method], method).to.be.a('function');
			}
		});

		it('reports the subclass as the constructor', function () {
			class Sub extends Database {}
			expect(build(Sub).constructor).to.equal(Sub);
		});

		it('installs the instance getters on subclass instances', function () {
			class Sub extends Database {}
			expect(Object.keys(build(Sub))).to.deep.equal(INSTANCE_GETTERS);
		});

		it('honors an explicit new.target via Reflect.construct', function () {
			// This is the assertion that catches a constructor which ignores
			// new.target and hardcodes its own identity: subclass instances
			// would silently come back as base instances, with no error.
			class Sub extends Database {}
			const db = Reflect.construct(Database, [':memory:', { nativeBinding: fakeAddon() }], Sub);
			expect(db).to.be.an.instanceof(Sub);
			expect(Object.getPrototypeOf(db)).to.equal(Sub.prototype);
		});

		it('supports two independent subclasses simultaneously', function () {
			class A extends Database { which() { return 'a'; } }
			class B extends Database { which() { return 'b'; } }
			expect(build(A).which()).to.equal('a');
			expect(build(B).which()).to.equal('b');
			expect(build(A)).to.not.be.an.instanceof(B);
		});
	});

	describe('prototype patching', function () {
		afterEach(function () {
			delete Database.prototype.patched;
		});

		it('is visible on instances created after the patch', function () {
			Database.prototype.patched = function patched() { return 'ok'; };
			expect(build(Database).patched()).to.equal('ok');
		});

		it('is visible on instances created before the patch', function () {
			const db = build(Database);
			Database.prototype.patched = function patched() { return 'ok'; };
			expect(db.patched()).to.equal('ok');
		});

		it('allows wrapping an existing method', function () {
			const original = Database.prototype.exec;
			const calls = [];
			Database.prototype.exec = function exec(sql) {
				calls.push(sql);
				return original.call(this, sql);
			};
			try {
				build(Database).exec('SELECT 1');
				expect(calls).to.deep.equal(['SELECT 1']);
			} finally {
				Database.prototype.exec = original;
			}
		});
	});

	describe('statics', function () {
		it('exposes SqliteError', function () {
			expect(Database.SqliteError).to.equal(require('../lib/sqlite-error'));
		});

		it('exposes SqliteError as an Error subclass', function () {
			const err = new Database.SqliteError('boom', 'SQLITE_BUSY');
			expect(err).to.be.an.instanceof(Error);
			expect(err.code).to.equal('SQLITE_BUSY');
			expect(err.name).to.equal('SqliteError');
		});

		it('permits additional statics to be attached', function () {
			Database.marker = 1;
			try {
				expect(Database.marker).to.equal(1);
			} finally {
				delete Database.marker;
			}
		});
	});

	describe('entrypoint isolation', function () {
		// Requiring a statically-bound entrypoint does not load its prebuild:
		// the loader is a closure that only runs at construction time. So these
		// assertions hold on every platform, with or without prebuilds present.
		const loaded = new Map(ENTRYPOINTS.map((name) => [name, require(`../lib/${name}`)]));

		it('exports a distinct constructor per entrypoint', function () {
			const seen = new Set([Database, ...loaded.values()]);
			expect(seen.size).to.equal(ENTRYPOINTS.length + 1);
		});

		it('exports a distinct prototype per entrypoint', function () {
			const protos = new Set([Database.prototype, ...[...loaded.values()].map((C) => C.prototype)]);
			expect(protos.size).to.equal(ENTRYPOINTS.length + 1);
		});

		it('exposes the same prototype surface from every entrypoint', function () {
			const expected = [...PROTOTYPE_METHODS].sort();
			for (const [name, Ctor] of loaded) {
				const actual = Object.getOwnPropertyNames(Ctor.prototype)
					.filter((key) => key !== 'constructor')
					.sort();
				expect(actual, name).to.deep.equal(expected);
			}
		});

		it('exposes SqliteError from every entrypoint', function () {
			for (const [name, Ctor] of loaded) {
				expect(Ctor.SqliteError, name).to.equal(require('../lib/sqlite-error'));
			}
		});

		it('keeps prototype patches from leaking between entrypoints', function () {
			const [first, second] = [...loaded.values()];
			first.prototype.leaked = function leaked() { return true; };
			try {
				expect(second.prototype.leaked).to.be.undefined;
				expect(Database.prototype.leaked).to.be.undefined;
			} finally {
				delete first.prototype.leaked;
			}
		});

		it('rejects nativeBinding from statically-bound entrypoints', function () {
			for (const [name, Ctor] of loaded) {
				expect(() => new Ctor(':memory:', { nativeBinding: fakeAddon() }), name)
					.to.throw(TypeError, 'only supported by the default');
			}
		});
	});

	describe('argument validation', function () {
		// Callers depend on these messages and error types; they show up in
		// user code as caught exceptions and in issue reports verbatim.
		it('rejects a non-string filename', function () {
			expect(() => new Database(42)).to.throw(TypeError, 'Expected first argument to be a string');
		});

		it('rejects a misspelled readonly option', function () {
			expect(() => new Database(':memory:', { readOnly: true }))
				.to.throw(TypeError, 'Misspelled option "readOnly" should be "readonly"');
		});

		it('rejects the removed memory option', function () {
			expect(() => new Database(':memory:', { memory: true }))
				.to.throw(TypeError, 'Option "memory" was removed in v7.0.0');
		});

		it('rejects a readonly anonymous database', function () {
			expect(() => new Database(':memory:', { readonly: true }))
				.to.throw(TypeError, 'In-memory/temporary databases cannot be readonly');
		});

		it('rejects a non-integer timeout', function () {
			expect(() => new Database(':memory:', { timeout: 1.5, nativeBinding: fakeAddon() }))
				.to.throw(TypeError, 'Expected the "timeout" option to be a positive integer');
		});

		it('rejects an out-of-range timeout', function () {
			expect(() => new Database(':memory:', { timeout: 0x80000000, nativeBinding: fakeAddon() }))
				.to.throw(RangeError, 'cannot be greater than 2147483647');
		});

		it('rejects a non-function verbose option', function () {
			expect(() => new Database(':memory:', { verbose: 'nope', nativeBinding: fakeAddon() }))
				.to.throw(TypeError, 'Expected the "verbose" option to be a function');
		});

		it('rejects a non-string, non-object nativeBinding', function () {
			expect(() => new Database(':memory:', { nativeBinding: 42 }))
				.to.throw(TypeError, 'Expected the "nativeBinding" option to be a string or addon object');
		});

		it('rejects a missing directory', function () {
			const missing = path.join(__dirname, 'no-such-dir', 'x.db');
			expect(() => new Database(missing, { nativeBinding: fakeAddon() }))
				.to.throw(TypeError, 'Cannot open database because the directory does not exist');
		});
	});

	describe('addon contract', function () {
		it('initializes the addon exactly once per addon object', function () {
			const addon = fakeAddon();
			new Database(':memory:', { nativeBinding: addon });
			new Database(':memory:', { nativeBinding: addon });
			expect(addon.initializeCalls).to.equal(1);
			expect(addon.isInitialized).to.be.true;
		});

		it('passes the documented argument list to the native constructor', function () {
			const addon = fakeAddon();
			const db = new Database(':memory:', { nativeBinding: addon });
			const args = db[util.cppdb].constructorArgs;
			expect(args).to.have.lengthOf(8);
			expect(args[0]).to.equal(':memory:'); // filename (trimmed)
			expect(args[1]).to.equal(':memory:'); // filename as given
			expect(args[2]).to.be.true; // anonymous
			expect(args[3]).to.be.false; // readonly
			expect(args[4]).to.be.false; // fileMustExist
			expect(args[5]).to.equal(5000); // timeout default
			expect(args[6]).to.be.null; // verbose
			expect(args[7]).to.be.null; // buffer
		});

		it('accepts a Buffer as the first argument', function () {
			const addon = fakeAddon();
			const buffer = Buffer.from([1, 2, 3]);
			const db = new Database(buffer, { nativeBinding: addon });
			const args = db[util.cppdb].constructorArgs;
			expect(args[1]).to.equal(':memory:');
			expect(args[7]).to.equal(buffer);
		});

		it('hands the addon its five factory functions', function () {
			const addon = fakeAddon();
			new Database(':memory:', { nativeBinding: addon });
			expect(addon.initializeArgs).to.have.lengthOf(5);
			expect(addon.initializeArgs[0]).to.equal(require('../lib/sqlite-error'));
			for (const factory of addon.initializeArgs.slice(1)) {
				expect(factory).to.be.a('function');
			}
		});
	});
});
