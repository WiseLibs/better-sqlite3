'use strict';
let dbId = 0;

const current = () => `temp/${dbId}.db`;
const next = () => (++dbId, current());

Object.assign(exports, { current, next });
