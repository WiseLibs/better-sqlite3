'use strict';
const moduleRoot = require('path').dirname(__dirname);
const lzzArgs = [
	'-hx', 'hpp',
	'-sx', 'cpp',
	'-k', 'BETTER_SQLITE3',
	'-d',
	'-hl',
	'-sl',
	'-e',
	'./src/better_sqlite3.lzz',
];

require('lzz-gyp')(lzzArgs, moduleRoot, process.env.CI === 'true').catch((err) => {
	console.error(err);
	process.exit(1);
});
