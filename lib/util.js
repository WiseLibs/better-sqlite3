'use strict';
var fs = require('fs');

exports.getBooleanOption = function (options, key) {
	var value = false;
	if (key in options && typeof (value = options[key]) !== 'boolean') {
		throw new TypeError('Expected the "' + key + '" option to be a boolean');
	}
	return value;
};

exports.pathExists = function (path) {
	try {fs.accessSync(path); return true;}
	catch (ex) {return false;}
};

exports.wrap = function (Class, methodName, wrapper) {
	var originalMethod = Class.prototype[methodName];
	if (typeof originalMethod !== 'function') {
		throw new TypeError('Missing method ' + methodName);
	}
	Class.prototype[methodName] = wrapper(originalMethod);
};
