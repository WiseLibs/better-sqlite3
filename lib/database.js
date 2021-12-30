'use strict';
const fs = require('fs');
const path = require('path');
const util = require('./util');

const {
	Constants,
	Database: CPPDatabase,
	setErrorConstructor,
} = require('bindings')('better_sqlite3.node');
const { OPEN_URI } = Constants;

function Database(filenameGiven, options) {
	if (new.target == null) {
		return new Database(filenameGiven, options);
	}

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
	const flags = 'flags' in options ? options.flags : 0;

	// Validate interpreted options
	if (readonly && anonymous && !buffer) throw new TypeError('In-memory/temporary databases cannot be readonly');
	if (!Number.isInteger(timeout) || timeout < 0) throw new TypeError('Expected the "timeout" option to be a positive integer');
	if (timeout > 0x7fffffff) throw new RangeError('Option "timeout" cannot be greater than 2147483647');
	if (verbose != null && typeof verbose !== 'function') throw new TypeError('Expected the "verbose" option to be a function');
	if (!Number.isInteger(flags)) throw new TypeError('Expected the "flags" option to be an integer');

	// Make sure the specified directory exists
	if (!anonymous && (flags & OPEN_URI) !== OPEN_URI && !fs.existsSync(path.dirname(filename))) {
		throw new TypeError('Cannot open database because the directory does not exist');
	}

	Object.defineProperties(this, {
		[util.cppdb]: { value: new CPPDatabase(filename, filenameGiven, anonymous, readonly, fileMustExist, timeout, verbose || null, buffer || null, flags) },
		...wrappers.getters,
	});
}

const wrappers = require('./methods/wrappers');
Database.prototype.prepare = wrappers.prepare;
Database.prototype.transaction = require('./methods/transaction');
Database.prototype.pragma = require('./methods/pragma');
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

Database.Constants = Constants;

module.exports = Database;
setErrorConstructor(require('./sqlite-error'));
