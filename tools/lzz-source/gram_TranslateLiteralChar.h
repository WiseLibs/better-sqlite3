// gram_TranslateLiteralChar.h
//

#ifndef LZZ_gram_TranslateLiteralChar_h
#define LZZ_gram_TranslateLiteralChar_h
// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace gram
{
  unsigned int translateLiteralChar (util::Loc const & loc, char const * str, char const * * next_ch);
}
#undef LZZ_INLINE
#endif
