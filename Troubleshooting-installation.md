If you have trouble installing `better-sqlite3`, follow this checklist:

1. Make sure you're using nodejs v4.8.4 or later

2. Make sure you have [`node-gyp`](https://github.com/nodejs/node-gyp#installation) globally installed, including all of [its dependencies](https://github.com/nodejs/node-gyp#on-unix)

3. If the error message said something about python, [install python 2.7](https://www.python.org/downloads/) and then run `npm config delete python`

4. If the error message included `exit code 3221225506`, this package might be triggering a false positive in your anti-virus software

5. If you're using [Electron](https://github.com/electron/electron), try running [`electron-rebuild`](https://www.npmjs.com/package/electron-rebuild)

6. If nothing else worked, try adding `LZZ_COMPAT=1` to your environment variables


If none of these solved your problem, try browsing [previous issues](https://github.com/JoshuaWise/better-sqlite3/issues?q=is%3Aissue) or open a [new issue](https://github.com/JoshuaWise/better-sqlite3/issues/new).
