'use strict';
var toDescriptor = require('to-descriptor');
var EventEmitterAsync = require('./event-emitter-async');
var CPPDatabase = require('bindings')('sqlite3_plus').Database;
var setPrototypeOf = require('./set-prototype-of');

function Database(filename, options) {
	if (typeof filename !== 'string') {
		throw new TypeError('Argument 0 must be a string filename.');
	}
	
	filename = filename.trim();
	if (typeof options !== 'object' || options === null) {
		options = {};
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
	
	return new CPPDatabase(filename);
}
CPPDatabase.prototype.constructor = Database;
Database.prototype = Object.create(Object.prototype, toDescriptor(CPPDatabase.prototype));
setPrototypeOf(Database.prototype, EventEmitterAsync.prototype);
setPrototypeOf(CPPDatabase.prototype, Database.prototype);
module.exports = Database;
