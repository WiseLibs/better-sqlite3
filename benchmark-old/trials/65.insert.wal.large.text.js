'use strict';
require('../get-db')('insert-text', function (ourDb, theirDb) {
	ourDb.pragma('journal_mode = WAL');
	ourDb.pragma('synchronous = 1');
	theirDb.exec('PRAGMA journal_mode = WAL; PRAGMA synchronous = 1;', function () {
		var bigString = '';
		while (bigString.length < 1024 * 1024) {
			bigString += 'John Peter Smith';
		}
		require('../types/insert')(ourDb, theirDb, 250, bigString);
	});
});
