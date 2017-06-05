'use strict';
var path = require('path');
var spawn = require('child_process').spawn;
var defaultCwd = path.dirname(__dirname);
var spawnOptions = {
	encoding: 'utf8',
	stdio: 'inherit',
	shell: true
};

function exec(command, cwd) {
	return new Promise(function (resolve, reject) {
		console.log('==>', command.join(' '));
		spawn(command[0], command.slice(1), Object.assign({cwd: cwd}, spawnOptions))
			.on('exit', function (code) {code === 0 ? resolve(0) : reject(code);});
	});
}
function exit(code) {
	if (typeof code !== 'number') {
		throw code;
		process.exit(1);
	}
	console.log('exit code', code);
	process.exit(code);
}

module.exports = function (commands) {
	commands.reduce(function (prev, command) {
		var cwd = command.cwd ? path.join(defaultCwd, command.cwd) : defaultCwd;
		return prev.then(function () {return exec(command, cwd);});
	}, Promise.resolve()).then(exit, exit);
};
