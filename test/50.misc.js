'use strict';
const Database = require('../.');

describe('miscellaneous', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
	});
	afterEach(function () {
		this.db.close();
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
