'use strict';
require('../get-db')('insert-db', function (ourDb, theirDb) {
	ourDb.pragma('journal_mode = WAL');
	ourDb.pragma('synchronous = 1');
	theirDb.exec('PRAGMA journal_mode = WAL; PRAGMA synchronous = 1;', function () {
		require('../insert-trial')(ourDb, theirDb, 500, [
			'John Smith',
			123456,
			null
		]);
	});
});
