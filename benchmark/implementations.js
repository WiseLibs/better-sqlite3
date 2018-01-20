'use strict';
const path = require('path');

const implementations = {
	'better-sqlite3': {
		connect: () => new (require('../.'))(path.join('temp', 'better-sqlite3.db')),
		close: function () { return this.close(); },
		run: function (SQL, ...args) { return this.prepare(SQL).run([].concat(...args)); },
	},
	'node-sqlite3': {
		connect: () => require('sqlite').open(path.join('temp', 'node-sqlite3.db'), { Promise }),
		close: function () { return this.close(); },
		run: function (SQL, ...args) { return this.run(...[SQL].concat(...args)); },
	},
};

module.exports = () => {
	const prototype = Object.create(null);
	const promiseTry = (fn, ctx, args) => {
		try { return Promise.resolve(fn.apply(ctx, args)); }
		catch (ex) { return Promise.reject(ex); }
	};
	prototype.each = function (action, ...args) {
		return Promise.all(Object.keys(implementations).map((key) => {
			const promise = promiseTry(implementations[key][action], this[key], args);
			if (action === 'connect') return promise.then((result) => { this[key] = result; });
			return promise;
		})).then(() => undefined);
	};
	return Object.create(prototype);
};
