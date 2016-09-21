'use strict';
require('../get-db')('real-world', function (ourDb, theirDb) {
	ourDb.pragma('journal_mode = DELETE');
	ourDb.pragma('synchronous = 2');
	theirDb.exec('PRAGMA journal_mode = DELETE; PRAGMA synchronous = 2;', function () {
		require('../types/real-world')(ourDb, theirDb, 1000, 10);
	});
});
