'use strict';

module.exports = function (setPragmaMode) {
	return function pragma(source, simplify) {
		if (typeof source !== 'string') {
			throw new TypeError('Expected first argument to be a string');
		}
		if (arguments.length > 1 && typeof simplify !== 'boolean') {
			throw new TypeError('Expected second argument to be a boolean');
		}
		
		setPragmaMode.call(this, true);
		try {
			return simplify
				? this.prepare(`PRAGMA ${source}`).pluck().get()
				: this.prepare(`PRAGMA ${source}`).all();
		} finally {
			setPragmaMode.call(this, false);
		}
	};
};
