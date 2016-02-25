var sqlite3 = require('..');

if( process.env.NODE_SQLITE3_JSON1 === 'no' ){
    describe('json', function() {
        it(
            'skips JSON tests when --sqlite=/usr (or similar) is tested',
            function(){}
        );
    });
} else {
    describe('json', function() {
        var db;

        before(function(done) {
            db = new sqlite3.Database(':memory:', done);
        });

        it('should select JSON', function(done) {
            db.run('SELECT json(?)', JSON.stringify({ok:true}), done);
        });
    });
}
