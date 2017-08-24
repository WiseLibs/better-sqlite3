'use strict';
var path = require('path');
var toDescriptor = require('to-descriptor');
var util = require('./util');
var CPPDatabase = require('bindings')({
	bindings: 'better_sqlite3.node',
	module_root: path.resolve(__dirname, '..')
}).Database;

function Database(filenameGiven, options) {
	if (typeof filenameGiven !== 'string') {
		throw new TypeError('Expected first argument to be a string');
	}
	var filename = filenameGiven.trim();
	if (!filename) {
		throw new TypeError('A database filename cannot be an empty string');
	}
	if (/^file:/i.test(filename)) {
		throw new TypeError('URI filenames are reserved for internal use only');
	}
	if (/^(:memory:)?$/i.test(filename)) {
		throw new TypeError('To create an in-memory database, specify a normal filename and use the "memory" option');
	}
	
	if (typeof options !== 'object' || options === null) {
		options = {};
	}
	if ('readOnly' in options) {
		throw new TypeError('Misspelled option "readOnly" should be "readonly"');
	}
	var memory = util.getBooleanOption(options, 'memory');
	var readonly = util.getBooleanOption(options, 'readonly');
	var fileMustExist = util.getBooleanOption(options, 'fileMustExist');
	
	if (memory) {
		if (process.platform === 'win32') {
			filename = filename.replace(/\\/g, '/').replace(/^[a-z]:\//i, '/$&');
		}
		filename = 'file:'
			+ filename
				.replace(/\?/g, '%3f')
				.replace(/\/\/+/g, '/')
				.replace(/#/g, '%23')
			+ '?mode=memory&cache=shared';
	} else if (!util.pathExists(path.dirname(filename))) {
		throw new TypeError('Cannot open database because the directory does not exist');
	}
	
	return new CPPDatabase(filename, filenameGiven, memory, readonly, fileMustExist);
}

util.wrap(CPPDatabase, 'pragma', require('./pragma'));
util.wrap(CPPDatabase, 'register', require('./register'));
CPPDatabase.prototype.constructor = Database;
Database.prototype = Object.create(Object.prototype, toDescriptor(CPPDatabase.prototype));
Object.keys(CPPDatabase.prototype).forEach(function (method) {delete CPPDatabase.prototype[method];});
Object.setPrototypeOf(CPPDatabase.prototype, Database.prototype);
module.exports = Database;
