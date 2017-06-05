// util_StringICompare.h
//

#ifndef LZZ_util_StringICompare_h
#define LZZ_util_StringICompare_h
// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  int stringICompare (String const & s1, String const & s2);
}
namespace util
{
  int stringICompare (char const * s1, char const * s2);
}
#undef LZZ_INLINE
#endif
