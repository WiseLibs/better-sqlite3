// util_SkipWs.cpp
//

#include "util_SkipWs.h"
// std lib
#include <cstring>
#define LZZ_INLINE inline
namespace util
{
  StringConstIter skipWs (StringConstIter str_beg, StringConstIter str_end, char const * ws)
  {
    StringConstIter i = str_beg;
    while (i != str_end && strchr (ws, * i) != NULL)
    {
      ++ i;
    }
    return i;
  }
}
namespace util
{
  StringConstIter skipWs (StringConstIter str_beg, StringConstIter str_end)
  {
    return skipWs (str_beg, str_end, " \t");
  }
}
#undef LZZ_INLINE
