'use strict';
var OurDatabase = require('../.');

module.exports = function (db, count, SQL, values, callback) {
	if (db instanceof OurDatabase) {
		db.transaction(new Array(count).fill(SQL)).run(values);
		callback();
		return;
	}
	
	// node-sqlite3 requires the "@" character for named parameters.
	var obj = {};
	for (var key in values) {
		obj['@' + key] = values[key];
	}
	
	var checkForError = function (err) {
		if (err) {throw err;}
	};
	db.serialize(function () {
		db.run('BEGIN TRANSACTION;', checkForError);
		for (var i=0; i<count; ++i) {
			db.run(SQL, obj, checkForError);
		}
		db.run('COMMIT TRANSACTION;', function (err) {
			checkForError(err);
			callback();
		});
	});
};
