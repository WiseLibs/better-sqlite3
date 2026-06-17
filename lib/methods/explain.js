'use strict';

module.exports = function explain(sql) {
	if (typeof sql !== 'string') throw new TypeError('Expected first argument to be a string');
	
	const explainSql = sql.trim().toUpperCase().startsWith('EXPLAIN') 
		? sql 
		: `EXPLAIN ${sql}`;

	const stmt = this.prepare(explainSql);

	try {
		return stmt.all();
	} catch (e) {
		if (e.message && (e.message.includes('Too few parameter') || e.message.includes('Missing named parameter'))) {
			const namedParams = sql.match(/:(\w+)|@(\w+)|\$(\w+)/g);
			
			if (namedParams && namedParams.length > 0) {
				const params = {};
				for (const param of namedParams) {
					const name = param.substring(1);
					params[name] = null;
				}
				return stmt.all(params);
			}
			let low = 1;
			let high = 100;
			
			while (low <= high) {
				const mid = Math.floor((low + high) / 2);
				try {
					return stmt.all(Array(mid).fill(null));
				} catch (err) {
					if (err.message && err.message.includes('Too few')) {
						low = mid + 1;
					} else if (err.message && err.message.includes('Too many')) {
						high = mid - 1;
					} else {
						throw err;
					}
				}
			}
		}
		throw e;
	}
};

