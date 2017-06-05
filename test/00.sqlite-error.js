var expect = require('chai').expect;
var SqliteError = require('../.').SqliteError;

describe('SqliteError', function () {
	it('should be a subclass of Error', function () {
		expect(SqliteError).to.be.a('function');
		expect(SqliteError).to.not.equal(Error);
		expect(SqliteError.prototype).to.be.an.instanceof(Error);
	});
	it('should have the correct name', function () {
		expect(SqliteError.prototype.name).to.equal('SqliteError');
	});
	it('should accept a first argument for setting the error message', function () {
		expect(SqliteError('foobar', 'baz').message).to.equal('foobar');
		expect(SqliteError(123, 'baz').message).to.equal('123');
	});
	it('should accept a second argument for setting the error code', function () {
		expect(SqliteError(null, 'baz').code).to.equal('baz');
	});
	it('should capture stack traces', function () {
		expect(SqliteError(null, 'baz').stack).to.be.a('string');
	});
});
