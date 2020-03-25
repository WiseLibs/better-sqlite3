'use strict'
const Database = require('../.');

// writing to a table while reading the same table within an iterator.
function writeWhileIterating(db) {
  // create table & prepared statements
  db.prepare(`CREATE TABLE test (a TEXT)`).run();
  const stmt = {
    insert: db.prepare(`INSERT INTO test VALUES (?)`),
    each: db.prepare(`SELECT * FROM test WHERE a == 'FOO'`)
  };

  // populate table with two FOO values
  stmt.insert.run('FOO');
  stmt.insert.run('FOO');

  // iterate and insert from/to the same table at the same time
  // note: we insert 'BAR' which is not matched by the iterator.
  // warning: this is unsafe, if you insert 'FOO' here then the
  // database connection will hang forever, you were warned!
  for (let _ of stmt.each.iterate()) {
    stmt.insert.run('BAR');
  }
};

describe('unsafe mode', () => {
  afterEach(() => {
    if (this.db) this.db.close();
  });

  it('disabled: writeWhileIterating', () => {
    this.db = new Database(util.next(), { unsafe: false });
    expect(this.db.unsafe).to.be.false;
    expect(() => {
      writeWhileIterating(this.db);
    }).to.throw(TypeError);
  });
  it('enabled: writeWhileIterating', () => {
    this.db = new Database(util.next(), { unsafe: true });
    expect(this.db.unsafe).to.be.true;
    expect(() => {
      writeWhileIterating(this.db);
    }).not.throw();
    const aggs = this.db.prepare(`SELECT a, COUNT(a) AS total FROM test GROUP BY a`).all();
    expect(aggs).to.eql([
      { a: 'BAR', total: 2 }, // two 'BAR' rows
      { a: 'FOO', total: 2 }  // two 'FOO' rows
    ]);
  });
});
