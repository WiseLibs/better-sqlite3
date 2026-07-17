'use strict';
const Database = require('./database')(() => require('../prebuilds/linuxmusl-arm64.node'), false);
Database.SqliteError = require('./sqlite-error');
module.exports = Database;
