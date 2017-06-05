'use strict';
var lzzArgs = [
	'-hx', 'hpp',
	'-sx', 'cpp',
	'-k', 'BETTER_SQLITE3',
	'-d',
	'-hl',
	'-sl',
	'-e',
	'./src/better_sqlite3.lzz'
];
var moduleRoot = require('path').dirname(__dirname);

require('lzz-gyp')(lzzArgs, moduleRoot, process.env.CI === 'true')
.catch(function (err) {
	console.error(err);
	process.exit(1);
});
