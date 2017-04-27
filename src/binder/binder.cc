#include <sqlite3.h>
#include <nan.h>
#include "binder.h"
#include "../objects/query.h"
#include "../util/macros.h"
#include "../util/data.h"

#include "is-plain-object.cc"
#include "next-anon-index.cc"
#include "bind-value.cc"
#include "bind-array.cc"
#include "bind-object.cc"
#include "bind-args.cc"

Binder::Binder(sqlite3_stmt* handle)
	: error(NULL)
	, handle(handle)
	, param_count(sqlite3_bind_parameter_count(handle))
	, anon_index(0) {}

Binder::~Binder() {
	delete[] error;
}

void Binder::Bind(Nan::NAN_METHOD_ARGS_TYPE info, int len, Query* query) {
  int count = BindArgs(info, len, query);
  if (!error && count != param_count) {
    if (count < param_count) {
      error = COPY("Too few parameter values were provided.");
    } else {
      error = COPY("Too many parameter values were provided.");
    }
  }
}
