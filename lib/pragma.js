'use strict';
const { getBooleanOption } = require('./util');

module.exports = (setPragmaMode) => {
	return function pragma(source, options) {
		if (options == null) options = {};
		if (typeof source !== 'string') throw new TypeError('Expected first argument to be a string');
		if (typeof options !== 'object') throw new TypeError('Expected second argument to be an options object');
		const simple = getBooleanOption(options, 'simple');
		
		setPragmaMode.call(this, true);
		try {
			return simple
				? this.prepare(`PRAGMA ${source}`).pluck().get()
				: this.prepare(`PRAGMA ${source}`).all();
		} finally {
			setPragmaMode.call(this, false);
		}
	};
};
