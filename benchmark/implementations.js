'use strict';
var path = require('path');
var slice = Array.prototype.slice;
var concat = Array.prototype.concat;

var implementations = {
	'better-sqlite3': {
		connect: function () {return new (require('../.'))(path.join('temp', 'better-sqlite3.db'));},
		close: function () {return this.close();},
		run: function (SQL) {return this.prepare(SQL).run(concat.apply([], slice.call(arguments, 1)));}
	},
	'node-sqlite3': {
		connect: function () {return require('sqlite').open(path.join('temp', 'node-sqlite3.db'), {Promise: Promise});},
		close: function () {return this.close();},
		run: function (SQL) {return this.run.apply(this, concat.apply([SQL], slice.call(arguments, 1)));}
	}
};

module.exports = function () {
	var prototype = Object.create(null);
	var promiseTry = function (fn, ctx, args) {
		try {return Promise.resolve(fn.apply(ctx, args));}
		catch (ex) {return Promise.reject(ex);}
	};
	prototype.each = function (action) {
		var controller = this;
		var args = slice.call(arguments, 1);
		
		return Promise.all(Object.keys(implementations).map(function (key) {
			if (action === 'connect') {
				var after = function (result) {controller[key] = result;};
			}
			return promiseTry(implementations[key][action], controller[key], args).then(after);
		})).then(function () {});
	};
	return Object.create(prototype);
};
