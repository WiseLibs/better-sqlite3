// util_StringVector.h
//

#ifndef LZZ_util_StringVector_h
#define LZZ_util_StringVector_h
#include <vector>
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  typedef std::vector <String> StringVector;
}
namespace util
{
  typedef std::vector <String>::iterator StringVectorIter;
}
namespace util
{
  typedef std::vector <String>::const_iterator StringVectorConstIter;
}
#undef LZZ_INLINE
#endif
