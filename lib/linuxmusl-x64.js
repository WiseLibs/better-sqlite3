'use strict';
const Database = require('./database')(() => require('../prebuilds/linuxmusl-x64.node'), false);
Database.SqliteError = require('./sqlite-error');
module.exports = Database;
