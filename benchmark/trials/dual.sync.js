'use strict';
require('../get-db')('insert-db', function (ourDb, theirDb) {
	ourDb.pragma('journal_mode = DELETE');
	ourDb.pragma('synchronous = 2');
	theirDb.exec('PRAGMA journal_mode = DELETE; PRAGMA synchronous = 2;', function () {
		require('../dual-trial')(ourDb, theirDb, 1000, 10);
	});
});
