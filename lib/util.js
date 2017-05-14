'use strict';
var fs = require('fs');

exports.getBooleanOption = function (options, key) {
	if (key in options && typeof options[key] !== 'boolean') {
		throw new TypeError('Expected the "' + key + '" option to be a boolean.');
	}
	return !!options[key];
};

exports.pathExists = function (path) {
	try {fs.accessSync(path); return true;}
	catch (ex) {return false;}
};
