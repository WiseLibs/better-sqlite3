'use strict';
require('../get-db')('select-db', function (ourDb, theirDb) {
	ourDb.pragma('journal_mode = DELETE');
	ourDb.pragma('synchronous = 2');
	theirDb.exec('PRAGMA journal_mode = DELETE; PRAGMA synchronous = 2;', function () {
		require('../select-trial')(ourDb, theirDb, 10000, true);
	});
});
