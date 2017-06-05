// util_StringList.h
//

#ifndef LZZ_util_StringList_h
#define LZZ_util_StringList_h
#include <list>
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  typedef std::list <String> StringList;
}
namespace util
{
  typedef std::list <String>::iterator StringListIter;
}
namespace util
{
  typedef std::list <String>::const_iterator StringListConstIter;
}
#undef LZZ_INLINE
#endif
