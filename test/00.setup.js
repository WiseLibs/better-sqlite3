import fs from 'fs-extra';
import path from 'path';
import os from 'os';
import * as chai from 'chai';

const isWindows = os.platform().startsWith('win');
const tempDir = path.join('temp');
let dbId = 0;

global.expect = chai.expect;
global.util = {
	current: () => path.join(tempDir, `${dbId}.db`),
	next: () => (++dbId, global.util.current()),
	itUnix: isWindows ? it.skip : it,
};

before(function () {
	fs.removeSync(tempDir);
	fs.ensureDirSync(tempDir);
});

after(function () {
	fs.removeSync(tempDir);
});
