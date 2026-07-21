const napi_type_tag Backup::TYPE_TAG = RandomTypeTag();

Backup::Backup(const Napi::CallbackInfo& info) :
	Napi::ObjectWrap<Backup>(info),
	db(NULL),
	dest_handle(NULL),
	backup_handle(NULL),
	id(0),
	alive(false),
	unlink(false) {
	napi_status status = napi_type_tag_object(info.Env(), info.This(), &TYPE_TAG);
	assert(status == napi_ok); ((void)status);
	JS_new(info);
}

Backup::~Backup() {
	if (alive) db->RemoveBackup(this);
	CloseHandles();
}

// Whenever this is used, db->RemoveBackup must be invoked beforehand.
void Backup::CloseHandles() {
	if (alive) {
		alive = false;
		std::string filename(sqlite3_db_filename(dest_handle, "main"));
		sqlite3_backup_finish(backup_handle);
		int status = sqlite3_close(dest_handle);
		assert(status == SQLITE_OK); ((void)status);
		if (unlink) remove(filename.c_str());
	}
}

INIT(Backup::Init) {
	return DefineClass(env, "Backup", {
		PrototypeMethod<Backup, &Backup::JS_transfer>("transfer", addon),
		PrototypeMethod<Backup, &Backup::JS_close>("close", addon),
	}, addon);
}

NODE_METHOD(Backup::JS_new) {
	UseAddon;
	if (!addon->privileged_info) return ThrowTypeError(info.Env(), "Disabled constructor");
	assert(info.IsConstructCall());
	const Napi::CallbackInfo& pinfo = *addon->privileged_info;
	Database* db = ::Unwrap<Database>(pinfo.This());
	REQUIRE_DATABASE_OPEN(db->GetState());
	REQUIRE_DATABASE_NOT_BUSY(db->GetState());

	Napi::Object database = pinfo[0].As<Napi::Object>();
	Napi::String attachedName = pinfo[1].As<Napi::String>();
	Napi::String destFile = pinfo[2].As<Napi::String>();
	bool unlink = pinfo[3].As<Napi::Boolean>().Value();

	UseIsolate;
	sqlite3* dest_handle;
	std::string dest_file = destFile.Utf8Value();
	std::string attached_name = attachedName.Utf8Value();
	int mask = (SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

	if (sqlite3_open_v2(dest_file.c_str(), &dest_handle, mask, NULL) != SQLITE_OK) {
		Database::ThrowSqliteError(env, addon, dest_handle);
		int status = sqlite3_close(dest_handle);
		assert(status == SQLITE_OK); ((void)status);
		return env.Undefined();
	}

	sqlite3_extended_result_codes(dest_handle, 1);
	sqlite3_limit(dest_handle, SQLITE_LIMIT_LENGTH, INT_MAX);
	sqlite3_backup* backup_handle = sqlite3_backup_init(dest_handle, "main", db->GetHandle(), attached_name.c_str());
	if (backup_handle == NULL) {
		Database::ThrowSqliteError(env, addon, dest_handle);
		int status = sqlite3_close(dest_handle);
		assert(status == SQLITE_OK); ((void)status);
		return env.Undefined();
	}

	this->db = db;
	this->dest_handle = dest_handle;
	this->backup_handle = backup_handle;
	this->id = addon->NextId();
	this->unlink = unlink;
	this->alive = true;
	db->AddBackup(this);

	SetFrozen(env, info.This().As<Napi::Object>(), addon->cs.database, database);

	return info.This();
}

NODE_METHOD(Backup::JS_transfer) {
	Backup* backup = ::Unwrap<Backup>(info.This());
	REQUIRE_ARGUMENT_INT32(first, int pages);
	REQUIRE_DATABASE_OPEN(backup->db->GetState());
	assert(backup->db->GetState()->busy == false);
	assert(backup->alive == true);

	UseIsolate;
	sqlite3_backup* backup_handle = backup->backup_handle;
	int status = sqlite3_backup_step(backup_handle, pages) & 0xff;

	Addon* addon = backup->db->GetAddon();
	if (status == SQLITE_OK || status == SQLITE_DONE || status == SQLITE_BUSY) {
		int total_pages = sqlite3_backup_pagecount(backup_handle);
		int remaining_pages = sqlite3_backup_remaining(backup_handle);
		Napi::Object result = Napi::Object::New(env);
		result.Set(addon->cs.totalPages.Value(), Napi::Number::New(env, total_pages));
		result.Set(addon->cs.remainingPages.Value(), Napi::Number::New(env, remaining_pages));
		if (status == SQLITE_DONE) backup->unlink = false;
		return result;
	} else {
		Database::ThrowSqliteError(env, addon, sqlite3_errstr(status), status);
		return env.Undefined();
	}
}

NODE_METHOD(Backup::JS_close) {
	Backup* backup = ::Unwrap<Backup>(info.This());
	assert(backup->db->GetState()->busy == false);
	if (backup->alive) backup->db->RemoveBackup(backup);
	backup->CloseHandles();
	return info.This();
}
