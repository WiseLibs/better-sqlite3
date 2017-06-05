// util_GetSpaces.cpp
//

#include "util_GetSpaces.h"
#define LZZ_INLINE inline
namespace util
{
  char const * getSpaces (int n)
  {
    static const char spaces [] = "                                                                                               ";
    return spaces + sizeof (spaces) - 1 - n % (sizeof (spaces) - 1);
  }
}
#undef LZZ_INLINE
