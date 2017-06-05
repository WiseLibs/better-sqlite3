// gram_MacroArg.h
//

#ifndef LZZ_gram_MacroArg_h
#define LZZ_gram_MacroArg_h
// basl
#include "basl_TokenVector.h"
#define LZZ_INLINE inline
namespace gram
{
  class MacroArg
  {
    basl::TokenVector m_token_set;
  public:
    MacroArg (basl::TokenVector const & token_set);
    ~ MacroArg ();
    basl::TokenVector const & getTokenSet () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_MacroArg.inl"
#endif
#endif
