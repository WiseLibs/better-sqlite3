#ifndef BETTER_SQLITE3_WORKER_QUERY_H
#define BETTER_SQLITE3_WORKER_QUERY_H

#include <sqlite3.h>
#include <nan.h>
#include "../objects/database/database.h"
#include "../util/macros.h"

template <class OBJECT, class ASYNC>
class QueryWorker : public ASYNC {
	public:
		QueryWorker(OBJECT* obj, Nan::Callback* cb) : ASYNC(cb)
		, obj(obj) {}
		
		void HandleErrorCallback() {
			Nan::HandleScope scope;
			CONCAT2(message, "SQLite: ", ASYNC::ErrorMessage());
			Reject(Nan::Error(message));
		}
		
		inline v8::Local<v8::Object> GetPersistentObject() {
			return Nan::New(ASYNC::persistentHandle);
		}
		
	protected:
		void Resolve(v8::Local<v8::Value> value) {
			FinishRequest();
			v8::Local<v8::Value> args[2] = {Nan::Null(), value};
			ASYNC::callback->Call(2, args);
		}
		void Reject(v8::Local<v8::Value> value) {
			FinishRequest();
			v8::Local<v8::Value> args[1] = {value};
			ASYNC::callback->Call(1, args);
		}
		
		OBJECT* const obj;
		
	private:
		void FinishRequest() {
			obj->state &= ~BUSY;
			obj->Unref();
			if (!(obj->state & BOUND)) {
				obj->ClearBindings();
			}
			if (obj->db->state == DB_DONE) {
				obj->CloseHandles();
				obj->EraseFromSet();
				obj->db->MaybeClose();
			}
		}
};

#endif