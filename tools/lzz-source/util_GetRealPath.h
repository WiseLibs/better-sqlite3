// util_GetRealPath.h
//

#ifndef LZZ_util_GetRealPath_h
#define LZZ_util_GetRealPath_h
// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  bool getRealPath (util::String const & file, util::String & real_file);
}
#undef LZZ_INLINE
#endif
