'use strict';
const path = require('path');
const tar = require('tar');

const source = path.join(__dirname, process.argv[2]);
const dest = process.argv[3];

process.on('unhandledRejection', (err) => { throw err; });

tar.extract({ file: source, cwd: dest, onwarn: process.emitWarning })
	.then(() => process.exit(0));
