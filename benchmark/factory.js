'use strict';
var dbs = require('./implementations')();
var rows = 1000;

exports.buildTables = function () {
	return createTables([
		'allSmall (integer INTEGER, real REAL, text TEXT, blob BLOB, nul)',
		'allLarge (text TEXT, blob BLOB)',
		'integerSmall (integer INTEGER)',
		'realSmall (real REAL)',
		'textSmall (text TEXT)',
		'blobSmall (blob BLOB)',
		'nulSmall (nul)',
		'textLarge (text TEXT)',
		'blobLarge (blob BLOB)'
	]).then(function () {
		return fillTable('allSmall', getFakeData('small', ['integer', 'real', 'text', 'blob', 'nul']));
	}).then(function () {
		return fillTable('allLarge', getFakeData('large', ['text', 'blob']));
	});
};
exports.params = params;

function createTables(strings) {
	return strings.reduce(function (promise, SQL) {
		return promise.then(function () {return createTable(SQL);});
	}, Promise.resolve());
}

function createTable(SQL) {
	return dbs.each('connect').then(function () {
		return dbs.each('run', 'CREATE TABLE ' + SQL);
	}).then(function () {return dbs.each('close');});
}

function fillTable(table, values) {
	var i = 0;
	var SQL = 'INSERT INTO ' + table + ' VALUES ' + params(values.length);
	return dbs.each('connect').then(function () {
		return dbs.each('run', 'BEGIN').then(function insert() {
			if (++i < rows) {
				return dbs.each('run', SQL, values).then(insert);
			}
			return dbs.each('run', SQL, values).then(function () {return dbs.each('run', 'COMMIT');});
		});
	}).then(function () {return dbs.each('close');});
}

var getFakeData = (function () {
	var smallData = {
		integer: 12345,
		real: 0.12345,
		text: 'John Peter Smith',
		blob: Buffer.from('John Peter Smith'),
		nul: null
	};
	var largeData = {
		text: bufferOf('John Peter Smith', 1024 * 100).toString(),
		blob: bufferOf('John Peter Smith', 1024 * 100)
	};
	function getColumn(column) {
		if (!this.hasOwnProperty(column)) {
			var table = this === largeData ? 'large' : 'small';
			throw new TypeError('No data defined for column "' + table + '.' + column + '".');
		}
		return this[column];
	}
	return function (size, columns) {
		var isLarge = size.toLowerCase().indexOf('large') !== -1;
		return columns.map(getColumn, isLarge ? largeData : smallData);
	};
}());

function bufferOf(str, size) {
	var bytesWritten = 0;
	var source = Buffer.from(String(str));
	var result = Buffer.allocUnsafe(size >>> 0);
	while (bytesWritten < size) {
		bytesWritten += source.copy(result, bytesWritten, 0, Math.min(source.length, size - bytesWritten));
	}
	return result;
}

function params(count) {
	return '(' + new Array(count >>> 0).fill('?').join(', ') + ')';
}

module.exports = Object.assign(getFakeData, exports);
