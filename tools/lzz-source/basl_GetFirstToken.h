// basl_GetFirstToken.h
//

#ifndef LZZ_basl_GetFirstToken_h
#define LZZ_basl_GetFirstToken_h
// basil
#include "basl_Nonterm.h"
#define LZZ_INLINE inline
namespace basl
{
  Token getFirstToken (Nonterm const & nonterm);
}
namespace basl
{
  util::Loc getFirstLoc (Nonterm const & nonterm);
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "basl_GetFirstToken.inl"
#endif
#endif
