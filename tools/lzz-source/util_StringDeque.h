// util_StringDeque.h
//

#ifndef LZZ_util_StringDeque_h
#define LZZ_util_StringDeque_h
#include <deque>
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  typedef std::deque <String> StringDeque;
}
namespace util
{
  typedef std::deque <String>::iterator StringDequeIter;
}
namespace util
{
  typedef std::deque <String>::const_iterator StringDequeConstIter;
}
#undef LZZ_INLINE
#endif
