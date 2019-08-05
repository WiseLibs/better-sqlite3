'use strict';
const fs = require('fs-extra');
const path = require('path');
const { platform } = require('os');
const chai = require('chai');

const tempDir = path.join(__dirname, '..', 'temp');
const isWin = platform().startsWith('win')
let dbId = 0;

global.expect = chai.expect;
global.util = {
	current: () => path.join(tempDir, `${dbId}.db`),
	next: () => (++dbId, global.util.current()),
	isWin,
	describe: isWin ? describe.skip : describe
};

before(function () {
	fs.removeSync(tempDir);
	fs.ensureDirSync(tempDir);
});

after(function () {
	fs.removeSync(tempDir);
});
