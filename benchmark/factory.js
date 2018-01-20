'use strict';
const dbs = require('./implementations')();
const rows = 1000;

const buildTables = () => createTables([
		'allSmall (integer INTEGER, real REAL, text TEXT, blob BLOB, nul)',
		'allLarge (text TEXT, blob BLOB)',
		'integerSmall (integer INTEGER)',
		'realSmall (real REAL)',
		'textSmall (text TEXT)',
		'blobSmall (blob BLOB)',
		'nulSmall (nul)',
		'textLarge (text TEXT)',
		'blobLarge (blob BLOB)',
	])
	.then(() => fillTable('allSmall', getFakeData('small', ['integer', 'real', 'text', 'blob', 'nul'])))
	.then(() => fillTable('allLarge', getFakeData('large', ['text', 'blob'])));

const createTables = strings => strings
	.reduce((previous, SQL) => previous.then(() => createTable(SQL)), Promise.resolve());

const createTable = SQL => dbs.each('connect')
	.then(() => dbs.each('run', `CREATE TABLE ${SQL}`))
	.then(() => dbs.each('close'));

const fillTable = (table, values) => {
	const SQL = `INSERT INTO ${table} VALUES ${params(values.length)}`;
	let i = 0;
	return dbs.each('connect')
		.then(() => dbs.each('run', 'BEGIN')
			.then(function insert() {
				if (++i < rows) return dbs.each('run', SQL, values).then(insert);
				return dbs.each('run', SQL, values).then(() => dbs.each('run', 'COMMIT'));
			}))
		.then(() => dbs.each('close'));
};

const bufferOf = (str, size) => {
	let bytesWritten = 0;
	const source = Buffer.from(String(str));
	const result = Buffer.allocUnsafe(size >>> 0);
	while (bytesWritten < size) {
		bytesWritten += source.copy(result, bytesWritten, 0, Math.min(source.length, size - bytesWritten));
	}
	return result;
};

const getFakeData = (() => {
	const smallData = {
		integer: 12345,
		real: 0.12345,
		text: 'John Peter Smith',
		blob: Buffer.from('John Peter Smith'),
		nul: null,
	};
	const largeData = {
		text: bufferOf('John Peter Smith', 1024 * 100).toString(),
		blob: bufferOf('John Peter Smith', 1024 * 100),
	};
	function getColumn(column) {
		if (!this.hasOwnProperty(column)) {
			const table = this === largeData ? 'large' : 'small';
			throw new TypeError(`No data defined for column "${table}.${column}"`);
		}
		return this[column];
	}
	return (size, columns) => {
		const isLarge = size.toLowerCase().includes('large');
		return columns.map(getColumn, isLarge ? largeData : smallData);
	};
})();

const params = count => `(${new Array(count >>> 0).fill('?').join(', ')})`;

module.exports = Object.assign(getFakeData, { buildTables, params });
