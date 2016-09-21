'use strict';
require('../get-db')('select-large', function (ourDb, theirDb) {
	require('../types/select')(ourDb, theirDb, 500, 'blob');
});
