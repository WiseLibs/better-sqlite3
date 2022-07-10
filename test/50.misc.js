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

	it('stores booleans and ints as ints', function() {
		this.db.exec('create table test(a,b,c,d)');
		this.db.prepare('insert into test values(?,?,?,?)').run(false, true, 1, 2.1);
		const result = this.db.prepare('select * from test').all();
		expect(result).to.deep.equal([{a: 0, b: 1, c: 1, d: 2.1}]);
		const types = this.db.prepare('select typeof(a) a, typeof(b) b, typeof(c) c, typeof(d) d from test').all();
		expect(types).to.deep.equal([{a: "integer", b: "integer", c: "integer", d: "real"}]);
	});
});
