# Troubleshooting installation

If you have trouble installing `better-sqlite3`, follow this checklist:

1. Make sure you're using nodejs v6.11.4 or later.

2. Make sure you have [`node-gyp`](https://github.com/nodejs/node-gyp#installation) globally installed, including all of [its dependencies](https://github.com/nodejs/node-gyp#on-unix). On Windows you may need to [configure some things manually](https://github.com/nodejs/node-gyp#on-windows).

3. If the error message said something about python, [install python 2.7](https://www.python.org/downloads/) (not 3) and then run `npm config delete python`, and [make sure python is in your PATH variable](https://github.com/JoshuaWise/better-sqlite3/issues/64#issuecomment-327029706).

4. If you're using [Electron](https://github.com/electron/electron), try running [`electron-rebuild`](https://www.npmjs.com/package/electron-rebuild).

If none of these solved your problem, try browsing [previous issues](https://github.com/JoshuaWise/better-sqlite3/issues?q=is%3Aissue) or open a [new issue](https://github.com/JoshuaWise/better-sqlite3/issues/new).
