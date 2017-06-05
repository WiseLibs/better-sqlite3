// util_GetNextWord.cpp
//

#include "util_GetNextWord.h"
// std lib
#include <cstring>
#define LZZ_INLINE inline
namespace util
{
  StringConstIter getNextWord (StringConstIter str_beg, StringConstIter str_end, char const * end_chars)
  {
    StringConstIter i = str_beg;
    while (i != str_end && strchr (end_chars, * i) == NULL)
    {
      ++ i;
    }
    return i;
  }
}
namespace util
{
  String getNextWord (StringConstIter str_beg, StringConstIter str_end, char const * end_chars, StringConstIter & word_end)
  {
    word_end = getNextWord (str_beg, str_end, end_chars);
    return String (str_beg, word_end);
  }
}
#undef LZZ_INLINE
