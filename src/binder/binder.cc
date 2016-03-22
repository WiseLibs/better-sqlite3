#include <cstdio>
#include <cstring>
#include <sqlite3.h>
#include <nan.h>
#include "binder.h"
#include "../util/strlcpy.h"

#include "next-anon-index.cc"
#include "get-array-like-length.cc"
#include "set-binding-error.cc"
#include "get-error.cc"
#include "bind-number.cc"
#include "bind-string.cc"
#include "bind-buffer.cc"
#include "bind-null.cc"
#include "bind-value.cc"
#include "bind-array.cc"
#include "bind-array-like.cc"
#include "bind-object.cc"
#include "bind.cc"

Binder::Binder(sqlite3_stmt* handle)
	: handle(handle)
	, param_count(sqlite3_bind_parameter_count(handle))
	, anon_index(0)
	, error(NULL)
	, error_extra(NULL)
	, error_full(NULL) {}

Binder::~Binder() {
	delete[] error_extra;
	delete[] error_full;
}

void Binder::Unbind() {
	sqlite3_clear_bindings(handle);
}
