'use strict';
require('../get-db2')('insert-db', function (ourDbs, theirDbs) {
	ourDbs[0].pragma('journal_mode = WAL');
	ourDbs[1].pragma('journal_mode = WAL');
	ourDbs[0].pragma('synchronous = 1');
	ourDbs[1].pragma('synchronous = 1');
	theirDbs[0].exec('PRAGMA journal_mode = WAL; PRAGMA synchronous = 1;', setPragma);
	theirDbs[1].exec('PRAGMA journal_mode = WAL; PRAGMA synchronous = 1;', setPragma);
	var pragmaCount = 0;
	function setPragma() {
		if (++pragmaCount === 2) {
			require('../concurrency-trial')(ourDbs, theirDbs, 10000, 10);
		}
	}
});
