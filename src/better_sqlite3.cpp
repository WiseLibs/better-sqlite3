// Main implementation file
#include "better_sqlite3.hpp"
#include "better_sqlite3_impl.hpp"

// Addon implementation
void Addon::Cleanup(void *ptr) {
  Addon *addon = static_cast<Addon *>(ptr);
  for (Database *db : addon->dbs)
    db->CloseHandles();
  addon->dbs.clear();
  delete addon;
}

Addon::Addon(v8::Isolate *isolate)
    : privileged_info(NULL), next_id(0), cs(isolate) {}

void Addon::JS_setErrorConstructor(
    v8::FunctionCallbackInfo<v8::Value> const &info) {
  v8::Local<v8::Function> e = v8::Local<v8::Function>::Cast(info[0]);
  assert(info[0]->IsFunction());
  Addon *addon =
      static_cast<Addon *>(v8::Local<v8::External>::Cast(info.Data())->Value());
  addon->SqliteError.Reset(info.GetIsolate(), e);
}

NODE_MODULE_INIT(/* exports, context */) {
  v8::Isolate *isolate = context->GetIsolate();
  v8::HandleScope scope(isolate);

  // Initialize addon instance.
  Addon *addon = new Addon(isolate);
  v8::Local<v8::External> data = v8::External::New(isolate, addon);
  node::AddEnvironmentCleanupHook(isolate, Addon::Cleanup, addon);

  // Create and export native-backed classes and functions.
  exports
      ->Set(context, InternalizedFromLatin1(isolate, "Database"),
            Database::Init(isolate, data))
      .FromJust();
  exports
      ->Set(context, InternalizedFromLatin1(isolate, "Statement"),
            Statement::Init(isolate, data))
      .FromJust();
  exports
      ->Set(context, InternalizedFromLatin1(isolate, "StatementIterator"),
            StatementIterator::Init(isolate, data))
      .FromJust();
  exports
      ->Set(context, InternalizedFromLatin1(isolate, "Backup"),
            Backup::Init(isolate, data))
      .FromJust();
  exports
      ->Set(context, InternalizedFromLatin1(isolate, "setErrorConstructor"),
            v8::FunctionTemplate::New(isolate, Addon::JS_setErrorConstructor,
                                      data)
                ->GetFunction(context)
                .ToLocalChecked())
      .FromJust();

  // Store addon instance data.
  addon->Statement.Reset(
      isolate,
      exports->Get(context, InternalizedFromLatin1(isolate, "Statement"))
          .ToLocalChecked()
          .As<v8::Function>());
  addon->StatementIterator.Reset(
      isolate,
      exports
          ->Get(context, InternalizedFromLatin1(isolate, "StatementIterator"))
          .ToLocalChecked()
          .As<v8::Function>());
  addon->Backup.Reset(
      isolate, exports->Get(context, InternalizedFromLatin1(isolate, "Backup"))
                   .ToLocalChecked()
                   .As<v8::Function>());
}
