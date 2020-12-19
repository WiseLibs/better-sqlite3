'use strict';
const wrappedMethods = new WeakSet();

exports.getBooleanOption = (options, key) => {
	let value = false;
	if (key in options && typeof (value = options[key]) !== 'boolean') {
		throw new TypeError(`Expected the "${key}" option to be a boolean`);
	}
	return value;
};

exports.wrap = (Class, methodName, wrapper) => {
	const originalMethod = Class.prototype[methodName];
	if (typeof originalMethod !== 'function') {
		throw new TypeError(`Missing method ${methodName}`);
	}
	if (!wrappedMethods.has(originalMethod)) {
		const wrapped = wrapper(originalMethod);
		wrappedMethods.add(wrapped);
		Class.prototype[methodName] = wrapped;
	}
};
