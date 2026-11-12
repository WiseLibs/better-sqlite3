'use strict';
module.exports = require('./with-binding')(() => require('../prebuilds/linux-x64.node'), false);
module.exports.SqliteError = require('./sqlite-error');
