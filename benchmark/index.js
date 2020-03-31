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
		`(${trial.columns.join(', ')})`,
		`(${trial.columns.join(',')})`,
		...trial.columns,
		...trial.customPragma,
	];
	return searchTerms.every(arg => terms.includes(arg));
};

const sortTrials = (a, b) => {
	const aRo = require(`./types/${a.type}`).readonly;
	const bRo = require(`./types/${b.type}`).readonly;
	if (typeof aRo !== 'boolean') throw new TypeError(`Missing readonly export in benchmark type ${a.type}`);
	if (typeof bRo !== 'boolean') throw new TypeError(`Missing readonly export in benchmark type ${b.type}`);
	return bRo - aRo;
};

const displayTrialName = (trial) => {
	if (trial.description) return console.log(clc.magenta(`--- ${trial.description} ---`));
	const name = `${trial.type} ${trial.table} (${trial.columns.join(', ')})`;
	const pragma = trial.customPragma.length ? ` | ${trial.customPragma.join('; ')}` : '';
	console.log(clc.magenta(name) + clc.yellow(pragma));
};

const createContext = (trial, driver) => {
	const tableInfo = Object.assign({}, tables.get(trial.table), { data: undefined });
	return JSON.stringify(Object.assign({}, trial, tableInfo, { driver, tables: [...tables.keys()] }));
};

const erase = () => {
	return clc.move(0, -1) + clc.erase.line;
};

// Determine which trials should be executed.
process.chdir(__dirname);
const trials = getTrials(process.argv.slice(2)).sort(sortTrials);
if (!trials.length) {
	console.log(clc.yellow('No matching benchmarks found!'));
	process.exit();
}

// Create the temporary database needed to run the benchmark trials.
console.log('Generating tables...');
const tables = require('./seed')();
process.stdout.write(erase());

// Execute each trial for each available driver.
const drivers = require('./drivers');
const nameLength = [...drivers.keys()].reduce((m, d) => Math.max(m, d.length), 0);
for (const trial of trials) {
	displayTrialName(trial);
	for (const driver of drivers.keys()) {
		const driverName = driver.padEnd(nameLength);
		const ctx = createContext(trial, driver);
		process.stdout.write(`${driver} (running...)\n`);
		try {
			const result = execFileSync('node', ['./benchmark.js', ctx], { stdio: 'pipe', encoding: 'utf8' });
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
