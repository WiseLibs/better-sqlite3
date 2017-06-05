// util_IntToString.cpp
//

#include "util_IntToString.h"
// lib
#include <stdio.h>
#define LZZ_INLINE inline
namespace util
{
  util::String intToString (int n)
  {
    char buf [64];
    sprintf (buf, "%d", n);
    return buf;
  }
}
#undef LZZ_INLINE
