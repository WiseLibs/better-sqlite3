'use strict';

module.exports = [
	{type: 'select', table: 'allSmall', columns: ['integer']},
	{type: 'select', table: 'allSmall', columns: ['real']},
	{type: 'select', table: 'allSmall', columns: ['text']},
	{type: 'select', table: 'allSmall', columns: ['blob']},
	{type: 'select', table: 'allSmall', columns: ['nul']},
	{type: 'select', table: 'allLarge', columns: ['text']},
	{type: 'select', table: 'allLarge', columns: ['blob']}
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
