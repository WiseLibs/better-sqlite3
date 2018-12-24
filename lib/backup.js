'use strict';

module.exports = (createBackup) => {
	return function backup(filename, options) {
		if (options == null) options = {};
		if (typeof filename !== 'string') throw new TypeError('Expected first argument to be a string');
		if (typeof options !== 'object') throw new TypeError('Expected second argument to be an options object');
		if (!filename) throw new TypeError('Backup filename cannot be an empty string');

		const sourceDatabase = 'attached' in options ? options.attached : 'main';
		if (typeof sourceDatabase !== 'string') throw new TypeError('Expected the "attached" option to be a string');
		if (!sourceDatabase) throw new TypeError('The "attached" option cannot be an empty string');

		return createBackup.call(this, sourceDatabase, filename);
	};
};
