'use strict';
const fs = require('fs');
const path = require('path');
const { promisify } = require('util');

const fsAccess = promisify(fs.access);
// const fsUnlink = promisify(fs.unlink);

module.exports = (createBackup) => {
	return async function backup(filename, options) {
		if (options == null) options = {};
		if (typeof filename !== 'string') throw new TypeError('Expected first argument to be a string');
		if (typeof options !== 'object') throw new TypeError('Expected second argument to be an options object');

		filename = filename.trim();
		if (!filename) throw new TypeError('Backup filename cannot be an empty string');
		if (filename === ':memory:') throw new TypeError('Invalid backup filename ":memory:"');
		if (filename.toLowerCase().startsWith('file:')) throw new TypeError('URI filenames are reserved for internal use only');

		const attachedName = 'attached' in options ? options.attached : 'main';
		const handler = 'progress' in options ? options.progress : null;

		if (typeof attachedName !== 'string') throw new TypeError('Expected the "attached" option to be a string');
		if (!attachedName) throw new TypeError('The "attached" option cannot be an empty string');
		if (handler != null && typeof handler !== 'function') throw new TypeError('Expected the "progress" option to be a function');

		await fsAccess(path.dirname(filename)).catch(() => {
			throw new TypeError('Cannot save backup because the directory does not exist');
		});

		// TODO: delete file before backup starts, and delete file if aborted (backup.filename)
		// TOOD: REQUIRE_DATABASE_OPEN and REQUIRE_DATABASE_NOT_BUSY happen asynchronously
		// TODO: backup.close() is called synchronously after the final transfer

		return runBackup(createBackup.call(this, attachedName, filename), handler || null);
	};
};

const runBackup = (backup, handler) => {
	let rate = 0;
	let useDefault = true;

	return new Promise((resolve, reject) => {
		setImmediate(function step() {
			try {
				const progress = backup.transfer(rate);
				if (!progress.remainingPages) {
					backup.close();
					resolve(progress);
					return;
				}
				if (useDefault) {
					useDefault = false;
					rate = 100;
				}
				if (handler) {
					const ret = handler(progress);
					if (ret !== undefined) {
						if (typeof ret === 'number' && ret === ret) rate = Math.max(0, Math.min(0x7fffffff, Math.round(ret)));
						else throw new TypeError('Expected progress callback to return a number or undefined');
					}
				}
				setImmediate(step);
			} catch (err) {
				backup.close();
				reject(err);
			}
		});
	});
}
