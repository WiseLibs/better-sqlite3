'use strict';
const { existsSync, writeFileSync } = require('fs');
const { fork } = require('child_process');

describe('node::AtExit()', function () {
	this.slow(500);
	const source = (filename1, filename2) => `
		'use strict';
		const Database = require('../.');
		const db1 = new Database('${filename1.replace(/(?=\W)/g, '\\')}');
		const db2 = new Database('${filename2.replace(/(?=\W)/g, '\\')}');
		for (const db of [db1, db2]) {
			db.pragma('journal_mode = WAL');
			db.prepare('CREATE TABLE people (name TEXT)').run();
			db.prepare('INSERT INTO people VALUES (\\'foobar\\')').run();
		}
		const interval = setInterval(() => {}, 60000);
		const messageHandler = (message) => {
			if (message !== 'bar') return;
			clearInterval(interval);
			process.removeListener('message', messageHandler);
		};
		process.on('message', messageHandler);
		process.send('foo');
	`;

	it('should close all databases when the process exits gracefully', async function () {
		const filename1 = util.next();
		const filename2 = util.next();
		const jsFile = filename1 + '.js';
		writeFileSync(jsFile, source(filename1, filename2));
		await new Promise((resolve, reject) => {
			const child = fork(jsFile);
			child.on('error', reject);
			child.on('close', () => reject(new Error('Child process was closed prematurely')));
			child.on('message', (message) => {
				if (message !== 'foo') return;
				expect(existsSync(filename1)).to.be.true;
				expect(existsSync(filename1 + '-wal')).to.be.true;
				expect(existsSync(filename2)).to.be.true;
				expect(existsSync(filename2 + '-wal')).to.be.true;
				child.on('exit', resolve);
				child.send('bar');
			});
		});
		expect(existsSync(filename1)).to.be.true;
		expect(existsSync(filename1 + '-wal')).to.be.false;
		expect(existsSync(filename2)).to.be.true;
		expect(existsSync(filename2 + '-wal')).to.be.false;
	});
});
