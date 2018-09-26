'use strict';
const fs = require('fs-extra');
const path = require('path');
const chai = require('chai');

const tempDir = path.join(__dirname, '..', 'temp');
let dbId = 0;

global.expect = chai.expect;
global.util = {
	current: () => path.join(tempDir, `${dbId}.db`),
	next: () => (++dbId, global.util.current()),
};

before(function () {
	fs.removeSync(tempDir);
	fs.ensureDirSync(tempDir);
});

after(function () {
	fs.removeSync(tempDir);
});
