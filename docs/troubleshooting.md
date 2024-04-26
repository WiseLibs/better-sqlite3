# Troubleshooting installation

If `better-sqlite3` refuses to install, follow these guidelines:

## Use the latest version of better-sqlite3

- Check the [releases page](https://github.com/WiseLibs/better-sqlite3/releases) to make sure you're using the latest and greatest.

## Install a recent Node.js

- Make sure you're using a [supported version of Node.js](https://nodejs.org/en/about/previous-releases). `better-sqlite3` is only tested with currently-supported versions of Node.js.

## "Install the necessary tools" 
   
- If you're on Windows, during installation of Node.js, be sure to select "Automatically install the necessary tools" from the "Tools for Native Modules" page.

- If you missed this when you installed Node.js, double-click `C:\Program Files\nodejs\install_tools.bat` from the File Explorer or run it in a terminal.

This will open an administrative PowerShell terminal and installing Chocolatey, Visual Studio, and Python.

This may take several minutes.

## No special characters in your project path

- Make sure there are no spaces in your project path: `node-gyp` may not escape spaces or special characters (like `%` or `$`) properly.

## Electron

1. If you're using [Electron](https://github.com/electron/electron), use [`electron-rebuild`](https://www.npmjs.com/package/electron-rebuild).

2. If you're using an app.asar bundle, be sure all native libraries are "unpacked". If you're using [electron-forge]([url](https://www.electronforge.io)), you should use the [auto-unpack-natives plugin](https://www.electronforge.io/config/plugins/auto-unpack-natives)

## Windows

If you still have issues, try these steps:

1. Delete your `node_modules` subdirectory
1. Delete your `$HOME/.node-gyp` directory
1. Run `npm install`

## Still stuck?

Browse [previous installation issues](https://github.com/WiseLibs/better-sqlite3/issues?q=is%3Aissue).
