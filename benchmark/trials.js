'use strict';

exports.default = [
	{ type: 'select', table: 'small', columns: ['nul', 'integer', 'real', 'text'],
		description: 'reading rows individually' },
	{ type: 'select-all', table: 'small', columns: ['nul', 'integer', 'real', 'text'],
		description: 'reading 100 rows into an array' },
	{ type: 'select-iterate', table: 'small', columns: ['nul', 'integer', 'real', 'text'],
		description: 'iterating over 100 rows' },
	{ type: 'insert', table: 'small', columns: ['nul', 'integer', 'real', 'text'],
		description: 'inserting rows individually' },
	{ type: 'transaction', table: 'small', columns: ['nul', 'integer', 'real', 'text'],
		description: 'inserting 100 rows in a single transaction' },
];

exports.searchable = [
	{ type: 'select', table: 'small', columns: ['nul'] },
	{ type: 'select', table: 'small', columns: ['integer'] },
	{ type: 'select', table: 'small', columns: ['real'] },
	{ type: 'select', table: 'small', columns: ['text'] },
	{ type: 'select', table: 'small', columns: ['blob'] },
	{ type: 'select', table: 'large_text', columns: ['text'] },
	{ type: 'select', table: 'large_blob', columns: ['blob'] },
	{ type: 'select-all', table: 'small', columns: ['nul'] },
	{ type: 'select-all', table: 'small', columns: ['integer'] },
	{ type: 'select-all', table: 'small', columns: ['real'] },
	{ type: 'select-all', table: 'small', columns: ['text'] },
	{ type: 'select-all', table: 'small', columns: ['blob'] },
	{ type: 'select-all', table: 'large_text', columns: ['text'] },
	{ type: 'select-all', table: 'large_blob', columns: ['blob'] },
	{ type: 'select-iterate', table: 'small', columns: ['nul'] },
	{ type: 'select-iterate', table: 'small', columns: ['integer'] },
	{ type: 'select-iterate', table: 'small', columns: ['real'] },
	{ type: 'select-iterate', table: 'small', columns: ['text'] },
	{ type: 'select-iterate', table: 'small', columns: ['blob'] },
	{ type: 'select-iterate', table: 'large_text', columns: ['text'] },
	{ type: 'select-iterate', table: 'large_blob', columns: ['blob'] },
	{ type: 'insert', table: 'small', columns: ['nul'] },
	{ type: 'insert', table: 'small', columns: ['integer'] },
	{ type: 'insert', table: 'small', columns: ['real'] },
	{ type: 'insert', table: 'small', columns: ['text'] },
	{ type: 'insert', table: 'small', columns: ['blob'] },
	{ type: 'insert', table: 'large_text', columns: ['text'] },
	{ type: 'insert', table: 'large_blob', columns: ['blob'] },
	{ type: 'transaction', table: 'small', columns: ['nul'] },
	{ type: 'transaction', table: 'small', columns: ['integer'] },
	{ type: 'transaction', table: 'small', columns: ['real'] },
	{ type: 'transaction', table: 'small', columns: ['text'] },
	{ type: 'transaction', table: 'small', columns: ['blob'] },
	{ type: 'transaction', table: 'large_text', columns: ['text'] },
	{ type: 'transaction', table: 'large_blob', columns: ['blob'] },
];

(() => {
	const defaultPragma = [];
	const yes = /^\s*(1|true|on|yes)\s*$/i;
	if (yes.test(process.env.NO_CACHE)) defaultPragma.push('cache_size = 0');
	else defaultPragma.push('cache_size = -16000');
	if (yes.test(process.env.NO_WAL)) defaultPragma.push('journal_mode = DELETE', 'synchronous = FULL');
	else defaultPragma.push('journal_mode = WAL', 'synchronous = NORMAL');
	for (const trial of [].concat(...Object.values(exports))) {
		trial.customPragma = trial.pragma || [];
		trial.pragma = defaultPragma.concat(trial.customPragma);
	}
})();
