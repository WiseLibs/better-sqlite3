'use strict';
var path = require('path');
var ours = require('../.');
var theirs = require('sqlite3');

module.exports = function (name, callback) {
	var opened = 0;
	var ours1 = new ours(path.join('temp', name + '.ours.db')).on('open', open);
	var ours2 = new ours(path.join('temp', name + '.ours.db')).on('open', open);
	var theirs1 = new theirs.Database(path.join('temp', name + '.theirs.db'), open);
	var theirs2 = new theirs.Database(path.join('temp', name + '.theirs.db'), open);
	function open() {
		++opened === 4 && pragma();
	}
	function pragma() {
		ours1.pragma('cache_size = -16000;');
		ours2.pragma('cache_size = -16000;');
		theirs1.run('PRAGMA cache_size = -16000;', ranPragma);
		theirs2.run('PRAGMA cache_size = -16000;', ranPragma);
		var pragmaCount = 0;
		function ranPragma() {
			if (++pragmaCount === 2) {
				callback([ours1, ours2], [theirs1, theirs2]);
			}
		}
	}
};
