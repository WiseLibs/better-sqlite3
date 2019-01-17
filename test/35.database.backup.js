'use strict';
const Database = require('../.');

describe('Database#backup()', function () {
  beforeEach(function () {
    this.db = new Database(util.next());
  });
  afterEach(function () {
    this.db.close();
  });

  it('should be tested');
});
