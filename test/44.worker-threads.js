'use strict';
if (parseInt(process.versions.node) >= 12) {
	const threads = require('worker_threads');
	const Database = require('../.');

	if (threads.isMainThread) {
		describe('Worker Threads', function () {
			afterEach(function () {
				return this.cleanup;
			});
			it('are properly supported', function () {
				this.slow(1000);
				return new Promise((resolve, reject) => {
					const db = Database(util.next()).defaultSafeIntegers();
					expect(db.prepare('select 555').constructor.foo).to.be.undefined;
					db.prepare('select 555').constructor.foo = 5;
					expect(db.prepare('select 555').constructor.foo).to.equal(5);
					const worker = new threads.Worker(__filename);
					worker.on('exit', code => reject(new Error(`worker exited with code ${code}`)));
					worker.on('error', reject);
					worker.on('message', ({ msg, info, data }) => {
						try {
							if (msg === 'hello') {
								db.exec('create table data (a, b)');
								worker.postMessage({ msg: 'hello', filename: util.current() });
							} else if (msg === 'success') {
								const checkedData = db.prepare("select * from data").all();
								expect(info.changes).to.equal(checkedData.length);
								expect(data).to.not.equal(checkedData);
								expect(data).to.deep.equal(checkedData);
								expect(db.prepare('select 555').constructor.foo).to.equal(5);
								resolve();
								this.cleanup = worker.terminate();
							} else {
								throw new Error('unexpected message from worker');
							}
						} catch (err) {
							reject(err);
							this.cleanup = worker.terminate();
						}
					});
				});
			});
		});
	} else {
		const { expect } = require('chai');
		threads.parentPort.on('message', ({ msg, filename }) => {
			if (msg === 'hello') {
				const db = Database(filename).defaultSafeIntegers();
				expect(db.prepare('select 555').constructor.foo).to.be.undefined;
				db.prepare('select 555').constructor.foo = 27;
				expect(db.prepare('select 555').constructor.foo).to.equal(27);
				const info = db.prepare("insert into data values (1, 2), ('foo', 5.5)").run();
				const data = db.prepare("select * from data").all();
				expect(info.changes).to.be.a('number');
				expect(info.lastInsertRowid).to.be.a('bigint');
				expect(data.length).to.equal(2);
				threads.parentPort.postMessage({ msg: 'success', info, data });
			} else {
				throw new Error('unexpected message from main thread');
			}
		});
		threads.parentPort.postMessage({ msg: 'hello' });
	}
}
