'use strict';

exports.default = [
	{ type: 'select', table: 'small', columns: ['nul', 'integer', 'real', 'text'],
		description: 'reading rows individually' },
	{ type: 'select-all', table: 'small', columns: ['nul', 'integer', 'real', 'text'],
		description: 'reading 100 rows into an array' },
	{ type: 'select-iterate', table: 'small', columns: ['nul', 'integer', 'real', 'text'],
		description: 'iterating over 100 rows' },
	{ type: 'insert', table: 'small_empty', columns: ['nul', 'integer', 'real', 'text'],
		description: 'inserting rows individually' },
	{ type: 'transaction', table: 'small_empty', columns: ['nul', 'integer', 'real', 'text'],
		description: 'inserting 100 rows in a single transaction' },
];

exports.searchable = [
	{ type: 'select', table: 'small', columns: ['nul'] },
	{ type: 'select', table: 'small', columns: ['integer'] },
	{ type: 'select', table: 'small', columns: ['real'] },
	{ type: 'select', table: 'small', columns: ['text'] },
	{ type: 'select', table: 'small', columns: ['blob'] },
	{ type: 'select', table: 'large', columns: ['text'] },
	{ type: 'select', table: 'large', columns: ['blob'] },
	{ type: 'select-all', table: 'small', columns: ['nul'] },
	{ type: 'select-all', table: 'small', columns: ['integer'] },
	{ type: 'select-all', table: 'small', columns: ['real'] },
	{ type: 'select-all', table: 'small', columns: ['text'] },
	{ type: 'select-all', table: 'small', columns: ['blob'] },
	{ type: 'select-all', table: 'large', columns: ['text'] },
	{ type: 'select-all', table: 'large', columns: ['blob'] },
	{ type: 'select-iterate', table: 'small', columns: ['nul'] },
	{ type: 'select-iterate', table: 'small', columns: ['integer'] },
	{ type: 'select-iterate', table: 'small', columns: ['real'] },
	{ type: 'select-iterate', table: 'small', columns: ['text'] },
	{ type: 'select-iterate', table: 'small', columns: ['blob'] },
	{ type: 'select-iterate', table: 'large', columns: ['text'] },
	{ type: 'select-iterate', table: 'large', columns: ['blob'] },
	{ type: 'insert', table: 'small_empty', columns: ['nul'] },
	{ type: 'insert', table: 'small_empty', columns: ['integer'] },
	{ type: 'insert', table: 'small_empty', columns: ['real'] },
	{ type: 'insert', table: 'small_empty', columns: ['text'] },
	{ type: 'insert', table: 'small_empty', columns: ['blob'] },
	{ type: 'insert', table: 'large_empty', columns: ['text'] },
	{ type: 'insert', table: 'large_empty', columns: ['blob'] },
	{ type: 'transaction', table: 'small_empty', columns: ['nul'] },
	{ type: 'transaction', table: 'small_empty', columns: ['integer'] },
	{ type: 'transaction', table: 'small_empty', columns: ['real'] },
	{ type: 'transaction', table: 'small_empty', columns: ['text'] },
	{ type: 'transaction', table: 'small_empty', columns: ['blob'] },
	{ type: 'transaction', table: 'large_empty', columns: ['text'] },
	{ type: 'transaction', table: 'large_empty', columns: ['blob'] },
];

(() => {
	const cacheSize = /^(1|true|on|yes)$/i.test(process.env.NO_CACHE) ? 'cache_size = 0' : 'cache_size = -16000';
	const trials = [].concat(...Object.values(exports));
	for (const trial of trials) trial.pragma = (trial.pragma || []).concat(cacheSize);
})();
