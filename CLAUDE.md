# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**better-sqlite3** is a Node.js native addon providing synchronous SQLite database access. It's architected as a hybrid C++/JavaScript library where C++ handles direct SQLite operations and JavaScript provides the high-level API.

## Build & Development Commands

### Essential Commands
- **Build**: `npm run build-release` (production build)
- **Debug Build**: `npm run build-debug` 
- **Full Rebuild**: `npm run rebuild-release` (includes LZZ preprocessing)
- **Test**: `npm test` (mocha with 5s timeout)
- **Single Test**: `npx mocha test/[test-file].js`
- **Benchmark**: `npm run benchmark`

### LZZ-Specific (Current Architecture)
- **Generate C++**: `npm run lzz` (preprocesses .lzz files to .cpp/.hpp)
- **Download SQLite**: `npm run download`

## Architecture

### Code Organization
```
lib/                    # JavaScript API layer
├── index.js           # Main export (Database constructor)
├── database.js        # Database class with native binding
└── methods/           # Method implementations

src/                   # C++ source (LZZ-based)
├── better_sqlite3.lzz # Main file (generates .cpp/.hpp)
├── objects/           # Core classes (Database, Statement, etc.)
└── util/              # Utilities and type conversion
```

### Critical LZZ Pattern
- **Never edit `.cpp` or `.hpp` files directly** - they are generated
- Edit `.lzz` files only, then run `npm run lzz`
- Uses `#insert` directive (literal inclusion, not C++ #include)
- Single compilation unit architecture
- Order dependency matters in .lzz files

### LZZ Migration Status
This codebase is currently migrating away from LZZ (see `lzz-migration.md`). The current branch `no-lzz-20250428` contains migration work. Be aware that the build process may change during this transition.

## Native Addon Structure

### Data Flow
```
JavaScript API → C++ Native Methods → SQLite C API → Results → Type Conversion → JavaScript
```

### Key Classes
- `Database`: Main database connection and operations
- `Statement`: Prepared SQL statements  
- `StatementIterator`: Row iteration
- `Backup`: Database backup functionality

### Type Conversion
The C++ layer handles conversion between SQLite types and V8/JavaScript types, including support for 64-bit integers, Buffers, and BigInts.

## Testing

Tests are organized by functionality in `test/`:
- `00.setup.js`: Global test setup
- `10-19.*`: Database-level operations
- `20-29.*`: Statement operations  
- `30-39.*`: Advanced features (transactions, custom functions)
- `40-50.*`: Special cases (BigInts, worker threads, unsafe mode)

## Development Workflow

1. **For C++ changes**: Edit `.lzz` files → `npm run lzz` → `npm run build-release` → `npm test`
2. **For JavaScript changes**: Edit files in `lib/` → `npm test`
3. **Performance testing**: Use `npm run benchmark` after changes

## Important Notes

- This is a **synchronous** SQLite library (no async/await)
- Single-threaded SQLite access for performance
- Uses Node.js N-API for forward compatibility
- Embeds SQLite source in `deps/` directory
- Supports Node.js 20.x, 22.x, 23.x, 24.x