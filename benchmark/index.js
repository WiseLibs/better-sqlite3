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
	if (++createdCount === 8) {
		console.log(clc.magenta('--- Benchmarks ---'));
		next();
	}
}

require('./create-table')('CREATE TABLE entries (text TEXT, integer INTEGER, real REAL, blob BLOB, nul)', 'select-small', fillSmallDataTable);
require('./create-table')('CREATE TABLE entries (text TEXT, blob BLOB)', 'select-large', function (ourDb, theirDb) {
	var bigString = '';
	while (bigString.length < 1024 * 1024) {
		bigString += 'John Peter Smith';
	}
	var values = {
		a: bigString,
		b: Buffer.alloc(1024 * 1024).fill(0xdd)
	};
	var filledCount = 0;
	function filled() {++filledCount === 2 && created();}
	require('./fill-table')(ourDb, 1000, 'INSERT INTO entries VALUES (@a, @b)', values, filled);
	require('./fill-table')(theirDb, 1000, 'INSERT INTO entries VALUES (@a, @b)', values, filled);
});
require('./create-table')('CREATE TABLE entries (data TEXT)', 'insert-text', created);
require('./create-table')('CREATE TABLE entries (data INTEGER)', 'insert-integer', created);
require('./create-table')('CREATE TABLE entries (data REAL)', 'insert-real', created);
require('./create-table')('CREATE TABLE entries (data BLOB)', 'insert-blob', created);
require('./create-table')('CREATE TABLE entries (data)', 'insert-null', created);
require('./create-table')('CREATE TABLE entries (text TEXT, integer INTEGER, real REAL, blob BLOB, nul)', 'real-world', fillSmallDataTable);

function fillSmallDataTable(ourDb, theirDb) {
	var values = {
		a: 'John Peter Smith',
		b: 12345,
		c: 0.12345,
		d: Buffer.alloc(16).fill(0xdd),
		e: null
	};
	var filledCount = 0;
	function filled() {++filledCount === 2 && created();}
	require('./fill-table')(ourDb, 1000, 'INSERT INTO entries VALUES (@a, @b, @c, @d, @e)', values, filled);
	require('./fill-table')(theirDb, 1000, 'INSERT INTO entries VALUES (@a, @b, @c, @d, @e)', values, filled);
}

function next() {
	if (!trials.length) {
		console.log(clc.green('All benchmarks complete!'));
		fs.removeSync('temp/');
		process.exit();
	}
	
	var trialName = trials.shift();
	
	console.log(clc.cyan(trialName));
	var child = spawn('node', ['--expose-gc', path.join(__dirname, 'trials', trialName)], {stdio: 'inherit'});
	child.on('exit', function (code) {
		if (code !== 0) {
			console.log(clc.red('ERROR (code ' + code + '), probably out of memory'));
		}
		setTimeout(next, 100);
	});
}
