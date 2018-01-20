'use strict';
const Benchmark = require('benchmark');
const dbs = require('./implementations')();
const trial = JSON.parse(process.argv[2]);

module.exports = (callback, multiplier = 1) => {
	// Setup the benchmark suite.
	const suite = new Benchmark.Suite;
	const addBenchmark = suite.add;
	suite.add = function (name, fn) {
		const options = { maxTime: 0.5, defer: fn.length !== 0 };
		return addBenchmark.call(this, pad(name, 14), fn, options);
	};
	suite.on('cycle', (ev) => {
		ev.target.hz *= multiplier;
		console.log(String(ev.target));
	});
	
	// Run this process' trial within the benchmark suite.
	dbs.each('connect')
		.then(() => runPragmas(trial.pragma || []))
		.then(() => {
			suite.on('complete', () => void dbs.each('close'));
			setImmediate(() => {
				callback(suite, dbs, trial); // Load trial to bootstrap benchmarks
				suite.run({ async: true });
			});
		}, (err) => {
			console.log(err && err.stack || err);
			process.exit(1);
		});
};

const runPragmas = strings => strings
	.reduce((previous, SQL) => previous.then(() => dbs.each('run', `PRAGMA ${SQL}`)), Promise.resolve());

const pad = (str, length) => {
	while (str.length < length) str = str + ' ';
	return str;
};
