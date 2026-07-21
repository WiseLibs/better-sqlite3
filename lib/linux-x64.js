'use strict';
module.exports = require('./database')(() => require('../prebuilds/linux-x64.node'), false);
module.exports.SqliteError = require('./sqlite-error');
