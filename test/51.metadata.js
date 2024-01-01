'use strict';
const Database = require('../lib');
const snapshotData = require('./51.metadata.json');

describe('version', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
	});
	afterEach(function () {
		this.db.close();
	});
	// Added for issue: https://github.com/WiseLibs/better-sqlite3/issues/1021
	it('can get metadata', function () {
		expect(this.db.metadata).to.deep.equal(snapshotData['it can get metadata']);
	});
});
