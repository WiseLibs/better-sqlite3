'use strict';
const fs = require('fs');
const path = require('path');
const Database = require('../.');

describe('integrity checks', function () {
	beforeEach(function () {
		let func = () => {};
		this.useFunc = fn => { func = fn; };
		this.db = new Database(util.next());
		this.db.prepare("CREATE TABLE entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)").run();
		this.db.prepare("INSERT INTO entries WITH RECURSIVE temp(a, b, c, d, e) AS (SELECT 'foo', 1, 3.14, x'dddddddd', NULL UNION ALL SELECT a, b + 1, c, d, e FROM temp LIMIT 5) SELECT * FROM temp").run();
		this.db.function('func', x => (func(), x));
		this.iterator = this.db.prepare("SELECT func(b) from entries ORDER BY rowid");
		this.reader = this.db.prepare("SELECT func(b) from entries ORDER BY rowid");
		this.writer = this.db.prepare("UPDATE entries SET c = c + 2.718")
	});
	afterEach(function () {
		this.db.close();
	});

	const allowed = fn => () => expect(fn).to.not.throw();
	const blocked = fn => () => expect(fn).to.throw(TypeError);
	const normally = fn => fn();
	const whileIterating = (self, fn) => {
		let count = 0;
		for (const _ of self.iterator.iterate()) { count += 1; fn(); }
		expect(count).to.equal(5);
	};
	const whileBusy = (self, fn) => {
		let count = 0;
		self.useFunc(() => { count += 1; fn(); });
		self.iterator.all();
		expect(count).to.equal(5);
	};
	const whileClosed = (self, fn) => {
		self.db.close();
		fn();
	};

	describe('Database#prepare()', function () {
		specify('while iterating (allowed)', function () {
			whileIterating(this, allowed(() => this.db.prepare('SELECT 555')));
			whileIterating(this, allowed(() => this.db.prepare('DELETE FROM entries')));
			normally(allowed(() => this.db.prepare('SELECT 555')));
			normally(allowed(() => this.db.prepare('DELETE FROM entries')));
		});
		specify('while busy (blocked)', function () {
			whileBusy(this, blocked(() => this.db.prepare('SELECT 555')));
			whileBusy(this, blocked(() => this.db.prepare('DELETE FROM entries')));
			normally(allowed(() => this.db.prepare('SELECT 555')));
			normally(allowed(() => this.db.prepare('DELETE FROM entries')));
		});
		specify('while closed (blocked)', function () {
			whileClosed(this, blocked(() => this.db.prepare('SELECT 555')));
			whileClosed(this, blocked(() => this.db.prepare('DELETE FROM entries')));
		});
	});

	describe('Database#exec()', function () {
		specify('while iterating (blocked)', function () {
			whileIterating(this, blocked(() => this.db.exec('SELECT 555')));
			whileIterating(this, blocked(() => this.db.exec('DELETE FROM entries')));
			normally(allowed(() => this.db.exec('SELECT 555')));
			normally(allowed(() => this.db.exec('DELETE FROM entries')));
		});
		specify('while busy (blocked)', function () {
			whileBusy(this, blocked(() => this.db.exec('SELECT 555')));
			whileBusy(this, blocked(() => this.db.exec('DELETE FROM entries')));
			normally(allowed(() => this.db.exec('SELECT 555')));
			normally(allowed(() => this.db.exec('DELETE FROM entries')));
		});
		specify('while closed (blocked)', function () {
			whileClosed(this, blocked(() => this.db.exec('SELECT 555')));
			whileClosed(this, blocked(() => this.db.exec('DELETE FROM entries')));
		});
	});

	describe('Database#pragma()', function () {
		specify('while iterating (blocked)', function () {
			whileIterating(this, blocked(() => this.db.pragma('cache_size')));
			normally(allowed(() => this.db.pragma('cache_size')));
		});
		specify('while busy (blocked)', function () {
			whileBusy(this, blocked(() => this.db.pragma('cache_size')));
			normally(allowed(() => this.db.pragma('cache_size')));
		});
		specify('while closed (blocked)', function () {
			whileClosed(this, blocked(() => this.db.pragma('cache_size')));
		});
	});

	describe('Database#checkpoint()', function () {
		specify('while iterating (blocked)', function () {
			whileIterating(this, blocked(() => this.db.checkpoint()));
			normally(allowed(() => this.db.checkpoint()));
		});
		specify('while busy (blocked)', function () {
			whileBusy(this, blocked(() => this.db.checkpoint()));
			normally(allowed(() => this.db.checkpoint()));
		});
		specify('while closed (blocked)', function () {
			whileClosed(this, blocked(() => this.db.checkpoint()));
		});
	});

	describe('Database#backup()', function () {
		specify('while iterating (allowed)', async function () {
			const promises = [];
			whileIterating(this, allowed(() => promises.push(this.db.backup(util.next()))));
			expect(promises.length).to.equal(5);
			return Promise.all(promises);
		});
		specify('while busy (allowed)', async function () {
			const promises = [];
			whileBusy(this, allowed(() => promises.push(this.db.backup(util.next()))));
			expect(promises.length).to.equal(5);
			return Promise.all(promises);
		});
		specify('while closed (blocked)', async function () {
			const promises = [];
			whileClosed(this, allowed(() => promises.push(this.db.backup(util.next()))));
			expect(promises.length).to.equal(1);
			return Promise.all(promises.map(p =>
				p.then(() => { throw new Error('Promise should have been rejected'); }, () => {})
			));
		});
	});

	describe('Database#function()', function () {
		specify('while iterating (blocked)', function () {
			let i = 0;
			whileIterating(this, blocked(() => this.db.function(`fn_${++i}`, () => {})));
			expect(i).to.equal(5);
			normally(allowed(() => this.db.function(`fn_${++i}`, () => {})));
		});
		specify('while busy (blocked)', function () {
			let i = 0;
			whileBusy(this, blocked(() => this.db.function(`fn_${++i}`, () => {})));
			expect(i).to.equal(5);
			normally(allowed(() => this.db.function(`fn_${++i}`, () => {})));
		});
		specify('while closed (blocked)', function () {
			let i = 0;
			whileClosed(this, blocked(() => this.db.function(`fn_${++i}`, () => {})));
			expect(i).to.equal(1);
		});
	});

	describe('Database#aggregate()', function () {
		specify('while iterating (blocked)', function () {
			let i = 0;
			whileIterating(this, blocked(() => this.db.aggregate(`agg_${++i}`, { step: () => {} })));
			expect(i).to.equal(5);
			normally(allowed(() => this.db.aggregate(`agg_${++i}`, { step: () => {} })));
		});
		specify('while busy (blocked)', function () {
			let i = 0;
			whileBusy(this, blocked(() => this.db.aggregate(`agg_${++i}`, { step: () => {} })));
			expect(i).to.equal(5);
			normally(allowed(() => this.db.aggregate(`agg_${++i}`, { step: () => {} })));
		});
		specify('while closed (blocked)', function () {
			let i = 0;
			whileClosed(this, blocked(() => this.db.aggregate(`agg_${++i}`, { step: () => {} })));
			expect(i).to.equal(1);
		});
	});

	describe('Database#loadExtension()', function () {
		let filepath;
		before(function () {
			const releaseFilepath = path.join(__dirname, '..', 'build', 'Release', 'test_extension.node');
			const debugFilepath = path.join(__dirname, '..', 'build', 'Debug', 'test_extension.node');
			try {
				fs.accessSync(releaseFilepath);
				filepath = releaseFilepath;
			} catch (_) {
				fs.accessSync(debugFilepath);
				filepath = debugFilepath;
			}
		});

		specify('while iterating (blocked)', function () {
			whileIterating(this, blocked(() => this.db.loadExtension(filepath)));
			normally(allowed(() => this.db.loadExtension(filepath)));
		});
		specify('while busy (blocked)', function () {
			whileBusy(this, blocked(() => this.db.loadExtension(filepath)));
			normally(allowed(() => this.db.loadExtension(filepath)));
		});
		specify('while closed (blocked)', function () {
			whileClosed(this, blocked(() => this.db.loadExtension(filepath)));
		});
	});

	describe('Database#close()', function () {
		specify('while iterating (blocked)', function () {
			whileIterating(this, blocked(() => this.db.close()));
			normally(allowed(() => this.db.close()));
		});
		specify('while busy (blocked)', function () {
			whileBusy(this, blocked(() => this.db.close()));
			normally(allowed(() => this.db.close()));
		});
		specify('while closed (allowed)', function () {
			whileClosed(this, allowed(() => this.db.close()));
		});
	});

	describe('Database#defaultSafeIntegers()', function () {
		specify('while iterating (allowed)', function () {
			let bool = true;
			whileIterating(this, allowed(() => this.db.defaultSafeIntegers(bool = !bool)));
		});
		specify('while busy (allowed)', function () {
			let bool = true;
			whileBusy(this, allowed(() => this.db.defaultSafeIntegers(bool = !bool)));
		});
		specify('while closed (allowed)', function () {
			let bool = true;
			whileClosed(this, allowed(() => this.db.defaultSafeIntegers(bool = !bool)));
		});
	});

	describe('Database#open', function () {
		specify('while iterating (allowed)', function () {
			whileIterating(this, allowed(() => expect(this.db.open).to.be.true));
		});
		specify('while busy (allowed)', function () {
			whileBusy(this, allowed(() => expect(this.db.open).to.be.true));
		});
		specify('while closed (allowed)', function () {
			whileClosed(this, allowed(() => expect(this.db.open).to.be.false));
		});
	});

	describe('Database#inTransaction', function () {
		specify('while iterating (allowed)', function () {
			this.db.exec('BEGIN');
			whileIterating(this, allowed(() => expect(this.db.inTransaction).to.be.true));
		});
		specify('while busy (allowed)', function () {
			this.db.exec('BEGIN');
			whileBusy(this, allowed(() => expect(this.db.inTransaction).to.be.true));
		});
		specify('while closed (allowed)', function () {
			this.db.exec('BEGIN');
			whileClosed(this, allowed(() => expect(this.db.inTransaction).to.be.false));
		});
	});

	describe('Statement#run()', function () {
		specify('while iterating (blocked)', function () {
			whileIterating(this, blocked(() => this.writer.run()));
			normally(allowed(() => this.writer.run()));
		});
		specify('while busy (blocked)', function () {
			whileBusy(this, blocked(() => this.writer.run()));
			normally(allowed(() => this.writer.run()));
		});
		specify('while closed (blocked)', function () {
			whileClosed(this, blocked(() => this.writer.run()));
		});
	});

	describe('Statement#get()', function () {
		specify('while iterating (allowed)', function () {
			whileIterating(this, allowed(() => this.reader.get()));
			normally(allowed(() => this.reader.get()));
		});
		specify('while self-iterating (blocked)', function () {
			whileIterating(this, blocked(() => this.iterator.get()));
			normally(allowed(() => this.iterator.get()));
		});
		specify('while busy (blocked)', function () {
			whileBusy(this, blocked(() => this.reader.get()));
			normally(allowed(() => this.reader.get()));
		});
		specify('while closed (blocked)', function () {
			whileClosed(this, blocked(() => this.reader.get()));
		});
	});

	describe('Statement#all()', function () {
		specify('while iterating (allowed)', function () {
			whileIterating(this, allowed(() => this.reader.all()));
			normally(allowed(() => this.reader.all()));
		});
		specify('while self-iterating (blocked)', function () {
			whileIterating(this, blocked(() => this.iterator.all()));
			normally(allowed(() => this.iterator.all()));
		});
		specify('while busy (blocked)', function () {
			whileBusy(this, blocked(() => this.reader.all()));
			normally(allowed(() => this.reader.all()));
		});
		specify('while closed (blocked)', function () {
			whileClosed(this, blocked(() => this.reader.all()));
		});
	});

	describe('Statement#iterate()', function () {
		specify('while iterating (allowed)', function () {
			whileIterating(this, allowed(() => Array.from(this.reader.iterate())));
			normally(allowed(() => Array.from(this.reader.iterate())));
		});
		specify('while self-iterating (blocked)', function () {
			whileIterating(this, blocked(() => Array.from(this.iterator.iterate())));
			normally(allowed(() => Array.from(this.iterator.iterate())));
		});
		specify('while busy (blocked)', function () {
			whileBusy(this, blocked(() => Array.from(this.reader.iterate())));
			normally(allowed(() => Array.from(this.reader.iterate())));
		});
		specify('while closed (blocked)', function () {
			whileClosed(this, blocked(() => Array.from(this.reader.iterate())));
		});
	});

	describe('Statement#bind()', function () {
		const bind = (stmt) => {
			if (!stmt.__bound) {
				stmt.bind();
				stmt.__bound = true;
			}
		};
		specify('while iterating (allowed)', function () {
			whileIterating(this, allowed(() => bind(this.reader)));
		});
		specify('while self-iterating (blocked)', function () {
			whileIterating(this, blocked(() => bind(this.iterator)));
			normally(allowed(() => bind(this.iterator)));
		});
		specify('while busy (blocked)', function () {
			whileBusy(this, blocked(() => bind(this.reader)));
			normally(allowed(() => bind(this.reader)));
		});
		specify('while closed (blocked)', function () {
			whileClosed(this, blocked(() => bind(this.reader)));
		});
	});

	describe('Statement#pluck()', function () {
		specify('while iterating (allowed)', function () {
			whileIterating(this, allowed(() => this.reader.pluck()));
			normally(allowed(() => this.reader.pluck()));
		});
		specify('while self-iterating (blocked)', function () {
			whileIterating(this, blocked(() => this.iterator.pluck()));
			normally(allowed(() => this.iterator.pluck()));
		});
		specify('while busy (blocked)', function () {
			whileBusy(this, blocked(() => this.reader.pluck()));
			normally(allowed(() => this.reader.pluck()));
		});
		specify('while closed (allowed)', function () {
			whileClosed(this, allowed(() => this.reader.pluck()));
		});
	});

	describe('Statement#expand()', function () {
		specify('while iterating (allowed)', function () {
			whileIterating(this, allowed(() => this.reader.expand()));
			normally(allowed(() => this.reader.expand()));
		});
		specify('while self-iterating (blocked)', function () {
			whileIterating(this, blocked(() => this.iterator.expand()));
			normally(allowed(() => this.iterator.expand()));
		});
		specify('while busy (blocked)', function () {
			whileBusy(this, blocked(() => this.reader.expand()));
			normally(allowed(() => this.reader.expand()));
		});
		specify('while closed (allowed)', function () {
			whileClosed(this, allowed(() => this.reader.expand()));
		});
	});

	describe('Statement#raw()', function () {
		specify('while iterating (allowed)', function () {
			whileIterating(this, allowed(() => this.reader.raw()));
			normally(allowed(() => this.reader.raw()));
		});
		specify('while self-iterating (blocked)', function () {
			whileIterating(this, blocked(() => this.iterator.raw()));
			normally(allowed(() => this.iterator.raw()));
		});
		specify('while busy (blocked)', function () {
			whileBusy(this, blocked(() => this.reader.raw()));
			normally(allowed(() => this.reader.raw()));
		});
		specify('while closed (allowed)', function () {
			whileClosed(this, allowed(() => this.reader.raw()));
		});
	});

	describe('Statement#safeIntegers()', function () {
		specify('while iterating (allowed)', function () {
			whileIterating(this, allowed(() => this.reader.safeIntegers()));
			normally(allowed(() => this.reader.safeIntegers()));
		});
		specify('while self-iterating (blocked)', function () {
			whileIterating(this, blocked(() => this.iterator.safeIntegers()));
			normally(allowed(() => this.iterator.safeIntegers()));
		});
		specify('while busy (blocked)', function () {
			whileBusy(this, blocked(() => this.reader.safeIntegers()));
			normally(allowed(() => this.reader.safeIntegers()));
		});
		specify('while closed (allowed)', function () {
			whileClosed(this, allowed(() => this.reader.safeIntegers()));
		});
	});

	describe('Statement#columns()', function () {
		specify('while iterating (allowed)', function () {
			whileIterating(this, allowed(() => this.reader.columns()));
			normally(allowed(() => this.reader.columns()));
		});
		specify('while self-iterating (allowed)', function () {
			whileIterating(this, allowed(() => this.iterator.columns()));
			normally(allowed(() => this.iterator.columns()));
		});
		specify('while busy (blocked)', function () {
			whileBusy(this, blocked(() => this.reader.columns()));
			normally(allowed(() => this.reader.columns()));
		});
		specify('while closed (blocked)', function () {
			whileClosed(this, blocked(() => this.reader.columns()));
		});
	});

	describe('StatementIterator#next()', function () {
		specify('while iterating (allowed)', function () {
			const iterator = this.reader.iterate();
			try {
				whileIterating(this, allowed(() => iterator.next()));
				normally(allowed(() => iterator.next()));
			} finally {
				iterator.return();
			}
		});
		specify('while self-iterating (allowed)', function () {
			const iterator = this.iterator.iterate();
			try {
				let count = 0;
				for (const _ of iterator) {
					count += 1;
					iterator.next();
				}
				expect(count).to.equal(3);
			} finally {
				iterator.return();
			}
		});
		specify('while busy (blocked)', function () {
			const iterator = this.reader.iterate();
			try {
				whileBusy(this, blocked(() => iterator.next()));
				normally(allowed(() => iterator.next()));
			} finally {
				iterator.return();
			}
		});
		specify('while closed (allowed)', function () {
			const iterator = this.reader.iterate();
			iterator.return();
			whileClosed(this, allowed(() => iterator.next()));
		});
	});

	describe('StatementIterator#return()', function () {
		specify('while iterating (allowed)', function () {
			const iterator = this.reader.iterate();
			try {
				whileIterating(this, allowed(() => iterator.return()));
				normally(allowed(() => iterator.return()));
			} finally {
				iterator.return();
			}
		});
		specify('while self-iterating (allowed)', function () {
			const iterator = this.iterator.iterate();
			try {
				let count = 0;
				for (const _ of iterator) {
					count += 1;
					iterator.return();
				}
				expect(count).to.equal(1);
			} finally {
				iterator.return();
			}
		});
		specify('while busy (blocked)', function () {
			const iterator = this.reader.iterate();
			try {
				whileBusy(this, blocked(() => iterator.return()));
				normally(allowed(() => iterator.return()));
			} finally {
				iterator.return();
			}
		});
		specify('while closed (allowed)', function () {
			const iterator = this.reader.iterate();
			iterator.return();
			whileClosed(this, allowed(() => iterator.return()));
		});
	});
});
