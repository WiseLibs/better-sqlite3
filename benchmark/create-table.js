'use strict';
var path = require('path');
var ours = require('../.');
var theirs = require('sqlite3');

module.exports = function (sql, name, callback) {
	var opened = 0;
	var ourDb = new ours(path.join('temp', name + '.ours.db')).on('open', open);
	var theirDb = new theirs.Database(path.join('temp', name + '.theirs.db'), open);
	
	function open() {
		if (++opened === 2) {
			ourDb.statement(sql).run();
			theirDb.run(sql, function (err) {
				if (err) {
					console.error(err);
					process.exit(1);
				}
				callback(ourDb, theirDb);
			});
		}
	}
};
