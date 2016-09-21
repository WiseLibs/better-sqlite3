'use strict';
require('../get-db')('insert-text', function (ourDb, theirDb) {
	ourDb.pragma('journal_mode = DELETE');
	ourDb.pragma('synchronous = 2');
	theirDb.exec('PRAGMA journal_mode = DELETE; PRAGMA synchronous = 2;', function () {
		require('../types/insert')(ourDb, theirDb, 500, 'John Peter Smith');
	});
});
