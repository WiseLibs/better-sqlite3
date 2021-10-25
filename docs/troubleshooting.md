# Troubleshooting installation

If you have trouble installing `better-sqlite3`, follow this checklist:

1. Make sure you're using nodejs v10.20.1 or later

2. Make sure you have [`node-gyp`](https://github.com/nodejs/node-gyp#installation) globally installed, including all of [its dependencies](https://github.com/nodejs/node-gyp#on-unix). On Windows you may need to [configure some things manually](https://github.com/nodejs/node-gyp#on-windows). Use `npm ls node-gyp` to make sure none of your local packages installed an outdated version of `node-gyp` that is used over the global one.

3. If you're using [Electron](https://github.com/electron/electron), try running [`electron-rebuild`](https://www.npmjs.com/package/electron-rebuild)

4. If you're using Windows, follow these steps. Do them **in this order**, and **don't skip steps**.

    1. Install the **latest** of node 10, 12, or 14.
    2. Install **latest** Visual Studio Community and Desktop Development with C++ extension.
    3. Install **latest** Python.
    4. Run following commands:
    ```
    npm config set msvs_version 2019
    npm config set msbuild_path "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"
    ```
    5. Run `npm install`

If none of these solved your problem, try browsing [previous issues](https://github.com/JoshuaWise/better-sqlite3/issues?q=is%3Aissue) or open a [new issue](https://github.com/JoshuaWise/better-sqlite3/issues/new).
