'use strict';
const chai = require('chai');
chai.use(require('chai-spies'))

const expect = chai.expect
const Database = require('../.');
const { SQLITE_OK, SQLITE_DENY, SQLITE_SELECT, SQLITE_READ } = require('../lib/codes')
const SqliteError = require('../lib/sqlite-error');

describe('Database#setAuthorizer', function(){
    beforeEach(function () {
		let db = new Database(util.next());
		db.exec('CREATE TABLE sample (id INTEGER PRIMARY KEY, site)')
        
        let add = db.prepare('INSERT INTO sample (site) VALUES (?)')
        add.run('google.com')
        add.run('facebook.com')
        add.run('amazon.com')
        add.run('netflix.com')

        this.db = db
	});

	afterEach(function () {
		this.db.close();
	});

    it('should throw an exception if the correct arguments are not provided', function () {
        expect(() => this.db.setAuthorizer()).to.throw(TypeError)
        expect(() => this.db.setAuthorizer(1)).to.throw(TypeError)
        expect(() => this.db.setAuthorizer(undefined)).to.throw(TypeError)
        expect(() => this.db.setAuthorizer((a, b) => { })).to.throw(RangeError)
    })

    it('should register the given function and return the database object', function () {
        expect(this.db.setAuthorizer((op, a0, a1, d, t) => SQLITE_OK)).to.equal(this.db)
    })

    it('should invoke registered authorizer with arguments received from sqlite', function() {
        let authorizer = (op, a0, a1, d, t) => SQLITE_OK
        let spied = chai.spy(authorizer)
        this.db.setAuthorizer(spied)

        this.db.prepare('SELECT site FROM sample').all() // result is not that important

        expect(spied).to.have.been.first.called.with(SQLITE_SELECT, "", "", "", "") // SELECT
        expect(spied).to.have.been.second.called.with(SQLITE_READ, "sample", "site", "main", "") // READ
    })

    it('should properly return values from authorizer to ensure actions are blocked / allowed', function() {
        // deny read on 'id' column
        let authorizer = (op, a0, col, d, t) => { return (op == SQLITE_READ && col == 'id')? 1 : 0}
        this.db.setAuthorizer(authorizer)

        expect(() => this.db.prepare('SELECT site FROM sample')).to.not.throw
        expect(() => this.db.prepare('SELECT id, site FROM sample')).to.throw(SqliteError)
    })

    it('should unset authorizer if null is passed', function() {
        let authorizer = (op, a0, a1, d, t) => SQLITE_DENY // deny all
        this.db.setAuthorizer(authorizer)
        expect(() => this.db.prepare('SELECT site FROM sample')).to.throw(SqliteError)
        this.db.setAuthorizer(null)
        expect(() => this.db.prepare('SELECT site FROM sample')).to.not.throw
    })
})