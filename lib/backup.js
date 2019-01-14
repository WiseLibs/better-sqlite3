'use strict';
const fs = require('fs');
const path = require('path');

module.exports = (createBackup) => {
	return function backup(filename, options) {
		if (options == null) options = {};
		if (typeof filename !== 'string') throw new TypeError('Expected first argument to be a string');
		if (typeof options !== 'object') throw new TypeError('Expected second argument to be an options object');

		filename = filename.trim();
		if (!filename) throw new TypeError('Backup filename cannot be an empty string');
		if (filename === ':memory:') throw new TypeError('Invalid backup filename ":memory:"');
		if (filename.toLowerCase().startsWith('file:')) throw new TypeError('URI filenames are reserved for internal use only');

		const sourceDatabase = 'attached' in options ? options.attached : 'main';
		const progressCallback = 'progress' in options ? options.progress : null;

		if (typeof sourceDatabase !== 'string') throw new TypeError('Expected the "attached" option to be a string');
		if (!sourceDatabase) throw new TypeError('The "attached" option cannot be an empty string');
		if (progressCallback != null && typeof progressCallback !== 'function') throw new TypeError('Expected the "progress" option to be a function');

		// TODO: make this check async
		if (!fs.existsSync(path.dirname(filename))) {
			throw new TypeError('Cannot save backup because the directory does not exist');
		}

		// TODO: dont throw synchronous errors
		// TODO: delete file before backup starts, and delete file if aborted
		// TODO: make transfer size (pages) configurable
		// TODO: allow the user to abort (via progressCallback?)

		return runBackup(createBackup.call(this, sourceDatabase, filename), progressCallback || null);
	};
};

const runBackup = (backup, progressCallback) => new Promise((resolve, reject) => {
	setImmediate(function step() {
		try {
			const result = backup.transfer(100);
			if (!result.remainingPages) return resolve(result);
			if (progressCallback) progressCallback(result);
		} catch (err) {
			return reject(err);
		}
		setImmediate(step);
	});
});
