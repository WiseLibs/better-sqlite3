'use strict';
var path = require('path');
var ours = require('../.');
var theirs = require('sqlite3');

module.exports = function (name, callback) {
	ours = new ours(path.join('temp', name + '.ours.db'));
	theirs = new theirs.Database(path.join('temp', name + '.theirs.db'), opened);
	function opened() {
		ours.pragma('cache_size = -16000;');
		theirs.run('PRAGMA cache_size = -16000;', function () {
			callback(ours, theirs);
		});
	}
};
