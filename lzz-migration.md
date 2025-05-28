# LZZ Migration Analysis

## Current Architecture

### How LZZ Works in better-sqlite3
1. **Single Entry Point**: All code is processed through `src/better_sqlite3.lzz`
2. **#insert Directive**: Functions like C's `#include` but literally inserts file contents during lzz preprocessing
3. **Single Compilation Unit**: Everything compiles as one large .cpp file
4. **Build Process**: `lzz -hx hpp -sx cpp -k BETTER_SQLITE3 -d -hl -sl -e ./src/better_sqlite3.lzz`

### LZZ Syntax
- `#hdr ... #end` - Content for header file (.hpp)
- `#src ... #end` - Content for source file (.cpp)
- `#insert "file.lzz"` - Include another .lzz file (processed inline, not like #include)

### Command Line Options Used
- `-hx hpp` - Set header extension to .hpp
- `-sx cpp` - Set source extension to .cpp
- `-k BETTER_SQLITE3` - Package name for include guards
- `-d` - Delete old files no longer created
- `-hl -sl` - Output #line directives (REMOVE for migration)
- `-e` - Preprocess all code

### File Structure
```
src/better_sqlite3.lzz (main file)
├── #insert util/macros.lzz
├── #insert util/query-macros.lzz
├── #insert util/constants.lzz
├── #insert util/bind-map.lzz
├── #insert objects/database.lzz
├── #insert objects/statement.lzz
├── #insert objects/statement-iterator.lzz
├── #insert objects/backup.lzz
├── #insert util/data-converter.lzz
├── #insert util/custom-function.lzz
├── #insert util/custom-aggregate.lzz
├── #insert util/custom-table.lzz
├── #insert util/data.lzz
└── #insert util/binder.lzz
```

### All LZZ Files (15 total)
- **Main**: `src/better_sqlite3.lzz`
- **Objects** (4): `backup.lzz`, `database.lzz`, `statement.lzz`, `statement-iterator.lzz`
- **Utils** (10): `bind-map.lzz`, `binder.lzz`, `constants.lzz`, `custom-aggregate.lzz`, `custom-function.lzz`, `custom-table.lzz`, `data.lzz`, `data-converter.lzz`, `macros.lzz`, `query-macros.lzz`

## Key Challenges

1. **Interdependencies**: Files depend on types/macros defined in files inserted before them
2. **Order Matters**: The specific insertion order is critical for compilation
3. **Single Unit**: Currently everything is one compilation unit, which may hide circular dependencies
4. **#insert vs #include**: Cannot simply run lzz on each file individually

## Migration Options

### Option A: Preserve Single Compilation Unit
**Approach**: Maintain the current architecture but with standard C++ files

**Steps**:
1. Run lzz once on the main file to generate a single .cpp/.hpp pair
2. Manually split the generated code into individual .hpp files matching the original .lzz structure
3. Create one main .cpp file that includes all .hpp files in the correct order
4. Keep the same compilation model (one big .cpp file)

**Advantages**:
- Minimal risk of breaking functionality
- Preserves current compilation behavior
- Easier to verify correctness
- No need to resolve circular dependencies

**Disadvantages**:
- Still compiles as one large unit (slower builds)
- Doesn't improve code organization
- Header dependencies remain unclear

**Detailed Instructions**:
```bash
# 1. Generate baseline without #line directives
lzz -hx hpp -sx cpp -k BETTER_SQLITE3 -d -e ./src/better_sqlite3.lzz

# 2. Backup generated files
cp src/better_sqlite3.hpp src/better_sqlite3.hpp.backup
cp src/better_sqlite3.cpp src/better_sqlite3.cpp.backup

# 3. Manually split the .hpp content into individual files:
#    - src/util/macros.hpp
#    - src/util/constants.hpp
#    - etc.

# 4. Create new src/better_sqlite3.hpp that includes all headers:
#include "util/macros.hpp"
#include "util/query-macros.hpp"
// ... in the same order as #insert directives

# 5. Update src/better_sqlite3.cpp to include the split headers
```

### Option B: Proper Modular Architecture
**Approach**: Convert to standard C++ with individual compilation units

**Steps**:
1. Analyze dependencies between .lzz files
2. Convert each .lzz to proper .hpp/.cpp pairs
3. Replace #insert with #include
4. Update binding.gyp to compile all .cpp files
5. Resolve any circular dependencies

**Advantages**:
- Better build times (parallel compilation)
- Clearer code organization
- Easier to maintain
- Standard C++ practices

**Disadvantages**:
- Higher risk of breaking functionality
- May expose hidden circular dependencies
- Requires careful dependency analysis
- More complex migration

**Detailed Instructions**:
```bash
# 1. Create dependency graph
# Analyze each .lzz file to understand what it needs from others

# 2. Start with leaf nodes (files with no dependencies on other .lzz files)
# Typically: macros.lzz, constants.lzz

# 3. For each .lzz file:
#    a. Extract #hdr content → .hpp file
#    b. Extract #src content → .cpp file
#    c. Add proper includes instead of relying on #insert order
#    d. Add include guards to .hpp files

# 4. Update binding.gyp:
'sources': [
  'src/better_sqlite3.cpp',
  'src/objects/database.cpp',
  'src/objects/statement.cpp',
  'src/objects/statement-iterator.cpp',
  'src/objects/backup.cpp',
  'src/util/data.cpp',
  'src/util/binder.cpp',
  // ... all other .cpp files
]

# 5. Test incrementally after converting each module
```

## Dependency Analysis

### Known Dependencies:
- All files depend on `util/macros.lzz` (macro definitions)
- Object files depend on each other (forward declarations exist)
- `util/data.lzz` likely depends on most type definitions
- `util/binder.lzz` depends on data structures from other utils

### Recommended Conversion Order:
1. `util/macros.lzz` - No dependencies
2. `util/constants.lzz` - Only depends on macros
3. `util/query-macros.lzz` - Only depends on macros
4. `util/bind-map.lzz` - Basic utility
5. Other utils in dependency order
6. Object files (may need forward declarations)

## Risk Assessment

### Option A Risk: **LOW**
- Preserves exact current behavior
- Easy to verify correctness
- Can always fall back to original

### Option B Risk: **MEDIUM-HIGH**
- May expose hidden issues
- Requires careful testing
- Could improve code quality significantly

## Migration Options (continued)

### Option C: Automated Split Using #line Directives
**Approach**: Use lzz's #line directives as metadata to automate file splitting

**Steps**:
1. Generate files WITH #line directives to use as splitting guides
2. Parse #line directives to automatically split into correct files
3. Clean up the split files and remove #line directives
4. Maintain single compilation unit or modularize as needed

**Advantages**:
- Automated and accurate file splitting
- No manual boundary detection needed
- Preserves exact lzz file organization
- Less error-prone than manual splitting
- Can be scripted for repeatability

**Disadvantages**:
- Requires writing a parsing script
- Still need to clean up #line directives
- Temporary use of "dirty" files with #line

**Detailed Instructions**:
```bash
# 1. Generate with #line directives (intentionally keeping them)
lzz -hx hpp -sx cpp -k BETTER_SQLITE3 -d -hl -sl -e ./src/better_sqlite3.lzz

# 2. Backup the #line-annotated files
cp src/better_sqlite3.hpp src/better_sqlite3.hpp.withlines
cp src/better_sqlite3.cpp src/better_sqlite3.cpp.withlines

# 3. Parse #line directives to understand file boundaries
# Example #line format: #line 1 "util/macros.lzz"
# This indicates the following content originated from util/macros.lzz

# 4. Write a script to:
#    a. Read the generated .hpp file
#    b. Split content based on #line directives
#    c. Create individual .hpp files for each original .lzz file
#    d. Remove all #line directives from the split files

# 5. For the .cpp file:
#    - Keep as single compilation unit (Option C-A), OR
#    - Split into modules using same #line parsing (Option C-B)

# 6. Create new src/better_sqlite3.hpp that includes all split headers:
#include "util/macros.hpp"
#include "util/query-macros.hpp"
// ... in original #insert order

# 7. Test the build and remove .lzz files
```

**Sample Splitting Script Logic**:
```python
# Pseudocode for splitting based on #line
current_file = None
current_content = []

for line in generated_file:
    if line.startswith('#line'):
        # Parse: #line 123 "path/to/file.lzz"
        if current_file:
            write_content_to_file(current_file, current_content)
        current_file = extract_path_from_line_directive(line)
        current_content = []
    elif not line.startswith('#line'):
        current_content.append(line)

# Write final file
if current_file:
    write_content_to_file(current_file, current_content)
```

## Recommendation

**Option C** is likely the best approach because it:
1. Automates the most error-prone part (identifying file boundaries)
2. Guarantees correct file organization matching original .lzz structure
3. Can be validated by comparing against original .lzz files
4. Provides a clear migration path with less manual work

After using Option C to split files, you can then decide whether to:
- Keep single compilation unit (simpler, like Option A)
- Move to modular compilation (cleaner, like Option B)