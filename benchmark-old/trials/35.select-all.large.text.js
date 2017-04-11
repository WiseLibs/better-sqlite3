'use strict';
require('../get-db')('select-large', function (ourDb, theirDb) {
	require('../types/select-all')(ourDb, theirDb, 1, 1000, 'text');
});
