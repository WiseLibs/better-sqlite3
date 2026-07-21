'use strict';
const { expect } = require('chai');
const fs = require('fs');
const path = require('path');
const childProcess = require('child_process');

describe('entrypoints', function () {
	const target = `${process.platform}-${process.arch}`;
	const prebuild = path.join(__dirname, '..', 'prebuilds', `${target}.node`);
	let removePrebuild = false;

	before(function () {
		if (!fs.existsSync(prebuild)) {
			const configuration = fs.existsSync(path.join(__dirname, '..', 'build', 'Debug', 'better_sqlite3.node')) ? 'Debug' : 'Release';
			fs.mkdirSync(path.dirname(prebuild), { recursive: true });
			fs.copyFileSync(path.join(__dirname, '..', 'build', configuration, 'better_sqlite3.node'), prebuild);
			removePrebuild = true;
		}
	});

	after(function () {
		if (removePrebuild) fs.rmSync(prebuild);
	});

	it('publishes a statically-bound entrypoint for the current platform', function () {
		// Load the temporary prebuild in a child process. On Windows, a native
		// addon cannot be removed while the process that loaded it is running.
		const script = `const Database = require('./lib/${target}'); const db = new Database(':memory:'); try { process.stdout.write(JSON.stringify(db.prepare('SELECT 1 AS value').get())) } finally { db.close() }`;
		const result = childProcess.execFileSync(process.execPath, ['-e', script], { cwd: path.join(__dirname, '..'), encoding: 'utf8' });
		expect(JSON.parse(result)).to.deep.equal({ value: 1 });
	});

	it('rejects nativeBinding from statically-bound entrypoints', function () {
		const Database = require(`../lib/${target}`);
		expect(() => new Database(':memory:', { nativeBinding: {} })).to.throw(TypeError, 'only supported by the default');
	});

	it('keeps detection and compilation out of static entrypoint graphs', function () {
		const source = fs.readFileSync(path.join(__dirname, '..', 'lib', `${target}.js`), 'utf8');
		expect(source).not.to.include('./binding');
		const script = `require('./lib/${target}'); process.stdout.write(String(Object.keys(require.cache).some(x => x.endsWith('/lib/binding.js'))))`;
		expect(childProcess.execFileSync(process.execPath, ['-e', script], { cwd: path.join(__dirname, '..'), encoding: 'utf8' })).to.equal('false');
	});
});
