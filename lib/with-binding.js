'use strict';
const util = require('./util');
const Database = require('./database');

/**
 * Creates a Database constructor bound to a specific native addon loader.
 *
 * Every package entrypoint calls this once, so each entrypoint exports its own
 * constructor with its own prototype. That isolation is deliberate: patching
 * one entrypoint's prototype must not affect another's, and an instance from
 * one entrypoint must not be `instanceof` another's constructor.
 *
 * The returned constructor is observationally identical to the one the previous
 * factory produced: same name, same arity, same prototype contents, same
 * prototype depth, and the same behavior with and without `new`.
 *
 * @param {Function} getAddon Called with the `nativeBinding` option's value and
 *   returning the native addon object.
 * @param {boolean} allowNativeBinding Whether this entrypoint permits the
 *   `nativeBinding` option; only the default entrypoint does.
 * @returns {Function} A Database constructor bound to `getAddon`.
 *
 * @example
 * // lib/index.js
 * module.exports = require('./with-binding')(require('./binding').getBinding, true);
 *
 * @see lib/database.js
 */
module.exports = function withBinding(getAddon, allowNativeBinding) {
	function BoundDatabase(...args) {
		// new.target is forwarded so that subclasses construct as themselves.
		// Hardcoding BoundDatabase here would silently produce base instances
		// from `class Sub extends Database {}`, with no error raised.
		return Reflect.construct(Database, args, new.target || BoundDatabase);
	}

	// Copy the prototype's descriptors rather than chaining to it, so instances
	// sit exactly one link from Object.prototype as they always have. Chaining
	// would add a hop to every method lookup and change the observable shape.
	// The copy is safe because lib/database.js populates Database.prototype at
	// module load, before any entrypoint can call this function.
	BoundDatabase.prototype = Object.create(
		Object.prototype,
		Object.getOwnPropertyDescriptors(Database.prototype),
	);

	// Redefined rather than assigned, to keep `constructor` non-enumerable and
	// therefore absent from for..in over an instance.
	Object.defineProperty(BoundDatabase.prototype, 'constructor', {
		value: BoundDatabase,
		writable: true,
		enumerable: false,
		configurable: true,
	});

	// Preserve the identity callers and stack traces see.
	Object.defineProperty(BoundDatabase, 'name', { value: Database.name, configurable: true });
	Object.defineProperty(BoundDatabase, 'length', { value: Database.length, configurable: true });

	BoundDatabase[util.binding] = { getAddon, allowNativeBinding };

	return BoundDatabase;
};
