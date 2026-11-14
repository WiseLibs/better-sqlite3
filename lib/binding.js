'use strict';
const fs = require('fs');
const path = require('path');

const PREBUILD_PLATFORMS = ['linux', 'darwin', 'win32'];
const PREBUILD_ARCHS = ['x64', 'arm64'];
let DEFAULT_ADDON;

function getBinding(nativeBinding) {
	// If a path was provided, load the binding from the filesystem.
	if (typeof nativeBinding === 'string') {
		// See <https://webpack.js.org/api/module-variables/#__non_webpack_require__-webpack-specific>
		const requireFunc = typeof __non_webpack_require__ === 'function' ? __non_webpack_require__ : require;
		return requireFunc(path.resolve(nativeBinding).replace(/(\.node)?$/, '.node'));
	}

	// If an object was provided, use it as the binding directly.
	if (typeof nativeBinding === 'object' && nativeBinding !== null) {
		return nativeBinding;
	}

	// If we're using the default binding and it already exists, just return it.
	if (DEFAULT_ADDON) {
		return DEFAULT_ADDON;
	}

	// Otherwise, try the default node-gyp locations, which only contain a
	// binary if one was compiled on purpose.
	let filename = path.join(__dirname, '..', 'build', 'Debug', 'better_sqlite3.node');
	if (!fs.existsSync(filename)) {
		filename = path.join(__dirname, '..', 'build', 'Release', 'better_sqlite3.node');
	}
	if (fs.existsSync(filename)) {
		return DEFAULT_ADDON = require(filename);
	}

	// If nothing was compiled, try to find the binding as a prebuilt binary.
	return DEFAULT_ADDON = require(getPrebuildPath() || filename);
}

function getPrebuildPath() {
	if (PREBUILD_PLATFORMS.includes(process.platform) && PREBUILD_ARCHS.includes(process.arch)) {
		const target = `${isLinuxMusl() ? 'linuxmusl' : process.platform}-${process.arch}`;
		const filename = path.join(__dirname, '..', 'prebuilds', `${target}.node`);
		if (fs.existsSync(filename)) {
			return filename;
		}
	}
	return null;
}

function isLinuxMusl() {
	if (process.platform !== 'linux') {
		return false;
	}

	// Look at which libc loader is mapped into this process (See #1517, #1527).
	try {
		const maps = fs.readFileSync('/proc/self/maps', 'latin1');
		if (/\/ld-musl-[^/\s]*\.so/.test(maps)) return true;
		if (/\/(?:ld-linux[^/\s]*|libc)\.so\.\d/.test(maps)) return false;
	} catch {}

	// Fallback detection (less reliable, potentially slow).
	const { report } = process;
	const previousExcludeNetwork = report.excludeNetwork;
	report.excludeNetwork = true;
	try {
		return !report.getReport().header.glibcVersionRuntime;
	} finally {
		report.excludeNetwork = previousExcludeNetwork;
	}
}

exports.getBinding = getBinding;
exports.getPrebuildPath = getPrebuildPath;

// This script is executed directly by binding.gyp to detect prebuilt binaries.
if (require.main === module) {
	process.stdout.write(getPrebuildPath() ? '1' : '0');
}
