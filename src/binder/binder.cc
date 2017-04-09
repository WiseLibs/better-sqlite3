#include <cstdio>
#include <cstring>
#include <stdint.h>
#include <sqlite3.h>
#include <nan.h>
#include "binder.h"
#include "../objects/query.h"
#include "../objects/int64/int64.h"
#include "../util/strlcpy.h"
#include "../util/macros.h"
#include "../util/data.h"

#include "next-anon-index.cc"
#include "is-plain-object.cc"
#include "get-error.cc"
#include "bind-value.cc"
#include "bind-array.cc"
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
