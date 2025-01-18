'use strict';
const Database = require('../.');

describe('miscellaneous', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
	});
	afterEach(function () {
		this.db.close();
	});

	it('supports LIMIT in DELETE statements', function () {
		this.db.prepare("CREATE TABLE foo (x INTEGER PRIMARY KEY)").run();
		expect(this.db.prepare('INSERT INTO foo (x) VALUES (1), (2), (3)').run())
			.to.deep.equal({ changes: 3, lastInsertRowid: 3 });

		expect(this.db.prepare('DELETE FROM foo ORDER BY x ASC LIMIT 1').run())
			.to.have.property('changes', 1);

		expect(this.db.prepare('SELECT x FROM foo ORDER BY x ASC').all())
			.to.deep.equal([{ x: 2 }, { x: 3 }]);
	});

	it('supports LIMIT in UPDATE statements', function () {
		this.db.prepare("CREATE TABLE foo (x INTEGER PRIMARY KEY, y INTEGER)").run();
		expect(this.db.prepare('INSERT INTO foo (x, y) VALUES (1, 1), (2, 2), (3, 3)').run())
			.to.deep.equal({ changes: 3, lastInsertRowid: 3 });

		expect(this.db.prepare('UPDATE foo SET y = 100 ORDER BY x DESC LIMIT 2').run())
			.to.have.property('changes', 2);

		expect(this.db.prepare('SELECT x, y FROM foo ORDER BY x ASC').all())
			.to.deep.equal([{ x: 1, y: 1 }, { x: 2, y: 100 }, { x: 3, y: 100 }]);
	});

	it('persists non-trivial quantities of reads and writes', function () {
		const runDuration = 1000;
		const runUntil = Date.now() + runDuration;
		this.slow(runDuration * 10);
		this.timeout(runDuration * 3);
		this.db.pragma("journal_mode = WAL");
		this.db.prepare("CREATE TABLE foo (a INTEGER, b TEXT, c REAL)").run();

		let i = 1;
		const r = 0.141592654;
		const insert = this.db.prepare("INSERT INTO foo VALUES (?, ?, ?)");
		const insertMany = this.db.transaction((count) => {
			for (const end = i + count; i < end; ++i) {
				expect(insert.run(i, String(i), i + r))
					.to.deep.equal({ changes: 1, lastInsertRowid: i });
			}
		});

		// Batched transactions of 100 inserts.
		while (Date.now() < runUntil) insertMany(100);

		// Expect 10K~50K on reasonable machines.
		expect(i).to.be.above(1000);

		const select = this.db.prepare("SELECT * FROM foo ORDER BY a DESC");
		for (const row of select.iterate()) {
			i -= 1;
			expect(row).to.deep.equal({ a: i, b: String(i), c: i + r });
		}

		expect(i).to.equal(1);
	});
});
