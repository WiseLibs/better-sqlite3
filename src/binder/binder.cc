#include <sqlite3.h>
#include <nan.h>
#include "binder.h"

#include "advance-anon-index.cc"
#include "set-binding-error.cc"
#include "bind-number.cc"
#include "bind-string.cc"
#include "bind-buffer.cc"
#include "bind-null.cc"
#include "bind-value.cc"

Binder::Binder(sqlite3_stmt* handle)
	: handle(handle)
	, param_count(sqlite3_bind_parameter_count(handle))
	, bound_args(0)
	, anon_index(1)
	, error(NULL) {}

