'use strict';

module.exports = function (db, count, SQL, values, callback) {
	if (db.pragma) {
		var run = function (values, cb) {
			cb(null, db.statement(SQL).run(values));
		};
	} else {
		var run = function (values, cb) {
			db.run(SQL, values, cb);
		};
	}
	
	var ranCount = 0;
	for (var i=0; i<count; ++i) {
		run(values, ran);
	}
	function ran(err) {
		if (err) {
			console.log('Error: Failed to fill table.');
		}
		if (++ranCount === count) {
			callback();
		}
	}
};
