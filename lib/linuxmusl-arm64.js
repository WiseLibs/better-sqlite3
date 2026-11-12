'use strict';
const Database = require('./with-binding')(() => require('../prebuilds/linuxmusl-arm64.node'), false);
Database.SqliteError = require('./sqlite-error');
module.exports = Database;
