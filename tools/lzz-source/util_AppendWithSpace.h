// util_AppendWithSpace.h
//

#ifndef LZZ_util_AppendWithSpace_h
#define LZZ_util_AppendWithSpace_h
// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  void appendWithSpace (util::String & str1, util::String const & str2);
}
namespace util
{
  void appendWithSpace (util::String & str1, char const * str2);
}
namespace util
{
  void appendWithSpace (util::String & str1, char ch);
}
#undef LZZ_INLINE
#endif
