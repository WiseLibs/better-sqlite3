var sqlite3 = require('..');
var assert = require('assert');

describe('data types', function() {
    var db;
    before(function(done) {
        db = new sqlite3.Database(':memory:');
        db.run("CREATE TABLE txt_table (txt TEXT)");
        db.run("CREATE TABLE int_table (int INTEGER)");
        db.run("CREATE TABLE flt_table (flt FLOAT)");
        db.wait(done);
    });

    beforeEach(function(done) {
        db.exec('DELETE FROM txt_table; DELETE FROM int_table; DELETE FROM flt_table;', done);
    });

    it('should serialize Date()', function(done) {
        var date = new Date();
        db.run("INSERT INTO int_table VALUES(?)", date, function (err) {
            if (err) throw err;
            db.get("SELECT int FROM int_table", function(err, row) {
                if (err) throw err;
                assert.equal(row.int, +date);
                done();
            });
        });
    });

    it('should serialize RegExp()', function(done) {
        var regexp = /^f\noo/;
        db.run("INSERT INTO txt_table VALUES(?)", regexp, function (err) {
            if (err) throw err;
            db.get("SELECT txt FROM txt_table", function(err, row) {
                if (err) throw err;
                assert.equal(row.txt, String(regexp));
                done();
            });
        });
    });

    [
        4294967296.249,
        Math.PI,
        3924729304762836.5,
        new Date().valueOf(),
        912667.394828365,
        2.3948728634826374e+83,
        9.293476892934982e+300,
        Infinity,
        -9.293476892934982e+300,
        -2.3948728634826374e+83,
        -Infinity
    ].forEach(function(flt) {
        it('should serialize float ' + flt, function(done) {
            db.run("INSERT INTO flt_table VALUES(?)", flt, function (err) {
                if (err) throw err;
                db.get("SELECT flt FROM flt_table", function(err, row) {
                    if (err) throw err;
                    assert.equal(row.flt, flt);
                    done();
                });
            });
        });
    });

    [
        4294967299,
        3924729304762836,
        new Date().valueOf(),
        2.3948728634826374e+83,
        9.293476892934982e+300,
        Infinity,
        -9.293476892934982e+300,
        -2.3948728634826374e+83,
        -Infinity
    ].forEach(function(integer) {
        it('should serialize integer ' + integer, function(done) {
            db.run("INSERT INTO int_table VALUES(?)", integer, function (err) {
                if (err) throw err;
                db.get("SELECT int AS integer FROM int_table", function(err, row) {
                    if (err) throw err;
                    assert.equal(row.integer, integer);
                    done();
                });
            });
        });
    });
});
