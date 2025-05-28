#ifndef BETTER_SQLITE3_UTIL_DATA_CONVERTER_HPP
#define BETTER_SQLITE3_UTIL_DATA_CONVERTER_HPP

#include "../better_sqlite3_deps.hpp"

class DataConverter {
public:
  void ThrowDataConversionError(sqlite3_context *invocation, bool isBigInt);

protected:
  virtual void PropagateJSError(sqlite3_context *invocation) = 0;
  virtual std::string GetDataErrorPrefix() = 0;
};

#endif // BETTER_SQLITE3_UTIL_DATA_CONVERTER_HPP
