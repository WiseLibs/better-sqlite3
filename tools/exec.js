'use strict';
var spawn = require('child_process').spawn;
var spawnOptions = {
	encoding: 'utf8',
	stdio: 'inherit',
	cwd: require('path').dirname(__dirname),
	shell: true
};

function exec(file, args) {
	return new Promise(function (resolve, reject) {
		spawn(file, args, spawnOptions).on('exit', function (code) {
			code === 0 ? resolve(0) : reject(code);
		});
	});
}
function exit(code) {
	process.exit(typeof code === 'number' ? code : 1);
}

module.exports = function (commands) {
	commands.reduce(function (previous, command) {
		var file = command[0];
		var args = command.slice(1);
		return previous.then(function () {return exec(file, args);});
	}, Promise.resolve()).then(exit, exit);
};
