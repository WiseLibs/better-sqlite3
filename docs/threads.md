# Worker threads

For most applications, `better-sqlite3` is fast enough to use in the main thread without blocking for a noticeable amount of time. However, if you need to perform very slow queries, you have the option of using [worker threads](https://nodejs.org/api/worker_threads.html) to keep things running smoothly. Below is an example of using a thread pool to perform queries in the background.

#### worker.js

The worker logic is very simple in our case. It accepts messages from the master thread, executes each message's SQL (with any given parameters), and sends back the query results.

```js
const { parentPort } = require('worker_threads');
const db = require('better-sqlite3')('foobar.db');

parentPort.on('message', ({ sql, parameters }) => {
  const result = db.prepare(sql).all(...parameters);
  parentPort.postMessage(result);
});
```

#### master.js

The master thread is responsible for spawning workers, respawning threads that crash, and accepting query jobs.

```js
const threads = require('worker_threads');
const os = require('os');

/*
  Export a function that queues pending work.
 */

const queue = [];
exports.asyncQuery = (sql, ...parameters) => {
  return new Promise((resolve, reject) => {
    queue.push({
      resolve,
      reject,
      message: { sql, parameters },
    });
  });
};

/*
  Spawn workers that try to drain the queue.
 */

os.cpus().forEach(function spawn() {
  const worker = new threads.Worker('./worker.js');

  let job = null; // Current item from the queue
  let error = null; // Error that caused the worker to crash
  let timer = null; // Timer used for polling

  function poll() {
    if (queue.length) {
      // If there's a job in the queue, send it to the worker
      job = queue.shift();
      worker.postMessage(job.message);
    } else {
      // Otherwise, check again later
      timer = setImmediate(poll);
    }
  }

  worker
    .on('online', poll)
    .on('message', (result) => {
      job.resolve(result);
      job = null;
      poll(); // Check if there's more work to do
    })
    .on('error', (err) => {
      console.error(err);
      error = err;
    })
    .on('exit', (code) => {
      clearImmediate(timer);
      if (job) {
        job.reject(error || new Error('worker died'));
      }
      if (code !== 0) {
        console.error(`worker exited with code ${code}`);
        spawn(); // Worker died, so spawn a new one
      }
    });
});
```
