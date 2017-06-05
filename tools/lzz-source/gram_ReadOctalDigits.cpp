// gram_ReadOctalDigits.cpp
//

#include "gram_ReadOctalDigits.h"
// gram
#include "gram_IsOctalDigit.h"
#define LZZ_INLINE inline
namespace gram
{
  int readOctalDigits (char const * str, int max_num, char * out, char const * * next_char)
  {
    int cnt = 0;
    for (; cnt < max_num; ++ cnt)
    {
      char ch = * str;
      if (ch == 0 || ! isOctalDigit (ch))
      {
        break;
      }
      * out ++ = ch;
      ++ str;
    }
    * out = '\0';
    * next_char = str;
    return cnt;
  }
}
#undef LZZ_INLINE
