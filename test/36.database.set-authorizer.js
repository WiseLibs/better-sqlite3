'use strict';
const chai = require('chai');
chai.use(require('chai-spies'))

const expect = chai.expect
const Database = require('../.');
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
        expect(this.db.setAuthorizer((op, a0, a1, d, t) => 0)).to.equal(this.db)
    })

    it('should invoke registered authorizer with arguments received from sqlite', function() {
        let authorizer = (op, a0, a1, d, t) => 0
        let spied = chai.spy(authorizer)
        this.db.setAuthorizer(spied)

        this.db.prepare('SELECT site FROM sample').all() // result is not that important

        expect(spied).to.have.been.first.called.with(21, "", "", "", "") // SELECT
        expect(spied).to.have.been.second.called.with(20, "sample", "site", "main", "") // READ
    })

    it('should properly return values from authorizer to ensure actions are blocked / allowed', function() {
        // deny read on 'id' column
        let authorizer = (op, a0, a1, d, t) => { return (op == 20 && a1 == 'id')? 1 : 0}
        this.db.setAuthorizer(authorizer)

        expect(() => this.db.prepare('SELECT site FROM sample')).to.not.throw
        expect(() => this.db.prepare('SELECT id, site FROM sample')).to.throw(SqliteError)
    })

    it('should unset authorizer if null is passed', function() {
        let authorizer = (op, a0, a1, d, t) => 1 // deny all
        this.db.setAuthorizer(authorizer)
        expect(() => this.db.prepare('SELECT site FROM sample')).to.throw(SqliteError)
        this.db.setAuthorizer(null)
        expect(() => this.db.prepare('SELECT site FROM sample')).to.not.throw
    })
})