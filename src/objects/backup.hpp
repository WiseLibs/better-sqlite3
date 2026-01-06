class Backup : public node::ObjectWrap {
public:

	~Backup();

	// Whenever this is used, db->RemoveBackup must be invoked beforehand.
	void CloseHandles();

	// Used to support ordered containers.
	static inline bool Compare(Backup const * const a, Backup const * const b) {
		return a->id < b->id;
	}

	static INIT(Init);

private:

	explicit Backup(
		Database* db,
		sqlite3* dest_handle,
		sqlite3_backup* backup_handle,
		sqlite3_uint64 id,
		bool unlink
	);

	static NODE_METHOD(JS_new);
	static NODE_METHOD(JS_transfer);
	static NODE_METHOD(JS_close);

	Database* const db;
	sqlite3* const dest_handle;
	sqlite3_backup* const backup_handle;
	const sqlite3_uint64 id;
	bool alive;
	bool unlink;
};
