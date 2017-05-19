'use strict';
var util = require('./util');

module.exports = function (runCheckpoint) {
	return function (options) {
		if (typeof options !== 'object' || options === null) {
			options = {};
		}
		var databaseName = '';
		var force = util.getBooleanOption(options, 'force');
		
		if ('only' in options) {
			databaseName = options.only;
			if (typeof databaseName !== 'string') {
				throw new TypeError('Expected the "only" option to be a string');
			}
			if (!databaseName) {
				throw new TypeError('Invalid database name (empty string)');
			}
		}
		return runCheckpoint.call(this, databaseName, force);
	};
};
