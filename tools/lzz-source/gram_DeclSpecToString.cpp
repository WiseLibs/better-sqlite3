// gram_DeclSpecToString.cpp
//

#include "gram_DeclSpecToString.h"
// gram
#include "gram_DeclSpecFlags.h"
#define LZZ_INLINE inline
namespace gram
{
  char const * declSpecToString (int flag)
  {
    char const * str;
    if (flag == TYPEDEF_SPEC)
    {
      str = "typedef";
    }
    else
    {
      str = "friend";
    }
    return str;
  }
}
#undef LZZ_INLINE
