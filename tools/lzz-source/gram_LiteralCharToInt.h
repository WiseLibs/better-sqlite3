// gram_LiteralCharToInt.h
//

#ifndef LZZ_gram_LiteralCharToInt_h
#define LZZ_gram_LiteralCharToInt_h
// util
#include "util_Ident.h"
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace gram
{
  unsigned int literalCharToInt (util::Loc const & loc, util::Ident const & lexeme);
}
#undef LZZ_INLINE
#endif
