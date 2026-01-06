# better-sqlite3 [![构建状态](https://github.com/JoshuaWise/better-sqlite3/actions/workflows/build.yml/badge.svg)](https://github.com/JoshuaWise/better-sqlite3/actions/workflows/build.yml?query=branch%3Amaster)


Node.js 中最快速和最简单的 SQLite3 库。

The fastest and simplest library for SQLite in Node.js.


- 完整的事务支持
- 高性能、高效率和高安全性
- 易于使用的同步 API *（比异步 API 有更好的并发性能...是的，你没看错）*
- 支持用户自定义函数、聚合函数、虚拟表和扩展
- 64 位整数支持 *（需要时才可见）*
- 工作线程支持 *（用于大型/慢速查询）*

## 帮助这个项目继续发展！&#128170;

`better-sqlite3` 每天都被成千上万的开发者和工程师使用。在没有要求任何补偿或资助的情况下，我们花费了无数个夜晚和周末来保持这个项目的强大和可靠，直到现在。如果你的公司正在使用 `better-sqlite3`，请让你的经理考虑支持这个项目：

- [成为 GitHub 赞助者](https://github.com/sponsors/JoshuaWise)
- [在 Patreon 上成为支持者](https://www.patreon.com/joshuawise)
- [通过 PayPal 进行一次性捐赠](https://www.paypal.me/joshuathomaswise)

## 与其他库的比较

|   |查询 1 行 &nbsp;`get()`&nbsp;|查询 100 行 &nbsp;&nbsp;`all()`&nbsp;&nbsp;|逐行查询 100 行 `iterate()`|插入 1 行 `run()`|在事务中插入 100 行|
|---|---|---|---|---|---|
|better-sqlite3|1x|1x|1x|1x|1x|
|[sqlite](https://www.npmjs.com/package/sqlite) 和 [sqlite3](https://www.npmjs.com/package/sqlite3)|慢 11.7 倍|慢 2.9 倍|慢 24.4 倍|慢 2.8 倍|慢 15.6 倍|

> 你可以通过[自行运行基准测试](./docs/benchmark.md)来验证这些结果。

## 安装

```bash
npm install better-sqlite3
```


> 你必须使用 Node.js v14.21.1 或更高版本。预编译的二进制文件适用于 [LTS 版本](https://nodejs.org/en/about/releases/)。如果安装遇到问题，请查看[故障排除指南](./docs/troubleshooting.md)。

## 使用方法

```js
const db = require('better-sqlite3')('foobar.db', options);

const row = db.prepare('SELECT * FROM users WHERE id = ?').get(userId);
console.log(row.firstName, row.lastName, row.email);
```

虽然不是必需的，但是[出于性能考虑，通常建议设置 WAL pragma](https://github.com/WiseLibs/better-sqlite3/blob/master/docs/performance.md)。

```js
db.pragma('journal_mode = WAL');
```

##### ES6 模块写法：

```js
import Database from 'better-sqlite3';
const db = new Database('foobar.db', options);
db.pragma('journal_mode = WAL');
```

## 为什么要使用这个而不是 [node-sqlite3](https://github.com/mapbox/node-sqlite3)？

- `node-sqlite3` 对 CPU 密集型或串行化的任务使用异步 API。这不仅设计不佳，还会浪费大量资源。它还会导致[互斥锁争用](https://en.wikipedia.org/wiki/Resource_contention)，这会对性能造成严重影响。
- `node-sqlite3` 暴露了低级（C 语言）内存管理函数。`better-sqlite3` 采用 JavaScript 的方式，让垃圾回收器来处理内存管理。
- `better-sqlite3` 使用更简单，并为一些在 `node-sqlite3` 中很难或无法实现的操作提供了便利的工具。
- `better-sqlite3` 在大多数情况下比 `node-sqlite3` 快得多，在其他情况下也同样快。

#### 什么时候不适合使用这个库？


在大多数情况下，如果你尝试做一些无法用 `better-sqlite3` 合理完成的事情，那么可能也无法用 SQLite3 合理完成。例如，如果你执行的查询需要一秒钟才能完成，并且你预计会有许多并发用户执行这些查询，那么无论多少异步性都无法解决 SQLite3 的串行化特性。幸运的是，SQLite3 非常非常快。通过适当的索引，我们能够在一个 60 GB 的数据库中实现每秒 2000 个带有 5 路连接的查询，每个查询处理 5-50 KB 的实际数据。


如果你遇到性能问题，最可能的原因是查询效率低下、索引不当或缺少 [WAL 模式](./docs/performance.md)，而不是 `better-sqlite3` 本身。但是，在某些情况下，`better-sqlite3` 可能不适合：

- 如果你预计会有大量并发读取，每次读取都返回多兆字节的数据（例如视频）
- 如果你预计会有大量并发写入（例如社交媒体网站）
- 如果你的数据库大小接近 TB 级别

对于这些情况，你可能应该使用完整的 RDBMS，比如 [PostgreSQL](https://www.postgresql.org/)。



## Upgrading

Upgrading your `better-sqlite3` dependency can potentially introduce breaking changes, either in the `better-sqlite3` API (if you upgrade to a new [major version](https://semver.org/)), or between your existing database(s) and the underlying version of SQLite. Before upgrading, review:

* [`better-sqlite3` release notes](https://github.com/WiseLibs/better-sqlite3/releases)
* [SQLite release history](https://www.sqlite.org/changes.html)

# Documentation

- [API documentation](./docs/api.md)
- [Performance](./docs/performance.md) (also see [benchmark results](./docs/benchmark.md))
- [64-bit integer support](./docs/integer.md)
- [Worker thread support](./docs/threads.md)
- [Unsafe mode (advanced)](./docs/unsafe.md)
- [SQLite compilation (advanced)](./docs/compilation.md)
- [Contribution rules](./docs/contribution.md)
- [Code of conduct](./docs/conduct.md)


# 许可证

[MIT](./LICENSE)

## 构建脚本说明

项目包含以下 npm 脚本命令：

### 基础命令
- `install`: 安装时优先使用预构建二进制，如果失败则本地编译
- `build-release`: 以发布模式编译项目
- `build-debug`: 以调试模式编译项目
- `rebuild-release`: 先生成C++代码，然后以发布模式编译
- `rebuild-debug`: 先生成C++代码，然后以调试模式编译
- `test`: 运行测试套件
- `benchmark`: 运行性能基准测试
- `download`: 下载依赖项
- `lzz`: 使用lzz工具生成C++代码

### 架构相关命令
- `build-arm64`: 为ARM64架构编译发布版本
- `build-x64`: 为x64架构编译发布版本
- `build-universal`: 创建通用二进制（同时支持ARM64和x64）

### N-API 预构建命令
- `prebuild-arm64`: 为ARM64架构预构建N-API版本
- `prebuild-x64`: 为x64架构预构建N-API版本
- `prebuild-all`: 预构建所有N-API架构版本

### Electron 相关命令
- `build-all`: 为Electron v22.0.0编译
- `build-electron-arm64`: 为Electron ARM64架构构建
- `build-electron-x64`: 为Electron x64架构构建
- `build-electron-universal`: 构建Electron通用版本（ARM64 + x64）
- `prebuild-electron-arm64`: 为Electron ARM64架构预构建
- `prebuild-electron-x64`: 为Electron x64架构预构建
- `prebuild-electron-all`: 预构建所有Electron架构版本
