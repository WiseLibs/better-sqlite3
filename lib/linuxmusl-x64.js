'use strict';
const Database = require('./with-binding')(() => require('../prebuilds/linuxmusl-x64.node'), false);
Database.SqliteError = require('./sqlite-error');
module.exports = Database;
