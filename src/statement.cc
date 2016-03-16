#include <cstdio>
#include <cstring>
#include <sqlite3.h>
#include <nan.h>
#include "macros.h"
#include "util/handle_manager.h"
#include "util/list.h"
#include "data.h"
#include "database.h"
#include "statement.h"

template <class T>
class StatementWorker : public T {
	public:
		StatementWorker(Statement*, sqlite3_stmt*, int);
		void HandleErrorCallback();
	protected:
		void Resolve(v8::Local<v8::Value>);
		void Reject(v8::Local<v8::Value>);
		sqlite3_stmt* handle;
		sqlite3* db_handle;
	private:
		Statement* stmt;
		int handle_index;
		void FinishRequest();
};

class RunWorker : public StatementWorker<Nan::AsyncWorker> {
	public:
		RunWorker(Statement*, sqlite3_stmt*, int);
		void Execute();
		void HandleOKCallback();
	private:
		int changes;
		sqlite3_int64 id;
};

class GetWorker : public StatementWorker<Nan::AsyncWorker> {
	public:
		GetWorker(Statement*, sqlite3_stmt*, int, int);
		void Execute();
		void HandleOKCallback();
	private:
		const int pluck_column;
		Data::Row row;
};

class AllWorker : public StatementWorker<Nan::AsyncWorker> {
	public:
		AllWorker(Statement*, sqlite3_stmt*, int, int);
		void Execute();
		void HandleOKCallback();
	private:
		const int pluck_column;
		int column_end;
		int row_count;
		List<Data::Row> rows;
};

class EachWorker : public StatementWorker<Nan::AsyncProgressWorker> {
	public:
		EachWorker(Statement*, sqlite3_stmt*, int, int, Nan::Callback*);
		~EachWorker();
		void Execute(const Nan::AsyncProgressWorker::ExecutionProgress&);
		void HandleProgressCallback(const char*, size_t);
		void HandleOKCallback();
	private:
		sqlite3_mutex* data_mutex;
		sqlite3_mutex* handle_mutex;
		const int pluck_column;
		int column_end;
		bool cached_names;
		List<Data::Row> rows;
};





Statement::Statement() : Nan::ObjectWrap(),
	db(NULL),
	config_locked(false),
	requests(0),
	pluck_column(-1) {}
Statement::~Statement() {
	if (handles.Close() && db != NULL) {
		db->stmts.Remove(this);
	}
}
void Statement::Init() {
	Nan::HandleScope scope;
	
	v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(New);
	t->InstanceTemplate()->SetInternalFieldCount(1);
	t->SetClassName(Nan::New("Statement").ToLocalChecked());
	
	Nan::SetPrototypeMethod(t, "cache", Cache);
	Nan::SetPrototypeMethod(t, "pluck", Pluck);
	Nan::SetPrototypeMethod(t, "run", Run);
	Nan::SetPrototypeMethod(t, "get", Get);
	Nan::SetPrototypeMethod(t, "all", All);
	Nan::SetPrototypeMethod(t, "each", Each);
	Nan::SetPrototypeMethod(t, "forEach", Each);
	Nan::SetAccessor(t->InstanceTemplate(), Nan::New("readonly").ToLocalChecked(), ReadonlyGetter);
	
	constructor.Reset(Nan::GetFunction(t).ToLocalChecked());
}
CONSTRUCTOR(Statement::constructor);
NAN_METHOD(Statement::New) {
	if (!CONSTRUCTING_PRIVILEGES) {
		return Nan::ThrowTypeError("Statements can only be constructed by the db.prepare() method.");
	}
	Statement* statement = new Statement();
	statement->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
}
NAN_GETTER(Statement::ReadonlyGetter) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	info.GetReturnValue().Set(stmt->readonly == true);
}
NAN_METHOD(Statement::Cache) {
	REQUIRE_ARGUMENT_NUMBER(0, number);
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->config_locked) {
		return Nan::ThrowError("A statement's cache cannot be altered after it has been executed.");
	}
	if (stmt->db->state != DB_READY) {
		return Nan::ThrowError("The associated database connection is closed.");
	}
	
	double numberValue = number->Value();
	if (!IS_POSITIVE_INTEGER(numberValue)) {
		return Nan::ThrowError("Argument 0 must be a positive, finite integer.");
	}
	if (numberValue < 1) {
		numberValue = 1;
	}
	
	int len = (int)numberValue;
	HandleManager handles = HandleManager(stmt, len);
	
	if (handles.Fill([&stmt] {return stmt->NewHandle();})) {
		return Nan::ThrowError("SQLite failed to create a prepared statement.");
	}
	
	stmt->handles = handles;
	handles.owner = false;
	
	info.GetReturnValue().Set(info.This());
}
NAN_METHOD(Statement::Pluck) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (!stmt->readonly) {
		return Nan::ThrowTypeError("The pluck() method can only be used by read-only statements.");
	}
	REQUIRE_ARGUMENTS(1);
	if (stmt->config_locked) {
		return Nan::ThrowError("A statement's pluck setting cannot be altered after it has been executed.");
	}
	if (stmt->db->state != DB_READY) {
		return Nan::ThrowError("The associated database connection is closed.");
	}
	v8::Local<v8::Value> arg = info[0];
	
	if (arg->IsFalse()) {
		stmt->pluck_column = -1;
	} else {
		sqlite3_stmt* handle = stmt->handles.First();
		int column_count = sqlite3_column_count(handle);
		
		if (arg->IsTrue()) {
			if (column_count < 1) {return Nan::ThrowTypeError("This statement does not return any result columns.");}
			stmt->pluck_column = 0;
		} else if (arg->IsNumber()) {
			double num = v8::Local<v8::Number>::Cast(arg)->Value();
			if (!IS_POSITIVE_INTEGER(num)) {
				return Nan::ThrowTypeError("Column numbers must be finite, positive integers.");
			}
			if (column_count <= num) {
				const char format[] = "This statement only returns %d result columns.";
				char buffer[sizeof(format) + 64];
				int len = sprintf(buffer, format, column_count);
				return Nan::ThrowTypeError(Nan::New<v8::String>(buffer, len).ToLocalChecked());
			}
			stmt->pluck_column = (int)num;
		} else if (arg->IsString()) {
			Nan::Utf8String utf8(v8::Local<v8::String>::Cast(arg));
			const char* str = *utf8;
			int i = 0;
			for (; i<column_count; i++) {
				const char* name = sqlite3_column_name(handle, i);
				if (strcmp(name, str) == 0) {
					stmt->pluck_column = i;
					break;
				}
			}
			if (i == column_count) {
				return Nan::ThrowTypeError("The specified column name is not returned by this statement.");
			}
		} else {
			return Nan::ThrowTypeError("You must specify true, false, a column number, or a column name.");
		}
	}
	info.GetReturnValue().Set(info.This());
}
NAN_METHOD(Statement::Run) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (stmt->readonly) {
		return Nan::ThrowTypeError("This statement is read-only. Use get(), all(), or each() instead.");
	}
	STATEMENT_START(stmt);
	RunWorker* worker = new RunWorker(stmt, _handle, _i);
	STATEMENT_END(stmt, worker);
}
NAN_METHOD(Statement::Get) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (!stmt->readonly) {
		return Nan::ThrowTypeError("This statement is not read-only. Use run() instead.");
	}
	STATEMENT_START(stmt);
	GetWorker* worker = new GetWorker(stmt, _handle, _i, stmt->pluck_column);
	STATEMENT_END(stmt, worker);
}
NAN_METHOD(Statement::All) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (!stmt->readonly) {
		return Nan::ThrowTypeError("This statement is not read-only. Use run() instead.");
	}
	STATEMENT_START(stmt);
	AllWorker* worker = new AllWorker(stmt, _handle, _i, stmt->pluck_column);
	STATEMENT_END(stmt, worker);
}
NAN_METHOD(Statement::Each) {
	Statement* stmt = Nan::ObjectWrap::Unwrap<Statement>(info.This());
	if (!stmt->readonly) {
		return Nan::ThrowTypeError("This statement is not read-only. Use run() instead.");
	}
	REQUIRE_ARGUMENT_FUNCTION(0, func);
	STATEMENT_START(stmt);
	EachWorker* worker = new EachWorker(stmt, _handle, _i, stmt->pluck_column, new Nan::Callback(func));
	STATEMENT_END(stmt, worker);
}
sqlite3_stmt* Statement::NewHandle() {
	sqlite3_stmt* handle;
	sqlite3_prepare_v2(db_handle, source.data, source.length, &handle, NULL);
	return handle;
}





template <class T>
StatementWorker<T>::StatementWorker(Statement* stmt, sqlite3_stmt* handle, int handle_index)
	: T(NULL), handle(handle), db_handle(stmt->db_handle), stmt(stmt), handle_index(handle_index) {}
template <class T>
void StatementWorker<T>::Resolve(v8::Local<v8::Value> value) {
	FinishRequest();
	v8::Local<v8::Promise::Resolver> resolver = v8::Local<v8::Promise::Resolver>::Cast(T::GetFromPersistent((uint32_t)0));
	resolver->Resolve(Nan::GetCurrentContext(), value);
}
template <class T>
void StatementWorker<T>::Reject(v8::Local<v8::Value> value) {
	FinishRequest();
	v8::Local<v8::Promise::Resolver> resolver = v8::Local<v8::Promise::Resolver>::Cast(T::GetFromPersistent((uint32_t)0));
	resolver->Reject(Nan::GetCurrentContext(), value);
}
template <class T>
void StatementWorker<T>::FinishRequest() {
	stmt->requests -= 1;
	stmt->db->requests -= 1;
	stmt->handles.Release(handle_index, handle);
	if (stmt->requests == 0) {
		stmt->Unref();
		if (stmt->db->state == DB_DONE && stmt->db->requests == 0) {
			stmt->db->ActuallyClose();
		}
	}
}
template <class T>
void StatementWorker<T>::HandleErrorCallback() {
	Nan::HandleScope scope;
	CONCAT2(message, "SQLite: ", T::ErrorMessage());
	Reject(Nan::Error(message));
}





RunWorker::RunWorker(Statement* stmt, sqlite3_stmt* handle, int handle_index)
	: StatementWorker<Nan::AsyncWorker>(stmt, handle, handle_index) {}
void RunWorker::Execute() {
	LOCK_DB(db_handle);
	int status = sqlite3_step(handle);
	if (status == SQLITE_DONE || status == SQLITE_ROW) {
		changes = sqlite3_changes(db_handle);
		id = sqlite3_last_insert_rowid(db_handle);
	} else {
		SetErrorMessage(sqlite3_errmsg(db_handle));
	}
	UNLOCK_DB(db_handle);
}
void RunWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	
	v8::Local<v8::Object> obj = Nan::New<v8::Object>();
	Nan::ForceSet(obj, Nan::New("changes").ToLocalChecked(), Nan::New<v8::Number>((double)changes));
	Nan::ForceSet(obj, Nan::New("id").ToLocalChecked(), Nan::New<v8::Number>((double)id));
	
	Resolve(obj);
}





GetWorker::GetWorker(Statement* stmt, sqlite3_stmt* handle, int handle_index, int pluck_column)
	: StatementWorker<Nan::AsyncWorker>(stmt, handle, handle_index),
	pluck_column(pluck_column) {}
void GetWorker::Execute() {
	LOCK_DB(db_handle);
	int status = sqlite3_step(handle);
	GET_ROW_RANGE(start, end);
	if (status == SQLITE_ROW) {
		Data::Row::Fill(&row, handle, start, end);
	} else if (status != SQLITE_DONE) {
		SetErrorMessage(sqlite3_errmsg(db_handle));
	}
	UNLOCK_DB(db_handle);
}
void GetWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	
	if (!row.column_count) {
		return Resolve(Nan::Undefined());
	}
	
	if (pluck_column >= 0) {
		return Resolve(row.values[0]->ToJS());
	}
	
	v8::Local<v8::Object> obj = Nan::New<v8::Object>();
	for (int i=0; i<row.column_count; i++) {
		Nan::ForceSet(obj,
			Nan::New(sqlite3_column_name(handle, i)).ToLocalChecked(),
			row.values[i]->ToJS());
	}
	
	Resolve(obj);
}





AllWorker::AllWorker(Statement* stmt, sqlite3_stmt* handle, int handle_index, int pluck_column)
	: StatementWorker<Nan::AsyncWorker>(stmt, handle, handle_index),
	pluck_column(pluck_column), row_count(0) {}
void AllWorker::Execute() {
	LOCK_DB(db_handle);
	int status = sqlite3_step(handle);
	GET_ROW_RANGE(start, end);
	column_end = end;
	while (status == SQLITE_ROW) {
		row_count++;
		Data::Row* row = new Data::Row();
		rows.Add(row);
		Data::Row::Fill(row, handle, start, end);
		status = sqlite3_step(handle);
	}
	if (status != SQLITE_DONE) {
		SetErrorMessage(sqlite3_errmsg(db_handle));
	}
	UNLOCK_DB(db_handle);
}
void AllWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	v8::Local<v8::Array> arr = Nan::New<v8::Array>(row_count);
	
	if (row_count > 0) {
		if (pluck_column >= 0) {
			rows.Flush([&arr] (Data::Row* row, int i) {
				Nan::Set(arr, i, row->values[0]->ToJS());
			});
		} else {
			v8::Local<v8::Array> columnNames = Nan::New<v8::Array>(column_end);
			for (int j=0; j<column_end; j++) {
				Nan::Set(columnNames, j, Nan::New(sqlite3_column_name(handle, j)).ToLocalChecked());
			}
			rows.Flush([&arr, &columnNames] (Data::Row* row, int i) {
				v8::Local<v8::Object> obj = Nan::New<v8::Object>();
				for (int j=0; j<row->column_count; j++) {
					Nan::ForceSet(obj, Nan::Get(columnNames, j).ToLocalChecked(), row->values[j]->ToJS());
				}
				Nan::Set(arr, i, obj);
			});
		}
	}
	
	Resolve(arr);
}





EachWorker::EachWorker(Statement* stmt, sqlite3_stmt* handle, int handle_index, int pluck_column, Nan::Callback* cb)
	: StatementWorker<Nan::AsyncProgressWorker>(stmt, handle, handle_index),
	data_mutex(NULL), handle_mutex(NULL), pluck_column(pluck_column), cached_names(false) {callback = cb;}
EachWorker::~EachWorker() {
	sqlite3_mutex_free(data_mutex);
	sqlite3_mutex_free(handle_mutex);
}
void EachWorker::Execute(const Nan::AsyncProgressWorker::ExecutionProgress &progress) {
	LOCK_DB(db_handle);
	data_mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
	if (data_mutex == NULL) {
		UNLOCK_DB(db_handle);
		return SetErrorMessage("Out of memory.");
	}
	handle_mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
	if (handle_mutex == NULL) {
		UNLOCK_DB(db_handle);
		return SetErrorMessage("Out of memory.");
	}
	
	int status = sqlite3_step(handle);
	GET_ROW_RANGE(start, end);
	column_end = end;
	
	while (status == SQLITE_ROW) {
		Data::Row* row = new Data::Row();
		
		sqlite3_mutex_enter(data_mutex);
		rows.Add(row);
		Data::Row::Fill(row, handle, start, end);
		sqlite3_mutex_leave(data_mutex);
		
		progress.Send("", 1);
		
		sqlite3_mutex_enter(handle_mutex);
		status = sqlite3_step(handle);
		sqlite3_mutex_leave(handle_mutex);
	}
	
	if (status != SQLITE_DONE) {
		SetErrorMessage(sqlite3_errmsg(db_handle));
	}
	
	UNLOCK_DB(db_handle);
}
void EachWorker::HandleProgressCallback(const char* not_used1, size_t not_used2) {
	Nan::HandleScope scope;
	if (pluck_column >= 0) {
		
		sqlite3_mutex_enter(data_mutex);
		rows.Flush([this] (Data::Row* row, int j) {
			v8::Local<v8::Value> args[1] = {row->values[0]->ToJS()};
			
			sqlite3_mutex_leave(data_mutex);
			callback->Call(1, args);
			sqlite3_mutex_enter(data_mutex);
			
		});
		sqlite3_mutex_leave(data_mutex);
		
	} else {
		v8::Local<v8::Array> columnNames;
		if (cached_names) {
			columnNames = v8::Local<v8::Array>::Cast(GetFromPersistent((uint32_t)1));
		} else {
			cached_names = true;
			columnNames = Nan::New<v8::Array>(column_end);
			
			sqlite3_mutex_enter(handle_mutex);
			for (int i=0; i<column_end; i++) {
				Nan::Set(columnNames, i, Nan::New(sqlite3_column_name(handle, i)).ToLocalChecked());
			}
			sqlite3_mutex_leave(handle_mutex);
			
			SaveToPersistent((uint32_t)1, columnNames);
		}
		
		sqlite3_mutex_enter(data_mutex);
		rows.Flush([this, &columnNames] (Data::Row* row, int j) {
			v8::Local<v8::Object> obj = Nan::New<v8::Object>();
			for (int i=0; i<row->column_count; i++) {
				Nan::ForceSet(obj, Nan::Get(columnNames, i).ToLocalChecked(), row->values[i]->ToJS());
			}
			
			sqlite3_mutex_leave(data_mutex);
			v8::Local<v8::Value> args[1] = {obj};
			callback->Call(1, args);
			sqlite3_mutex_enter(data_mutex);
			
		});
		sqlite3_mutex_leave(data_mutex);
	}
}
void EachWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	HandleProgressCallback(NULL, 0);
	Resolve(Nan::Undefined());
}
