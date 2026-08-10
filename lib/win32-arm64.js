'use strict';
module.exports = require('./with-binding')(() => require('../prebuilds/win32-arm64.node'), false);
module.exports.SqliteError = require('./sqlite-error');
