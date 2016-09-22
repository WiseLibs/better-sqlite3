'use strict';
require('../get-db')('real-world', function (ourDb, theirDb) {
	require('../types/prepare')(ourDb, theirDb, 100000);
});
