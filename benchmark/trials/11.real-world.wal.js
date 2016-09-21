'use strict';
require('../get-db')('real-world', function (ourDb, theirDb) {
	ourDb.pragma('journal_mode = WAL');
	ourDb.pragma('synchronous = 1');
	theirDb.exec('PRAGMA journal_mode = WAL; PRAGMA synchronous = 1;', function () {
		require('../types/real-world')(ourDb, theirDb, 10000, 10);
	});
});
