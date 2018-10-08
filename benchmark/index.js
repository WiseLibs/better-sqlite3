#!/usr/bin/env node
'use strict';
const { execFileSync } = require('child_process');
const clc = require('cli-color');

const getTrials = (searchTerms) => {
	// Without any command-line arguments, we do a general-purpose benchmark.
	if (!searchTerms.length) return require('./trials').default;
	
	// With command-line arguments, the user can run specific groups of trials.
	return require('./trials').searchable.filter(filterBySearchTerms(searchTerms));
};

const filterBySearchTerms = (searchTerms) => (trial) => {
	const terms = [
		trial.type,
		trial.table,
		trial.table.replace('_empty', ''),
		`(${trial.columns.join(', ')})`,
		`(${trial.columns.join(',')})`,
		...trial.columns,
		...trial.customPragma,
	];
	return searchTerms.every(arg => terms.includes(arg));
};

const displayTrialName = (trial) => {
	if (trial.description) return console.log(clc.magenta(`--- ${trial.description} ---`));
	const name = `${trial.type} ${trial.table} (${trial.columns.join(', ')})`;
	const pragma = trial.customPragma.length ? ` | ${trial.customPragma.join('; ')}` : '';
	console.log(clc.magenta(name) + clc.yellow(pragma));
};

const createContext = (trial, driver) => {
	const { data: _unused, ...tableInfo } = tables.get(trial.table);
	const ctx = { ...trial, ...tableInfo, driver, filename: `../temp/${iteration++}.db` };
	return JSON.stringify(ctx);
};

const erase = () => {
	return clc.move(0, -1) + clc.erase.line;
};

// Determine which trials should be executed.
process.chdir(__dirname);
const trials = getTrials(process.argv.slice(2));
if (!trials.length) {
	console.log(clc.yellow('No matching benchmarks found!'));
	process.exit();
}

// Create the temporary databases needed to run the benchmark trials.
console.log('Generating tables...');
const drivers = require('./drivers');
const tables = require('./seed')(drivers.size * trials.length);
process.stdout.write(erase());

// Execute each trial for each available driver.
let iteration = 0;
const nameLength = [...drivers.keys()].reduce((m, d) => Math.max(m, d.length), 0);
for (const trial of trials) {
	displayTrialName(trial);
	for (const driver of drivers.keys()) {
		const driverName = driver.padEnd(nameLength);
		const ctx = createContext(trial, driver);
		process.stdout.write(`${driver} (running...)\n`);
		try {
			const result = execFileSync('./benchmark.js', [ctx], { stdio: 'pipe', encoding: 'utf8' });
			console.log(erase() + `${driverName} x ${result}`);
		} catch (err) {
			console.log(erase() + clc.red(`${driverName} ERROR (probably out of memory)`));
			process.stderr.write(clc.xterm(247)(clc.strip(err.stderr)));
		}
	}
	console.log('');
}

console.log(clc.green('All benchmarks complete!'));
process.exit();
