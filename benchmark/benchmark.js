#!/usr/bin/env node
import process from "node:process";
import { setImmediate } from "node:timers";
import benchmark from 'nodemark';
import drivers from './drivers.js';
import types from './types/index.js';

const sync = (fn) => {
	display(benchmark(fn));
};

const async = (fn) => {
	const wrapped = cb => fn().then(() => cb(), cb);
	benchmark(wrapped).then(display);
};

const display = (result) => {
	process.stdout.write(String(result).replace(/ \(.*/, ''));
	process.exit();
};

(async () => {
	process.on('unhandledRejection', (err) => { throw err; });
	const ctx = JSON.parse(process.argv[2]);
	const type = types[ctx.type];
	const db = await drivers.get(ctx.driver)('../temp/benchmark.db', ctx.pragma);
	if (!type.readonly) {
		for (const table of ctx.tables) await db.exec(`DELETE FROM ${table} WHERE rowid > 1;`);
		await db.exec('VACUUM;');
	}
	const fn = type[ctx.driver](db, ctx);
	if (typeof fn === 'function') setImmediate(sync, fn);
	else setImmediate(async, await fn);
})();
