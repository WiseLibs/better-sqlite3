import path from 'path';
import fs from 'fs-extra';
import Database from '../lib/database.js';

const tables = new Map([
	['small', {
		schema: '(nul, integer INTEGER, real REAL, text TEXT, blob BLOB)',
		data: [null, 0x7fffffff, 1 / 3, 'this is the text', Buffer.from('this is the blob')],
		count: 10000,
	}],
	['large_text', {
		schema: '(text TEXT)',
		data: ['this is the text'.repeat(2048)],
		count: 10000,
	}],
	['large_blob', {
		schema: '(blob BLOB)',
		data: [Buffer.from('this is the blob'.repeat(2048))],
		count: 10000,
	}],
]);

/*
	This function creates a pre-populated database that is deleted when the
	process exits.
 */

export default () => {
	const tempDir = path.join('..', 'temp');
	process.on('exit', () => fs.removeSync(tempDir));
	fs.removeSync(tempDir);
	fs.ensureDirSync(tempDir);

	const db = Database(path.join(tempDir, 'benchmark.db'));
	db.pragma('journal_mode = OFF');
	db.pragma('synchronous = OFF');

	for (const [name, ctx] of tables.entries()) {
		db.exec(`CREATE TABLE ${name} ${ctx.schema}`);
		const columns = db.pragma(`table_info(${name})`).map(() => '?');
		const insert = db.prepare(`INSERT INTO ${name} VALUES (${columns.join(', ')})`).bind(ctx.data);
		for (let i = 0; i < ctx.count; ++i) insert.run();
	}

	db.close();
	return tables;
};
