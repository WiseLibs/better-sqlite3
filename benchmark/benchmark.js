#!/usr/bin/env node
'use strict';
const benchmark = require('nodemark');

const sync = (fn, multiplier) => {
	const wrapped = () => {
		for (let i = 0; i < multiplier; ++i) fn();
	};
	display(multiplier)(benchmark(wrapped));
};

const async = (fn, multiplier) => {
	const wrapped = (callback) => {
		const promises = [];
		for (let i = 0; i < multiplier; ++i) promises.push(fn());
		Promise.all(promises).then(() => callback(), callback);
	};
	benchmark(wrapped).then(display(multiplier));
};

const display = (multiplier) => (result) => {
	const hz = Math.round(1e9 / result.mean * multiplier);
	const error = Math.round(result.error * 10000) / 100;
	process.stdout.write(`${String(hz).replace(/\B(?=(?:\d{3})+$)/g, ',')} ops/sec \xb1${error}%`);
	process.exit();
};

(async () => {
	process.on('unhandledRejection', (err) => { throw err; });
	const concurrency = (process.env.CONCURRENCY >>> 0) || (process.env.UV_THREADPOOL_SIZE >>> 0) || 4;
	const ctx = JSON.parse(process.argv[2]);
	const db = await require('./drivers').get(ctx.driver)(ctx.filename, ctx.pragma);
	const fn = require(`./types/${ctx.type}`)[ctx.driver](db, ctx);
	if (typeof fn === 'function') setImmediate(sync, fn, concurrency);
	else setImmediate(async, await fn, concurrency);
})();
