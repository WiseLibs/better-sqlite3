'use strict';
var args = process.env.CI === 'true' ? ['rebuild', '--debug'] : ['rebuild'];
var child = require('child_process').spawn('node-gyp', args, {
	encoding: 'utf8',
	stdio: 'inherit',
	cwd: require('path').dirname(__dirname),
	shell: true
});

child.on('exit', function (code) {
	process.exit(code);
});

