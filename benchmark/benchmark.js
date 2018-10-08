#!/usr/bin/env node
'use strict';
process.on('unhandledRejection', (err) => { throw err; });


// const nodemark = require('nodemark');

// const sync = (fn) => {
// 	const result = nodemark(fn);
// 	process.stdout.write(String(result.hz()));
// 	process.exit();
// };

// const async = (fn) => {
// 	const wrapped = cb => fn().then(() => cb(), cb);
// 	nodemark(wrapped).then((result) => {
// 		process.stdout.write(String(result.hz()));
// 		process.exit();
// 	});
// };

// (async () => {
// 	const ctx = JSON.parse(process.argv[2]);
// 	const db = await require('./drivers').get(ctx.driver)(ctx.db, ctx.pragma);
// 	const promise = require(`./types/${ctx.type}`)[ctx.driver](db, ctx);
// 	const fn = await promise;
// 	if (typeof promise === 'function') setImmediate(sync, fn);
// 	else setImmediate(async, fn);
// })();


let fn;

let hz = 10;
let prevTick = 0;
let carryOver = 0;

let requestsOpen = 0;
let requestsFinished = 0;
let totalRequestsMade = 0;
let totalTimeWaited = 0;

const request = () => {
	const promise = fn();
	if (promise) promise.then(finishRequest);
	else finishRequest();
};

const finishRequest = () => {
	requestsFinished += 1;
};

const tick = () => {
	const currentTick = monoTime();
	const delta = currentTick - prevTick;
	const nspr = 1e9 / hz;
	const newRequests = Math.floor((delta + carryOver) / nspr);
	totalTimeWaited += delta * requestsOpen;
	requestsOpen -= requestsFinished;
	requestsFinished = 0;
	prevTick = currentTick;
	carryOver += delta - (newRequests * nspr);
	if (totalTimeWaited / totalRequestsMade > 3e7) {
		finish();
	}
	if (newRequests) {
		requestsOpen += newRequests;
		totalRequestsMade += newRequests;
		for (let i = 0; i < newRequests; ++i) request();
		hz += 1;
	}
	setImmediate(tick);
};

const monoTime = ((hrtime, [s, m]) => () => {
	const [seconds, milliseconds] = hrtime();
	return (seconds - s) * 1e9 + milliseconds - m;
})(process.hrtime, process.hrtime());

const finish = () => {
	process.stdout.write(String(hz));
	process.exit();
};

(async () => {
	const ctx = JSON.parse(process.argv[2]);
	const db = await require('./drivers').get(ctx.driver)(ctx.db, ctx.pragma);
	fn = await require(`./types/${ctx.type}`)[ctx.driver](db, ctx);
	prevTick = monoTime();
	setImmediate(tick);
})();
