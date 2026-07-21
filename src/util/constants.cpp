// Caches JavaScript strings that are used frequently as property keys or
// error codes. Persistent references to strings require Node-API version 10.
class CS {
public:

	Napi::String Code(Napi::Env env, int code) {
		auto element = codes.find(code);
		if (element != codes.end()) return element->second.Value();
		return StringFromUtf8(env, (std::string("UNKNOWN_SQLITE_ERROR_") + std::to_string(code)).c_str(), -1);
	}

	explicit CS(Napi::Env env) {
		SetString(env, database, "database");
		SetString(env, reader, "reader");
		SetString(env, source, "source");
		SetString(env, memory, "memory");
		SetString(env, readonly, "readonly");
		SetString(env, name, "name");
		SetString(env, next, "next");
		SetString(env, length, "length");
		SetString(env, done, "done");
		SetString(env, value, "value");
		SetString(env, changes, "changes");
		SetString(env, lastInsertRowid, "lastInsertRowid");
		SetString(env, statement, "statement");
		SetString(env, column, "column");
		SetString(env, table, "table");
		SetString(env, type, "type");
		SetString(env, totalPages, "totalPages");
		SetString(env, remainingPages, "remainingPages");

		SetCode(env, SQLITE_OK, "SQLITE_OK");
		SetCode(env, SQLITE_ERROR, "SQLITE_ERROR");
		SetCode(env, SQLITE_INTERNAL, "SQLITE_INTERNAL");
		SetCode(env, SQLITE_PERM, "SQLITE_PERM");
		SetCode(env, SQLITE_ABORT, "SQLITE_ABORT");
		SetCode(env, SQLITE_BUSY, "SQLITE_BUSY");
		SetCode(env, SQLITE_LOCKED, "SQLITE_LOCKED");
		SetCode(env, SQLITE_NOMEM, "SQLITE_NOMEM");
		SetCode(env, SQLITE_READONLY, "SQLITE_READONLY");
		SetCode(env, SQLITE_INTERRUPT, "SQLITE_INTERRUPT");
		SetCode(env, SQLITE_IOERR, "SQLITE_IOERR");
		SetCode(env, SQLITE_CORRUPT, "SQLITE_CORRUPT");
		SetCode(env, SQLITE_NOTFOUND, "SQLITE_NOTFOUND");
		SetCode(env, SQLITE_FULL, "SQLITE_FULL");
		SetCode(env, SQLITE_CANTOPEN, "SQLITE_CANTOPEN");
		SetCode(env, SQLITE_PROTOCOL, "SQLITE_PROTOCOL");
		SetCode(env, SQLITE_EMPTY, "SQLITE_EMPTY");
		SetCode(env, SQLITE_SCHEMA, "SQLITE_SCHEMA");
		SetCode(env, SQLITE_TOOBIG, "SQLITE_TOOBIG");
		SetCode(env, SQLITE_CONSTRAINT, "SQLITE_CONSTRAINT");
		SetCode(env, SQLITE_MISMATCH, "SQLITE_MISMATCH");
		SetCode(env, SQLITE_MISUSE, "SQLITE_MISUSE");
		SetCode(env, SQLITE_NOLFS, "SQLITE_NOLFS");
		SetCode(env, SQLITE_AUTH, "SQLITE_AUTH");
		SetCode(env, SQLITE_FORMAT, "SQLITE_FORMAT");
		SetCode(env, SQLITE_RANGE, "SQLITE_RANGE");
		SetCode(env, SQLITE_NOTADB, "SQLITE_NOTADB");
		SetCode(env, SQLITE_NOTICE, "SQLITE_NOTICE");
		SetCode(env, SQLITE_WARNING, "SQLITE_WARNING");
		SetCode(env, SQLITE_ROW, "SQLITE_ROW");
		SetCode(env, SQLITE_DONE, "SQLITE_DONE");

		SetCode(env, SQLITE_ERROR_MISSING_COLLSEQ, "SQLITE_ERROR_MISSING_COLLSEQ");
		SetCode(env, SQLITE_ERROR_RETRY, "SQLITE_ERROR_RETRY");
		SetCode(env, SQLITE_ERROR_SNAPSHOT, "SQLITE_ERROR_SNAPSHOT");
		SetCode(env, SQLITE_IOERR_READ, "SQLITE_IOERR_READ");
		SetCode(env, SQLITE_IOERR_SHORT_READ, "SQLITE_IOERR_SHORT_READ");
		SetCode(env, SQLITE_IOERR_WRITE, "SQLITE_IOERR_WRITE");
		SetCode(env, SQLITE_IOERR_FSYNC, "SQLITE_IOERR_FSYNC");
		SetCode(env, SQLITE_IOERR_DIR_FSYNC, "SQLITE_IOERR_DIR_FSYNC");
		SetCode(env, SQLITE_IOERR_TRUNCATE, "SQLITE_IOERR_TRUNCATE");
		SetCode(env, SQLITE_IOERR_FSTAT, "SQLITE_IOERR_FSTAT");
		SetCode(env, SQLITE_IOERR_UNLOCK, "SQLITE_IOERR_UNLOCK");
		SetCode(env, SQLITE_IOERR_RDLOCK, "SQLITE_IOERR_RDLOCK");
		SetCode(env, SQLITE_IOERR_DELETE, "SQLITE_IOERR_DELETE");
		SetCode(env, SQLITE_IOERR_BLOCKED, "SQLITE_IOERR_BLOCKED");
		SetCode(env, SQLITE_IOERR_NOMEM, "SQLITE_IOERR_NOMEM");
		SetCode(env, SQLITE_IOERR_ACCESS, "SQLITE_IOERR_ACCESS");
		SetCode(env, SQLITE_IOERR_CHECKRESERVEDLOCK, "SQLITE_IOERR_CHECKRESERVEDLOCK");
		SetCode(env, SQLITE_IOERR_LOCK, "SQLITE_IOERR_LOCK");
		SetCode(env, SQLITE_IOERR_CLOSE, "SQLITE_IOERR_CLOSE");
		SetCode(env, SQLITE_IOERR_DIR_CLOSE, "SQLITE_IOERR_DIR_CLOSE");
		SetCode(env, SQLITE_IOERR_SHMOPEN, "SQLITE_IOERR_SHMOPEN");
		SetCode(env, SQLITE_IOERR_SHMSIZE, "SQLITE_IOERR_SHMSIZE");
		SetCode(env, SQLITE_IOERR_SHMLOCK, "SQLITE_IOERR_SHMLOCK");
		SetCode(env, SQLITE_IOERR_SHMMAP, "SQLITE_IOERR_SHMMAP");
		SetCode(env, SQLITE_IOERR_SEEK, "SQLITE_IOERR_SEEK");
		SetCode(env, SQLITE_IOERR_DELETE_NOENT, "SQLITE_IOERR_DELETE_NOENT");
		SetCode(env, SQLITE_IOERR_MMAP, "SQLITE_IOERR_MMAP");
		SetCode(env, SQLITE_IOERR_GETTEMPPATH, "SQLITE_IOERR_GETTEMPPATH");
		SetCode(env, SQLITE_IOERR_CONVPATH, "SQLITE_IOERR_CONVPATH");
		SetCode(env, SQLITE_IOERR_VNODE, "SQLITE_IOERR_VNODE");
		SetCode(env, SQLITE_IOERR_AUTH, "SQLITE_IOERR_AUTH");
		SetCode(env, SQLITE_IOERR_BEGIN_ATOMIC, "SQLITE_IOERR_BEGIN_ATOMIC");
		SetCode(env, SQLITE_IOERR_COMMIT_ATOMIC, "SQLITE_IOERR_COMMIT_ATOMIC");
		SetCode(env, SQLITE_IOERR_ROLLBACK_ATOMIC, "SQLITE_IOERR_ROLLBACK_ATOMIC");
		SetCode(env, SQLITE_IOERR_DATA, "SQLITE_IOERR_DATA");
		SetCode(env, SQLITE_IOERR_CORRUPTFS, "SQLITE_IOERR_CORRUPTFS");
		SetCode(env, SQLITE_IOERR_IN_PAGE, "SQLITE_IOERR_IN_PAGE");
		SetCode(env, SQLITE_LOCKED_SHAREDCACHE, "SQLITE_LOCKED_SHAREDCACHE");
		SetCode(env, SQLITE_LOCKED_VTAB, "SQLITE_LOCKED_VTAB");
		SetCode(env, SQLITE_BUSY_RECOVERY, "SQLITE_BUSY_RECOVERY");
		SetCode(env, SQLITE_BUSY_SNAPSHOT, "SQLITE_BUSY_SNAPSHOT");
		SetCode(env, SQLITE_CANTOPEN_NOTEMPDIR, "SQLITE_CANTOPEN_NOTEMPDIR");
		SetCode(env, SQLITE_CANTOPEN_ISDIR, "SQLITE_CANTOPEN_ISDIR");
		SetCode(env, SQLITE_CANTOPEN_FULLPATH, "SQLITE_CANTOPEN_FULLPATH");
		SetCode(env, SQLITE_CANTOPEN_CONVPATH, "SQLITE_CANTOPEN_CONVPATH");
		SetCode(env, SQLITE_CANTOPEN_DIRTYWAL, "SQLITE_CANTOPEN_DIRTYWAL");
		SetCode(env, SQLITE_CANTOPEN_SYMLINK, "SQLITE_CANTOPEN_SYMLINK");
		SetCode(env, SQLITE_CORRUPT_VTAB, "SQLITE_CORRUPT_VTAB");
		SetCode(env, SQLITE_CORRUPT_SEQUENCE, "SQLITE_CORRUPT_SEQUENCE");
		SetCode(env, SQLITE_CORRUPT_INDEX, "SQLITE_CORRUPT_INDEX");
		SetCode(env, SQLITE_READONLY_RECOVERY, "SQLITE_READONLY_RECOVERY");
		SetCode(env, SQLITE_READONLY_CANTLOCK, "SQLITE_READONLY_CANTLOCK");
		SetCode(env, SQLITE_READONLY_ROLLBACK, "SQLITE_READONLY_ROLLBACK");
		SetCode(env, SQLITE_READONLY_DBMOVED, "SQLITE_READONLY_DBMOVED");
		SetCode(env, SQLITE_READONLY_CANTINIT, "SQLITE_READONLY_CANTINIT");
		SetCode(env, SQLITE_READONLY_DIRECTORY, "SQLITE_READONLY_DIRECTORY");
		SetCode(env, SQLITE_ABORT_ROLLBACK, "SQLITE_ABORT_ROLLBACK");
		SetCode(env, SQLITE_CONSTRAINT_CHECK, "SQLITE_CONSTRAINT_CHECK");
		SetCode(env, SQLITE_CONSTRAINT_COMMITHOOK, "SQLITE_CONSTRAINT_COMMITHOOK");
		SetCode(env, SQLITE_CONSTRAINT_FOREIGNKEY, "SQLITE_CONSTRAINT_FOREIGNKEY");
		SetCode(env, SQLITE_CONSTRAINT_FUNCTION, "SQLITE_CONSTRAINT_FUNCTION");
		SetCode(env, SQLITE_CONSTRAINT_NOTNULL, "SQLITE_CONSTRAINT_NOTNULL");
		SetCode(env, SQLITE_CONSTRAINT_PRIMARYKEY, "SQLITE_CONSTRAINT_PRIMARYKEY");
		SetCode(env, SQLITE_CONSTRAINT_TRIGGER, "SQLITE_CONSTRAINT_TRIGGER");
		SetCode(env, SQLITE_CONSTRAINT_UNIQUE, "SQLITE_CONSTRAINT_UNIQUE");
		SetCode(env, SQLITE_CONSTRAINT_VTAB, "SQLITE_CONSTRAINT_VTAB");
		SetCode(env, SQLITE_CONSTRAINT_ROWID, "SQLITE_CONSTRAINT_ROWID");
		SetCode(env, SQLITE_CONSTRAINT_PINNED, "SQLITE_CONSTRAINT_PINNED");
		SetCode(env, SQLITE_CONSTRAINT_DATATYPE, "SQLITE_CONSTRAINT_DATATYPE");
		SetCode(env, SQLITE_NOTICE_RECOVER_WAL, "SQLITE_NOTICE_RECOVER_WAL");
		SetCode(env, SQLITE_NOTICE_RECOVER_ROLLBACK, "SQLITE_NOTICE_RECOVER_ROLLBACK");
		SetCode(env, SQLITE_NOTICE_RBU, "SQLITE_NOTICE_RBU");
		SetCode(env, SQLITE_WARNING_AUTOINDEX, "SQLITE_WARNING_AUTOINDEX");
		SetCode(env, SQLITE_AUTH_USER, "SQLITE_AUTH_USER");
		SetCode(env, SQLITE_OK_LOAD_PERMANENTLY, "SQLITE_OK_LOAD_PERMANENTLY");
		SetCode(env, SQLITE_OK_SYMLINK, "SQLITE_OK_SYMLINK");
	}

	Napi::Reference<Napi::String> database;
	Napi::Reference<Napi::String> reader;
	Napi::Reference<Napi::String> source;
	Napi::Reference<Napi::String> memory;
	Napi::Reference<Napi::String> readonly;
	Napi::Reference<Napi::String> name;
	Napi::Reference<Napi::String> next;
	Napi::Reference<Napi::String> length;
	Napi::Reference<Napi::String> done;
	Napi::Reference<Napi::String> value;
	Napi::Reference<Napi::String> changes;
	Napi::Reference<Napi::String> lastInsertRowid;
	Napi::Reference<Napi::String> statement;
	Napi::Reference<Napi::String> column;
	Napi::Reference<Napi::String> table;
	Napi::Reference<Napi::String> type;
	Napi::Reference<Napi::String> totalPages;
	Napi::Reference<Napi::String> remainingPages;

private:

	static void SetString(Napi::Env env, Napi::Reference<Napi::String>& constant, const char* str) {
		constant = Napi::Persistent(InternalizedFromLatin1(env, str));
	}

	void SetCode(Napi::Env env, int code, const char* str) {
		codes.emplace(code, Napi::Persistent(InternalizedFromLatin1(env, str)));
	}

	std::unordered_map<int, Napi::Reference<Napi::String>> codes;
};
