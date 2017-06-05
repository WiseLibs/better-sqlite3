// gram_IsOctalDigit.cpp
//

#include "gram_IsOctalDigit.h"
#define LZZ_INLINE inline
namespace gram
{
  bool isOctalDigit (char ch)
  {
    return (ch >= '0' && ch <= '7');
  }
}
#undef LZZ_INLINE
