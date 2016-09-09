'use strict';
var EventEmitter = require('events').EventEmitter;
var toDescriptor = require('to-descriptor');
var CPPDatabase = require('bindings')('better_sqlite3').Database;

function Database(filename, options) {
	if (typeof filename !== 'string') {
		throw new TypeError('Expected argument 0 to be a string filename.');
	}
	
	filename = filename.trim();
	if (typeof options !== 'object' || options === null) {
		options = {};
	}
	
	if (!filename) {
		throw new TypeError('A database filename cannot be an empty string.');
	}
	if (/^file:/i.test(filename)) {
		throw new TypeError('URI filenames are reserved for internal use only.');
	}
	if (/^(:memory:)?$/i.test(filename)) {
		throw new TypeError('To create an in-memory database, specify a normal filename and use the "memory" option.');
	}
	
	if (options.memory) {
		if (process.platform === 'win32') {
			filename = filename.replace(/\\/g, '/').replace(/^[a-z]:\//i, '/$&');
		}
		filename = 'file:'
			+ filename
				.replace(/\?/g, '%3f')
				.replace(/\/\/+/g, '/')
				.replace(/#/g, '%23')
			+ '?mode=memory';
	}
	
	return new CPPDatabase(filename, NullFactory);
}
CPPDatabase.prototype.constructor = Database;
Database.prototype = Object.create(Object.prototype, toDescriptor(CPPDatabase.prototype));
Object.setPrototypeOf(Database.prototype, EventEmitter.prototype);
Object.setPrototypeOf(CPPDatabase.prototype, Database.prototype);
module.exports = Database;

function NullFactory() {}
NullFactory.prototype = Object.create(null);
