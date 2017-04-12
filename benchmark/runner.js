'use strict';
var Benchmark = require('benchmark');
var dbs = require('./implementations')();

module.exports = function (callback) {
	var trial = JSON.parse(process.argv[2]);
	
	var suite = new Benchmark.Suite;
	var addBenchmark = suite.add;
	suite.add = function (name, fn) {
		var options = {maxTime: 0.5};
		if (fn.length !== 0) {options.defer = true;}
		return addBenchmark.call(this, pad(name, 14), fn, options);
	};
	suite.on('cycle', function (ev) {
		console.log(String(ev.target));
	});
	
	dbs.each('connect').then(function () {
		return runPragmas(trial.pragma || []);
	}).then(function () {
		suite.on('complete', function () {dbs.each('close');});
		setImmediate(function () {
			callback(suite, dbs, trial);
			suite.run({async: true});
		});
	}, function (err) {
		console.log(err && err.stack || err);
		process.exit(1);
	});
};

function runPragmas(strings) {
	return strings.reduce(function (promise, SQL) {
		return promise.then(function () {return dbs.each('run', 'PRAGMA ' + SQL);});
	}, Promise.resolve());
}

function pad(str, length) {
	while (str.length < length) {str = str + ' ';}
	return str;
}
