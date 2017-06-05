// util_StringTable.h
//

#ifndef LZZ_util_StringTable_h
#define LZZ_util_StringTable_h
// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  char const * storeString (util::String const & name);
}
namespace util
{
  char const * storeString (char const * name);
}
#undef LZZ_INLINE
#endif
