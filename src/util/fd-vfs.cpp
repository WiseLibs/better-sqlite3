// A SQLite VFS that opens a database from existing file descriptors, instead of
// from a path. It is registered under the name "better-sqlite3-fd" (never as
// the default VFS), and it is only used by database connections that were
// constructed with a file descriptor.
//
// Two file descriptors are required: one for the database file, and one for its
// rollback journal (which must be the file "<database>-journal", so that other
// connections that use the database by path can find it after a crash). This
// allows a process to fully use a database (with complete ACID guarantees)
// without having any permission to open files in the database's directory.
//
// Since the journal cannot be re-created without directory permissions, it is
// never deleted. Instead, "deleting" the journal truncates it to zero bytes,
// which SQLite treats identically to a missing journal. If the database file
// or the journal file is ever deleted or replaced by some other process, this
// connection can no longer coordinate crash recovery with other connections,
// so it fails closed: every subsequent transaction fails with SQLITE_CANTOPEN.
//
// WAL mode is not supported, nor are transactions that write to multiple
// databases at once (which would require creating a super-journal). Every other
// file (temporary files, and the files of ATTACHed databases) is delegated,
// unchanged, to the default VFS.
//
// Locking uses the same byte-range protocol as SQLite's built-in "unix" VFS, so
// these connections interoperate with ordinary SQLite connections (in other
// processes) that use the same database file. Like the unix VFS, in-process
// lock state is tracked per inode, so that multiple connections in this process
// (even ones sharing a single open file description) coordinate correctly.
// Traditional POSIX advisory locks are used on all platforms. POSIX locks are
// owned by processes, so processes that inherited the same open file
// description from a common parent still exclude each other. The downside is
// the well-known pitfall of POSIX locks: closing ANY descriptor for the
// database file releases all of the process's locks on it (which is why we
// defer closing our own descriptors).
//
// Windows is not supported.

#ifndef _WIN32

#include <atomic>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

class FdVfs {
public:

	static constexpr const char* VFS_NAME = "better-sqlite3-fd";

	// Registers the VFS with SQLite. This is idempotent and thread-safe.
	static void Register() {
		static std::once_flag init_flag;
		std::call_once(init_flag, [](){
			sqlite3_vfs* base = sqlite3_vfs_find(NULL);
			assert(base != NULL);
			static sqlite3_vfs vfs;
			memset(&vfs, 0, sizeof(vfs));
			vfs.iVersion = 3;
			vfs.szOsFile = base->szOsFile > (int)sizeof(File) ? base->szOsFile : (int)sizeof(File);
			vfs.mxPathname = base->mxPathname;
			vfs.zName = VFS_NAME;
			vfs.pAppData = base;
			vfs.xOpen = xOpen;
			vfs.xDelete = xDelete;
			vfs.xAccess = xAccess;
			vfs.xFullPathname = xFullPathname;
			vfs.xDlOpen = xDlOpen;
			vfs.xDlError = xDlError;
			vfs.xDlSym = xDlSym;
			vfs.xDlClose = xDlClose;
			vfs.xRandomness = xRandomness;
			vfs.xSleep = xSleep;
			vfs.xCurrentTime = xCurrentTime;
			vfs.xGetLastError = xGetLastError;
			vfs.xCurrentTimeInt64 = xCurrentTimeInt64;
			vfs.xSetSystemCall = xSetSystemCall;
			vfs.xGetSystemCall = xGetSystemCall;
			vfs.xNextSystemCall = xNextSystemCall;
			int status = sqlite3_vfs_register(&vfs, 0);
			assert(status == SQLITE_OK); ((void)status);
		});
	}

	// Checks whether the given file descriptors can be used to open a
	// database. Returns NULL on success, or an error message on failure.
	static const char* Validate(int fd, int journal_fd, bool readonly) {
		static const char* const messages[2][6] = {{
			"Cannot open database because the database file descriptor is not open",
			"Cannot open database because the database file descriptor does not refer to a regular file",
			"Cannot open database because the database file descriptor was not opened for reading",
			"Cannot open database because the database file descriptor was not opened for writing (use the \"readonly\" option)",
			"Cannot open database because the database file descriptor was opened in append mode",
			"Cannot open database because the database file has been deleted",
		}, {
			"Cannot open database because the journal file descriptor is not open",
			"Cannot open database because the journal file descriptor does not refer to a regular file",
			"Cannot open database because the journal file descriptor was not opened for reading",
			"Cannot open database because the journal file descriptor was not opened for writing (use the \"readonly\" option)",
			"Cannot open database because the journal file descriptor was opened in append mode",
			"Cannot open database because the journal file has been deleted",
		}};
		struct stat st[2];
		const int fds[2] = { fd, journal_fd };
		for (int i = 0; i < 2; ++i) {
			int fl = fcntl(fds[i], F_GETFL);
			if (fl < 0) return messages[i][0];
			if (fstat(fds[i], &st[i]) != 0 || !S_ISREG(st[i].st_mode)) return messages[i][1];
			if ((fl & O_ACCMODE) == O_WRONLY) return messages[i][2];
			if (!readonly && (fl & O_ACCMODE) != O_RDWR) return messages[i][3];
			if (fl & O_APPEND) return messages[i][4];
			if (st[i].st_nlink == 0) return messages[i][5];
		}
		if (st[0].st_dev == st[1].st_dev && st[0].st_ino == st[1].st_ino) {
			return "Cannot open database because the database and journal file descriptors refer to the same file";
		}
		// Bytes 18 and 19 of the database header are both 2 in WAL mode.
		unsigned char version[2];
		if (pread(fd, version, 2, 18) == 2 && version[0] == 2 && version[1] == 2) {
			return "Cannot open database from a file descriptor because it is in WAL mode";
		}
		return NULL;
	}

	// Opens a database connection whose main database file and rollback journal
	// are the given file descriptors (which must have been checked by
	// Validate()). The descriptors are duplicated, so the caller retains
	// ownership of the originals. This has the same semantics as
	// sqlite3_open_v2() regarding the output handle. On failure, if this VFS
	// has a more specific error message than SQLite's, it is stored in
	// *error_message (otherwise, it is set to NULL).
	static int Open(int fd, int journal_fd, int flags, sqlite3** db_handle, const char** error_message) {
		Register();
		static std::atomic<unsigned long long> next_id(0);
		std::string name = "fd:" + std::to_string(fd) + ":" + std::to_string(next_id++);
		pending_fd = fd;
		pending_journal_fd = journal_fd;
		pending_name = name.c_str();
		open_error_code = SQLITE_OK;
		open_error_message = NULL;
		int status = sqlite3_open_v2(name.c_str(), db_handle, flags, VFS_NAME);
		int code = *db_handle != NULL ? sqlite3_extended_errcode(*db_handle) : status;
		*error_message = status != SQLITE_OK && open_error_code == code ? open_error_message : NULL;
		pending_fd = -1;
		pending_journal_fd = -1;
		pending_name = NULL;
		open_error_code = SQLITE_OK;
		open_error_message = NULL;
		return status;
	}

	// Marks the start of a new operation on this thread. Error messages
	// recorded by earlier operations are then considered stale (see
	// TakeErrorMessage()). This must be called before every SQLite call whose
	// failure is reported with Database::ThrowSqliteError(db_handle).
	static void BeginOperation() {
		++operation;
	}

	// SQLite has no way for a VFS to provide an error message, so when this
	// VFS fails with a specific reason, it records the message on the
	// connection's main database File. This returns (and clears) that
	// message, but only if the given error code matches and the message was
	// recorded during the current operation (otherwise, it's left over from
	// an error that was never reported, such as one that SQLite handled
	// internally, or one that was reported through a different connection).
	// It returns NULL for connections that don't use this VFS. The caller
	// must hold the database connection's mutex (if any).
	static const char* TakeErrorMessage(sqlite3* db_handle, int code) {
		sqlite3_file* f = NULL;
		if (sqlite3_file_control(db_handle, "main", SQLITE_FCNTL_FILE_POINTER, &f) != SQLITE_OK) return NULL;
		if (f == NULL || f->pMethods != &main_io_methods) return NULL;
		File* file = reinterpret_cast<File*>(f);
		const char* message = file->error_code == code && file->error_operation == operation ? file->error_message : NULL;
		ClearError(file);
		return message;
	}

private:

	// Lock byte offsets, which must match those of SQLite's unix VFS.
	static constexpr off_t PENDING_BYTE = 0x40000000;
	static constexpr off_t RESERVED_BYTE = PENDING_BYTE + 1;
	static constexpr off_t SHARED_FIRST = PENDING_BYTE + 2;
	static constexpr off_t SHARED_SIZE = 510;

	static constexpr const char* JOURNAL_SUFFIX = "-journal";

	static constexpr const char* UNLINKED_MESSAGE =
		"The database file or its journal file was deleted or replaced while the database was open (the database must be reopened)";
	static constexpr const char* JOURNAL_MISMATCH_MESSAGE =
		"Cannot open database because a different journal file is already being used for this database";
	static constexpr const char* SUPER_JOURNAL_MESSAGE =
		"Transactions that write to multiple databases are not supported by databases opened from file descriptors";

	// Lock state shared by all connections (in this process) that have the same
	// file open through this VFS. All fields are guarded by Mutex().
	struct Inode {
		dev_t dev;
		ino_t ino;
		dev_t journal_dev; // Every connection must use the same journal file
		ino_t journal_ino;
		int nRef; // Number of open Files referring to this Inode
		int nShared; // Number of Files holding a SHARED (or greater) lock
		int nLock; // Number of Files holding any lock
		int eFileLock; // Strongest lock held by any File
		int lockFd; // Descriptor through which all OS-level locks are acquired
		bool lockFdWritable; // Whether lockFd can acquire write locks (see OpenMain)
		std::vector<int> pendingFds; // Descriptors to close once nLock is 0
	};

	// The sqlite3_file subclass used for main database files and journals.
	// SQLite allocates this memory itself, so it must remain a plain struct.
	struct File {
		sqlite3_file base;
		int fd; // For journals, a duplicate of the main database File's journal_fd
		bool writable;
		int eFileLock;
		Inode* inode; // NULL for journals
		int journal_fd; // Owned by the main database File
		bool journal_writable;
		const char* name; // Valid until xClose (guaranteed by SQLite)
		int error_code; // See TakeErrorMessage() (main database Files only)
		const char* error_message;
		unsigned long long error_operation; // The operation that recorded the error
	};

	static std::mutex& Mutex() {
		static std::mutex* mutex = new std::mutex(); // Intentionally leaked
		return *mutex;
	}

	static std::vector<Inode*>& Inodes() {
		static std::vector<Inode*>* inodes = new std::vector<Inode*>(); // Intentionally leaked
		return *inodes;
	}

	// All open main database Files, so that their journals can be found.
	static std::vector<File*>& MainFiles() {
		static std::vector<File*>* files = new std::vector<File*>(); // Intentionally leaked
		return *files;
	}

	static inline sqlite3_vfs* Base(sqlite3_vfs* vfs) {
		return static_cast<sqlite3_vfs*>(vfs->pAppData);
	}

	// Returns whether the given filename belongs to this VFS (i.e., it is the
	// name of a database opened by file descriptor, or one of its side files).
	static bool IsFdName(const char* name) {
		return name != NULL && strncmp(name, "fd:", 3) == 0 && name[3] >= '0' && name[3] <= '9';
	}

	// Returns the open main database File whose name is the first
	// name_length characters of the given name, or NULL. This must be called
	// while holding Mutex().
	static File* FindMainFileByPrefix(const char* name, size_t name_length) {
		for (File* file : MainFiles()) {
			if (strlen(file->name) == name_length && strncmp(file->name, name, name_length) == 0) {
				return file;
			}
		}
		return NULL;
	}

	// Given the name of a journal, returns the main database File that it
	// belongs to, or NULL. This must be called while holding Mutex().
	static File* FindMainFile(const char* journal_name) {
		size_t length = strlen(journal_name);
		size_t suffix_length = strlen(JOURNAL_SUFFIX);
		if (length <= suffix_length) return NULL;
		size_t name_length = length - suffix_length;
		if (strcmp(journal_name + name_length, JOURNAL_SUFFIX) != 0) return NULL;
		return FindMainFileByPrefix(journal_name, name_length);
	}

	// Records an error message on the given main database File (see
	// TakeErrorMessage()). The File's connection must be the caller (so we're
	// on the thread whose operation counter applies).
	static int Fail(File* main, int code, const char* message) {
		main->error_code = code;
		main->error_message = message;
		main->error_operation = operation;
		return code;
	}

	// Records an error message for the Open() call in progress on this thread.
	static int FailOpen(int code, const char* message) {
		open_error_code = code;
		open_error_message = message;
		return code;
	}

	static void ClearError(File* main) {
		main->error_code = SQLITE_OK;
		main->error_message = NULL;
	}

	// Returns whether the file still has a name in the filesystem.
	static bool IsLinked(int fd) {
		struct stat st;
		return fstat(fd, &st) == 0 && st.st_nlink > 0;
	}

	// Duplicates a file descriptor, avoiding stdio descriptor numbers (so that
	// database content can never be written to stdout/stderr by accident).
	static int Dup(int fd) {
		return fcntl(fd, F_DUPFD_CLOEXEC, 3);
	}

	static void CloseFd(int fd) {
		// Retrying close() on EINTR is unsafe on Linux, so we don't.
		close(fd);
	}

	static void ClosePendingFds(Inode* inode) {
		for (int fd : inode->pendingFds) CloseFd(fd);
		inode->pendingFds.clear();
	}

	// Acquires, upgrades, or releases an OS-level lock on the given byte range.
	// Returns 0 on success, or -1 with errno set on failure.
	static int SetLock(Inode* inode, short type, off_t start, off_t len) {
		// Only writable Files request write locks, and the lock descriptor
		// is always writable when any writable File is open (see OpenMain).
		assert(type != F_WRLCK || inode->lockFdWritable);
		struct flock lock;
		memset(&lock, 0, sizeof(lock));
		lock.l_type = type;
		lock.l_whence = SEEK_SET;
		lock.l_start = start;
		lock.l_len = len;
		int rc;
		do rc = fcntl(inode->lockFd, F_SETLK, &lock);
		while (rc < 0 && errno == EINTR);
		return rc;
	}

	static int LockError(int err, int fallback) {
		switch (err) {
			case EACCES:
			case EAGAIN:
			case ETIMEDOUT:
			case EBUSY:
			case EINTR:
			case ENOLCK:
				return SQLITE_BUSY;
			case EPERM:
				return SQLITE_PERM;
			default:
				return fallback;
		}
	}

	// Common I/O methods (for main database files and journals)

	static int xRead(sqlite3_file* f, void* buffer, int amount, sqlite3_int64 offset) {
		File* file = reinterpret_cast<File*>(f);
		char* out = static_cast<char*>(buffer);
		while (amount > 0) {
			ssize_t got = pread(file->fd, out, amount, offset);
			if (got < 0) {
				if (errno == EINTR) continue;
				return SQLITE_IOERR_READ;
			}
			if (got == 0) {
				// SQLite requires unread bytes to be zero-filled.
				memset(out, 0, amount);
				return SQLITE_IOERR_SHORT_READ;
			}
			out += got;
			amount -= got;
			offset += got;
		}
		return SQLITE_OK;
	}

	static int xWrite(sqlite3_file* f, const void* buffer, int amount, sqlite3_int64 offset) {
		File* file = reinterpret_cast<File*>(f);
		const char* in = static_cast<const char*>(buffer);
		while (amount > 0) {
			ssize_t wrote = pwrite(file->fd, in, amount, offset);
			if (wrote < 0) {
				if (errno == EINTR) continue;
				if (errno == ENOSPC || errno == EDQUOT) return SQLITE_FULL;
				return SQLITE_IOERR_WRITE;
			}
			if (wrote == 0) return SQLITE_FULL;
			in += wrote;
			amount -= wrote;
			offset += wrote;
		}
		return SQLITE_OK;
	}

	static int Truncate(int fd, sqlite3_int64 size) {
		int rc;
		do rc = ftruncate(fd, static_cast<off_t>(size));
		while (rc < 0 && errno == EINTR);
		return rc;
	}

	static int xTruncate(sqlite3_file* f, sqlite3_int64 size) {
		File* file = reinterpret_cast<File*>(f);
		return Truncate(file->fd, size) == 0 ? SQLITE_OK : SQLITE_IOERR_TRUNCATE;
	}

	static int Sync(int fd, int flags) {
#if defined(__APPLE__)
		// Like the unix VFS, only use F_FULLFSYNC when asked to
		// (i.e., when PRAGMA fullfsync is enabled).
		if ((flags & 0x0F) == SQLITE_SYNC_FULL && fcntl(fd, F_FULLFSYNC, 0) == 0) {
			return 0;
		}
		return fsync(fd);
#elif defined(__linux__)
		(void)flags;
		return fdatasync(fd);
#else
		(void)flags;
		return fsync(fd);
#endif
	}

	static int xSync(sqlite3_file* f, int flags) {
		File* file = reinterpret_cast<File*>(f);
		return Sync(file->fd, flags) == 0 ? SQLITE_OK : SQLITE_IOERR_FSYNC;
	}

	static int xFileSize(sqlite3_file* f, sqlite3_int64* size) {
		File* file = reinterpret_cast<File*>(f);
		struct stat st;
		if (fstat(file->fd, &st) != 0) return SQLITE_IOERR_FSTAT;
		*size = st.st_size;
		return SQLITE_OK;
	}

	static int xSectorSize(sqlite3_file* f) {
		return 4096;
	}

	static int xDeviceCharacteristics(sqlite3_file* f) {
		return SQLITE_IOCAP_POWERSAFE_OVERWRITE;
	}

	// I/O methods for main database files

	static int xClose(sqlite3_file* f) {
		File* file = reinterpret_cast<File*>(f);
		xUnlock(f, SQLITE_LOCK_NONE);
		std::lock_guard<std::mutex> guard(Mutex());
		std::vector<File*>& files = MainFiles();
		std::vector<File*>::iterator file_it = std::find(files.begin(), files.end(), file);
		assert(file_it != files.end());
		files.erase(file_it);
		CloseFd(file->journal_fd);
		Inode* inode = file->inode;
		// With POSIX advisory locks, closing any descriptor for the file would
		// release all locks held by this process, so we defer it.
		inode->pendingFds.push_back(file->fd);
		if (inode->nLock == 0) ClosePendingFds(inode);
		if (--inode->nRef == 0) {
			std::vector<Inode*>& inodes = Inodes();
			std::vector<Inode*>::iterator inode_it = std::find(inodes.begin(), inodes.end(), inode);
			assert(inode_it != inodes.end());
			inodes.erase(inode_it);
			ClosePendingFds(inode);
			CloseFd(inode->lockFd);
			delete inode;
		}
		file->inode = NULL;
		file->fd = -1;
		file->journal_fd = -1;
		return SQLITE_OK;
	}

	// We make sure that the database and journal files are still where other
	// connections would look for them whenever a transaction begins (i.e.,
	// when acquiring a SHARED lock), so that we never read a database whose
	// hot journal we can't see. We check again when a write begins (i.e.,
	// when acquiring a RESERVED or greater lock), because SQLite deletes
	// journals while holding a RESERVED lock, which doesn't conflict with
	// our SHARED lock. Once we hold a RESERVED lock, no other connection can
	// delete the journal until we release it, so the journal we write to is
	// guaranteed to be the one that other connections would find after a
	// crash. Checking here (rather than when the journal is opened) matters
	// because SQLite may keep the journal open between transactions.
	static int xLock(sqlite3_file* f, int eFileLock) {
		File* file = reinterpret_cast<File*>(f);
		int previous = file->eFileLock;
		int rc = Lock(file, eFileLock);
		if (rc != SQLITE_OK) return rc;
		bool starting_read = previous == SQLITE_LOCK_NONE;
		bool starting_write = previous < SQLITE_LOCK_RESERVED && eFileLock >= SQLITE_LOCK_RESERVED;
		if ((starting_read || starting_write) && !(IsLinked(file->fd) && IsLinked(file->journal_fd))) {
			// SQLite assumes that a failed xLock() leaves the lock unchanged.
			xUnlock(f, starting_read ? SQLITE_LOCK_NONE : SQLITE_LOCK_SHARED);
			return Fail(file, SQLITE_CANTOPEN, UNLINKED_MESSAGE);
		}
		return rc;
	}

	// This is a port of unixLock() from SQLite's os_unix.c. Refer to it for
	// detailed commentary on the locking protocol.
	static int Lock(File* file, int eFileLock) {
		if (file->eFileLock >= eFileLock) return SQLITE_OK;
		assert(file->eFileLock != SQLITE_LOCK_NONE || eFileLock == SQLITE_LOCK_SHARED);
		assert(eFileLock != SQLITE_LOCK_PENDING);
		assert(eFileLock != SQLITE_LOCK_RESERVED || file->eFileLock == SQLITE_LOCK_SHARED);

		std::lock_guard<std::mutex> guard(Mutex());
		Inode* inode = file->inode;

		// Another connection in this process holds a conflicting lock.
		if (file->eFileLock != inode->eFileLock &&
			(inode->eFileLock >= SQLITE_LOCK_PENDING || eFileLock > SQLITE_LOCK_SHARED)) {
			return SQLITE_BUSY;
		}

		// Another connection in this process already holds a SHARED lock (or
		// a RESERVED lock), so we can piggyback on it.
		if (eFileLock == SQLITE_LOCK_SHARED &&
			(inode->eFileLock == SQLITE_LOCK_SHARED || inode->eFileLock == SQLITE_LOCK_RESERVED)) {
			file->eFileLock = SQLITE_LOCK_SHARED;
			inode->nShared++;
			inode->nLock++;
			return SQLITE_OK;
		}

		// A PENDING lock is needed before acquiring a SHARED lock, and before
		// upgrading from RESERVED to EXCLUSIVE.
		if (eFileLock == SQLITE_LOCK_SHARED ||
			(eFileLock == SQLITE_LOCK_EXCLUSIVE && file->eFileLock == SQLITE_LOCK_RESERVED)) {
			short type = eFileLock == SQLITE_LOCK_SHARED ? F_RDLCK : F_WRLCK;
			if (SetLock(inode, type, PENDING_BYTE, 1) != 0) {
				return LockError(errno, SQLITE_IOERR_LOCK);
			}
			if (eFileLock == SQLITE_LOCK_EXCLUSIVE) {
				file->eFileLock = SQLITE_LOCK_PENDING;
				inode->eFileLock = SQLITE_LOCK_PENDING;
			}
		}

		int rc = SQLITE_OK;
		if (eFileLock == SQLITE_LOCK_SHARED) {
			assert(inode->nShared == 0);
			assert(inode->eFileLock == SQLITE_LOCK_NONE);
			if (SetLock(inode, F_RDLCK, SHARED_FIRST, SHARED_SIZE) != 0) {
				rc = LockError(errno, SQLITE_IOERR_LOCK);
			}
			// Drop the temporary PENDING lock.
			if (SetLock(inode, F_UNLCK, PENDING_BYTE, 1) != 0 && rc == SQLITE_OK) {
				rc = SQLITE_IOERR_UNLOCK;
			}
			if (rc != SQLITE_OK) return rc;
			inode->nLock++;
			inode->nShared = 1;
		} else if (eFileLock == SQLITE_LOCK_EXCLUSIVE && inode->nShared > 1) {
			// Another connection in this process holds a SHARED lock.
			rc = SQLITE_BUSY;
		} else {
			assert(file->eFileLock != SQLITE_LOCK_NONE);
			assert(eFileLock == SQLITE_LOCK_RESERVED || eFileLock == SQLITE_LOCK_EXCLUSIVE);
			int failed = eFileLock == SQLITE_LOCK_RESERVED
				? SetLock(inode, F_WRLCK, RESERVED_BYTE, 1)
				: SetLock(inode, F_WRLCK, SHARED_FIRST, SHARED_SIZE);
			if (failed) rc = LockError(errno, SQLITE_IOERR_LOCK);
		}

		if (rc == SQLITE_OK) {
			file->eFileLock = eFileLock;
			inode->eFileLock = eFileLock;
		}
		return rc;
	}

	// This is a port of posixUnlock() from SQLite's os_unix.c.
	static int xUnlock(sqlite3_file* f, int eFileLock) {
		File* file = reinterpret_cast<File*>(f);
		assert(eFileLock <= SQLITE_LOCK_SHARED);
		if (file->eFileLock <= eFileLock) return SQLITE_OK;

		std::lock_guard<std::mutex> guard(Mutex());
		Inode* inode = file->inode;
		assert(inode->nShared != 0);

		if (file->eFileLock > SQLITE_LOCK_SHARED) {
			assert(inode->eFileLock == file->eFileLock);
			if (eFileLock == SQLITE_LOCK_SHARED) {
				if (SetLock(inode, F_RDLCK, SHARED_FIRST, SHARED_SIZE) != 0) {
					return SQLITE_IOERR_RDLOCK;
				}
			}
			if (SetLock(inode, F_UNLCK, PENDING_BYTE, 2) != 0) {
				return SQLITE_IOERR_UNLOCK;
			}
			inode->eFileLock = SQLITE_LOCK_SHARED;
		}

		int rc = SQLITE_OK;
		if (eFileLock == SQLITE_LOCK_NONE) {
			if (--inode->nShared == 0) {
				if (SetLock(inode, F_UNLCK, 0, 0) != 0) {
					rc = SQLITE_IOERR_UNLOCK;
					file->eFileLock = SQLITE_LOCK_NONE;
				}
				inode->eFileLock = SQLITE_LOCK_NONE;
			}
			if (--inode->nLock == 0) ClosePendingFds(inode);
		}

		if (rc == SQLITE_OK) file->eFileLock = eFileLock;
		return rc;
	}

	static int xCheckReservedLock(sqlite3_file* f, int* result) {
		File* file = reinterpret_cast<File*>(f);
		std::lock_guard<std::mutex> guard(Mutex());
		Inode* inode = file->inode;
		int rc = SQLITE_OK;
		int reserved = inode->eFileLock > SQLITE_LOCK_SHARED;
		if (!reserved) {
			struct flock lock;
			memset(&lock, 0, sizeof(lock));
			lock.l_type = F_WRLCK;
			lock.l_whence = SEEK_SET;
			lock.l_start = RESERVED_BYTE;
			lock.l_len = 1;
			if (fcntl(inode->lockFd, F_GETLK, &lock) != 0) {
				rc = SQLITE_IOERR_CHECKRESERVEDLOCK;
			} else if (lock.l_type != F_UNLCK) {
				reserved = 1;
			}
		}
		*result = reserved;
		return rc;
	}

	static int xFileControl(sqlite3_file* f, int op, void* arg) {
		File* file = reinterpret_cast<File*>(f);
		switch (op) {
			case SQLITE_FCNTL_LOCKSTATE:
				*static_cast<int*>(arg) = file->eFileLock;
				return SQLITE_OK;
			case SQLITE_FCNTL_HAS_MOVED:
				*static_cast<int*>(arg) = !IsLinked(file->fd);
				return SQLITE_OK;
			case SQLITE_FCNTL_VFSNAME:
				*static_cast<char**>(arg) = sqlite3_mprintf("%s", VFS_NAME);
				return SQLITE_OK;
			case SQLITE_FCNTL_PRAGMA: {
				// WAL mode would require creating "-wal" and "-shm" files.
				char** args = static_cast<char**>(arg);
				if (args[2] != NULL
					&& sqlite3_stricmp(args[1], "journal_mode") == 0
					&& sqlite3_stricmp(args[2], "wal") == 0) {
					args[0] = sqlite3_mprintf("journal_mode WAL is not supported for databases opened from file descriptors");
					return SQLITE_ERROR;
				}
				return SQLITE_NOTFOUND;
			}
			default:
				return SQLITE_NOTFOUND;
		}
	}

	static constexpr sqlite3_io_methods main_io_methods = {
		1,
		xClose,
		xRead,
		xWrite,
		xTruncate,
		xSync,
		xFileSize,
		xLock,
		xUnlock,
		xCheckReservedLock,
		xFileControl,
		xSectorSize,
		xDeviceCharacteristics,
		NULL, // xShmMap (WAL mode is not supported)
		NULL, // xShmLock
		NULL, // xShmBarrier
		NULL, // xShmUnmap
		NULL, // xFetch (memory-mapped I/O is not supported)
		NULL, // xUnfetch
	};

	// I/O methods for journals (which SQLite never locks)

	static int xJournalClose(sqlite3_file* f) {
		File* file = reinterpret_cast<File*>(f);
		// Closing a journal descriptor can't release any database locks
		// (they're on a different inode), so it doesn't need to be deferred.
		CloseFd(file->fd);
		file->fd = -1;
		return SQLITE_OK;
	}

	static int xJournalLock(sqlite3_file* f, int eFileLock) {
		return SQLITE_OK;
	}

	static int xJournalCheckReservedLock(sqlite3_file* f, int* result) {
		*result = 0;
		return SQLITE_OK;
	}

	static int xJournalFileControl(sqlite3_file* f, int op, void* arg) {
		return SQLITE_NOTFOUND;
	}

	static constexpr sqlite3_io_methods journal_io_methods = {
		1,
		xJournalClose,
		xRead,
		xWrite,
		xTruncate,
		xSync,
		xFileSize,
		xJournalLock,
		xJournalLock,
		xJournalCheckReservedLock,
		xJournalFileControl,
		xSectorSize,
		xDeviceCharacteristics,
		NULL, NULL, NULL, NULL, NULL, NULL,
	};

	// sqlite3_vfs methods

	static int xOpen(sqlite3_vfs* vfs, sqlite3_filename name, sqlite3_file* f, int flags, int* out_flags) {
		if (!IsFdName(name)) {
			return Base(vfs)->xOpen(Base(vfs), name, f, flags, out_flags);
		}
		File* file = reinterpret_cast<File*>(f);
		memset(file, 0, sizeof(File));
		if (flags & SQLITE_OPEN_MAIN_DB) {
			return OpenMain(name, file, flags, out_flags);
		}
		if (flags & SQLITE_OPEN_MAIN_JOURNAL) {
			return OpenJournal(name, file, flags, out_flags);
		}
		if (flags & SQLITE_OPEN_SUPER_JOURNAL) {
			// Super-journal names are "<database>-mjXXXXXXXXX", and our
			// database names contain no "-".
			const char* suffix = strrchr(name, '-');
			if (suffix != NULL) {
				std::lock_guard<std::mutex> guard(Mutex());
				File* main = FindMainFileByPrefix(name, suffix - name);
				if (main != NULL) return Fail(main, SQLITE_CANTOPEN, SUPER_JOURNAL_MESSAGE);
			}
		}
		return SQLITE_CANTOPEN;
	}

	static int OpenMain(const char* name, File* file, int flags, int* out_flags) {
		// A file descriptor can only be used by the Open() call that provided
		// it (e.g., "ATTACH 'fd:...'" is not allowed).
		if (pending_name == NULL || strcmp(name, pending_name) != 0) {
			return SQLITE_CANTOPEN;
		}
		int fd = pending_fd;
		int journal_fd = pending_journal_fd;
		pending_name = NULL;

		struct stat st;
		struct stat journal_st;
		int fl = fcntl(fd, F_GETFL);
		int journal_fl = fcntl(journal_fd, F_GETFL);
		if (fl < 0 || journal_fl < 0 || fstat(fd, &st) != 0 || fstat(journal_fd, &journal_st) != 0) {
			return SQLITE_CANTOPEN;
		}
		bool writable = (fl & O_ACCMODE) == O_RDWR;
		bool journal_writable = (journal_fl & O_ACCMODE) == O_RDWR;
		if ((flags & SQLITE_OPEN_READWRITE) && !(writable && journal_writable)) {
			return SQLITE_CANTOPEN;
		}

		int own_fd = Dup(fd);
		int own_journal_fd = Dup(journal_fd);
		if (own_fd < 0 || own_journal_fd < 0) {
			if (own_fd >= 0) CloseFd(own_fd);
			if (own_journal_fd >= 0) CloseFd(own_journal_fd);
			return SQLITE_CANTOPEN;
		}

		{
			std::lock_guard<std::mutex> guard(Mutex());
			Inode* inode = NULL;
			for (Inode* candidate : Inodes()) {
				if (candidate->dev == st.st_dev && candidate->ino == st.st_ino) {
					inode = candidate;
					break;
				}
			}
			if (inode != NULL && (inode->journal_dev != journal_st.st_dev || inode->journal_ino != journal_st.st_ino)) {
				CloseFd(own_fd);
				CloseFd(own_journal_fd);
				return FailOpen(SQLITE_CANTOPEN, JOURNAL_MISMATCH_MESSAGE);
			}
			if (inode == NULL) {
				int lock_fd = Dup(own_fd);
				if (lock_fd < 0) {
					CloseFd(own_fd);
					CloseFd(own_journal_fd);
					return SQLITE_CANTOPEN;
				}
				inode = new Inode();
				inode->dev = st.st_dev;
				inode->ino = st.st_ino;
				inode->journal_dev = journal_st.st_dev;
				inode->journal_ino = journal_st.st_ino;
				inode->nRef = 0;
				inode->nShared = 0;
				inode->nLock = 0;
				inode->eFileLock = SQLITE_LOCK_NONE;
				inode->lockFd = lock_fd;
				inode->lockFdWritable = writable;
				Inodes().push_back(inode);
			} else if (writable && !inode->lockFdWritable) {
				// Write locks can only be acquired through a writable
				// descriptor, so we switch to one now. POSIX locks belong to
				// the process and the inode (not to a descriptor), so locks
				// that are currently held remain held, but closing the old
				// descriptor would release them, so we defer that.
				int lock_fd = Dup(own_fd);
				if (lock_fd < 0) {
					CloseFd(own_fd);
					CloseFd(own_journal_fd);
					return SQLITE_CANTOPEN;
				}
				inode->pendingFds.push_back(inode->lockFd);
				if (inode->nLock == 0) ClosePendingFds(inode);
				inode->lockFd = lock_fd;
				inode->lockFdWritable = true;
			}
			inode->nRef += 1;
			file->inode = inode;
			file->fd = own_fd;
			file->writable = writable;
			file->eFileLock = SQLITE_LOCK_NONE;
			file->journal_fd = own_journal_fd;
			file->journal_writable = journal_writable;
			file->name = name;
			MainFiles().push_back(file);
		}

		file->base.pMethods = &main_io_methods;
		if (out_flags) *out_flags = flags;
		return SQLITE_OK;
	}

	static int OpenJournal(const char* name, File* file, int flags, int* out_flags) {
		std::lock_guard<std::mutex> guard(Mutex());
		File* main = FindMainFile(name);
		if (main == NULL) return SQLITE_CANTOPEN;
		if (!IsLinked(main->journal_fd)) return Fail(main, SQLITE_CANTOPEN, UNLINKED_MESSAGE);
		if ((flags & SQLITE_OPEN_READWRITE) && !main->journal_writable) {
			// The pager handles this when checking for a hot journal.
			flags = (flags & ~(SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE)) | SQLITE_OPEN_READONLY;
		}
		// The journal gets its own descriptor (rather than borrowing the main
		// database File's), so that it stays valid even if SQLite were to close
		// the main database File first.
		int fd = Dup(main->journal_fd);
		if (fd < 0) return SQLITE_CANTOPEN;
		file->fd = fd;
		file->writable = main->journal_writable;
		file->name = name;
		file->base.pMethods = &journal_io_methods;
		if (out_flags) *out_flags = flags;
		return SQLITE_OK;
	}

	// Journals are never deleted, because they couldn't be re-created without
	// permission to create files in the database's directory. Instead, they're
	// truncated, which is equivalent from SQLite's perspective (see xAccess).
	static int xDelete(sqlite3_vfs* vfs, const char* name, int sync_dir) {
		if (!IsFdName(name)) {
			return Base(vfs)->xDelete(Base(vfs), name, sync_dir);
		}
		std::lock_guard<std::mutex> guard(Mutex());
		File* main = FindMainFile(name);
		if (main == NULL) return SQLITE_IOERR_DELETE_NOENT;
		if (Truncate(main->journal_fd, 0) != 0) return SQLITE_IOERR_DELETE;
		// Like deleting a journal, truncating it commits the transaction. The
		// unix VFS only makes a deletion durable (by syncing the directory)
		// when SQLite asks for it via sync_dir (i.e., PRAGMA synchronous =
		// EXTRA), so we do the same, with an equivalent sync of the journal.
		if (sync_dir && Sync(main->journal_fd, SQLITE_SYNC_NORMAL) != 0) {
			return SQLITE_IOERR_DELETE;
		}
		return SQLITE_OK;
	}

	// Like SQLite's unix VFS, an empty journal is reported as nonexistent.
	static int xAccess(sqlite3_vfs* vfs, const char* name, int flags, int* result) {
		if (!IsFdName(name)) {
			return Base(vfs)->xAccess(Base(vfs), name, flags, result);
		}
		*result = 0;
		std::lock_guard<std::mutex> guard(Mutex());
		File* main = FindMainFile(name);
		if (main == NULL) return SQLITE_OK;
		struct stat st;
		if (fstat(main->journal_fd, &st) != 0) return SQLITE_IOERR_ACCESS;
		if (st.st_nlink == 0 || !IsLinked(main->fd)) return Fail(main, SQLITE_CANTOPEN, UNLINKED_MESSAGE);
		*result = st.st_size > 0 && (flags != SQLITE_ACCESS_READWRITE || main->journal_writable);
		return SQLITE_OK;
	}

	static int xFullPathname(sqlite3_vfs* vfs, const char* name, int size, char* out) {
		if (IsFdName(name)) {
			size_t length = strlen(name);
			if (length >= (size_t)size) return SQLITE_CANTOPEN;
			memcpy(out, name, length + 1);
			return SQLITE_OK;
		}
		return Base(vfs)->xFullPathname(Base(vfs), name, size, out);
	}

	static void* xDlOpen(sqlite3_vfs* vfs, const char* filename) {
		return Base(vfs)->xDlOpen(Base(vfs), filename);
	}

	static void xDlError(sqlite3_vfs* vfs, int size, char* out) {
		Base(vfs)->xDlError(Base(vfs), size, out);
	}

	static void (*xDlSym(sqlite3_vfs* vfs, void* handle, const char* symbol))(void) {
		return Base(vfs)->xDlSym(Base(vfs), handle, symbol);
	}

	static void xDlClose(sqlite3_vfs* vfs, void* handle) {
		Base(vfs)->xDlClose(Base(vfs), handle);
	}

	static int xRandomness(sqlite3_vfs* vfs, int size, char* out) {
		return Base(vfs)->xRandomness(Base(vfs), size, out);
	}

	static int xSleep(sqlite3_vfs* vfs, int microseconds) {
		return Base(vfs)->xSleep(Base(vfs), microseconds);
	}

	static int xCurrentTime(sqlite3_vfs* vfs, double* out) {
		return Base(vfs)->xCurrentTime(Base(vfs), out);
	}

	static int xGetLastError(sqlite3_vfs* vfs, int size, char* out) {
		return Base(vfs)->xGetLastError(Base(vfs), size, out);
	}

	static int xCurrentTimeInt64(sqlite3_vfs* vfs, sqlite3_int64* out) {
		sqlite3_vfs* base = Base(vfs);
		if (base->iVersion >= 2 && base->xCurrentTimeInt64 != NULL) {
			return base->xCurrentTimeInt64(base, out);
		}
		double now;
		int rc = base->xCurrentTime(base, &now);
		*out = (sqlite3_int64)(now * 86400000.0);
		return rc;
	}

	static int xSetSystemCall(sqlite3_vfs* vfs, const char* name, sqlite3_syscall_ptr ptr) {
		sqlite3_vfs* base = Base(vfs);
		if (base->iVersion < 3 || base->xSetSystemCall == NULL) return SQLITE_NOTFOUND;
		return base->xSetSystemCall(base, name, ptr);
	}

	static sqlite3_syscall_ptr xGetSystemCall(sqlite3_vfs* vfs, const char* name) {
		sqlite3_vfs* base = Base(vfs);
		if (base->iVersion < 3 || base->xGetSystemCall == NULL) return NULL;
		return base->xGetSystemCall(base, name);
	}

	static const char* xNextSystemCall(sqlite3_vfs* vfs, const char* name) {
		sqlite3_vfs* base = Base(vfs);
		if (base->iVersion < 3 || base->xNextSystemCall == NULL) return NULL;
		return base->xNextSystemCall(base, name);
	}

	// Used to pass file descriptors from Open() to xOpen(), which always
	// happen synchronously on the same thread.
	static thread_local int pending_fd;
	static thread_local int pending_journal_fd;
	static thread_local const char* pending_name;

	// Errors that occur before the main database File exists (see Open()).
	static thread_local int open_error_code;
	static thread_local const char* open_error_message;

	// Incremented by BeginOperation(). Each database connection is only used
	// by one thread at a time, so a per-thread counter suffices.
	static thread_local unsigned long long operation;
};

thread_local int FdVfs::pending_fd = -1;
thread_local int FdVfs::pending_journal_fd = -1;
thread_local const char* FdVfs::pending_name = NULL;
thread_local int FdVfs::open_error_code = SQLITE_OK;
thread_local const char* FdVfs::open_error_message = NULL;
thread_local unsigned long long FdVfs::operation = 0;

#else // _WIN32

class FdVfs {
public:
	static void Register() {}
	static void BeginOperation() {}
	static const char* Validate(int fd, int journal_fd, bool readonly) {
		return "Opening a database from a file descriptor is not supported on Windows";
	}
	static int Open(int fd, int journal_fd, int flags, sqlite3** db_handle, const char** error_message) {
		*db_handle = NULL;
		*error_message = NULL;
		return SQLITE_CANTOPEN;
	}
	static const char* TakeErrorMessage(sqlite3* db_handle, int code) {
		return NULL;
	}
};

#endif
