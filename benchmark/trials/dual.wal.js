'use strict';
require('../get-db')('insert-db', function (ourDb, theirDb) {
	ourDb.pragma('journal_mode = WAL');
	ourDb.pragma('synchronous = 1');
	theirDb.exec('PRAGMA journal_mode = WAL; PRAGMA synchronous = 1;', function () {
		require('../dual-trial')(ourDb, theirDb, 10000, 10);
	});
});
