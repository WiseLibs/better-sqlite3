'use strict';
require('../get-db')('insert-blob', function (ourDb, theirDb) {
	ourDb.pragma('journal_mode = DELETE');
	ourDb.pragma('synchronous = 2');
	theirDb.exec('PRAGMA journal_mode = DELETE; PRAGMA synchronous = 2;', function () {
		require('../types/transaction')(ourDb, theirDb, 250, Buffer.alloc(1024 * 1024).fill(0xdd));
	});
});
