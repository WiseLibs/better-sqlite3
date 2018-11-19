'use strict';
const controllers = new WeakMap;

module.exports = function transaction(fn) {
	if (typeof fn !== 'function') throw new TypeError('Expected first argument to be a function');
	const controller = getController(this);
	const { apply } = Function.prototype;

	const properties = {
		default: { value: wrapTransaction(apply, fn, this, controller.default) },
		deferred: { value: wrapTransaction(apply, fn, this, controller.deferred) },
		immediate: { value: wrapTransaction(apply, fn, this, controller.immediate) },
		exclusive: { value: wrapTransaction(apply, fn, this, controller.exclusive) },
		database: { value: this, enumerable: true },
	};

	Object.defineProperties(properties.default.value, properties);
	Object.defineProperties(properties.deferred.value, properties);
	Object.defineProperties(properties.immediate.value, properties);
	Object.defineProperties(properties.exclusive.value, properties);

	return properties.default.value;
};

const getController = (db) => {
	let controller = controllers.get(db);
	if (!controller) {
		const shared = {
			commit: db.prepare('COMMIT'),
			rollback: db.prepare('ROLLBACK'),
			savepoint: db.prepare('SAVEPOINT `\t_bs3.\t`'),
			release: db.prepare('RELEASE `\t_bs3.\t`'),
			rollbackTo: db.prepare('ROLLBACK TO `\t_bs3.\t`'),
		};
		controllers.set(db, controller = {
			default: { begin: db.prepare('BEGIN'), ...shared },
			deferred: { begin: db.prepare('BEGIN DEFERRED'), ...shared },
			immediate: { begin: db.prepare('BEGIN IMMEDIATE'), ...shared },
			exclusive: { begin: db.prepare('BEGIN EXCLUSIVE'), ...shared },
		});
	}
	return controller;
};

const wrapTransaction = (apply, fn, db, { begin, commit, rollback, savepoint, release, rollbackTo }) => function sqliteTransaction() {
	let before, after, undo;
	if (db.inTransaction) {
		before = savepoint;
		after = release;
		undo = rollbackTo;
	} else {
		before = begin;
		after = commit;
		undo = rollback;
	}
	before.run();
	try {
		const result = apply.call(fn, this, arguments);
		after.run();
		return result;
	} catch (ex) {
		if (db.inTransaction) {
			undo.run();
			if (undo !== rollback) after.run();
		}
		throw ex;
	}
};
