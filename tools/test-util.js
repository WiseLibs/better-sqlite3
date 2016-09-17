'use strict';
var path = require('path');
var dbId = 0;

exports.current = function () {
	return 'temp/' + path.basename(__filename).split('.')[0] + '.' + dbId + '.db';
};

exports.next = function () {
	++dbId;
	return exports.current();
};
