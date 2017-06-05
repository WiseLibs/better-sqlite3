// basl_FreeToken.h
//

#ifndef LZZ_basl_FreeToken_h
#define LZZ_basl_FreeToken_h
// basl
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace basl
{
  struct FreeToken
  {
    int number;
    util::Ident lexeme;
    FreeToken (int number, util::Ident const & lexeme);
  };
}
#undef LZZ_INLINE
#endif
