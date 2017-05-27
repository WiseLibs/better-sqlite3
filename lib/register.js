'use strict';
var util = require('./util');
var GeneratorFunctionProto = Object.getPrototypeOf(function*(){});

module.exports = function (createFunction) {
	return function register(options, func) {
		if (typeof options === 'function') {
			func = options;
		}
		if (typeof options !== 'object' || options === null) {
			options = {};
		}
		if (typeof func !== 'function') {
			throw new TypeError('Expected second argument to be a function');
		}
		
		var name = 'name' in options ? options.name : func.name;
		if (typeof name !== 'string') {
			throw new TypeError('Expected the "name" option to be a string');
		}
		if (!name) {
			throw new TypeError('Cannot create an SQL function without a name');
		}
		
		var defaultSafeIntegers = !('safeIntegers' in options);
		var safeIntegers = util.getBooleanOption(options, 'safeIntegers');
		var deterministic = util.getBooleanOption(options, 'deterministic');
		var aggregate = util.getBooleanOption(options, 'aggregate');
		var varargs = util.getBooleanOption(options, 'varargs');
		var argCount = -1;
		
		if (aggregate) {
			if (Object.getPrototypeOf(func) !== GeneratorFunctionProto) {
				throw new TypeError('Custom aggregates must be registered as generator functions');
			}
			var generator = func.call(undefined);
			var entry = generator.next();
			if (entry.done || typeof entry.value !== 'function') {
				throw new TypeError('Custom aggregates must yield a function');
			}
			if (!generator.next().done) {
				throw new TypeError('Custom aggregates should only yield once');
			}
		}
		
		if (!varargs) {
			argCount = entry ? entry.value.length : func.length;
			if (typeof argCount !== 'number') {
				throw new TypeError('Expected function.length to be a number');
			}
			if (argCount % 1 !== 0 || argCount < 0) {
				throw new TypeError('Expected function.length to be a positive integer');
			}
			if (argCount > 127) {
				throw new RangeError('Cannot create an SQL function with more than 127 arguments');
			}
		}
		
		return createFunction.call(this, func, name, argCount, aggregate, deterministic, defaultSafeIntegers, safeIntegers);
	};
};
