var sqlite3 = require('..');
var assert = require('assert');

describe('named parameters', function() {
    var db;
    before(function(done) {
        db = new sqlite3.Database(':memory:', done);
    });

    it('should create the table', function(done) {
        db.run("CREATE TABLE foo (txt TEXT, num INT)", done);
    });

    it('should insert a value with $ placeholders', function(done) {
        db.run("INSERT INTO foo VALUES($text, $id)", {
            $id: 1,
            $text: "Lorem Ipsum"
        }, done);
    });

    it('should insert a value with : placeholders', function(done) {
        db.run("INSERT INTO foo VALUES(:text, :id)", {
            ':id': 2,
            ':text': "Dolor Sit Amet"
        }, done);
    });

    it('should insert a value with @ placeholders', function(done) {
        db.run("INSERT INTO foo VALUES(@txt, @id)", {
            "@id": 3,
            "@txt": "Consectetur Adipiscing Elit"
        }, done);
    });

    it('should insert a value with @ placeholders using an array', function(done) {
        db.run("INSERT INTO foo VALUES(@txt, @id)", [ 'Sed Do Eiusmod', 4 ], done);
    });

    it('should insert a value with indexed placeholders', function(done) {
        db.run("INSERT INTO foo VALUES(?2, ?4)",
            [ null, 'Tempor Incididunt', null, 5 ], done);
    });

    it('should insert a value with autoindexed placeholders', function(done) {
        db.run("INSERT INTO foo VALUES(?, ?)", {
            2: 6,
            1: "Ut Labore Et Dolore"
        }, done);
    });

    it('should retrieve all inserted values', function(done) {
        db.all("SELECT txt, num FROM foo ORDER BY num", function(err, rows) {
            if (err) throw err;
            assert.equal(rows[0].txt, "Lorem Ipsum");
            assert.equal(rows[0].num, 1);
            assert.equal(rows[1].txt, "Dolor Sit Amet");
            assert.equal(rows[1].num, 2);
            assert.equal(rows[2].txt, "Consectetur Adipiscing Elit");
            assert.equal(rows[2].num, 3);
            assert.equal(rows[3].txt, "Sed Do Eiusmod");
            assert.equal(rows[3].num, 4);
            assert.equal(rows[4].txt, "Tempor Incididunt");
            assert.equal(rows[4].num, 5);
            assert.equal(rows[5].txt, "Ut Labore Et Dolore");
            assert.equal(rows[5].num, 6);
            done();
        });
    });
});
