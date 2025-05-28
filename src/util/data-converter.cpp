#include "data-converter.hpp"
#include "../better_sqlite3_impl.hpp"

void DataConverter::ThrowDataConversionError(sqlite3_context *invocation,
                                             bool isBigInt) {
  if (isBigInt) {
    ThrowRangeError(
        (GetDataErrorPrefix() + " a bigint that was too big").c_str());
  } else {
    ThrowTypeError((GetDataErrorPrefix() + " an invalid value").c_str());
  }
  PropagateJSError(invocation);
}
