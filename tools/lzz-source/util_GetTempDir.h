// util_GetTempDir.h
//

#ifndef LZZ_util_GetTempDir_h
#define LZZ_util_GetTempDir_h
// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  bool getTempDir (char const * prefix, util::String & dir);
}
#undef LZZ_INLINE
#endif
