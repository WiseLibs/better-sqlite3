#include <sqlite3.h>
#include <nan.h>
#include "checkpoint.h"
#include "../../objects/database/database.h"
#include "../../util/macros.h"

CheckpointWorker::CheckpointWorker(Database* db, bool force, Nan::Callback* cb) : Nan::AsyncWorker(cb),
	db(db),
	force(force) {}
void CheckpointWorker::Execute() {
	sqlite3* db_handle = db->write_handle;
	LOCK_DB(db_handle);
	
	int total_frames;
	int checkpointed_frames;
	int status = sqlite3_wal_checkpoint_v2(
		db_handle,
		"main",
		force ? SQLITE_CHECKPOINT_RESTART : SQLITE_CHECKPOINT_PASSIVE,
		&total_frames,
		&checkpointed_frames
	);
	
	if (status == SQLITE_OK) {
		if (checkpointed_frames < 0 || total_frames < 0) {
			fraction_checkpointed = 0;
		} else if (total_frames == 0) {
			fraction_checkpointed = 1;
		} else {
			fraction_checkpointed = (double)checkpointed_frames / (double)total_frames;
		}
	} else {
		SetErrorMessage(sqlite3_errmsg(db_handle));
	}
	
	UNLOCK_DB(db_handle);
}
void CheckpointWorker::HandleOKCallback() {
	Nan::HandleScope scope;
	FinishRequest();
	
	v8::Local<v8::Value> args[2] = {
		Nan::Null(),
		Nan::New<v8::Number>(fraction_checkpointed)
	};
	Nan::AsyncWorker::callback->Call(2, args);
}
void CheckpointWorker::HandleErrorCallback() {
	Nan::HandleScope scope;
	FinishRequest();
	
	CONCAT2(message, "SQLite: ", Nan::AsyncWorker::ErrorMessage());
	v8::Local<v8::Value> args[1] = {Nan::Error(message)};
	Nan::AsyncWorker::callback->Call(1, args);
}
void CheckpointWorker::FinishRequest() {
	if (--db->workers == 0) {
		db->Unref();
	}
	if (--db->checkpoints == 0 && db->state == DB_DONE) {
		db->MaybeClose();
	}
}
