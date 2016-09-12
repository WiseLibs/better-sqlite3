'use strict';
var path = require('path');
var fs = require('fs-extra');
var clc = require('cli-color');
var spawn = require('child_process').spawn;
process.chdir(path.dirname(__dirname));

fs.removeSync('temp/');
fs.ensureDirSync('temp/');

process.on('SIGINT', function () {fs.removeSync('temp/'); process.exit();});
process.on('SIGHUP', function () {fs.removeSync('temp/'); process.exit();});
process.on('SIGTERM', function () {fs.removeSync('temp/'); process.exit();});

var trials = fs.readdirSync(path.join(__dirname, 'trials')).filter(function (name) {return name[0] !== '.';});
if (!trials.length) {
	console.log(clc.yellow('No benchmarks exist!'));
	fs.removeSync('temp/');
	process.exit();
}

console.log('Generating tables...');

var createdCount = 0;
function created() {
	if (++createdCount === 2) {
		console.log(clc.magenta('--- Benchmarks ---'));
		next();
	}
}

require('./create-table')('CREATE TABLE entries (aaaa TEXT, bbbb INTEGER, cccc FLOAT, dddd TEXT, eeee INTEGER, ffff BLOB)', 'select-db', function (ourDb, theirDb) {
	var values = [
		'John Smith',
		524,
		0.324176234,
		'New York City',
		20,
		Buffer.alloc(1024 * 1024).fill(0xdd)
	];
	var filledCount = 0;
	function filled() {++filledCount === 2 && created();}
	require('./fill-table')(ourDb, 1000, 'INSERT INTO entries VALUES (?, ?, ?, ?, ?, ?)', values, filled);
	require('./fill-table')(theirDb, 1000, 'INSERT INTO entries VALUES (?, ?, ?, ?, ?, ?)', values, filled);
});
require('./create-table')('CREATE TABLE entries (name TEXT, number INTEGER, data BLOB)', 'insert-db', created);

function next() {
	if (!trials.length) {
		console.log(clc.green('All benchmarks complete!'));
		fs.removeSync('temp/');
		process.exit();
	}
	
	var trialName = trials.shift();
	
	console.log(clc.cyan(trialName));
	var child = spawn('node', ['--expose-gc', path.join(__dirname, 'trials', trialName)], {stdio: 'inherit'});
	child.on('exit', function () {setTimeout(next, 100);});
}
