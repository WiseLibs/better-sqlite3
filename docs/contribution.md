# Contribution

## Introduction and scope

`better-sqlite3` is a low-level Node.js package that provides bindings to [SQLite](https://sqlite.org/index.html). `better-sqlite3` is not an ORM, and does not lend itself to specific types of applications or frameworks.

Anything that SQLite does not directly provide is considered out-of-scope for `better-sqlite3`. Anything that SQLite *does* directly provide *may* be considered in-scope for `better-sqlite3`, with the additional requirement that:

- it can be implemented sensibly and safely (i.e., it cannot lead to [undefined behavior](https://en.wikipedia.org/wiki/Undefined_behavior))
- it is used commonly enough to warrent the extra code complexity that it brings
- it cannot be reasonably implemented by a user in JavaScript (e.g., by monkey-patching)

#### Native addons

`better-sqlite3` is a combination of JavaScript and C++. The C++ part is necessary in order to communicate with the [underlying SQLite library](https://sqlite.org/index.html), which is written in C.

Node.js supports [C++ addons](https://nodejs.org/api/addons.html) through a [build system](https://nodejs.org/api/addons.html#building) called [`node-gyp`](https://github.com/nodejs/node-gyp), which is automatically bundled with every installation of [npm](https://docs.npmjs.com/about-npm).

On most systems, C++ addons will simply be compiled as part of the installation process when running `npm install`. However, [history has shown](https://github.com/nodejs/node-gyp/issues/629) that Windows users have struggled significantly when trying to build C++ addons for Node.js. This is an issue with Node.js as a whole, and not specific to `better-sqlite3`.

#### Electron

`better-sqlite3` is a Node.js package, *not* an [Electron](https://www.electronjs.org/) package. Electron is considered a third-party platform that is not officially supported. However, many users do find great success in using `better-sqlite3` with Electron, and helpful contributors such as @mceachen have provided support to the Electron community.

#### TypeScript

Lastly, `better-sqlite3` is a JavaScript package, not a TypeScript package. Type definitions have been generously provided by the community at [`@types/better-sqlite3`](https://www.npmjs.com/package/@types/better-sqlite3), but no official support for TypeScript is currently provided (this may change in the future).

## Principles

Code that is contributed to `better-sqlite3` must adhere to the following principles, prioritized from first to last:

#### 1) Correctness

Code must behave as expected in all siutations. Many times when writing new features, only the nominal case is considered. However, many edge cases exist when you consider race conditions, uncommon states, and improper usage. All possibilities of improper usage must be detected, and an appropriate error must be thrown (never ignored). All possibilities of proper usage must be supported, and must behave as expected.

#### 2) Simplicity

The API that users interact with to operate `better-sqlite3` must be as simple as possible. Rather than calling 3 functions in a specific order, it's simpler for users to call a single function. Rather than providing many similar functions for doing similar things (e.g., "convenience functions"), there should just be one function that is already convenient by design. Sane defaults should be applied when possible. A function's minimal call signature should be as small as possible, with progressively complex customization available when needed. Function names should only be as long as necessary to convey their purpose. For any new feature, it should be easy to showcase code examples that is are so simple that they are self-explanatory.

This principle only applies to the public API, not necessarily to internal functions.

#### 3) Readability

Code must be written in a way that is intuitive and understandable by other programmers, now and in the future. Some code is naturally complex, and thus should be explained with comments (only when necesary). Code should be written in a style that is similar to existing code.

#### 4) Performance

Code should be written such that it does not use unnecessary computing resources. If a task can be accomplished without copying a potentially large buffer, it should be. If a complex algorithm can generally be avoided with a simple check, it should be. Calls to the operating system or filesystem should be limited to only occur when absolutely necessary. The API that users interact with should naturally encourage good performance habits, such as re-using prepared statements.

It's okay to sacrifice readability for performance if doing so has a clear, measureable benefit to users.

## How to contribute

If you've never written a native addon for Node.js before, you should start by reading the [official documentation](https://nodejs.org/api/addons.html) on the subject.

#### C++

The C++ code in `better-sqlite3` is written using a tool called [`lzz`](https://github.com/WiseLibs/lzz), which alleviates the programmer from needing to write header files. If you plan on changing any C++ code, you'll need to edit `*.lzz` files and then re-compile them into `*.cpp` and `*.hpp` by running `npm run lzz` (while the `lzz` executable is in your PATH). You can learn how to download and install `lzz` [here](https://github.com/WiseLibs/lzz).

#### Style guide

There is currently no linter or style guide associated with `better-sqlite3` (this may change in the future). For now, just try to match the style of existing code as much as possible. Code owners will reject your PR or rewrite your changes if they feel that you've used a coding style that doesn't match the existing code. Although the rules aren't layed out formally, you are expected to adhere to them by using your eyeballs.

#### Testing

All tests are written in JavaScript, and they test `better-sqlite3`'s public API. All new features must be accompinied by a robust set of tests that scrutinize the new feature under all manner of circumstances and edge cases. It's not enough to simply test the "common case". If you write code that detects errors and throws exceptions, those error cases should be tested too, to ensure that all errors are being properly detected. If a new feature interacts with existing features, those interactions must be tested as well.

#### Documentation

All new feature must be accompinied by [clear documentation](./api.md). All new methods and classes must be included in the [Table of Contents](./api.md#api), and must include code examples. Documentation must follow the existing formatting:

- Literal values use code formatting (monospace)
	- Examples: `"my string"`, `true`, `false`, `null`, `undefined`, `123`
- Package names and code identifiers use code formatting
	- Examples: `better-sqlite3`, `db.myMethod()`, `options.readOnly`, `this`
- Primitive data types are lower-cased, while other data types are capatalized
	- Examples: `string`, `number`, `Buffer`, `Database`
- References to other classes or methods must be linked and use code formatting
	- Examples: [`.get()`](./api.md#getbindparameters---row), [`new Database()`](./api.md#new-databasepath-options)
- Function signatures are written as:
	- .funcName(*requiredArg*, [*optionalArg*]) -> *returnValue*
	- Note that the arguments and return values are *italicized*
- All code examples should be highlighted using `js` syntax, except for bash commands which don't need highlighting

## Categories of contribution

Depending on the nature of your contribution, it will be held to a different level of scrutiny, from lowest to highest:

#### 1) General maintenance

These changes are self-explanatory. They include:

- Updating the bundled version of SQLite (using [this workflow](https://github.com/WiseLibs/better-sqlite3/actions/workflows/update-sqlite.yml))
- Updating dependencies in `package.json`
- Adding prebuild binaries for a new version of Node.js or Electron
- Adding prebuild binaries for a new architecture or operating system

These kinds of updates happen on a regular basis, and require zero knowledge of `better-sqlite3`'s code. Trusted contributors can merge these changes without approval from the original author.

#### 2) Documentation

Changes to documentation are usually helpful and harmless. However, they should be treated with a higher level of scrutiny because they affect how users learn about and use `better-sqlite3`. Importance is placed on the correctness and truthfuness of documentation. For example, documentation should not "go out of date" based on events outside of our control.

Depending on the type of documentation, trusted contributors might be able to merge these changes without approval from the original author.

#### 3) Minor quality-of-life improvements

These are code changes with a very small blast radius, such as adding a new read-only property to an object, or augmenting a function with a new option that gets passed directly to SQLite. These changes are *probably* harmless, but require additional scrutiny because they must be thoroughly tested and documented. These changes must be completely backwards-compatible, unless they're part of a major version update.

#### 4) New features

These are code changes with a substantial blast radius, such as implementing a new class or method. These changes must be completely backwards-compatible, unless they're part of a major version update.

New features are rarely accepted from external contributors because they are rarely held to the extremely high standard that `better-sqlite3` sets for itself. New features must behave correctly in all possible circumstances, including race conditions and edge cases. Likewise, even the most obscure circumstances must have test cases covering them.

When implementing a new feature, ask yourself:

- What could go wrong if I use this feature while executing a [user-defined function](./api.md#functionname-options-function---this)?
- What could go wrong if I use this feature while [iterating](./api.md#iteratebindparameters---iterator) through a prepared statement?
- What could go wrong if I use this feature while the database is [closed](./api.md#close---this)?
- What could go wrong if I use this feature from within the [verbose callback](./api.md#new-databasepath-options)?
- What could go wrong if I use this feature from within a [transaction](./api.md#transactionfunction---function)?
- What could go wrong if I use this feature on a prepared statement that has [bound parameters](./api.md#bindbindparameters---this)?
- What could go wrong if I use this feature within a [worker thread](./threads.md#worker-threads)?
- Should the user's [64-bit integer setting](integer.md#the-bigint-primitive-type) affect this feature?
- If this feature accepts a callback function:
	- What could go wrong if that callback function throws an exception?
	- What could go wrong if that callback function is triggered during one of the above scenarios?

People love `better-sqlite3` because of its robustness and reliability. Each and every feature of `better-sqlite3` accounts for every single scenario listed above. Additionally, all possible error scenarios are explicitly handled and tested. Any new feature of `better-sqlite3` must be held to the same standard. Currently, no new features are merged without approval from the original author.
