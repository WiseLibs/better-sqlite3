# Migration from .lzz to Standard C++ Files

## Overview
Migrate better-sqlite3 from using .lzz (Lazy C++) to standard .cpp/.hpp files. The current architecture uses #insert directives to create a single compilation unit, which requires a careful migration approach.

## Critical Understanding
- **Current Build**: All .lzz files are processed as ONE unit through `src/better_sqlite3.lzz`
- **#insert != #include**: The #insert directive literally inserts file contents during preprocessing
- **Single .cpp Output**: Currently produces only `better_sqlite3.cpp` and `better_sqlite3.hpp`

## Migration Approach: Option A (Recommended - Low Risk)
Preserve the single compilation unit architecture while removing lzz dependency.

### Phase 1: Preparation
- [ ] Create a backup branch for safety
- [ ] Document the current #insert order from `better_sqlite3.lzz`
- [ ] Verify lzz is installed and working

### Phase 2: Generate Baseline
- [ ] Run lzz WITHOUT #line directives:
  ```bash
  lzz -hx hpp -sx cpp -k BETTER_SQLITE3 -d -e ./src/better_sqlite3.lzz
  ```
- [ ] Backup the generated files:
  ```bash
  cp src/better_sqlite3.hpp src/better_sqlite3.hpp.generated
  cp src/better_sqlite3.cpp src/better_sqlite3.cpp.generated
  ```
- [ ] Verify the build still works with these generated files

### Phase 3: Split Generated Code
- [ ] Create directory structure for split files:
  ```bash
  mkdir -p src/util src/objects
  ```
- [ ] Manually extract code from generated files into individual .hpp files:
  - [ ] `src/util/macros.hpp` - Extract macro definitions
  - [ ] `src/util/query-macros.hpp` - Extract query macros
  - [ ] `src/util/constants.hpp` - Extract constants
  - [ ] `src/util/bind-map.hpp` - Extract BindMap class
  - [ ] `src/objects/database.hpp` - Extract Database class
  - [ ] `src/objects/statement.hpp` - Extract Statement class
  - [ ] `src/objects/statement-iterator.hpp` - Extract StatementIterator
  - [ ] `src/objects/backup.hpp` - Extract Backup class
  - [ ] `src/util/data-converter.hpp` - Extract data conversion utilities
  - [ ] `src/util/custom-function.hpp` - Extract custom function code
  - [ ] `src/util/custom-aggregate.hpp` - Extract custom aggregate code
  - [ ] `src/util/custom-table.hpp` - Extract custom table code
  - [ ] `src/util/data.hpp` - Extract data handling code
  - [ ] `src/util/binder.hpp` - Extract binder utilities

### Phase 4: Create New Main Files
- [ ] Create new `src/better_sqlite3.hpp` that includes all headers in correct order:
  ```cpp
  #pragma once
  #include <climits>
  #include <cstdio>
  // ... other system includes ...
  
  #include "util/macros.hpp"
  #include "util/query-macros.hpp"
  #include "util/constants.hpp"
  #include "util/bind-map.hpp"
  // Forward declarations
  struct Addon;
  class Statement;
  class Backup;
  #include "objects/database.hpp"
  #include "objects/statement.hpp"
  #include "objects/statement-iterator.hpp"
  #include "objects/backup.hpp"
  #include "util/data-converter.hpp"
  #include "util/custom-function.hpp"
  #include "util/custom-aggregate.hpp"
  #include "util/custom-table.hpp"
  #include "util/data.hpp"
  #include "util/binder.hpp"
  // Addon struct definition
  ```
- [ ] Update `src/better_sqlite3.cpp` to use the new header structure

### Phase 5: Verify and Test
- [ ] Build the project: `npm run build-release`
- [ ] Run the test suite: `npm test`
- [ ] Run benchmarks to ensure no performance regression
- [ ] Check that all exports work correctly

### Phase 6: Update Build System
- [ ] Update `package.json` to remove lzz script
- [ ] Update documentation to remove lzz references
- [ ] Update contribution guide

### Phase 7: Cleanup
- [ ] Once all tests pass, remove .lzz files
- [ ] Remove lzz from development dependencies
- [ ] Create a PR with the changes

## Alternative: Option B (Future Enhancement)
Convert to proper modular architecture with separate compilation units.

### Additional Steps for Option B:
- [ ] Analyze dependencies between modules
- [ ] Add proper .cpp files for each module
- [ ] Update binding.gyp to include all .cpp files
- [ ] Resolve circular dependencies
- [ ] Enable parallel compilation

## Rollback Plan
If issues arise:
1. Git reset to backup branch
2. Restore original .lzz files
3. Rebuild with lzz

## Success Criteria
- [ ] All tests pass
- [ ] No performance regression
- [ ] No lzz dependency
- [ ] Clean build without warnings
- [ ] Documentation updated