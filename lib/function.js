'use strict';
const util = require('./util');

module.exports = (createFunction) => {
	return function customFunction(name, options, fn) {
		if (options == null) options = {};
		if (typeof options === 'function') { fn = options; options = {}; }
		if (typeof name !== 'string') throw new TypeError('Expected first argument to be a string');
		if (typeof fn !== 'function') throw new TypeError('Expected last argument to be a function');
		if (typeof options !== 'object') throw new TypeError('Expected second argument to be an options object');
		if (!name) throw new TypeError('Custom function name cannot be an empty string');
		
		const safeIntegers = 'safeIntegers' in options ? +util.getBooleanOption(options, 'safeIntegers') : 2;
		const deterministic = util.getBooleanOption(options, 'deterministic');
		const varargs = util.getBooleanOption(options, 'varargs');
		let argCount = -1;
		
		if (!varargs) {
			argCount = fn.length;
			if (typeof argCount !== 'number') {
				throw new TypeError('Expected function.length to be a number');
			}
			if (argCount % 1 !== 0 || argCount < 0) {
				throw new TypeError('Expected function.length to be a positive integer');
			}
			if (argCount > 100) {
				throw new RangeError('Custom functions cannot have more than 100 arguments');
			}
		}
		
		return createFunction.call(this, fn, name, argCount, safeIntegers, deterministic);
	};
};
