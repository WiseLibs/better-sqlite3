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

	// Otherwise, try to find the binding as a prebuilt binary.
	let filename = getPrebuildPath();
	if (filename) {
		return DEFAULT_ADDON = require(filename);
	}

	// If no prebuilt binary was found, try the default node-gyp locations.
	filename = path.join(__dirname, '..', 'build', 'Debug', 'better_sqlite3.node');
	if (!fs.existsSync(filename)) {
		filename = path.join(__dirname, '..', 'build', 'Release', 'better_sqlite3.node');
	}
	return DEFAULT_ADDON = require(filename);
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
	return process.platform === 'linux' && !process.report.getReport().header.glibcVersionRuntime;
}

exports.getBinding = getBinding;
exports.getPrebuildPath = getPrebuildPath;

// This script is executed directly by binding.gyp to detect prebuilt binaries.
if (require.main === module) {
	process.stdout.write(getPrebuildPath() ? '1' : '0');
}
