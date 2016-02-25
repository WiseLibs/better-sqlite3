var sqlite3 = require('..');
var assert = require('assert');
var fs = require('fs');
var helper = require('./support/helper');

describe('open/close', function() {
    before(function() {
        helper.ensureExists('test/tmp');
    });

    describe('open and close non-existant database', function() {
        before(function() {
            helper.deleteFile('test/tmp/test_create.db');
        });

        var db;
        it('should open the database', function(done) {
            db = new sqlite3.Database('test/tmp/test_create.db', done);
        });

        it('should close the database', function(done) {
            db.close(done);
        });

        it('should have created the file', function() {
            assert.fileExists('test/tmp/test_create.db');
        });

        after(function() {
            helper.deleteFile('test/tmp/test_create.db');
        });
    });

    it('should not be unable to open an inaccessible database', function(done) {
        // NOTE: test assumes that the user is not allowed to create new files
        // in /usr/bin.
        var db = new sqlite3.Database('/test/tmp/directory-does-not-exist/test.db', function(err) {
            if (err && err.errno === sqlite3.CANTOPEN) {
                done();
            } else if (err) {
                done(err);
            } else {
                done('Opened database that should be inaccessible');
            }
        });
    });


    describe('creating database without create flag', function() {
        before(function() {
            helper.deleteFile('test/tmp/test_readonly.db');
        });

        it('should fail to open the database', function(done) {
            new sqlite3.Database('tmp/test_readonly.db', sqlite3.OPEN_READONLY, function(err) {
                if (err && err.errno === sqlite3.CANTOPEN) {
                    done();
                } else if (err) {
                    done(err);
                } else {
                    done('Created database without create flag');
                }
            });
        });

        it('should not have created the file', function() {
            assert.fileDoesNotExist('test/tmp/test_readonly.db');
        });

        after(function() {
            helper.deleteFile('test/tmp/test_readonly.db');
        });
    });

    describe('open and close memory database queuing', function() {
        var db;
        it('should open the database', function(done) {
            db = new sqlite3.Database(':memory:', done);
        });

        it('should close the database', function(done) {
            db.close(done);
        });

        it('shouldn\'t close the database again', function(done) {
            db.close(function(err) {
                assert.ok(err, 'No error object received on second close');
                assert.ok(err.errno === sqlite3.MISUSE);
                done();
            });
        });
    });

    describe('closing with unfinalized statements', function(done) {
        var completed = false;
        var completedSecond = false;
        var closed = false;

        var db;
        before(function() {
            db = new sqlite3.Database(':memory:', done);
        });

        it('should create a table', function(done) {
            db.run("CREATE TABLE foo (id INT, num INT)", done);
        });

        var stmt;
        it('should prepare/run a statement', function(done) {
            stmt = db.prepare('INSERT INTO foo VALUES (?, ?)');
            stmt.run(1, 2, done);
        });

        it('should fail to close the database', function(done) {
            db.close(function(err) {
                assert.ok(err.message,
                    "SQLITE_BUSY: unable to close due to unfinalised statements");
                done();
            });
        });

        it('should succeed to close the database after finalizing', function(done) {
            stmt.run(3, 4, function() {
                stmt.finalize();
                db.close(done);
            });
        });
    });
});
