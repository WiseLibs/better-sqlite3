'use strict';
var buildLzz = false;
var lzz = process.platform === 'darwin' ? './tools/lzz-osx'
	: process.platform === 'win32' ? './tools/lzz-windows.exe'
	: process.platform === 'linux' ? './tools/lzz-linux'
	: ((buildLzz = true), './tools/lzz-source/lazycpp');

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

if (buildLzz) {
	var buildLzzCommand = ['make', '-f', 'Makefile.release'];
	buildLzzCommand.cwd = './tools/lzz-source';
}

var commands = (buildLzzCommand ? [buildLzzCommand] : []).concat([
	[lzz].concat(lzzOptions),
	['node-gyp', 'rebuild'].concat(process.env.CI === 'true' ? ['--debug'] : [])
]);

require('./exec')(commands);
