// .run(Function callback) -> this

NAN_METHOD(Transaction::Run) {
	Transaction* trans = Nan::ObjectWrap::Unwrap<Transaction>(info.This());
	if (trans->busy) {
		return Nan::ThrowTypeError("This transaction is mid-execution. You must wait for it to finish.");
	}
	REQUIRE_LAST_ARGUMENT_FUNCTION(func_index, func);
	if (trans->db->state != DB_READY) {
		return Nan::ThrowError("The associated database connection is closed.");
	}
	if (!trans->config_locked) {
		trans->config_locked = true;
	}
	
	// Bind parameters.
	if (!trans->bound) {
		TRANSACTION_BIND(trans, info, func_index);
	} else if (func_index > 0) {
		return Nan::ThrowTypeError("This transaction already has bound parameters.");
	}
	
	TransactionWorker* worker = new TransactionWorker(trans, new Nan::Callback(func));
	
	// Queue worker.
	trans->busy = true;
	trans->db->requests += 1;
	trans->Ref();
	Nan::AsyncQueueWorker(worker);
	
	info.GetReturnValue().Set(info.This());
}
