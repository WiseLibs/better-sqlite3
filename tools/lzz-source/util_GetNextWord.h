// util_GetNextWord.h
//

#ifndef LZZ_util_GetNextWord_h
#define LZZ_util_GetNextWord_h
// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  StringConstIter getNextWord (StringConstIter str_beg, StringConstIter str_end, char const * end_chars);
}
namespace util
{
  String getNextWord (StringConstIter str_beg, StringConstIter str_end, char const * end_chars, StringConstIter & word_end);
}
#undef LZZ_INLINE
#endif
