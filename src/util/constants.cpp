class CS {
public:

	v8::Local<v8::String> Code(v8::Isolate* isolate, int code) {
		auto element = codes.find(code);
		if (element != codes.end()) return element->second.Get(isolate);
		return StringFromUtf8(isolate, (std::string("UNKNOWN_SQLITE_ERROR_") + std::to_string(code)).c_str(), -1);
	}

	explicit CS(v8::Isolate* isolate) {
		SetString(isolate, database, "database");
		SetString(isolate, reader, "reader");
		SetString(isolate, source, "source");
		SetString(isolate, memory, "memory");
		SetString(isolate, readonly, "readonly");
		SetString(isolate, name, "name");
		SetString(isolate, next, "next");
		SetString(isolate, length, "length");
		SetString(isolate, done, "done");
		SetString(isolate, value, "value");
		SetString(isolate, changes, "changes");
		SetString(isolate, lastInsertRowid, "lastInsertRowid");
		SetString(isolate, statement, "statement");
		SetString(isolate, column, "column");
		SetString(isolate, table, "table");
		SetString(isolate, type, "type");
		SetString(isolate, totalPages, "totalPages");
		SetString(isolate, remainingPages, "remainingPages");

		SetCode(isolate, SQLITE_OK, "SQLITE_OK");
		SetCode(isolate, SQLITE_ERROR, "SQLITE_ERROR");
		SetCode(isolate, SQLITE_INTERNAL, "SQLITE_INTERNAL");
		SetCode(isolate, SQLITE_PERM, "SQLITE_PERM");
		SetCode(isolate, SQLITE_ABORT, "SQLITE_ABORT");
		SetCode(isolate, SQLITE_BUSY, "SQLITE_BUSY");
		SetCode(isolate, SQLITE_LOCKED, "SQLITE_LOCKED");
		SetCode(isolate, SQLITE_NOMEM, "SQLITE_NOMEM");
		SetCode(isolate, SQLITE_READONLY, "SQLITE_READONLY");
		SetCode(isolate, SQLITE_INTERRUPT, "SQLITE_INTERRUPT");
		SetCode(isolate, SQLITE_IOERR, "SQLITE_IOERR");
		SetCode(isolate, SQLITE_CORRUPT, "SQLITE_CORRUPT");
		SetCode(isolate, SQLITE_NOTFOUND, "SQLITE_NOTFOUND");
		SetCode(isolate, SQLITE_FULL, "SQLITE_FULL");
		SetCode(isolate, SQLITE_CANTOPEN, "SQLITE_CANTOPEN");
		SetCode(isolate, SQLITE_PROTOCOL, "SQLITE_PROTOCOL");
		SetCode(isolate, SQLITE_EMPTY, "SQLITE_EMPTY");
		SetCode(isolate, SQLITE_SCHEMA, "SQLITE_SCHEMA");
		SetCode(isolate, SQLITE_TOOBIG, "SQLITE_TOOBIG");
		SetCode(isolate, SQLITE_CONSTRAINT, "SQLITE_CONSTRAINT");
		SetCode(isolate, SQLITE_MISMATCH, "SQLITE_MISMATCH");
		SetCode(isolate, SQLITE_MISUSE, "SQLITE_MISUSE");
		SetCode(isolate, SQLITE_NOLFS, "SQLITE_NOLFS");
		SetCode(isolate, SQLITE_AUTH, "SQLITE_AUTH");
		SetCode(isolate, SQLITE_FORMAT, "SQLITE_FORMAT");
		SetCode(isolate, SQLITE_RANGE, "SQLITE_RANGE");
		SetCode(isolate, SQLITE_NOTADB, "SQLITE_NOTADB");
		SetCode(isolate, SQLITE_NOTICE, "SQLITE_NOTICE");
		SetCode(isolate, SQLITE_WARNING, "SQLITE_WARNING");
		SetCode(isolate, SQLITE_ROW, "SQLITE_ROW");
		SetCode(isolate, SQLITE_DONE, "SQLITE_DONE");

		SetCode(isolate, SQLITE_ERROR_MISSING_COLLSEQ, "SQLITE_ERROR_MISSING_COLLSEQ");
		SetCode(isolate, SQLITE_ERROR_RETRY, "SQLITE_ERROR_RETRY");
		SetCode(isolate, SQLITE_ERROR_SNAPSHOT, "SQLITE_ERROR_SNAPSHOT");
		SetCode(isolate, SQLITE_IOERR_READ, "SQLITE_IOERR_READ");
		SetCode(isolate, SQLITE_IOERR_SHORT_READ, "SQLITE_IOERR_SHORT_READ");
		SetCode(isolate, SQLITE_IOERR_WRITE, "SQLITE_IOERR_WRITE");
		SetCode(isolate, SQLITE_IOERR_FSYNC, "SQLITE_IOERR_FSYNC");
		SetCode(isolate, SQLITE_IOERR_DIR_FSYNC, "SQLITE_IOERR_DIR_FSYNC");
		SetCode(isolate, SQLITE_IOERR_TRUNCATE, "SQLITE_IOERR_TRUNCATE");
		SetCode(isolate, SQLITE_IOERR_FSTAT, "SQLITE_IOERR_FSTAT");
		SetCode(isolate, SQLITE_IOERR_UNLOCK, "SQLITE_IOERR_UNLOCK");
		SetCode(isolate, SQLITE_IOERR_RDLOCK, "SQLITE_IOERR_RDLOCK");
		SetCode(isolate, SQLITE_IOERR_DELETE, "SQLITE_IOERR_DELETE");
		SetCode(isolate, SQLITE_IOERR_BLOCKED, "SQLITE_IOERR_BLOCKED");
		SetCode(isolate, SQLITE_IOERR_NOMEM, "SQLITE_IOERR_NOMEM");
		SetCode(isolate, SQLITE_IOERR_ACCESS, "SQLITE_IOERR_ACCESS");
		SetCode(isolate, SQLITE_IOERR_CHECKRESERVEDLOCK, "SQLITE_IOERR_CHECKRESERVEDLOCK");
		SetCode(isolate, SQLITE_IOERR_LOCK, "SQLITE_IOERR_LOCK");
		SetCode(isolate, SQLITE_IOERR_CLOSE, "SQLITE_IOERR_CLOSE");
		SetCode(isolate, SQLITE_IOERR_DIR_CLOSE, "SQLITE_IOERR_DIR_CLOSE");
		SetCode(isolate, SQLITE_IOERR_SHMOPEN, "SQLITE_IOERR_SHMOPEN");
		SetCode(isolate, SQLITE_IOERR_SHMSIZE, "SQLITE_IOERR_SHMSIZE");
		SetCode(isolate, SQLITE_IOERR_SHMLOCK, "SQLITE_IOERR_SHMLOCK");
		SetCode(isolate, SQLITE_IOERR_SHMMAP, "SQLITE_IOERR_SHMMAP");
		SetCode(isolate, SQLITE_IOERR_SEEK, "SQLITE_IOERR_SEEK");
		SetCode(isolate, SQLITE_IOERR_DELETE_NOENT, "SQLITE_IOERR_DELETE_NOENT");
		SetCode(isolate, SQLITE_IOERR_MMAP, "SQLITE_IOERR_MMAP");
		SetCode(isolate, SQLITE_IOERR_GETTEMPPATH, "SQLITE_IOERR_GETTEMPPATH");
		SetCode(isolate, SQLITE_IOERR_CONVPATH, "SQLITE_IOERR_CONVPATH");
		SetCode(isolate, SQLITE_IOERR_VNODE, "SQLITE_IOERR_VNODE");
		SetCode(isolate, SQLITE_IOERR_AUTH, "SQLITE_IOERR_AUTH");
		SetCode(isolate, SQLITE_IOERR_BEGIN_ATOMIC, "SQLITE_IOERR_BEGIN_ATOMIC");
		SetCode(isolate, SQLITE_IOERR_COMMIT_ATOMIC, "SQLITE_IOERR_COMMIT_ATOMIC");
		SetCode(isolate, SQLITE_IOERR_ROLLBACK_ATOMIC, "SQLITE_IOERR_ROLLBACK_ATOMIC");
		SetCode(isolate, SQLITE_IOERR_DATA, "SQLITE_IOERR_DATA");
		SetCode(isolate, SQLITE_IOERR_CORRUPTFS, "SQLITE_IOERR_CORRUPTFS");
		SetCode(isolate, SQLITE_IOERR_IN_PAGE, "SQLITE_IOERR_IN_PAGE");
		SetCode(isolate, SQLITE_LOCKED_SHAREDCACHE, "SQLITE_LOCKED_SHAREDCACHE");
		SetCode(isolate, SQLITE_LOCKED_VTAB, "SQLITE_LOCKED_VTAB");
		SetCode(isolate, SQLITE_BUSY_RECOVERY, "SQLITE_BUSY_RECOVERY");
		SetCode(isolate, SQLITE_BUSY_SNAPSHOT, "SQLITE_BUSY_SNAPSHOT");
		SetCode(isolate, SQLITE_CANTOPEN_NOTEMPDIR, "SQLITE_CANTOPEN_NOTEMPDIR");
		SetCode(isolate, SQLITE_CANTOPEN_ISDIR, "SQLITE_CANTOPEN_ISDIR");
		SetCode(isolate, SQLITE_CANTOPEN_FULLPATH, "SQLITE_CANTOPEN_FULLPATH");
		SetCode(isolate, SQLITE_CANTOPEN_CONVPATH, "SQLITE_CANTOPEN_CONVPATH");
		SetCode(isolate, SQLITE_CANTOPEN_DIRTYWAL, "SQLITE_CANTOPEN_DIRTYWAL");
		SetCode(isolate, SQLITE_CANTOPEN_SYMLINK, "SQLITE_CANTOPEN_SYMLINK");
		SetCode(isolate, SQLITE_CORRUPT_VTAB, "SQLITE_CORRUPT_VTAB");
		SetCode(isolate, SQLITE_CORRUPT_SEQUENCE, "SQLITE_CORRUPT_SEQUENCE");
		SetCode(isolate, SQLITE_CORRUPT_INDEX, "SQLITE_CORRUPT_INDEX");
		SetCode(isolate, SQLITE_READONLY_RECOVERY, "SQLITE_READONLY_RECOVERY");
		SetCode(isolate, SQLITE_READONLY_CANTLOCK, "SQLITE_READONLY_CANTLOCK");
		SetCode(isolate, SQLITE_READONLY_ROLLBACK, "SQLITE_READONLY_ROLLBACK");
		SetCode(isolate, SQLITE_READONLY_DBMOVED, "SQLITE_READONLY_DBMOVED");
		SetCode(isolate, SQLITE_READONLY_CANTINIT, "SQLITE_READONLY_CANTINIT");
		SetCode(isolate, SQLITE_READONLY_DIRECTORY, "SQLITE_READONLY_DIRECTORY");
		SetCode(isolate, SQLITE_ABORT_ROLLBACK, "SQLITE_ABORT_ROLLBACK");
		SetCode(isolate, SQLITE_CONSTRAINT_CHECK, "SQLITE_CONSTRAINT_CHECK");
		SetCode(isolate, SQLITE_CONSTRAINT_COMMITHOOK, "SQLITE_CONSTRAINT_COMMITHOOK");
		SetCode(isolate, SQLITE_CONSTRAINT_FOREIGNKEY, "SQLITE_CONSTRAINT_FOREIGNKEY");
		SetCode(isolate, SQLITE_CONSTRAINT_FUNCTION, "SQLITE_CONSTRAINT_FUNCTION");
		SetCode(isolate, SQLITE_CONSTRAINT_NOTNULL, "SQLITE_CONSTRAINT_NOTNULL");
		SetCode(isolate, SQLITE_CONSTRAINT_PRIMARYKEY, "SQLITE_CONSTRAINT_PRIMARYKEY");
		SetCode(isolate, SQLITE_CONSTRAINT_TRIGGER, "SQLITE_CONSTRAINT_TRIGGER");
		SetCode(isolate, SQLITE_CONSTRAINT_UNIQUE, "SQLITE_CONSTRAINT_UNIQUE");
		SetCode(isolate, SQLITE_CONSTRAINT_VTAB, "SQLITE_CONSTRAINT_VTAB");
		SetCode(isolate, SQLITE_CONSTRAINT_ROWID, "SQLITE_CONSTRAINT_ROWID");
		SetCode(isolate, SQLITE_CONSTRAINT_PINNED, "SQLITE_CONSTRAINT_PINNED");
		SetCode(isolate, SQLITE_CONSTRAINT_DATATYPE, "SQLITE_CONSTRAINT_DATATYPE");
		SetCode(isolate, SQLITE_NOTICE_RECOVER_WAL, "SQLITE_NOTICE_RECOVER_WAL");
		SetCode(isolate, SQLITE_NOTICE_RECOVER_ROLLBACK, "SQLITE_NOTICE_RECOVER_ROLLBACK");
		SetCode(isolate, SQLITE_NOTICE_RBU, "SQLITE_NOTICE_RBU");
		SetCode(isolate, SQLITE_WARNING_AUTOINDEX, "SQLITE_WARNING_AUTOINDEX");
		SetCode(isolate, SQLITE_AUTH_USER, "SQLITE_AUTH_USER");
		SetCode(isolate, SQLITE_OK_LOAD_PERMANENTLY, "SQLITE_OK_LOAD_PERMANENTLY");
		SetCode(isolate, SQLITE_OK_SYMLINK, "SQLITE_OK_SYMLINK");
	}

	v8::Global<v8::String> database;
	v8::Global<v8::String> reader;
	v8::Global<v8::String> source;
	v8::Global<v8::String> memory;
	v8::Global<v8::String> readonly;
	v8::Global<v8::String> name;
	v8::Global<v8::String> next;
	v8::Global<v8::String> length;
	v8::Global<v8::String> done;
	v8::Global<v8::String> value;
	v8::Global<v8::String> changes;
	v8::Global<v8::String> lastInsertRowid;
	v8::Global<v8::String> statement;
	v8::Global<v8::String> column;
	v8::Global<v8::String> table;
	v8::Global<v8::String> type;
	v8::Global<v8::String> totalPages;
	v8::Global<v8::String> remainingPages;

private:

	static void SetString(v8::Isolate* isolate, v8::Global<v8::String>& constant, const char* str) {
		constant.Reset(isolate, InternalizedFromLatin1(isolate, str));
	}

	void SetCode(v8::Isolate* isolate, int code, const char* str) {
		codes.emplace(std::piecewise_construct,
			std::forward_as_tuple(code),
			std::forward_as_tuple(isolate, InternalizedFromLatin1(isolate, str)));
	}

	std::unordered_map<int, v8::Global<v8::String> > codes;
};
