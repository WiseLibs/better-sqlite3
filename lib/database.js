'use strict';
const fs = require('fs');
const path = require('path');
const util = require('./util');
const CPPDatabase = require('../build/better_sqlite3.node').Database;

function Database(filenameGiven, options) {
	if (options == null) options = {};
	if (typeof filenameGiven !== 'string') throw new TypeError('Expected first argument to be a string');
	if (typeof options !== 'object') throw new TypeError('Expected second argument to be an options object');

	let filename = filenameGiven.trim();
	if (!filename) throw new TypeError('Database filename cannot be an empty string');
	if (filename.toLowerCase().startsWith('file:')) throw new TypeError('URI filenames are reserved for internal use only');
	if ('readOnly' in options) throw new TypeError('Misspelled option "readOnly" should be "readonly"');

	const anonymous = filename === ':memory:';
	const memory = util.getBooleanOption(options, 'memory');
	const readonly = util.getBooleanOption(options, 'readonly');
	const fileMustExist = util.getBooleanOption(options, 'fileMustExist');
	const timeout = 'timeout' in options ? options.timeout : 5000;

	if (readonly && (memory || anonymous)) throw new TypeError('In-memory databases cannot be readonly');
	if (anonymous && !memory && 'memory' in options) throw new TypeError('Option "memory" conflicts with :memory: filename');
	if (!Number.isInteger(timeout) || timeout < 0) throw new TypeError('Expected the "timeout" option to be a positive integer');
	if (timeout > 0x7fffffff) throw new RangeError('Option "timeout" cannot be greater than 2147483647');

	if (!memory && !anonymous && !fs.existsSync(path.dirname(filename))) {
		throw new TypeError('Cannot open database because the directory does not exist');
	}

	if (memory && !anonymous) {
		if (process.platform === 'win32') {
			filename = filename.replace(/\\/g, '/').replace(/^[a-z]:\//i, '/$&');
		}
		filename = 'file:'
			+ filename
				.replace(/#/g, '%23')
				.replace(/\?/g, '%3f')
				.replace(/\/\/+/g, '/')
			+ '?mode=memory&cache=shared';
	}
	return new CPPDatabase(filename, filenameGiven, memory || anonymous, readonly, fileMustExist, timeout);
}

util.wrap(CPPDatabase, 'pragma', require('./pragma'));
util.wrap(CPPDatabase, 'function', require('./function'));
util.wrap(CPPDatabase, 'aggregate', require('./aggregate'));
util.wrap(CPPDatabase, 'backup', require('./backup'));
CPPDatabase.prototype.transaction = require('./transaction');
CPPDatabase.prototype.constructor = Database;
Database.prototype = CPPDatabase.prototype;
module.exports = Database;
