'use strict';
var fs = require('fs');
var path = require('path');
var toDescriptor = require('to-descriptor');
var CPPDatabase = require('bindings')({
	bindings: 'better_sqlite3.node',
	module_root: path.resolve(__dirname, '..'),
}).Database;

function Database(filenameGiven, options) {
	if (typeof filenameGiven !== 'string') {
		throw new TypeError('Expected argument 0 to be a string filename.');
	}
	var filename = filenameGiven.trim();
	if (!filename) {
		throw new TypeError('A database filename cannot be an empty string.');
	}
	if (/^file:/i.test(filename)) {
		throw new TypeError('URI filenames are reserved for internal use only.');
	}
	if (/^(:memory:)?$/i.test(filename)) {
		throw new TypeError('To create an in-memory database, specify a normal filename and use the "memory" option.');
	}
	
	if (typeof options !== 'object' || options === null) {
		options = {};
	}
	var memory = getBoolean(options, 'memory');
	var readonly = getBoolean(options, 'readonly');
	
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
	} else if (!pathExists(path.dirname(filename))) {
		throw new TypeError('Cannot open database because the directory does not exist.');
	}
	
	return new CPPDatabase(filename, filenameGiven, memory, readonly);
}

var createFunction = CPPDatabase.prototype.register;
var GeneratorFunctionProto = Object.getPrototypeOf(function*(){});
CPPDatabase.prototype.register = function register(options, func) {
	if (typeof options === 'function') {
		func = options;
	}
	if (typeof options !== 'object' || options === null) {
		options = {};
	}
	if (typeof func !== 'function') {
		throw new TypeError('Expected argument 2 to be a function.');
	}
	var name = 'name' in options ? options.name : func.name;
	var defaultSafeIntegers = !('safeIntegers' in options);
	var deterministic = getBoolean(options, 'deterministic');
	var aggregate = getBoolean(options, 'aggregate');
	var safeIntegers = getBoolean(options, 'safeIntegers');
	var varargs = getBoolean(options, 'varargs');
	var argCount = func.length;
	if (typeof name !== 'string') {
		throw new TypeError('Expected the "name" option to be a string.');
	}
	if (!varargs && typeof argCount !== 'number') {
		throw new TypeError('Expected function.length to be a number.');
	}
	if (aggregate && Object.getPrototypeOf(func) !== GeneratorFunctionProto) {
		throw new TypeError('Custom aggregates must be registered as generator functions.');
	}
	return createFunction.call(this, func, name, deterministic, aggregate, defaultSafeIntegers, varargs, safeIntegers, argCount);
};

function pathExists(path) {
	try {fs.accessSync(path); return true;}
	catch (ex) {return false;}
}

function getBoolean(options, key) {
	if (key in options && typeof options[key] !== 'boolean') {
		throw new TypeError('Expected the "' + key + '" option to be a boolean.');
	}
	return !!options[key];
}

CPPDatabase.prototype.constructor = Database;
Database.prototype = Object.create(Object.prototype, toDescriptor(CPPDatabase.prototype));
Object.keys(CPPDatabase.prototype).forEach(function (method) {delete CPPDatabase.prototype[method];});
Object.setPrototypeOf(CPPDatabase.prototype, Database.prototype);
module.exports = Database;
