'use strict';

class SqliteError extends Error {
	constructor(message, code) {
		if (typeof code !== 'string') {
			throw new TypeError('Expected second argument to be a string');
		}
		super('' + message);
		Object.defineProperty(this, 'message', {
			value: '' + message,
			writable: true,
			enumerable: false,
			configurable: true,
		});
		this.code = code;
		if (Error.captureStackTrace) {
			Error.captureStackTrace(this, SqliteError);
		}
	}
}

Object.defineProperty(SqliteError.prototype, 'name', {
	value: 'SqliteError',
	writable: true,
	enumerable: false,
	configurable: true,
});

module.exports = SqliteError;
