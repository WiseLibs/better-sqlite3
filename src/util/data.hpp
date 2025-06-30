#ifndef BETTER_SQLITE3_UTIL_DATA_HPP
#define BETTER_SQLITE3_UTIL_DATA_HPP

#include "../better_sqlite3_deps.hpp"

// Forward declarations
class DataConverter;

namespace Data {
// Mode constants for row retrieval
static const char FLAT = 0;
static const char PLUCK = 1;
static const char EXPAND = 2;
static const char RAW = 3;
v8::Local<v8::Value> GetValueJS(v8::Isolate *isolate, sqlite3_stmt *handle,
                                int column, bool safe_ints);
} // namespace Data
namespace Data {
v8::Local<v8::Value> GetValueJS(v8::Isolate *isolate, sqlite3_value *value,
                                bool safe_ints);
}
namespace Data {
v8::Local<v8::Value> GetFlatRowJS(v8::Isolate *isolate,
                                  v8::Local<v8::Context> ctx,
                                  sqlite3_stmt *handle, bool safe_ints);
}
namespace Data {
v8::Local<v8::Value> GetExpandedRowJS(v8::Isolate *isolate,
                                      v8::Local<v8::Context> ctx,
                                      sqlite3_stmt *handle, bool safe_ints);
}
namespace Data {
v8::Local<v8::Value> GetRawRowJS(v8::Isolate *isolate,
                                 v8::Local<v8::Context> ctx,
                                 sqlite3_stmt *handle, bool safe_ints);
}
namespace Data {
v8::Local<v8::Value> GetRowJS(v8::Isolate *isolate, v8::Local<v8::Context> ctx,
                              sqlite3_stmt *handle, bool safe_ints, char mode);
}
namespace Data {
void GetArgumentsJS(v8::Isolate *isolate, v8::Local<v8::Value> *out,
                    sqlite3_value **values, int argument_count, bool safe_ints);
}
namespace Data {
int BindValueFromJS(v8::Isolate *isolate, sqlite3_stmt *handle, int index,
                    v8::Local<v8::Value> value);
}
namespace Data {
void ResultValueFromJS(v8::Isolate *isolate, sqlite3_context *invocation,
                       v8::Local<v8::Value> value, DataConverter *converter);
}

#endif // BETTER_SQLITE3_UTIL_DATA_HPP
