'use strict';
module.exports = require('./database')(() => require('../prebuilds/darwin-arm64.node'), false);
module.exports.SqliteError = require('./sqlite-error');
