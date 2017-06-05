// util_SkipWs.h
//

#ifndef LZZ_util_SkipWs_h
#define LZZ_util_SkipWs_h
// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  StringConstIter skipWs (StringConstIter str_beg, StringConstIter str_end, char const * ws);
}
namespace util
{
  StringConstIter skipWs (StringConstIter str_beg, StringConstIter str_end);
}
#undef LZZ_INLINE
#endif
