'use strict';

class SqliteError extends Error {
	constructor(message, code) {
		if (typeof code !== 'string') {
			throw new TypeError('Expected second argument to be a string');
		}

		super('' + message);
		this.code = code;

		if (typeof Error.captureStackTrace === 'function') {
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
