'use strict';
const fs = require('fs');
const path = require('path');
const util = require('./util');
const SqliteError = require('./sqlite-error');
const wrappers = require('./methods/wrappers');

/**
 * A database connection.
 *
 * Declared at module scope rather than inside a factory so that the type can be
 * named. Each package entrypoint exports its own constructor, produced by
 * lib/with-binding.js, which supplies the native addon loader for that
 * entrypoint. Constructing this base directly is not supported; it has no
 * addon loader of its own.
 *
 * @param {string|Buffer} [filenameGiven] Path to the database file; ':memory:'
 *   for an in-memory database, an empty string or omitted for a temporary one,
 *   or a Buffer previously returned by `.serialize()`.
 * @param {object} [options] Connection options: `readonly`, `fileMustExist`,
 *   `timeout` in milliseconds, `verbose`, and `nativeBinding`.
 * @returns {Database} The new connection. Returned explicitly so that invoking
 *   an entrypoint constructor without `new` behaves identically to using `new`.
 *
 * @throws {TypeError} If an argument or option is invalid, if the containing
 *   directory does not exist, or if this base is constructed without a bound
 *   addon loader.
 * @throws {RangeError} If `timeout` exceeds 2147483647.
 *
 * @example
 * const Database = require('better-sqlite3');
 * const db = new Database('foobar.db', { verbose: console.log });
 * db.prepare('SELECT 1 AS value').get(); // => { value: 1 }
 *
 * @see lib/with-binding.js
 */
function Database(filenameGiven, options) {
	if (new.target == null) {
		return new Database(filenameGiven, options);
	}

	// Each entrypoint's constructor carries its own addon loader. Reading it
	// from new.target rather than a closure is what allows this function to be
	// declared at module scope, and it resolves through the static prototype
	// chain so that subclasses of an entrypoint constructor work unchanged.
	const bound = new.target[util.binding];
	if (bound == null) {
		throw new TypeError('Database cannot be constructed directly; require a better-sqlite3 entrypoint instead');
	}
	const { getAddon, allowNativeBinding } = bound;

	// Apply defaults
	let buffer;
	if (Buffer.isBuffer(filenameGiven)) {
		buffer = filenameGiven;
		filenameGiven = ':memory:';
	}
	if (filenameGiven == null) filenameGiven = '';
	if (options == null) options = {};

	// Validate arguments
	if (typeof filenameGiven !== 'string') throw new TypeError('Expected first argument to be a string');
	if (typeof options !== 'object') throw new TypeError('Expected second argument to be an options object');
	if ('readOnly' in options) throw new TypeError('Misspelled option "readOnly" should be "readonly"');
	if ('memory' in options) throw new TypeError('Option "memory" was removed in v7.0.0 (use ":memory:" filename instead)');

	// Interpret options
	const filename = filenameGiven.trim();
	const anonymous = filename === '' || filename === ':memory:';
	const readonly = util.getBooleanOption(options, 'readonly');
	const fileMustExist = util.getBooleanOption(options, 'fileMustExist');
	const timeout = 'timeout' in options ? options.timeout : 5000;
	const verbose = 'verbose' in options ? options.verbose : null;
	const nativeBinding = 'nativeBinding' in options ? options.nativeBinding : null;

	// Validate interpreted options
	if (readonly && anonymous && !buffer) throw new TypeError('In-memory/temporary databases cannot be readonly');
	if (!Number.isInteger(timeout) || timeout < 0) throw new TypeError('Expected the "timeout" option to be a positive integer');
	if (timeout > 0x7fffffff) throw new RangeError('Option "timeout" cannot be greater than 2147483647');
	if (verbose != null && typeof verbose !== 'function') throw new TypeError('Expected the "verbose" option to be a function');
	if (!allowNativeBinding && 'nativeBinding' in options) throw new TypeError('The "nativeBinding" option is only supported by the default better-sqlite3 entrypoint');
	if (allowNativeBinding && nativeBinding != null && typeof nativeBinding !== 'string' && typeof nativeBinding !== 'object') throw new TypeError('Expected the "nativeBinding" option to be a string or addon object');

	// Load the native addon
	const addon = getAddon(nativeBinding);
	if (!addon.isInitialized) {
		addon.initialize(SqliteError, arrayFactory, arrayAppender, rowFactory, recordFactory);
		addon.isInitialized = true;
	}

	// Make sure the specified directory exists
	if (!anonymous && !filename.startsWith('file:') && !fs.existsSync(path.dirname(filename))) {
		throw new TypeError('Cannot open database because the directory does not exist');
	}

	Object.defineProperties(this, {
		[util.cppdb]: { value: new addon.Database(filename, filenameGiven, anonymous, readonly, fileMustExist, timeout, verbose || null, buffer || null) },
		...wrappers.getters,
	});
}

Database.prototype.prepare = wrappers.prepare;
Database.prototype.transaction = require('./methods/transaction');
Database.prototype.pragma = require('./methods/pragma');
Database.prototype.explain = require('./methods/explain');
Database.prototype.backup = require('./methods/backup');
Database.prototype.serialize = require('./methods/serialize');
Database.prototype.function = require('./methods/function');
Database.prototype.aggregate = require('./methods/aggregate');
Database.prototype.table = require('./methods/table');
Database.prototype.loadExtension = wrappers.loadExtension;
Database.prototype.exec = wrappers.exec;
Database.prototype.close = wrappers.close;
Database.prototype.defaultSafeIntegers = wrappers.defaultSafeIntegers;
Database.prototype.unsafeMode = wrappers.unsafeMode;
Database.prototype[util.inspect] = require('./methods/inspect');

module.exports = Database;

function arrayFactory(...values) {
	return values;
}

function arrayAppender(array, ...values) {
	const offset = array.length;
	for (let i = 0; i < values.length; ++i) {
		array[offset + i] = values[i];
	}
}

function rowFactory(...keys) {
	if (!keys.includes('__proto__')) {
		const parameters = keys.map((_, index) => `v${index}`).join(',');
		const properties = keys.map((key, index) => `${JSON.stringify(key)}:v${index}`).join(',');
		return Function(`return (${parameters}) => ({${properties}})`)();
	}
	return (...values) => {
		const row = {};
		for (let i = 0; i < keys.length; ++i) row[keys[i]] = values[i];
		return row;
	};
}

function recordFactory(value) {
	return { value, done: false };
}
