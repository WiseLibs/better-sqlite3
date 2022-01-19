'use strict';
const path = require('path');
const fs = require('fs');

const dest = process.argv[2];
const source = path.resolve(path.sep, process.argv[3] || path.join(__dirname, 'sqlite3'));
const filenames = process.argv.slice(4);

console.log(`CWD: ${JSON.stringify(process.cwd())}`);
console.log(`ARGV: ${JSON.stringify(process.argv)}`);
console.log(`DIRNAME: ${JSON.stringify(__dirname)}`);
console.log(`DEST: ${JSON.stringify(dest)}`);
console.log(`SOURCE: ${JSON.stringify(source)}`);
console.log(`FILENAMES: ${JSON.stringify(filenames)}`);

/*
	This creates symlinks inside the <$2> directory, linking to files inside the
	directory specified by the absolute path <$3>. If no path <$3> is provided,
	the default path of "./deps/sqlite3" is used. The basenames of the files to
	link are specified by <$4...>.
 */

for (const filename of filenames) {
	fs.accessSync(path.join(source, filename));
	fs.symlinkSync(path.join(source, filename), path.join(dest, filename), 'file');
}
