var sqlite3 = require('..'),
    assert = require('assert');

describe('buffer', function() {
    var db;
    // before(function() {
    // });

    it('should insert blobs', function(done) {
        db = new sqlite3.Database(':memory:');
        db.serialize(function () {

            db.run("CREATE TABLE lorem (info BLOB)");
            var stmt = db.prepare("INSERT INTO lorem VALUES (?)");

            stmt.on('error', function (err) {
                throw err;
            });

            var buff = new Buffer(2);
            stmt.run('a');
            stmt.finalize();
        });

        db.close(done);

    });
});
