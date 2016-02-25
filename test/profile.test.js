var sqlite3 = require('..');
var assert = require('assert');

describe('profiling', function() {
    var create = false;
    var select = false;

    var db;
    before(function(done) {
        db = new sqlite3.Database(':memory:', done);

        db.on('profile', function(sql, nsecs) {
            assert.ok(typeof nsecs === "number");
            if (sql.match(/^SELECT/)) {
                assert.ok(!select);
                assert.equal(sql, "SELECT * FROM foo");
                console.log('profile select');
                select = true;
            }
            else if (sql.match(/^CREATE/)) {
                assert.ok(!create);
                assert.equal(sql, "CREATE TABLE foo (id int)");
                create = true;
            }
            else {
                assert.ok(false);
            }
        });
    });

    it('should profile a create table', function(done) {
        assert.ok(!create);
        db.run("CREATE TABLE foo (id int)", function(err) {
            if (err) throw err;
            setImmediate(function() {
                assert.ok(create);
                done();
            });
        });
    });


    it('should profile a select', function(done) {
        assert.ok(!select);
        db.run("SELECT * FROM foo", function(err) {
            if (err) throw err;
            setImmediate(function() {
                assert.ok(select);
                done();
            }, 0);
        });
    });

    after(function(done) {
        db.close(done);
    });
});
