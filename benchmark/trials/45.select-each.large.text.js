'use strict';
require('../get-db')('select-large', function (ourDb, theirDb) {
	require('../types/select-each')(ourDb, theirDb, 1, 1000, 'text');
});
