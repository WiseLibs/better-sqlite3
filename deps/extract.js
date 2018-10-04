'use strict';
const path = require('path');
const tar = require('tar');

const dest = process.argv[2];
const source = path.join(__dirname, 'sqlite3.tar.gz');

process.on('unhandledRejection', (err) => { throw err; });

/*
	This extracts the bundled sqlite3.tar.gz file and places the resulting files
	into the directory specified by <$2>.
 */

tar.extract({ file: source, cwd: dest, onwarn: process.emitWarning })
	.then(() => process.exit(0));
