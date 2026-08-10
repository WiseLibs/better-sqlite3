'use strict';
module.exports = require('./with-binding')(() => require('../prebuilds/darwin-x64.node'), false);
module.exports.SqliteError = require('./sqlite-error');
