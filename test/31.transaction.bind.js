'use strict';
var expect = require('chai').expect;
var Database = require('../.');
var db;

before(function (done) {
	db = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.db');
	db.on('open', done);
});

describe('Transaction#bind()', function () {
	it('should permanently bind the given parameters', function () {
		db.transaction(['CREATE TABLE entries (a TEXT, b INTEGER, c BLOB)']).run();
		var trans = db.transaction(['INSERT INTO entries VALUES (?, ?, ?)']);
		var buffer = bufferOfSize(4).fill(0xdd);
		trans.bind('foobar', 25, buffer)
		trans.run();
		buffer.fill(0xaa);
		trans.run();
		var row1 = db.prepare('SELECT * FROM entries WHERE rowid=1').get();
		var row2 = db.prepare('SELECT * FROM entries WHERE rowid=2').get();
		expect(row1.a).to.equal(row2.a);
		expect(row1.b).to.equal(row2.b);
		expect(row1.c).to.deep.equal(row2.c);
	});
	it('should not allow you to bind temporary parameters afterwards', function () {
		var trans = db.transaction(['INSERT INTO entries VALUES (?, ?, ?)']);
		var buffer = bufferOfSize(4).fill(0xdd);
		trans.bind('foobar', 25, buffer)
		expect(function () {trans.run(null);}).to.throw(TypeError);
		expect(function () {trans.run(buffer);}).to.throw(TypeError);
		expect(function () {trans.run('foobar', 25, buffer);}).to.throw(TypeError);
	});
	it('should throw an exception when invoked twice on the same transaction', function () {
		var trans = db.transaction(['INSERT INTO entries VALUES (?, ?, ?)']);
		trans.bind('foobar', 25, null);
		expect(function () {trans.bind('foobar', 25, null);}).to.throw(TypeError);
		expect(function () {trans.bind();}).to.throw(TypeError);
		
		trans = db.transaction(["INSERT INTO entries VALUES ('foobar', 25, null)"]);
		trans.bind();
		expect(function () {trans.bind();}).to.throw(TypeError);
	});
	it('should throw an exception when invoked after the first execution', function () {
		var trans = db.transaction(["INSERT INTO entries VALUES ('foobar', 25, NULL)"]);
		trans.run();
		expect(function () {trans.bind();}).to.throw(TypeError);
		
		trans = db.transaction(["INSERT INTO entries VALUES ('foobar', 25, NULL)"]);
		trans.bind();
	});
	it('should throw an exception when invalid parameters are given', function () {
		var trans = db.transaction(['INSERT INTO entries VALUES (?, ?, ?)']);
		
		expect(function () {
			trans.bind('foo', 25);
		}).to.throw(Error);
		
		expect(function () {
			trans.bind('foo', 25, null, null);
		}).to.throw(Error);
		
		expect(function () {
			trans.bind('foo', new Number(25), null);
		}).to.throw(Error);
		
		expect(function () {
			trans.bind();
		}).to.throw(Error);
		
		trans.bind('foo', 25, null);
		
		trans = db.transaction(['INSERT INTO entries VALUES (@a, @a, ?)']);
		
		expect(function () {
			trans.bind({a: '123'});
		}).to.throw(Error);
		
		expect(function () {
			trans.bind({a: '123', 1: null});
		}).to.throw(Error);
		
		expect(function () {
			trans.bind({a: '123', b: null}, null);
		}).to.throw(Error);
		
		expect(function () {
			trans.bind({a: '123'}, null, null);
		}).to.throw(Error);
		
		trans.bind({a: '123'}, null);
	});
});

function bufferOfSize(size) {
	return Buffer.alloc ? Buffer.alloc(+size) : new Buffer(+size);
}
