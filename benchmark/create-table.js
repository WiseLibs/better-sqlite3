'use strict';
var path = require('path');
var ours = require('../.');
var theirs = require('sqlite3');

module.exports = function (sql, filename, ourTest, theirTest) {
	var opened = 0;
	var created = 0;
	ours = new ours(path.join('temp', path.basename(filename) + '.1.db')).on('open', open);
	theirs = new theirs.Database(path.join('temp', path.basename(filename) + '.2.db'), open);
	
	function open() {
		if (++opened === 2) {
			ours.statement(sql).run(ready);
			theirs.run(sql, ready);
		}
	}
	function ready(err) {
		if (++created === 2) {
			var done = function () {
				process.exit();
			};
			var callback = function () {
				global.gc();
				theirTest(theirs, done);
			};
			setTimeout(function () {
				global.gc();
				ourTest(ours, callback);
			}, 100);
		}
	}
};
