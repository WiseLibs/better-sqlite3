'use strict';

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

	// Check if this method was previously wrapped for this class
	if (!Class.prototype.wrappedMethods().has(originalMethod)) {
		const wrapped = wrapper(originalMethod);
		Class.prototype.wrappedMethods().add(wrapped);
		Class.prototype[methodName] = wrapped;
	}
};
