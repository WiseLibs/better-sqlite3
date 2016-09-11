'use strict';
var path = require('path');
var ours = require('../.');
var theirs = require('sqlite3');

module.exports = function (name, callback) {
	var opened = 0;
	ours = new ours(path.join('temp', name + '.ours.db')).on('open', open);
	theirs = new theirs.Database(path.join('temp', name + '.theirs.db'), open);
	function open() {
		++opened === 2 && pragma();
	}
	function pragma() {
		ours.pragma('cache_size = -16000;');
		theirs.run('PRAGMA cache_size = -16000;', function () {
			callback(ours, theirs);
		});
	}
};
