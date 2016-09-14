'use strict';
require('../get-db')('insert-db', function (ourDb, theirDb) {
	ourDb.pragma('journal_mode = DELETE');
	ourDb.pragma('synchronous = 2');
	theirDb.exec('PRAGMA journal_mode = DELETE; PRAGMA synchronous = 2;', function () {
		require('../transaction-trial')(ourDb, theirDb, 5000, [
			'John Smith',
			123456,
			null
		]);
	});
});
