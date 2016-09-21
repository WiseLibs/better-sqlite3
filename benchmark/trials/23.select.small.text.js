'use strict';
require('../get-db')('select-small', function (ourDb, theirDb) {
	require('../types/select')(ourDb, theirDb, 10000, 'text');
});
