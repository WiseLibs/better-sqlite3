'use strict';
const fs = require('fs');
const path = require('path');
const util = require('./util');

const {
	Database: CPPDatabase,
	setErrorConstructor,
} = require('bindings')('better_sqlite3.node');

function Database(filenameGiven, options) {
	if (filenameGiven == null) filenameGiven = '';
	if (options == null) options = {};
	if (typeof filenameGiven !== 'string') throw new TypeError('Expected first argument to be a string');
	if (typeof options !== 'object') throw new TypeError('Expected second argument to be an options object');
	if ('readOnly' in options) throw new TypeError('Misspelled option "readOnly" should be "readonly"');
	if ('memory' in options) throw new TypeError('Option "memory" was removed in v7.0.0 (use ":memory:" filename instead)');

	const filename = filenameGiven.trim();
	const anonymous = filename === '' || filename === ':memory:';
	const readonly = util.getBooleanOption(options, 'readonly');
	const fileMustExist = util.getBooleanOption(options, 'fileMustExist');
	const timeout = 'timeout' in options ? options.timeout : 5000;
	const verbose = 'verbose' in options ? options.verbose : null;

	if (readonly && anonymous) throw new TypeError('In-memory/temporary databases cannot be readonly');
	if (!Number.isInteger(timeout) || timeout < 0) throw new TypeError('Expected the "timeout" option to be a positive integer');
	if (timeout > 0x7fffffff) throw new RangeError('Option "timeout" cannot be greater than 2147483647');
	if (verbose != null && typeof verbose !== 'function') throw new TypeError('Expected the "verbose" option to be a function');

	if (!anonymous && !fs.existsSync(path.dirname(filename))) {
		throw new TypeError('Cannot open database because the directory does not exist');
	}
	return new CPPDatabase(filename, filenameGiven, anonymous, readonly, fileMustExist, timeout, verbose || null);
}

setErrorConstructor(require('./sqlite-error'));
util.wrap(CPPDatabase, 'pragma', require('./pragma'));
util.wrap(CPPDatabase, 'function', require('./function'));
util.wrap(CPPDatabase, 'aggregate', require('./aggregate'));
util.wrap(CPPDatabase, 'backup', require('./backup'));
CPPDatabase.prototype.transaction = require('./transaction');
CPPDatabase.prototype.constructor = Database;
Database.prototype = CPPDatabase.prototype;
module.exports = Database;
