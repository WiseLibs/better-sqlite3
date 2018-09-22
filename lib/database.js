'use strict';
const fs = require('fs');
const path = require('path');
const util = require('./util');
const CPPDatabase = require('bindings')({
	bindings: 'better_sqlite3.node',
	module_root: path.resolve(__dirname, '..'),
}).Database;

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
	
	if (readonly && (memory || anonymous)) throw new TypeError('In-memory databases cannot be readonly');
	if (anonymous && !memory && 'memory' in options) throw new TypeError('Option "memory" conflicts with :memory: filename');
	
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
	return new CPPDatabase(filename, filenameGiven, memory || anonymous, readonly, fileMustExist);
}

util.wrap(CPPDatabase, 'pragma', require('./pragma'));
util.wrap(CPPDatabase, 'function', require('./function'));
CPPDatabase.prototype.transaction = require('./transaction');
CPPDatabase.prototype.constructor = Database;
Database.prototype = CPPDatabase.prototype;
module.exports = Database;
