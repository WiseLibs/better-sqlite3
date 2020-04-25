'use strict';
const { getBooleanOption } = require('./util');

module.exports = (setPragmaMode) => {
	return function pragma(source, options) {
		if (options == null) options = {};
		if (typeof source !== 'string') throw new TypeError('Expected first argument to be a string');
		if (typeof options !== 'object') throw new TypeError('Expected second argument to be an options object');
		const simple = getBooleanOption(options, 'simple');

		let stmt;
		setPragmaMode.call(this, true);
		try {
			stmt = this.prepare(`PRAGMA ${source}`);
		} finally {
			setPragmaMode.call(this, false);
		}
		return simple ? stmt.pluck().get() : stmt.all();
	};
};
