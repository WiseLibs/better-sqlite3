'use strict';
var dbs = require('./implementations')();
var rows = 1000;

module.exports = function () {
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
		return fillTable('allSmall', [12345, 0.12345, 'John Peter Smith', Buffer.from('John Peter Smith'), null]);
	}).then(function () {
		var buffer = bufferOf('John Peter Smith', 1024 * 100);
		return fillTable('allLarge', [buffer.toString(), buffer]);
	});
};

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

function bufferOf(str, length) {
	var bytesWritten = 0;
	var source = Buffer.from(String(str));
	var result = Buffer.allocUnsafe(length >>> 0);
	while (bytesWritten < length) {
		bytesWritten += source.copy(result, bytesWritten, 0, Math.min(source.length, length - bytesWritten));
	}
	return result;
}

function params(count) {
	return '(' + new Array(count >>> 0).fill('?').join(', ') + ')';
}
