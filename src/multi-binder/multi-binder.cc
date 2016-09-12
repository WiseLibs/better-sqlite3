#include <sqlite3.h>
#include <nan.h>
#include "multi-binder.h"
#include "../binder/binder.h"
#include "../objects/query.h"
#include "../util/strlcpy.h"
#include "../util/macros.h"

#include "next-anon-index.cc"
#include "bind-object.cc"
#include "bind.cc"

MultiBinder::MultiBinder(sqlite3_stmt** handles, unsigned int handle_count, sqlite3_destructor_type bind_type)
	: Binder(handles[0], bind_type)
	, handles(handles)
	, handle_count(handle_count)
	, handle_index(0)
	, param_count_sum(param_count) {}
