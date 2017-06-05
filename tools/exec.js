'use strict';
var joinPath = require('path').join;
var spawn = require('child_process').spawn;
var defaultCwd = require('path').dirname(__dirname);
var spawnOptions = {
	encoding: 'utf8',
	stdio: 'inherit',
	shell: true
};

function exec(command, cwd) {
	return new Promise(function (resolve, reject) {
		spawn(command[0], command.slice(1), Object.assign({cwd: cwd}, spawnOptions))
			.on('exit', function (code) {code === 0 ? resolve(0) : reject(code);});
	});
}
function exit(code) {
	process.exit(typeof code === 'number' ? code : 1);
}

module.exports = function (commands) {
	commands.reduce(function (prev, command) {
		var cwd = command.cwd ? joinPath(defaultCwd, command.cwd) : defaultCwd;
		return prev.then(function () {return exec(command, cwd);});
	}, Promise.resolve()).then(exit, exit);
};
