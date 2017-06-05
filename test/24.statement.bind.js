'use strict';
var expect = require('chai').expect;
var Database = require('../.');
var db;

before(function () {
	db = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.db');
});

describe('Statement#bind()', function () {
	it('should permanently bind the given parameters', function () {
		db.prepare('CREATE TABLE entries (a TEXT, b INTEGER, c BLOB)').run();
		var stmt = db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		var buffer = bufferOfSize(4).fill(0xdd);
		stmt.bind('foobar', 25, buffer)
		stmt.run();
		buffer.fill(0xaa);
		stmt.run();
		var row1 = db.prepare('SELECT * FROM entries WHERE rowid=1').get();
		var row2 = db.prepare('SELECT * FROM entries WHERE rowid=2').get();
		expect(row1.a).to.equal(row2.a);
		expect(row1.b).to.equal(row2.b);
		expect(row1.c).to.deep.equal(row2.c);
	});
	it('should not allow you to bind temporary parameters afterwards', function () {
		var stmt = db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		var buffer = bufferOfSize(4).fill(0xdd);
		stmt.bind('foobar', 25, buffer)
		expect(function () {stmt.run(null);}).to.throw(TypeError);
		expect(function () {stmt.run(buffer);}).to.throw(TypeError);
		expect(function () {stmt.run('foobar', 25, buffer);}).to.throw(TypeError);
	});
	it('should throw an exception when invoked twice on the same statement', function () {
		var stmt = db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		stmt.bind('foobar', 25, null);
		expect(function () {stmt.bind('foobar', 25, null);}).to.throw(TypeError);
		expect(function () {stmt.bind();}).to.throw(TypeError);
		
		stmt = db.prepare('SELECT * FROM entries');
		stmt.bind();
		expect(function () {stmt.bind();}).to.throw(TypeError);
	});
	it('should throw an exception when invalid parameters are given', function () {
		var stmt = db.prepare('INSERT INTO entries VALUES (?, ?, ?)');
		
		expect(function () {
			stmt.bind('foo', 25);
		}).to.throw(RangeError);
		
		expect(function () {
			stmt.bind('foo', 25, null, null);
		}).to.throw(RangeError);
		
		expect(function () {
			stmt.bind('foo', new Number(25), null);
		}).to.throw(TypeError);
		
		expect(function () {
			stmt.bind();
		}).to.throw(RangeError);
		
		stmt.bind('foo', 25, null);
		
		stmt = db.prepare('INSERT INTO entries VALUES (@a, @a, ?)');
		
		expect(function () {
			stmt.bind({a: '123'});
		}).to.throw(RangeError);
		
		expect(function () {
			stmt.bind({a: '123', 1: null});
		}).to.throw(RangeError);
		
		expect(function () {
			stmt.bind({a: '123'}, null, null);
		}).to.throw(RangeError);
		
		stmt.bind({a: '123'}, null);
		
		stmt = db.prepare('INSERT INTO entries VALUES (@a, @a, ?)');
		stmt.bind({a: '123', b: null}, null);
	});
	it('should propagate exceptions thrown while accessing array/object members', function () {
		var arr = [22];
		var obj = {};
		var err = new TypeError('foobar');
		Object.defineProperty(arr, '0', {get: function () {throw err;}})
		Object.defineProperty(obj, 'baz', {get: function () {throw err;}})
		var stmt1 = db.prepare('SELECT ?');
		var stmt2 = db.prepare('SELECT @baz');
		expect(function () {stmt1.bind(arr);}).to.throw(err);
		expect(function () {stmt2.bind(obj);}).to.throw(err);
	});
});

function bufferOfSize(size) {
	return Buffer.alloc ? Buffer.alloc(+size) : new Buffer(+size);
}
