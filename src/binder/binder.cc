#include <cstdio>
#include <cstring>
#include <sqlite3.h>
#include <nan.h>
#include "binder.h"
#include "../util/strlcpy.h"
#include "../util/macros.h"

#include "next-anon-index.cc"
#include "get-array-like-length.cc"
#include "is-plain-object.cc"
#include "get-named-parameter-index.cc"
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
#include "bind-multi.cc"

Binder::Binder(sqlite3_stmt* handle)
	: handles(NULL)
	, handle_count(0)
	, handle(handle)
	, param_count(sqlite3_bind_parameter_count(handle))
	, anon_index(0)
	, error(NULL)
	, error_extra(NULL)
	, error_full(NULL) {}

Binder::Binder(sqlite3_stmt** handles, unsigned int handle_count)
	: handles(handles)
	, handle_count(handle_count)
	, handle(NULL)
	, param_count(CountParams())
	, anon_index(0)
	, error(NULL)
	, error_extra(NULL)
	, error_full(NULL) {}

Binder::~Binder() {
	delete[] error_extra;
	delete[] error_full;
}
