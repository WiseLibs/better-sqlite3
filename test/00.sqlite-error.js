const { expect } = require('chai');
const { SqliteError } = require('../.');

describe('SqliteError', function () {
	it('should be a subclass of Error', function () {
		expect(SqliteError).to.be.a('function');
		expect(SqliteError).to.not.equal(Error);
		expect(SqliteError.prototype).to.be.an.instanceof(Error);
		expect(SqliteError('foo', 'bar')).to.be.an.instanceof(Error);
		expect(new SqliteError('foo', 'bar')).to.be.an.instanceof(Error);
	});
	it('should have the correct name', function () {
		expect(SqliteError.prototype.name).to.equal('SqliteError');
	});
	it('should accept two arguments for setting the message and error code', function () {
		const err = SqliteError('foobar', 'baz');
		expect(err.message).to.equal('foobar');
		expect(err.code).to.equal('baz');
		expect(SqliteError(123, 'baz').message).to.equal('123');
	});
	it('should capture stack traces', function () {
		expect(SqliteError(null, 'baz').stack).to.be.a('string');
	});
});
