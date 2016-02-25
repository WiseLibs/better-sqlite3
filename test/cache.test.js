var sqlite3 = require('..');
var assert = require('assert');
var helper = require('./support/helper');

describe('cache', function() {
    before(function() {
        helper.ensureExists('test/tmp');
    });

    it('should cache Database objects while opening', function(done) {
        var filename = 'test/tmp/test_cache.db';
        helper.deleteFile(filename);
        var opened1 = false, opened2 = false;
        var db1 = new sqlite3.cached.Database(filename, function(err) {
            if (err) throw err;
            opened1 = true;
            if (opened1 && opened2) done();
        });
        var db2 = new sqlite3.cached.Database(filename, function(err) {
            if (err) throw err;
            opened2 = true;
            if (opened1 && opened2) done();
        });
        assert.equal(db1, db2);
    });

    it('should cache Database objects after they are open', function(done) {
        var filename = 'test/tmp/test_cache2.db';
        helper.deleteFile(filename);
        var db1, db2;
        db1 = new sqlite3.cached.Database(filename, function(err) {
            if (err) throw err;
            process.nextTick(function() {
                db2 = new sqlite3.cached.Database(filename, function(err) {
                    done();

                });
                assert.equal(db1, db2);
            });
        });
    });
});
