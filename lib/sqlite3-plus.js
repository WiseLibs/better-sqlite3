'use strict';
// var isVerbose = false;
var Database = module.exports = exports = require('./database');

// Database.verbose = function () {
// 	if (!isVerbose) {
// 		isVerbose = true;
// 		['close'].forEach(extendTrace, Database.prototype);
// 		// ['bind', 'get', 'run', 'all', 'each', 'map', 'reset', 'finalize']
// 		// 	.forEach(extendTrace, Statement.prototype);
// 	}
// 	return Database;
// };
// function extendTrace(methodName) {
// 	require('./trace').extendTrace(this, methodName);
// }
