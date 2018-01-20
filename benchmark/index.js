'use strict';
const { spawn } = require('child_process');
const path = require('path');
const fs = require('fs-extra');
const clc = require('cli-color');
const factory = require('./factory');

process.chdir(path.dirname(__dirname));
process.on('SIGINT', exit);
process.on('SIGHUP', exit);
process.on('SIGTERM', exit);
let trials;

(function init() {
	fs.removeSync('temp/');
	fs.ensureDirSync('temp/');
	
	trials = getTrials();
	if (!trials.length) {
		console.log(clc.yellow('No matching benchmarks found!'));
		return exit();
	}
	
	console.log('Generating tables...');
	factory.buildTables().then(() => {
		console.log(clc.magenta('--- Benchmarks ---'));
		nextTrial();
	}, (err) => {
		console.log(clc.red(err && err.stack || err));
		exit(1);
	});
}());

function getTrials() {
	// Without any command-line arguments, we do a general-purpose benchmark.
	if (process.argv.length === 2) return require('./trials').default.map(addSearchTerms);
	
	// With command-line arguments, the user can run specific groups of trials.
	return process.argv.slice(2).reduce(filterByArgs, require('./trials').searchable.map(addSearchTerms));
	
	function addSearchTerms(trial) {
		const size = trial.table.toLowerCase().includes('large') ? 'large' : 'small';
		let columns = trial.columns.join(',').toLowerCase();
		if (trial.columns.length > 1) columns = `(${columns})`;
		trial.terms = [trial.type.toLowerCase(), size, columns];
		trial.looseTerms = (trial.pragma || []).filter(customPragma).join('; ').toLowerCase();
		return trial;
	}
	function filterByArgs(trials, arg) {
		arg = arg.toLowerCase();
		return trials.filter(obj => obj.terms.includes(arg) || obj.looseTerms.includes(arg));
	}
	function customPragma(str) {
		return !str.includes('cache_size') && !str.includes('synchronous');
	}
};

function exit(code) {
	fs.removeSync('temp/');
	process.exit(typeof code === 'number' ? code : 0);
}

function nextTrial() {
	if (!trials.length) {
		console.log(clc.green('All benchmarks complete!'));
		return exit();
	}
	
	// Consume the next trial and display its name.
	const trial = trials.shift();
	const extraName = trial.looseTerms ? clc.yellow(` | ${trial.looseTerms}`) : '';
	console.log(clc.cyan(trial.terms.join(' ')) + extraName);
	
	// Spawn each trial within its own process.
	const child = spawn('node', [path.join(__dirname, 'types', trial.type), JSON.stringify(trial)], { stdio: 'inherit' });
	child.on('exit', (code) => {
		if (code !== 0) console.log(clc.red('ERROR (probably out of memory)'));
		setTimeout(nextTrial, 0);
	});
}
