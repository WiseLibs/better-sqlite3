'use strict';

exports.default = [
	{type: 'select', table: 'allSmall', columns: ['integer', 'real', 'text', 'nul']},
	{type: 'select-all', table: 'allSmall', columns: ['integer', 'real', 'text', 'nul']},
	{type: 'select-each', table: 'allSmall', columns: ['integer', 'real', 'text', 'nul']},
	{type: 'insert', table: 'allSmall', columns: ['integer', 'real', 'text', 'nul'], pragma: ['journal_mode = WAL', 'synchronous = 1']},
	{type: 'insert', table: 'allSmall', columns: ['integer', 'real', 'text', 'nul'], pragma: ['journal_mode = DELETE', 'synchronous = 2']},
	{type: 'transaction', table: 'allSmall', columns: ['integer', 'real', 'text', 'nul']},
	{type: 'real-world', table: 'allSmall', columns: ['integer', 'real', 'text', 'nul'], pragma: ['journal_mode = WAL', 'synchronous = 1']},
	{type: 'real-world', table: 'allSmall', columns: ['integer', 'real', 'text', 'nul'], pragma: ['journal_mode = DELETE', 'synchronous = 2']}
];

exports.searchable = [
	{type: 'select', table: 'allSmall', columns: ['integer']},
	{type: 'select', table: 'allSmall', columns: ['real']},
	{type: 'select', table: 'allSmall', columns: ['text']},
	{type: 'select', table: 'allSmall', columns: ['blob']},
	{type: 'select', table: 'allSmall', columns: ['nul']},
	{type: 'select', table: 'allLarge', columns: ['text']},
	{type: 'select', table: 'allLarge', columns: ['blob']},
	{type: 'select-all', table: 'allSmall', columns: ['integer']},
	{type: 'select-all', table: 'allSmall', columns: ['real']},
	{type: 'select-all', table: 'allSmall', columns: ['text']},
	{type: 'select-all', table: 'allSmall', columns: ['blob']},
	{type: 'select-all', table: 'allSmall', columns: ['nul']},
	{type: 'select-all', table: 'allLarge', columns: ['text']},
	{type: 'select-all', table: 'allLarge', columns: ['blob']},
	{type: 'select-each', table: 'allSmall', columns: ['integer']},
	{type: 'select-each', table: 'allSmall', columns: ['real']},
	{type: 'select-each', table: 'allSmall', columns: ['text']},
	{type: 'select-each', table: 'allSmall', columns: ['blob']},
	{type: 'select-each', table: 'allSmall', columns: ['nul']},
	{type: 'select-each', table: 'allLarge', columns: ['text']},
	{type: 'select-each', table: 'allLarge', columns: ['blob']},
	{type: 'insert', table: 'integerSmall', columns: ['integer'], pragma: ['journal_mode = WAL', 'synchronous = 1']},
	{type: 'insert', table: 'realSmall', columns: ['real'], pragma: ['journal_mode = WAL', 'synchronous = 1']},
	{type: 'insert', table: 'textSmall', columns: ['text'], pragma: ['journal_mode = WAL', 'synchronous = 1']},
	{type: 'insert', table: 'blobSmall', columns: ['blob'], pragma: ['journal_mode = WAL', 'synchronous = 1']},
	{type: 'insert', table: 'nulSmall', columns: ['nul'], pragma: ['journal_mode = WAL', 'synchronous = 1']},
	{type: 'insert', table: 'textLarge', columns: ['text'], pragma: ['journal_mode = WAL', 'synchronous = 1']},
	{type: 'insert', table: 'blobLarge', columns: ['blob'], pragma: ['journal_mode = WAL', 'synchronous = 1']},
	{type: 'insert', table: 'integerSmall', columns: ['integer'], pragma: ['journal_mode = DELETE', 'synchronous = 2']},
	{type: 'insert', table: 'realSmall', columns: ['real'], pragma: ['journal_mode = DELETE', 'synchronous = 2']},
	{type: 'insert', table: 'textSmall', columns: ['text'], pragma: ['journal_mode = DELETE', 'synchronous = 2']},
	{type: 'insert', table: 'blobSmall', columns: ['blob'], pragma: ['journal_mode = DELETE', 'synchronous = 2']},
	{type: 'insert', table: 'nulSmall', columns: ['nul'], pragma: ['journal_mode = DELETE', 'synchronous = 2']},
	{type: 'insert', table: 'textLarge', columns: ['text'], pragma: ['journal_mode = DELETE', 'synchronous = 2']},
	{type: 'insert', table: 'blobLarge', columns: ['blob'], pragma: ['journal_mode = DELETE', 'synchronous = 2']},
	{type: 'transaction', table: 'integerSmall', columns: ['integer']},
	{type: 'transaction', table: 'realSmall', columns: ['real']},
	{type: 'transaction', table: 'textSmall', columns: ['text']},
	{type: 'transaction', table: 'blobSmall', columns: ['blob']},
	{type: 'transaction', table: 'nulSmall', columns: ['nul']},
	{type: 'transaction', table: 'textLarge', columns: ['text']},
	{type: 'transaction', table: 'blobLarge', columns: ['blob']}
];

(function () {
	var cacheSize = /^(1|true|on|yes)$/i.test(process.env.NO_CACHE) ? 'cache_size = 0' : 'cache_size = -16000';
	var trials = [].concat.apply([], Object.keys(exports).map(function (key) {return exports[key];}));
	trials.forEach(function (trial) {
		trial.pragma = [cacheSize].concat(trial.pragma || []);
	});
}());
