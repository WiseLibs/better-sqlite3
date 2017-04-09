var expect = require('chai').expect;
var Database = require('../.');
var db;

before(function () {
	db = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.db');
});

describe('Database#register()', function () {
	it('should throw an exception if a function is not provided');
	it('should throw an exception if the function name is not a string');
	it('should throw an exception if the function name is empty');
	it('should register the given function');
	it('should return the database object');
	it('should accept a "name" option');
	it('should accept a "safeIntegers" option');
	it('should accept an "argCount" option');
	it('should throw an exception if argCount is not a positive integer');
	it('should throw an exception if argCount is larger than 127');
	it('should throw an exception if the database is busy');
	it('should cause the database to become busy when executing the function');
	it('should throw an exception if the function returns an invalid value');
	it('should propagate exceptions thrown in the registered function');
	it('should not be able to affect bound buffers mid-query');
	describe('should not affect external state', function () {
		specify('busy state');
		specify('safeIntegers state');
		specify('was_js_error state');
	});
});
