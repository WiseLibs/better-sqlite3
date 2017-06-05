// util_LocToString.h
//

#ifndef LZZ_util_LocToString_h
#define LZZ_util_LocToString_h
// std lib
#include <cstdio>

// util
#include "util_Loc.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  String locToString (Loc const & loc);
}
#undef LZZ_INLINE
#endif
