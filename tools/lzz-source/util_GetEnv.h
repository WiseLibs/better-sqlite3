// util_GetEnv.h
//

#ifndef LZZ_util_GetEnv_h
#define LZZ_util_GetEnv_h
// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  bool getEnv (char const * name, util::String & value);
}
namespace util
{
  util::String getEnv (char const * name);
}
#undef LZZ_INLINE
#endif
