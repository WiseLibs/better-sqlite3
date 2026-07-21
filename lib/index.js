'use strict';
module.exports = require('./database')(require('./binding').getBinding, true);
module.exports.SqliteError = require('./sqlite-error');
