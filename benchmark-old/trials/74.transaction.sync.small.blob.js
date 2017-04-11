'use strict';
require('../get-db')('insert-blob', function (ourDb, theirDb) {
	ourDb.pragma('journal_mode = DELETE');
	ourDb.pragma('synchronous = 2');
	theirDb.exec('PRAGMA journal_mode = DELETE; PRAGMA synchronous = 2;', function () {
		require('../types/transaction')(ourDb, theirDb, 5000, Buffer.alloc(16).fill(0xdd));
	});
});
