// basl_HasTokenSameLexeme.h
//

#ifndef LZZ_basl_HasTokenSameLexeme_h
#define LZZ_basl_HasTokenSameLexeme_h
// basil
#include "basl_Token.h"
#define LZZ_INLINE inline
namespace basl
{
  struct HasTokenSameLexeme
  {
    bool operator () (Token const & a, Token const & b) const;
  public:
    explicit HasTokenSameLexeme ();
    ~ HasTokenSameLexeme ();
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "basl_HasTokenSameLexeme.inl"
#endif
#endif
