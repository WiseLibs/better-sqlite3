'use strict';

module.exports = [
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
	{type: 'insert', table: 'integerSmall', columns: ['integer'], pragma: ['journal_mode = WAL']},
	{type: 'insert', table: 'realSmall', columns: ['real'], pragma: ['journal_mode = WAL']},
	{type: 'insert', table: 'textSmall', columns: ['text'], pragma: ['journal_mode = WAL']},
	{type: 'insert', table: 'blobSmall', columns: ['blob'], pragma: ['journal_mode = WAL']},
	{type: 'insert', table: 'nulSmall', columns: ['nul'], pragma: ['journal_mode = WAL']},
	{type: 'insert', table: 'textLarge', columns: ['text'], pragma: ['journal_mode = WAL']},
	{type: 'insert', table: 'blobLarge', columns: ['blob'], pragma: ['journal_mode = WAL']},
	{type: 'insert', table: 'integerSmall', columns: ['integer'], pragma: ['journal_mode = DELETE']},
	{type: 'insert', table: 'realSmall', columns: ['real'], pragma: ['journal_mode = DELETE']},
	{type: 'insert', table: 'textSmall', columns: ['text'], pragma: ['journal_mode = DELETE']},
	{type: 'insert', table: 'blobSmall', columns: ['blob'], pragma: ['journal_mode = DELETE']},
	{type: 'insert', table: 'nulSmall', columns: ['nul'], pragma: ['journal_mode = DELETE']},
	{type: 'insert', table: 'textLarge', columns: ['text'], pragma: ['journal_mode = DELETE']},
	{type: 'insert', table: 'blobLarge', columns: ['blob'], pragma: ['journal_mode = DELETE']},
	{type: 'transaction', table: 'integerSmall', columns: ['integer']},
	{type: 'transaction', table: 'realSmall', columns: ['real']},
	{type: 'transaction', table: 'textSmall', columns: ['text']},
	{type: 'transaction', table: 'blobSmall', columns: ['blob']},
	{type: 'transaction', table: 'nulSmall', columns: ['nul']},
	{type: 'transaction', table: 'textLarge', columns: ['text']},
	{type: 'transaction', table: 'blobLarge', columns: ['blob']},
	{type: 'real-world', table: 'allSmall', columns: ['integer', 'real', 'text', 'blob', 'nul'], pragma: ['journal_mode = WAL']},
	{type: 'real-world', table: 'allSmall', columns: ['integer', 'real', 'text', 'blob', 'nul'], pragma: ['journal_mode = DELETE']}
];

if (/^(1|true|on|yes)$/i.test(process.env.NO_CACHE)) {
	module.exports.forEach(function (trial) {
		trial.pragma = ['cache_size = 0'].concat(trial.pragma || []);
	});
} else {
	module.exports.forEach(function (trial) {
		trial.pragma = ['cache_size = -16000'].concat(trial.pragma || []);
	});
}
