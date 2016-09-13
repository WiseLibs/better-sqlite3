'use strict';
module.exports = require('./lib/database');
module.exports.Int64 = require('bindings')('better_sqlite3').Int64;