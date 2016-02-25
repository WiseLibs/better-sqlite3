var sqlite3 = require('..');
var assert = require('assert');

describe('scheduling', function() {
    it('scheduling after the database was closed', function(done) {
        var db = new sqlite3.Database(':memory:');
        db.on('error', function(err) {
            assert.ok(err.message && err.message.indexOf("SQLITE_MISUSE: Database handle is closed") > -1);
            done();
        });

        db.close();
        db.run("CREATE TABLE foo (id int)");
    });


    it('scheduling a query with callback after the database was closed', function(done) {
        var db = new sqlite3.Database(':memory:');
        db.on('error', function(err) {
            assert.ok(false, 'Event was accidentally triggered');
        });

        db.close();
        db.run("CREATE TABLE foo (id int)", function(err) {
            assert.ok(err.message && err.message.indexOf("SQLITE_MISUSE: Database handle is closed") > -1);
            done();
        });
    });

    it('running a query after the database was closed', function(done) {
        var db = new sqlite3.Database(':memory:');

        var stmt = db.prepare("SELECT * FROM sqlite_master", function(err) {
            if (err) throw err;
            db.close(function(err) {
                assert.ok(err);
                assert.ok(err.message && err.message.indexOf("SQLITE_BUSY: unable to close due to") > -1);

                // Running a statement now should not fail.
                stmt.run(done);
            });
        });
    });
});
