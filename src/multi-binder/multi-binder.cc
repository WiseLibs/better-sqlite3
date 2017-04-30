#include <sqlite3.h>
#include <nan.h>
#include "multi-binder.h"
#include "../binder/binder.h"
#include "../objects/query.h"
#include "../util/macros.h"
#include "../util/bind-map.h"

#include "next-anon-index.cc"
#include "bind-object.cc"

MultiBinder::MultiBinder(sqlite3_stmt** handles, unsigned int handle_count)
	: Binder(handles[0])
	, handles(handles)
	, handle_count(handle_count)
	, handle_index(0)
	, param_count_sum(param_count) {}

void MultiBinder::Bind(Nan::NAN_METHOD_ARGS_TYPE info, int len, Query* query) {
	int result = BindArgs(info, len, query);
	int count = result >> 1;
	if (!error) {
		while (handle_index + 1 < handle_count) {
			param_count_sum += sqlite3_bind_parameter_count(handles[++handle_index]);
		}
		if (count != param_count_sum) {
			if (count < param_count_sum) {
				if (!(result & 1) && query->GetBindMap()->length) {
					error = COPY("Missing named parameters.");
				} else {
					error = COPY("Too few parameter values were provided.");
				}
			} else {
				error = COPY("Too many parameter values were provided.");
			}
		}
	}
}
