// gram_RepMacro.h
//

#ifndef LZZ_gram_RepMacro_h
#define LZZ_gram_RepMacro_h
// gram
#include "gram_Macro.h"

// basil
#include "basl_TokenVector.h"
#define LZZ_INLINE inline
namespace gram
{
  class RepMacro : public Macro
  {
    basl::TokenVector m_rep_set;
  public:
    RepMacro (util::Loc const & loc, util::Ident const & name, basl::TokenVector const & rep_set);
    ~ RepMacro ();
    basl::TokenVector const & getRepSet () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_RepMacro.inl"
#endif
#endif
