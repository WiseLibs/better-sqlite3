import insert from './insert.js';
import select from './select.js';
import selectAll from './select-all.js';
import selectIterate from './select-iterate.js';
import transaction from './transaction.js';

export default {
	'insert': insert,
	'select': select,
	'select-all': selectAll,
	'select-iterate': selectIterate,
	'transaction': transaction,
};