'use strict';
const { getBooleanOption } = require('./util');

module.exports = (createFunction) => {
	return function defineFunction(name, options, fn) {
		if (options == null) options = {};
		if (typeof options === 'function') { fn = options; options = {}; }
		if (typeof name !== 'string') throw new TypeError('Expected first argument to be a string');
		if (typeof fn !== 'function') throw new TypeError('Expected last argument to be a function');
		if (typeof options !== 'object') throw new TypeError('Expected second argument to be an options object');
		if (!name) throw new TypeError('User-defined function name cannot be an empty string');

		const safeIntegers = 'safeIntegers' in options ? +getBooleanOption(options, 'safeIntegers') : 2;
		const deterministic = getBooleanOption(options, 'deterministic');
		const varargs = getBooleanOption(options, 'varargs');
		let argCount = -1;

		if (!varargs) {
			argCount = fn.length;
			if (!Number.isInteger(argCount) || argCount < 0) throw new TypeError('Expected function.length to be a positive integer');
			if (argCount > 100) throw new RangeError('User-defined functions cannot have more than 100 arguments');
		}

		return createFunction.call(this, fn, name, argCount, safeIntegers, deterministic);
	};
};
