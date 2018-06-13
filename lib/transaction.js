'use strict';
const controllers = new WeakMap;
const { apply } = Function.prototype;

module.exports = function transaction(mode, fn) {
	if (typeof mode === 'function') {
		fn = mode;
		mode = 'default';
	} else {
		if (typeof mode !== 'string') {
			throw new TypeError('Expected first argument to be a string or function');
		}
		if (typeof fn !== 'function') {
			throw new TypeError('Expected second argument to be a function');
		}
	}
	const t = getController(this)[mode];
	if (t === undefined) {
		throw new TypeError(`Unrecognized transaction mode "${mode}"`);
	}
	return wrapTransaction(fn, t.begin, t.commit, t.rollback, this);
};

const getController = (db) => {
	let controller = controllers.get(db);
	if (controller === undefined) {
		const commit = db.prepare('COMMIT');
		const rollback = db.prepare('ROLLBACK');
		controllers.set(db, controller = Object.assign(Object.create(null), {
			default: { begin: db.prepare('BEGIN'), commit, rollback },
			deferred: { begin: db.prepare('BEGIN DEFERRED'), commit, rollback },
			immediate: { begin: db.prepare('BEGIN IMMEDIATE'), commit, rollback },
			exclusive: { begin: db.prepare('BEGIN EXCLUSIVE'), commit, rollback },
		}));
	}
	return controller;
};

const wrapTransaction = (fn, begin, commit, rollback, db) => function sqliteTransaction() {
	let result;
	begin.run();
	try {
		result = apply.call(fn, this, arguments);
		commit.run();
	} finally {
		if (db.inTransaction) rollback.run();
	}
	return result;
};
