'use strict';
const Database = require('../.');

describe('Database#serialization', function () {
  beforeEach(function () {
    this.db = new Database(util.next());
    this.db.prepare('CREATE TABLE entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)').run();
    this.db.prepare("INSERT INTO entries WITH RECURSIVE temp(a, b, c, d, e) AS (SELECT 'foo', 1, 3.14, x'dddddddd', NULL UNION ALL SELECT a, b + 1, c, d, e FROM temp LIMIT 10) SELECT * FROM temp").run();
  });
  afterEach(function () {
    this.db.close();
  });

  it('should be able to call serialize and deserialize', async function () {
    const row = { a: 'foo', b: 1, c: 3.14, d: Buffer.alloc(4).fill(0xdd), e: null };
    const stmt_sel = this.db.prepare("SELECT * FROM entries WHERE b > 5 ORDER BY rowid");
    const stmt_del = this.db.prepare("DELETE FROM entries");
    let all;

    // select all desired rows
    all = stmt_sel.all();
    expect(all.length).to.equal(5);
    matchesFrom(all, 6);

    // serialize DB into a buffer
    const data = this.db.serialize();
    expect(data).to.not.equal(null);
    expect(data.length > 0).to.equal(true);

    // delete all table rows
    stmt_del.run();

    // we should now have zero matching rows
    all = stmt_sel.all();
    expect(all.length).to.equal(0);

    // recover database from serialized buffer
    const ret = this.db.deserialize(data);
    expect(ret).to.equal(true);

    // check that we can again select all desired rows
    all = stmt_sel.all();
    expect(all.length).to.equal(5);
    matchesFrom(all, 6);

    function matchesFrom(rows, i) {
      let index = 0;
      for (; i <= 10; ++i, ++index) {
        row.b = i;
        expect(rows[index]).to.deep.equal(row);
      }
      expect(index).to.equal(rows.length);
    }
  });
});
