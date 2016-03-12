'use strict';
var util = require('util');
var EventEmitter = require('events').EventEmitter;

function EventEmitterAsync() {
	EventEmitter.call(this);
}
util.inherits(EventEmitterAsync, EventEmitter);
EventEmitterAsync.prototype.emitAsync = function () {
	var self = this;
	var len = arguments.length;
	var args = new Array(len);
	for (var i=0; i<len; i++) {args[i] = arguments[i];}
	setImmediate(function () {
		self.emit.apply(self, args);
	});
};
module.exports = EventEmitterAsync;
