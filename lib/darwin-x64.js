'use strict';
module.exports = require('./database')(() => require('../prebuilds/darwin-x64.node'), false);
module.exports.SqliteError = require('./sqlite-error');
