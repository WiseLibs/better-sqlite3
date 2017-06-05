// util_RemoveChars.h
//

#ifndef LZZ_util_RemoveChars_h
#define LZZ_util_RemoveChars_h
// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  String removeChars (String const & str1, char const * chars);
}
#undef LZZ_INLINE
#endif
