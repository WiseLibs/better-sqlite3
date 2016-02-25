var sqlite3 = require('..');
var assert = require('assert');

describe('fts', function() {
    var db;
    before(function(done) {
        db = new sqlite3.Database(':memory:', done);
    });

    it('should create a new fts4 table', function(done) {
        db.exec('CREATE VIRTUAL TABLE t1 USING fts4(content="", a, b, c);', done);
    });
});
