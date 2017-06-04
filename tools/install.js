'use strict';
var lzz = process.platform === 'darwin' ? './tools/lzz-osx'
        : process.platform === 'win32' ? './tools/lzz-windows.exe'
        : './tools/lzz-linux';

var lzzOptions = [
	'-hx', 'hpp',
	'-sx', 'cpp',
	'-k', 'BETTER_SQLITE3',
	'-d',
	'-hl',
	'-sl',
	'-e',
	'./src/better_sqlite3.lzz'
];

require('./exec')([
	['ls', lzz],
	[lzz].concat(lzzOptions),
	['node-gyp', 'rebuild'].concat(process.env.CI === 'true' ? ['--debug'] : [])
]);
