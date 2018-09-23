'use strict';
const { getBooleanOption } = require('./util');

module.exports = (createAggregate) => {
	return function customAggregate(name, options) {
		if (typeof name !== 'string') throw new TypeError('Expected first argument to be a string');
		if (typeof options !== 'object' || options === null) throw new TypeError('Expected second argument to be an options object');
		if (!name) throw new TypeError('Custom aggregate name cannot be an empty string');
		
		const start = 'start' in options ? options.start : null;
		const step = getFunctionOption(options, 'step', true);
		const inverse = getFunctionOption(options, 'inverse', false);
		const result = getFunctionOption(options, 'result', false);
		const safeIntegers = 'safeIntegers' in options ? +getBooleanOption(options, 'safeIntegers') : 2;
		const deterministic = getBooleanOption(options, 'deterministic');
		const varargs = getBooleanOption(options, 'varargs');
		let argCount = -1;
		
		if (!varargs) {
			argCount = Math.max(getLength(step), inverse ? getLength(inverse) : 0);
			if (argCount > 0) argCount -= 1;
			if (argCount > 100) throw new RangeError('Custom aggregates cannot have more than 100 arguments');
		}
		
		return createAggregate.call(this, start, step, inverse, result, name, argCount, safeIntegers, deterministic);
	};
};

const getFunctionOption = (options, key, required) => {
	const value = key in options ? options[key] : null;
	if (typeof value === 'function') return value;
	if (value != null) throw new TypeError(`Expected the "${key}" option to be a function`);
	if (required) throw new TypeError(`Missing required option "${key}"`);
	return null;
};

const assertLength = ({ length }) => {
	if (Number.isInteger(length) && length >= 0) return length;
	throw new TypeError('Expected function.length to be a positive integer');
};
