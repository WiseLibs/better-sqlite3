inline v8::Local<v8::String> NEW_INTERNAL_STRING_FAST(const char* data) {
	return v8::String::NewFromOneByte(v8::Isolate::GetCurrent(), reinterpret_cast<const uint8_t*>(data), v8::NewStringType::kInternalized).ToLocalChecked();
}
inline v8::Local<v8::String> StringFromLatin1(v8::Isolate* isolate, const char* data, int length) {
	return v8::String::NewFromOneByte(isolate, reinterpret_cast<const uint8_t*>(data), v8::NewStringType::kNormal, length).ToLocalChecked();
}
inline v8::Local<v8::String> StringFromUtf8(v8::Isolate* isolate, const char* data, int length) {
	return v8::String::NewFromUtf8(isolate, data, v8::NewStringType::kNormal, length).ToLocalChecked();
}
inline v8::Local<v8::String> InternalizedFromUtf8(v8::Isolate* isolate, const char* data, int length) {
	return v8::String::NewFromUtf8(isolate, data, v8::NewStringType::kInternalized, length).ToLocalChecked();
}

const sqlite3_int64 MAX_SAFE = (sqlite3_int64)9007199254740991;
const sqlite3_int64 MIN_SAFE = (sqlite3_int64)-9007199254740991;
const sqlite3_uint64 U32_in_U64 = (sqlite3_uint64)0xffffffff;

class Int64 : public node::ObjectWrap {
public:
	explicit Int64(int32_t _low, int32_t _high) : node::ObjectWrap() {
		low = _low;
		high = _high;
		full = (sqlite3_int64)((((sqlite3_uint64)((uint32_t)_high)) << 32) | (uint32_t)_low);
	}
	explicit Int64(sqlite3_int64 _full) : node::ObjectWrap() {
		low = (int32_t)((uint32_t)(((sqlite3_uint64)_full) & U32_in_U64));
		high = (int32_t)((uint32_t)(((sqlite3_uint64)_full) >> 32));
		full = _full;
	}
	static void Init(v8::Local<v8::Object> exports) {
		v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(JS_new);
		t->InstanceTemplate()->SetInternalFieldCount(1);
		t->SetClassName(NEW_INTERNAL_STRING_FAST("Int64"));
		
		Nan::SetAccessor(t->InstanceTemplate(), NEW_INTERNAL_STRING_FAST("low"), JS_low);
		Nan::SetAccessor(t->InstanceTemplate(), NEW_INTERNAL_STRING_FAST("high"), JS_high);
		Nan::SetPrototypeMethod(t, "toString", JS_toString);
		Nan::SetPrototypeMethod(t, "valueOf", JS_valueOf);
		
		constructor.Reset(exports->GetIsolate(), Nan::GetFunction(t).ToLocalChecked());
		constructorTemplate.Reset(exports->GetIsolate(), t);
		
		Nan::Set(exports, NEW_INTERNAL_STRING_FAST("Int64"), Nan::GetFunction(t).ToLocalChecked());
	}
	
	static inline v8::Local<v8::Value> NewProperInteger(sqlite3_int64 value, bool safe_integers) {
		v8::Isolate* isolate = v8::Isolate::GetCurrent();
		if (safe_integers) {
			FastConstructInt = &value;
			return v8::Local<v8::Function>::New(isolate, constructor)->NewInstance(isolate->GetCurrentContext()).ToLocalChecked();
		}
		return v8::Number::New(isolate, static_cast<double>(value));
	}
	
	static inline bool HasInstance(v8::Local<v8::Value> value) {
		v8::Isolate* isolate = v8::Isolate::GetCurrent();
		v8::Local<v8::FunctionTemplate> Int64Template = v8::Local<v8::FunctionTemplate>::New(isolate, constructorTemplate);
		return Int64Template->HasInstance(value);
	}
	
	inline sqlite3_int64 GetValue() {
		return full;
	}
	
private:
	static v8::Persistent<v8::Function> constructor;
	static v8::Persistent<v8::FunctionTemplate> constructorTemplate;
	static sqlite3_int64* FastConstructInt;
	
	sqlite3_int64 full;
	int32_t low;
	int32_t high;
	
	static NAN_METHOD(JS_new) {
		if (FastConstructInt != NULL) {
			Int64* int64 = new Int64(*FastConstructInt);
			FastConstructInt = NULL;
			int64->Wrap(info.This());
			return info.GetReturnValue().Set(info.This());
		}
		
		int32_t low;
		int32_t high;
		
		if (info.Length() < 1 || !info[0]->IsInt32()) {
			info.GetIsolate()->ThrowException(v8::Exception::TypeError(
				StringFromUtf8(info.GetIsolate(), "Expected arguemnt 1 to be a 32-bit signed integer", -1)));
			return;
		}
		low = v8::Local<v8::Int32>::Cast(info[0])->Value();
		
		if (info.Length() > 1) {
			if (!info[1]->IsInt32()) {
				info.GetIsolate()->ThrowException(v8::Exception::TypeError(
					StringFromUtf8(info.GetIsolate(), "Expected arguemnt 2 to be a 32-bit signed integer", -1)));
				return;
			}
			high = v8::Local<v8::Int32>::Cast(info[1])->Value();
		} else {
			high = 0;
		}
		
		Int64* int64 = new Int64(low, high);
		int64->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	}
	static NAN_GETTER(JS_low) {
		info.GetReturnValue().Set(v8::Int32::New(info.GetIsolate(), node::ObjectWrap::Unwrap<Int64>(info.This())->low));
	}
	static NAN_GETTER(JS_high) {
		info.GetReturnValue().Set(v8::Int32::New(info.GetIsolate(), node::ObjectWrap::Unwrap<Int64>(info.This())->high));
	}
	static NAN_METHOD(JS_toString) {
		v8::Isolate* const isolate = info.GetIsolate();
		std::string string = std::to_string(static_cast<long long>(node::ObjectWrap::Unwrap<Int64>(info.This())->full));
		info.GetReturnValue().Set(StringFromLatin1(isolate, string.c_str(), string.length()));
	}
	static NAN_METHOD(JS_valueOf) {
		sqlite3_int64 full = node::ObjectWrap::Unwrap<Int64>(info.This())->full;
		if (full <= MAX_SAFE && full >= MIN_SAFE) {
			info.GetReturnValue().Set(v8::Number::New(info.GetIsolate(), static_cast<double>(full)));
		} else {
			info.GetReturnValue().Set(v8::Number::New(info.GetIsolate(), std::numeric_limits<double>::quiet_NaN()));
		}
	}
};

sqlite3_int64* Int64::FastConstructInt = NULL;
v8::Persistent<v8::Function> Int64::constructor;
v8::Persistent<v8::FunctionTemplate> Int64::constructorTemplate;
