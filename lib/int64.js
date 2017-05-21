var path = require('path');
var Int64 = module.exports = require('bindings')({
	bindings: 'better_sqlite3.node',
	module_root: path.resolve(__dirname, '..'),
}).Int64;

defineFrozen(Int64, 'MAX_VALUE', new Int64(-1, 0x7fffffff));
defineFrozen(Int64, 'MIN_VALUE', new Int64(0, -0x80000000));
defineFrozen(Int64, 'ZERO', new Int64(0, 0));
defineFrozen(Int64, 'ONE', new Int64(1, 0));
defineFrozen(Int64, 'NEG_ONE', new Int64(-1, -1));

Int64.prototype.equals = function equals(other) {
	if (typeof other === 'string') {
		return this.toString() === other;
	}
	if (typeof other === 'number') {
		return this.isSafe() && this.valueOf() === other;
	}
	if (hasInt64Interface(other)) {
		return this.low === other.low && this.high === other.high;
	}
	return false;
};
Int64.prototype.value = function value() {
	return new Int64(this.low, this.high);
};

function hasInt64Interface(value) {
	return value !== null
		&& (typeof value === 'object' || typeof value === 'function')
		&& typeof value.low === 'number'
		&& typeof value.high === 'number';
}

function defineFrozen(obj, key, value) {
	Object.defineProperty(obj, key, {
		writable: false,
		enumerable: true,
		configurable: false,
		value: value
	});
}
