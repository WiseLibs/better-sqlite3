'use strict';
const path = require('path');
const fs = require('fs');

const dest = process.argv[2];
const source = path.resolve(process.argv[3]);

/*
	This creates symlinks inside the <$2> directory, linking to the SQLite3
	amalgamation files inside the directory specified by the path <$3>.
 */

for (const filename of ['sqlite3.c', 'sqlite3.h']) {
	fs.accessSync(path.join(source, filename));
	fs.symlinkSync(path.join(source, filename), path.join(dest, filename), 'file');
}
