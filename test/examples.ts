// NOTE: this file is only used to validate `index.d.ts`
// (and if `tsc` compiles this file, the "tests pass")

// ALSO NOTE: most of the type assertions are not necessary in this file and
// certainly do not reflect idiomatic typescript use--they're their to assert
// the type is what I expect it to be.

import * as b from "..";

const db = new b.Database("file.db");
new b.Database("mem.db", { memory: true });
new b.Database("ro.db", { readonly: true });

const begin: b.Statement = db.prepare("BEGIN");
const commit: b.Statement = db.prepare("COMMIT");
const rollback: b.Statement = db.prepare("ROLLBACK");

// Higher order function - returns a function that always runs in a transaction
export function withTransaction<T, R>(f: (...args: T[]) => R) {
  return (...args: T[]) => {
    begin.run();
    try {
      const result = f(...args);
      commit.run();
      return result;
    } finally {
      if (db.inTransaction) {
        rollback.run();
      }
    }
  };
}

const s: string = db.name;
const m: boolean = db.memory;
const r: boolean = db.readonly;
const o: boolean = db.open;
const i: boolean = db.inTransaction;
const t: b.Transaction = db.transaction([]);
const p: any = db.pragma("");
const chkpt: b.Database = db.checkpoint();
const re: b.Database = db.register(() => undefined);
const e: b.Database = db.exec("select 1");
const c: b.Database = db.close();

const stmt: b.Statement = db.prepare("insert into table values(:a, :b)");
stmt.bind({a: "a", b: "b"});
stmt.bind(1, 2);
stmt.bind([1, 2]);
stmt.pluck();
const changes: number = stmt.run().changes;
const rowid: number = stmt.run().lastInsertROWID;
const all: b.Row[] = stmt.all();
