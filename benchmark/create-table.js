'use strict';
var path = require('path');
var ours = require('../.');
var theirs = require('sqlite3');

module.exports = function (sql, name, callback) {
	var ourDb = new ours(path.join('temp', name + '.ours.db'));
	var theirDb = new theirs.Database(path.join('temp', name + '.theirs.db'), opened);
	
	function opened() {
		ourDb.prepare(sql).run();
		theirDb.run(sql, function (err) {
			if (err) {
				console.error(err);
				process.exit(1);
			}
			callback(ourDb, theirDb);
		});
	}
};
