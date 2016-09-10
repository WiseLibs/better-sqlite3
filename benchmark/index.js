'use strict';
var path = require('path');
var fs = require('fs-extra');
var clc = require('cli-color');
var spawn = require('child_process').spawn;

fs.removeSync(path.join(__dirname, '..', 'temp'));
fs.ensureDirSync(path.join(__dirname, '..', 'temp'));

var trials = fs.readdirSync(path.join(__dirname, 'trials'));
if (!trials.length) {
	console.log(clc.yellow('No benchmarks exist!'));
	process.exit();
}

console.log(clc.magenta('--- Benchmarks ---'));
;(function next() {
	if (!trials.length) {
		fs.removeSync(path.join(__dirname, '..', 'temp'));
		console.log(clc.green('All benchmarks complete!'));
		process.exit();
	}
	
	var trialName = trials.shift();
	
	console.log(clc.cyan(trialName));
	var child = spawn('node', ['--expose-gc', path.join(__dirname, 'trials', trialName)], {
		cwd: path.dirname(__dirname),
		stdio: 'inherit'
	});
	child.on('exit', function () {
		setTimeout(next, 100);
	});
}());
