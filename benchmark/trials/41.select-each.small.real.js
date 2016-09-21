'use strict';
require('../get-db')('select-small', function (ourDb, theirDb) {
	require('../types/select-each')(ourDb, theirDb, 100, 1000, 'real');
});
