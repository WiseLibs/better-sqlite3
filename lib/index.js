'use strict';
module.exports = require('./with-binding')(require('./binding').getBinding, true);
module.exports.SqliteError = require('./sqlite-error');
