'use strict';
var expect = require('chai').expect;
var Database = require('../.');
var db;

before(function (done) {
	db = new Database('temp/' + require('path').basename(__filename).split('.')[0] + '.db');
	db.on('open', done);
});

describe('Statement#bind()', function () {
	
});
