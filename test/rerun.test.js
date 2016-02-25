var sqlite3 = require('..');
var assert = require('assert');

describe('rerunning statements', function() {
    var db;
    before(function(done) { db = new sqlite3.Database(':memory:', done); });

    var count = 10;
    var inserted = 0;
    var retrieved = 0;

    it('should create the table', function(done) {
        db.run("CREATE TABLE foo (id int)", done);
    });

    it('should insert repeatedly, reusing the same statement', function(done) {
        var stmt = db.prepare("INSERT INTO foo VALUES(?)");
        for (var i = 5; i < count; i++) {
            stmt.run(i, function(err) {
                if (err) throw err;
                inserted++;
            });
        }
        stmt.finalize(done);
    });

    it('should retrieve repeatedly, resuing the same statement', function(done) {
        var collected = [];
        var stmt = db.prepare("SELECT id FROM foo WHERE id = ?");
        for (var i = 0; i < count; i++) {
            stmt.get(i, function(err, row) {
                if (err) throw err;
                if (row) collected.push(row);
            });
        }
        stmt.finalize(function(err) {
            if (err) throw err;
            retrieved += collected.length;
            assert.deepEqual(collected, [ { id: 5 }, { id: 6 }, { id: 7 }, { id: 8 }, { id: 9 } ]);
            done();
        });
    });

    it('should have inserted and retrieved the right amount', function() {
        assert.equal(inserted, 5);
        assert.equal(retrieved, 5);
    });

    after(function(done) { db.close(done); });
});
