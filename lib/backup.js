'use strict';

module.exports = (startBackup) => {
	return function backup(filename, options) {
		return new Promise((resolve, reject) => {
			if (typeof filename !== 'string') throw new TypeError('Expected first argument to be a string');
			if (typeof options !== 'object' || options === null) throw new TypeError('Expected second argument to be an options object');
			if (!filename) throw new TypeError('Backup filename cannot be an empty string');

			const pages = 'pages' in options ? options.pages : 256;
			const usageLimit = 'usageLimit' in options ? options.usageLimit : 0.1;
			const sourceDatabase = 'attached' in options ? options.attached : 'main';

			if (!Number.isInteger(pages)) throw new TypeError('Expected the "pages" option to be an integer');
			if (pages <= 0) throw new RangeError('The "pages" option must be greater than 0');
			if (pages >= 0x80000000) throw new RangeError('The "pages" option must be less than 2147483648');
			if (!Number.isFinite(usageLimit)) throw new TypeError('Expected the "usageLimit" option to be a finite number');
			if (usageLimit <= 0) throw new RangeError('The "usageLimit" option must be greater than 0');
			if (usageLimit > 1) throw new RangeError('The "usageLimit" option cannot be greater than 1');
			if (typeof sourceDatabase !== 'string') throw new TypeError('Expected the "attached" option to be a string');
			if (!sourceDatabase) throw new TypeError('The "attached" option cannot be an empty string');

			const backup = startBackup.call(this, sourceDatabase, filename, pages);
			setImmediate(runBackup(backup, resolve, reject, usageLimit));
		});
	};
};

const runBackup = (backup, resolve, reject, usageLimit) => function step() {
	const startTime = Date.now();
	try {
		if (backup.step()) return resolve();
	} catch (err) {
		return reject(err);
	}
	const deltaTime = Date.now() - startTime;
	setTimeout(step, Math.round(deltaTime / usageLimit - deltaTime));
};

const getPositiveIntegerOption = (options, key, defaultValue) => {
	const value = key in options ? options[key] : defaultValue;
	if (Number.isInteger(value) && value >= 0) {
		if (value === 0) throw new RangeError(`The "${key}" option must be greater than 0`);
		if (value > 0x7fffffff) throw new RangeError(`The "${key}" option must be less than 2147483647`);
		return value;
	}
	throw new TypeError(`Expected the "${key}" option to be a positive integer`);
};

const getStringOption = (options, key, defaultValue) => {
	const value = key in options ? options[key] : defaultValue;
	if (typeof value === 'string') {
		if (!value) throw new TypeError(`The "${key}" option cannot be an empty string`);
		return value;
	}
	throw new TypeError(`Expected the "${key}" option to be a string`);
};
