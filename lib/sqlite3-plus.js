'use strict';
var util = require('util');
var EventEmitterAsync = require('./event-emitter-async');
var sqlite3 = module.exports = exports = require('bindings')('sqlite3_plus');
var isVerbose = false;

var Database = sqlite3.Database;
// var Statement = sqlite3.Statement;
util.inherits(Database, EventEmitterAsync);
// util.inherits(Statement, EventEmitterAsync);



delete sqlite3.path;
sqlite3.verbose = function () {
	if (!isVerbose) {
		['close'].forEach(extendTrace, Database.prototype);
		// ['bind', 'get', 'run', 'all', 'each', 'map', 'reset', 'finalize']
		// 	.forEach(extendTrace, Statement.prototype);
	}
	
	isVerbose = true;
	function extendTrace(methodName) {
		require('./trace').extendTrace(this, methodName);
	}
	return this;
};
