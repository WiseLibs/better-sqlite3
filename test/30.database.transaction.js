'use strict';
const Database = require('../.');

describe('Database#transaction()', function () {
	it('should throw an exception if a function is not provided', function () {
		expect(() => this.db.transaction(123)).to.throw(TypeError);
		expect(() => this.db.transaction(0)).to.throw(TypeError);
		expect(() => this.db.transaction(null)).to.throw(TypeError);
		expect(() => this.db.transaction()).to.throw(TypeError);
		expect(() => this.db.transaction([])).to.throw(TypeError);
		expect(() => this.db.transaction('CREATE TABLE people (name TEXT)')).to.throw(TypeError);
		expect(() => this.db.transaction(['CREATE TABLE people (name TEXT)'])).to.throw(TypeError);
	});
});
