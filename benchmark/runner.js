'use strict';
var Benchmark = require('benchmark');
var dbs = require('./implementations')();

module.exports = function (callback) {
	var trial = JSON.parse(process.argv[2]);
	
	var suite = new Benchmark.Suite;
	var addBenchmark = suite.add;
	suite.add = function (name, fn) {
		return addBenchmark.call(this, name, fn, {defer: true});
	};
	suite.on('cycle', function (ev) {
		console.log(String(ev.target));
	});
	
	dbs.each('connect').then(function () {
		suite.on('complete', function () {dbs.each('close').then(function () {console.log('closed!');});});
		setImmediate(function () {
			callback(suite, dbs, trial);
			suite.run({async: true});
		});
	}, function (err) {
		console.log(err && err.stack || err);
		process.exit(1);
	});
};
