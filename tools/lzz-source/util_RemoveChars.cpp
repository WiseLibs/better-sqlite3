// util_RemoveChars.cpp
//

#include "util_RemoveChars.h"
// std lib
#include <cstring>
#define LZZ_INLINE inline
namespace util
{
  String removeChars (String const & str1, char const * chars)
  {
    String str2;
    for (StringConstIter i = str1.begin (); i != str1.end (); ++ i)
    {
      char ch = * i;
      if (strchr (chars, ch) == NULL)
      {
        str2 += ch;
      }
    }
    return str2;
  }
}
#undef LZZ_INLINE
