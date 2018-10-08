#!/usr/bin/env node
'use strict';
const benchmark = require('nodemark');

const sync = (fn) => {
	const result = benchmark(fn);
	process.stdout.write(String(result).replace(/ \(.*/, ''));
	process.exit();
};

const async = (fn) => {
	const wrapped = cb => fn().then(() => cb(), cb);
	benchmark(wrapped).then((result) => {
		process.stdout.write(String(result).replace(/ \(.*/, ''));
		process.exit();
	});
};

(async () => {
	process.on('unhandledRejection', (err) => { throw err; });
	const ctx = JSON.parse(process.argv[2]);
	const db = await require('./drivers').get(ctx.driver)(ctx.filename, ctx.pragma);
	const fn = require(`./types/${ctx.type}`)[ctx.driver](db, ctx);
	if (typeof fn === 'function') setImmediate(sync, fn);
	else setImmediate(async, await fn);
})();
