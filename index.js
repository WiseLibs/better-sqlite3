'use strict';
module.exports = require('./lib/database');
var Int64 = module.exports.Int64 = require('bindings')('better_sqlite3').Int64;

defineFrozen(Int64, 'MAX_VALUE', new Int64(-1, 0x7fffffff));
defineFrozen(Int64, 'MIN_VALUE', new Int64(0, -0x80000000));
defineFrozen(Int64, 'ZERO', new Int64(0, 0));
defineFrozen(Int64, 'ONE', new Int64(1, 0));
defineFrozen(Int64, 'NEG_ONE', new Int64(-1, -1));

Int64.prototype.equals = function (other) {
	if (!(other instanceof Int64)) {
		return +this == other;
	}
	return this.low === other.low && this.high === other.high;
};

function defineFrozen(obj, key, value) {
	Object.defineProperty(obj, key, {
		writable: false,
		enumerable: true,
		configurable: false,
		value: value
	});
}
