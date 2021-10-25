'use strict';
const Database = require('../.');

describe('Database#serialize()', function () {
	beforeEach(function () {
		this.db = new Database(util.next());
		this.db.prepare("CREATE TABLE entries (a TEXT, b INTEGER, c REAL, d BLOB, e TEXT)").run();
		this.seed = () => {
			this.db.prepare("INSERT INTO entries WITH RECURSIVE temp(a, b, c, d, e) AS (SELECT 'foo', 1, 3.14, x'dddddddd', NULL UNION ALL SELECT a, b + 1, c, d, e FROM temp LIMIT 1000) SELECT * FROM temp").run();
		};
	});
	afterEach(function () {
		this.db.close();
	});

	it('should serialize the database and return a buffer', async function () {
		let buffer = this.db.serialize();
		expect(buffer).to.be.an.instanceof(Buffer);
		expect(buffer.length).to.be.above(1000);
		const lengthBefore = buffer.length;
		this.seed();
		buffer = this.db.serialize();
		expect(buffer).to.be.an.instanceof(Buffer);
		expect(buffer.length).to.be.above(lengthBefore);
	});
	it('should return a buffer that can be used by the Database constructor', async function () {
		this.seed();
		const buffer = this.db.serialize();
		expect(buffer).to.be.an.instanceof(Buffer);
		expect(buffer.length).to.be.above(1000);
		this.db.prepare('delete from entries').run();
		this.db.close();
		this.db = new Database(buffer);
		const bufferCopy = this.db.serialize();
		expect(buffer.length).to.equal(bufferCopy.length);
		expect(buffer).to.deep.equal(bufferCopy);
		this.db.prepare('insert into entries (rowid, a, b) values (?, ?, ?)').run(0, 'bar', -999);
		expect(this.db.prepare('select a, b from entries order by rowid limit 2').all())
			.to.deep.equal([{ a: 'bar', b: -999 }, { a: 'foo', b: 1 }]);
	});
	it('should accept the "attached" option', async function () {
		const smallBuffer = this.db.serialize();
		this.seed();
		const bigBuffer = this.db.serialize();
		this.db.close();
		this.db = new Database();
		this.db.prepare('attach ? as other').run(util.current());
		const smallBuffer2 = this.db.serialize();
		const bigBuffer2 = this.db.serialize({ attached: 'other' });
		expect(bigBuffer.length === bigBuffer2.length);
		expect(bigBuffer).to.deep.equal(bigBuffer2);
		expect(smallBuffer.length < bigBuffer.length);
		expect(smallBuffer2.length < bigBuffer.length);
		expect(smallBuffer).to.not.deep.equal(smallBuffer2);
	});
	it('should return a buffer that can be opened with the "readonly" option', async function () {
		this.seed();
		const buffer = this.db.serialize();
		expect(buffer).to.be.an.instanceof(Buffer);
		expect(buffer.length).to.be.above(1000);
		this.db.close();
		this.db = new Database(buffer, { readonly: true });
		expect(() => this.db.prepare('insert into entries (rowid, a, b) values (?, ?, ?)').run(0, 'bar', -999))
			.to.throw(Database.SqliteError);
		expect(this.db.prepare('select a, b from entries order by rowid limit 2').all())
			.to.deep.equal([{ a: 'foo', b: 1 }, { a: 'foo', b: 2 }]);
		const bufferCopy = this.db.serialize();
		expect(buffer.length).to.equal(bufferCopy.length);
		expect(buffer).to.deep.equal(bufferCopy);
	});
	it('should work with an empty database', async function () {
		this.db.close();
		this.db = new Database();
		const buffer = this.db.serialize();
		expect(buffer).to.be.an.instanceof(Buffer);
		expect(buffer.length).to.equal(0);
		this.db.close();
		this.db = new Database(buffer);
		expect(this.db.serialize().length).to.equal(0);
	});
});
