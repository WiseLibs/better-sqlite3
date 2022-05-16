# Troubleshooting installation

If you have trouble installing `better-sqlite3`, follow this checklist:

## Install a recent Node.js

1. Make sure you're using Node.js v14.19.2 or later. 
2. If you're on Windows, while installing, be sure to select "Automatically install the necessary tools" on the "Tools for Native Modules" page, and follow the remaining steps, including opening an admin PowerShell and installing visual studio and python. Everything _should_ just work.

## Install the `node-gyp` toolchain

1. Make sure you have [`node-gyp`](https://github.com/nodejs/node-gyp#installation) globally installed
1. Make sure all [`node-gyp` dependencies are installed](https://github.com/nodejs/node-gyp#on-unix). On Windows you may need to [configure some things manually](https://github.com/nodejs/node-gyp#on-windows). Use `npm ls node-gyp` to make sure none of your local packages installed an outdated version of `node-gyp` that is used over the global one.

## No special characters in your project path

1. Make sure there are no spaces in your project path: `node-gyp` may not escape spaces or special characters (like `%` or `$`) properly.

## Electron

1. If you're using [Electron](https://github.com/electron/electron), try running [`electron-rebuild`](https://www.npmjs.com/package/electron-rebuild)

## Windows

If you still have issues on Windows and are on an older version of Node, try these steps: 

1. Install the **latest** of node 12, 14, or 16.
1. Install **latest** Visual Studio Community and Desktop Development with C++ extension.
1. Install **latest** Python.
1. Run following commands:
```
npm config set msvs_version 2019
npm config set msbuild_path "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"
```
1. Delete your `node_modules` subdirectory
1. Delete your `$HOME/.node-gyp` directory
1. Run `npm install`

## If all else fails

If none of these solved your problem, try browsing [previous issues](https://github.com/JoshuaWise/better-sqlite3/issues?q=is%3Aissue) or open a [new issue](https://github.com/JoshuaWise/better-sqlite3/issues/new).
