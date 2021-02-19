'use strict';

module.exports = (setAuthorizer) => {
    return function defineAuthorizer(fn) {
        if(fn !== null) { // must be a valid function if not null
            if (typeof fn !== 'function') {
                throw new TypeError('Expected argument to be a function');
            }
            
            if(fn.length != 5) {
                throw new RangeError('Authorizer function must accept exactly 5 arguments')
            }
        }

        return setAuthorizer.call(this, fn)
    }
}