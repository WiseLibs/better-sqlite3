'use strict';

if (typeof Object.setPrototypeOf === 'function') {
	module.exports = Object.setPrototypeOf;
} else {
	module.exports = function (obj, prototype) {
		obj.__proto__ = prototype;
		return obj;
	};
}
