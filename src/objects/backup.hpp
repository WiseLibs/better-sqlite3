class Backup : public Napi::ObjectWrap<Backup> {
public:

	explicit Backup(const Napi::CallbackInfo& info);
	~Backup();

	// Whenever this is used, db->RemoveBackup must be invoked beforehand.
	void CloseHandles();

	// Used to support ordered containers.
	static inline bool Compare(Backup const * const a, Backup const * const b) {
		return a->id < b->id;
	}

	// Identifies objects that are backed by this class (see IsInstanceOf).
	static const napi_type_tag TYPE_TAG;

	static INIT(Init);

private:

	NODE_METHOD(JS_new);
	static NODE_METHOD(JS_transfer);
	static NODE_METHOD(JS_close);

	Database* db;
	sqlite3* dest_handle;
	sqlite3_backup* backup_handle;
	sqlite3_uint64 id;
	bool alive;
	bool unlink;
};
