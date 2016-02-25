var sqlite3 = require('..');
var assert = require('assert');

describe('constants', function() {
    it('should have the right OPEN_* flags', function() {
        assert.ok(sqlite3.OPEN_READONLY === 1);
        assert.ok(sqlite3.OPEN_READWRITE === 2);
        assert.ok(sqlite3.OPEN_CREATE === 4);
    });

    it('should have the right error flags', function() {
        assert.ok(sqlite3.OK === 0);
        assert.ok(sqlite3.ERROR === 1);
        assert.ok(sqlite3.INTERNAL === 2);
        assert.ok(sqlite3.PERM === 3);
        assert.ok(sqlite3.ABORT === 4);
        assert.ok(sqlite3.BUSY === 5);
        assert.ok(sqlite3.LOCKED === 6);
        assert.ok(sqlite3.NOMEM === 7);
        assert.ok(sqlite3.READONLY === 8);
        assert.ok(sqlite3.INTERRUPT === 9);
        assert.ok(sqlite3.IOERR === 10);
        assert.ok(sqlite3.CORRUPT === 11);
        assert.ok(sqlite3.NOTFOUND === 12);
        assert.ok(sqlite3.FULL === 13);
        assert.ok(sqlite3.CANTOPEN === 14);
        assert.ok(sqlite3.PROTOCOL === 15);
        assert.ok(sqlite3.EMPTY === 16);
        assert.ok(sqlite3.SCHEMA === 17);
        assert.ok(sqlite3.TOOBIG === 18);
        assert.ok(sqlite3.CONSTRAINT === 19);
        assert.ok(sqlite3.MISMATCH === 20);
        assert.ok(sqlite3.MISUSE === 21);
        assert.ok(sqlite3.NOLFS === 22);
        assert.ok(sqlite3.AUTH === 23);
        assert.ok(sqlite3.FORMAT === 24);
        assert.ok(sqlite3.RANGE === 25);
        assert.ok(sqlite3.NOTADB === 26);
    });
});
