'use strict';
const descriptor = { writable: true, enumerable: false, configurable: true, value: 'SqliteError' };

function SqliteError(message, code) {
	if (!(this instanceof SqliteError)) {
		return new SqliteError(message, code);
	}
	if (typeof code !== 'string') {
		throw new TypeError('Expected second argument to be a string');
	}
	Error.call(this, message);
	descriptor.value = '' + message;
	Object.defineProperty(this, 'message', descriptor);
	descriptor.value = code;
	Object.defineProperty(this, 'code', descriptor);
	Error.captureStackTrace(this, SqliteError);
}
Object.setPrototypeOf(SqliteError.prototype, Error.prototype);
Object.defineProperty(SqliteError.prototype, 'name', descriptor);
module.exports = SqliteError;
