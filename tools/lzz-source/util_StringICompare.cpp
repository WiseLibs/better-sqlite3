// util_StringICompare.cpp
//

#include "util_StringICompare.h"
// lib
#include <ctype.h>
#define LZZ_INLINE inline
namespace util
{
  int stringICompare (String const & s1, String const & s2)
  {
    return stringICompare (s1.c_str (), s2.c_str ());
  }
}
namespace util
{
  int stringICompare (char const * s1, char const * s2)
  {
    while (* s1 && * s2)
    {
      char c1 = toupper (* s1);
      char c2 = toupper (* s2);
      if (c1 != c2)
      {
        return (c1 < c2) ? -1 : 1;
      }
      ++ s1;
      ++ s2;
    }
    if (* s1)
    {
      return 1;
    }
    else if (* s2)
    {
      return -1;
    }
    else
    {
      return 0;
    }
  }
}
#undef LZZ_INLINE
