'use strict';
const fs = require('fs');

exports.getBooleanOption = (options, key) => {
	let value = false;
	if (key in options && typeof (value = options[key]) !== 'boolean') {
		throw new TypeError(`Expected the "${key}" option to be a boolean`);
	}
	return value;
};

exports.pathExists = (path) => {
	try { fs.accessSync(path); return true; }
	catch (_) { return false; }
};

exports.wrap = (Class, methodName, wrapper) => {
	const originalMethod = Class.prototype[methodName];
	if (typeof originalMethod !== 'function') {
		throw new TypeError(`Missing method ${methodName}`);
	}
	Class.prototype[methodName] = wrapper(originalMethod);
};
