'use strict';

module.exports = function (db, count, SQL, values, callback) {
	var newStatement = db.prepare ? function () {return db.prepare(SQL);}
	                              : function () {return db.statement(SQL);};
	
	var ranCount = 0;
	for (var i=0; i<count; ++i) {
		newStatement().run(values, ran);
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
