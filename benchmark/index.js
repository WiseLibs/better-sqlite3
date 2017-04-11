'use strict';
var path = require('path');
var fs = require('fs-extra');
var clc = require('cli-color');
var spawn = require('child_process').spawn;
var generateData = require('./generate-data');
process.chdir(path.dirname(__dirname));
process.on('SIGINT', exit);
process.on('SIGHUP', exit);
process.on('SIGTERM', exit);
var trials;

(function init() {
	fs.removeSync('temp/');
	fs.ensureDirSync('temp/');
	
	trials = getTrials();
	if (!trials.length) {
		console.log(clc.yellow('No matching benchmarks found!'));
		return exit();
	}
	
	console.log('Generating tables...');
	generateData().then(function () {
		console.log(clc.magenta('--- Benchmarks ---'));
		nextTrial();
	}, function (err) {
		console.log(clc.red(err && err.stack || err));
		exit(1);
	});
}());

function getTrials() {
	return process.argv.slice(2).reduce(filterByArgs, require('./trials'));
	
	function filterByArgs(trials, arg) {
		arg = arg.toLowerCase();
		return trials.filter(function (obj) {return valuesOf(obj).some(containsThis, arg);});
	}
	function valuesOf(obj) {
		return Object.keys(obj).map(function (key) {return String(this[key]);}, obj).join(',').toLowerCase().split(',');
	}
	function containsThis(str) {
		return str.indexOf(this) !== -1;
	}
}

function exit(code) {
	fs.removeSync('temp/');
	process.exit(typeof code === 'number' ? code : 0);
}

function nextTrial() {
	if (!trials.length) {
		console.log(clc.green('All benchmarks complete!'));
		return exit();
	}
	
	var trial = trials.shift();
	var type = trial.type;
	var size = trial.table.toLowerCase().indexOf('large') === -1 ? 'small' : 'large';
	var columns = trial.columns.join(',');
	console.log(clc.cyan([type, size, columns].join(' ')));
	
	var child = spawn('node', [path.join(__dirname, 'types', type), JSON.stringify(trial)], {stdio: 'inherit'});
	child.on('exit', function (code) {
		if (code !== 0) {
			console.log(clc.red('ERROR (probably out of memory)'));
		}
		setTimeout(nextTrial, 0);
	});
}
