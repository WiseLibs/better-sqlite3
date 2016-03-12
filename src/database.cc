#include <cstdlib>
#include <sqlite3.h>
#include <nan.h>
#include "macros.h"
#include "statement.h"
#include "transaction.h"
#include "database.h"

const int WRITE_MODE = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_SHAREDCACHE;
const int READ_MODE = SQLITE_OPEN_READONLY | SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_SHAREDCACHE;
const v8::PropertyAttribute FROZEN = static_cast<v8::PropertyAttribute>(v8::DontDelete | v8::ReadOnly);
bool CONSTRUCTING_PRIVILEGES = false;

class OpenWorker : public Nan::AsyncWorker {
	public:
		OpenWorker(Database*, char*);
		~OpenWorker();
		void Execute();
		void HandleOKCallback();
		void HandleErrorCallback();
	private:
		Database* db;
		char* filename;
};

class CloseWorker : public Nan::AsyncWorker {
	public:
		CloseWorker(Database*, bool);
		~CloseWorker();
		void Execute();
		void HandleOKCallback();
		void HandleErrorCallback();
	private:
		Database* db;
		bool still_connecting;
};





Database::Database() : Nan::ObjectWrap(),
	readHandle(NULL),
	writeHandle(NULL),
	state(DB_CONNECTING),
	requests(0),
	workers(0),
	stmts() {}
Database::~Database() {
	state = DB_DONE;
	stmts.Flush(Statement::CloseStatement);
	sqlite3_close_v2(readHandle);
	sqlite3_close_v2(writeHandle);
}
NAN_MODULE_INIT(Database::Init) {
	Nan::HandleScope scope;
	
	v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
	t->InstanceTemplate()->SetInternalFieldCount(1);
	t->SetClassName(Nan::New("Database").ToLocalChecked());
	
	Nan::SetPrototypeMethod(t, "close", Close);
	Nan::SetPrototypeMethod(t, "prepare", PrepareStatement);
	Nan::SetPrototypeMethod(t, "begin", PrepareTransaction);
	Nan::SetAccessor(t->InstanceTemplate(), Nan::New("open").ToLocalChecked(), OpenGetter);
	
	constructor.Reset(Nan::GetFunction(t).ToLocalChecked());
	Nan::Set(target, Nan::New("Database").ToLocalChecked(),
		Nan::GetFunction(t).ToLocalChecked());
}
CONSTRUCTOR(Database::constructor);
NAN_METHOD(Database::New) {
	REQUIRE_ARGUMENTS(1);
	if (!info.IsConstructCall()) {
		v8::Local<v8::Value> args[1] = {info[0]};
		v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
		info.GetReturnValue().Set(cons->NewInstance(1, args));
	} else {
		REQUIRE_ARGUMENT_STRING(0, filename);
		
		Database* db = new Database();
		db->Wrap(info.This());
		
		db->Ref();
		db->workers += 1;
		Nan::AsyncQueueWorker(new OpenWorker(db, RAW_STRING(filename)));
		
		info.GetReturnValue().Set(info.This());
	}
}
NAN_GETTER(Database::OpenGetter) {
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	info.GetReturnValue().Set(db->state == DB_READY);
}
NAN_METHOD(Database::Close) {
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	
	if (db->state != DB_DONE) {
		db->state = DB_DONE;
		db->Ref();
		db->workers += 1;
		
		if (db->requests == 0) {
			db->ActuallyClose();
		}
	}
	
	info.GetReturnValue().Set(info.This());
}
void Database::ActuallyClose() {
	Nan::AsyncQueueWorker(new CloseWorker(this, state == DB_CONNECTING));
}
NAN_METHOD(Database::PrepareStatement) {
	REQUIRE_ARGUMENT_STRING(0, source);
	Database* db = Nan::ObjectWrap::Unwrap<Database>(info.This());
	if (db->state != DB_READY) {
		return Nan::ThrowError("The database connection is not open.");
	}
	
	CONSTRUCTING_PRIVILEGES = true;
	v8::Local<v8::Function> cons = Nan::New<v8::Function>(Statement::constructor);
	v8::Local<v8::Object> statement = cons->NewInstance(0, NULL);
	CONSTRUCTING_PRIVILEGES = false;
	
	// Invokes String.prototype.trim on the input string.
	v8::Local<v8::StringObject> str = Nan::New<v8::StringObject>(source);
	INVOKE_METHOD(trimmedSource, str, "trim", 0, NULL);
	if (!trimmedSource->IsString()) {
		return Nan::ThrowTypeError("Expected String.prototype.trim to return a string.");
	} else {
		source = v8::Local<v8::String>::Cast(trimmedSource);
	}
	
	// Allocates source string.
	Nan::Utf8String utf8(source);
	int utf8_len = utf8.length();
	char* utf8_value = (char*) calloc(sizeof(char), utf8_len);
	strncpy(utf8_value, *utf8, utf8_len);
	
	// Initializes object properties.
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(statement);
	stmt->db = db;
	stmt->source_string = utf8_value;
	stmt->source_length = utf8_len;
	Nan::ForceSet(statement, Nan::New("database").ToLocalChecked(), info.This(), FROZEN);
	Nan::ForceSet(statement, Nan::New("source").ToLocalChecked(), source, FROZEN);
	
	// Builds actual sqlite3_stmt.
	const char* tail;
	sqlite3_stmt* handle;
	int status = sqlite3_prepare_v2(db->readHandle, utf8_value, utf8_len, &handle, &tail);
	
	stmt->handles = new sqlite3_stmt* [1];
	stmt->handles[0] = handle;
	stmt->handle_states = new bool [1]();
	stmt->handle_count = 1;
	
	// Validates the sqlite3_stmt.
	if (status != SQLITE_OK) {
		CONCAT3(message, "Failed to construct the SQL statement. (", sqlite3_errmsg(db->readHandle), ")");
		return Nan::ThrowError(message);
	}
	if (handle == NULL) {
		return Nan::ThrowError("The supplied SQL query contains no statements.");
	}
	if (tail != utf8_value + utf8_len) {
		return Nan::ThrowError("The db.prepare() method only accepts a single SQL statement.");
	}
	
	// If the sqlite3_stmt is not read-only, replaces the handle with a proper one.
	if (!sqlite3_stmt_readonly(handle)) {
		sqlite3_finalize(handle);
		status = sqlite3_prepare_v2(db->writeHandle, utf8_value, utf8_len, &handle, NULL);
		stmt->handles[0] = handle;
		
		if (status != SQLITE_OK) {
			CONCAT3(message, "Failed to construct the SQL statement. (", sqlite3_errmsg(db->writeHandle), ")");
			return Nan::ThrowError(message);
		}
		
		stmt->db_handle = db->writeHandle;
		stmt->readonly = false;
	} else {
		stmt->db_handle = db->readHandle;
		stmt->readonly = true;
	}
	
	// Push onto stmts list.
	db->stmts.Add(stmt);
	
	info.GetReturnValue().Set(statement);
}
NAN_METHOD(Database::PrepareTransaction) {
	v8::Local<v8::Function> cons = Nan::New<v8::Function>(Transaction::constructor);
	
	CONSTRUCTING_PRIVILEGES = true;
	v8::Local<v8::Object> transaction = cons->NewInstance(0, NULL);
	CONSTRUCTING_PRIVILEGES = false;
	
	Nan::ForceSet(transaction, Nan::New("database").ToLocalChecked(), info.This(), FROZEN);
	
	info.GetReturnValue().Set(transaction);
}





OpenWorker::OpenWorker(Database* db, char* filename)
	: Nan::AsyncWorker(NULL), db(db), filename(filename) {}
OpenWorker::~OpenWorker() {
	free(filename);
}
void OpenWorker::Execute() {
	int status;
	
	status = sqlite3_open_v2(filename, &db->writeHandle, WRITE_MODE, NULL);
	if (status != SQLITE_OK) {
		SetErrorMessage(sqlite3_errmsg(db->writeHandle));
		sqlite3_close(db->writeHandle);
		db->writeHandle = NULL;
		return;
	}
	
	status = sqlite3_open_v2(filename, &db->readHandle, READ_MODE, NULL);
	if (status != SQLITE_OK) {
		SetErrorMessage(sqlite3_errmsg(db->readHandle));
		sqlite3_close(db->writeHandle);
		sqlite3_close(db->readHandle);
		db->writeHandle = NULL;
		db->readHandle = NULL;
		return;
	}
	
	sqlite3_busy_timeout(db->writeHandle, 30000);
	sqlite3_busy_timeout(db->readHandle, 30000);
}
void OpenWorker::HandleOKCallback() {
	Nan::HandleScope scope;
    v8::Local<v8::Object> database = db->handle();
    
    db->workers -= 1;
    if (db->workers == 0) {db->Unref();}
    
	if (db->state == DB_DONE) {
		sqlite3_close(db->writeHandle);
		sqlite3_close(db->readHandle);
		db->writeHandle = NULL;
		db->readHandle = NULL;
	} else {
		db->state = DB_READY;
		v8::Local<v8::Value> args[1] = {Nan::New("open").ToLocalChecked()};
		EMIT_EVENT(database, 1, args);
	}
}
void OpenWorker::HandleErrorCallback() {
	Nan::HandleScope scope;
    v8::Local<v8::Object> database = db->handle();
    
    db->workers -= 1;
    if (db->workers == 0) {db->Unref();}
    
	if (db->state != DB_DONE) {
		db->state = DB_DONE;
		v8::Local<v8::Value> args[2] = {
			Nan::New("close").ToLocalChecked(),
			v8::Exception::Error(Nan::New<v8::String>(ErrorMessage()).ToLocalChecked())
		};
		EMIT_EVENT(database, 2, args);
	}
}





CloseWorker::CloseWorker(Database* db, bool still_connecting)
	: Nan::AsyncWorker(NULL), db(db), still_connecting(still_connecting) {}
CloseWorker::~CloseWorker() {}
void CloseWorker::Execute() {
	if (!still_connecting) {
		db->stmts.Flush(Statement::CloseStatement);
		int status1 = sqlite3_close(db->writeHandle);
		int status2 = sqlite3_close(db->readHandle);
		db->writeHandle = NULL;
		db->readHandle = NULL;
		if (status1 != SQLITE_OK) {
			SetErrorMessage(sqlite3_errmsg(db->writeHandle));
		} else if (status2 != SQLITE_OK) {
			SetErrorMessage(sqlite3_errmsg(db->readHandle));
		}
	}
}
void CloseWorker::HandleOKCallback() {
	Nan::HandleScope scope;
    v8::Local<v8::Object> database = db->handle();
    
    db->workers -= 1;
    if (db->workers == 0) {db->Unref();}
    
	v8::Local<v8::Value> args[2] = {Nan::New("close").ToLocalChecked(), Nan::Null()};
	EMIT_EVENT_ASYNC(database, 2, args);
}
void CloseWorker::HandleErrorCallback() {
	Nan::HandleScope scope;
    v8::Local<v8::Object> database = db->handle();
    
    db->workers -= 1;
    if (db->workers == 0) {db->Unref();}
    
	v8::Local<v8::Value> args[2] = {
		Nan::New("close").ToLocalChecked(),
		v8::Exception::Error(Nan::New<v8::String>(ErrorMessage()).ToLocalChecked())
	};
	EMIT_EVENT_ASYNC(database, 2, args);
}
