// Returns whether the given object is a plain object.

bool Binder::IsPlainObject(v8::Local<v8::Object> obj) {
	v8::Local<v8::Value> proto = obj->GetPrototype();
	v8::Local<v8::Value> baseProto = Nan::New<v8::Object>()->GetPrototype();
	return proto->StrictEquals(baseProto) || proto->StrictEquals(Nan::Null());
}
