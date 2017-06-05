// gram_FuncMacro.h
//

#ifndef LZZ_gram_FuncMacro_h
#define LZZ_gram_FuncMacro_h
// gram
#include "gram_RepMacro.h"

// util
#include "util_IdentVector.h"
#define LZZ_INLINE inline
namespace gram
{
  class FuncMacro : public RepMacro
  {
    util::IdentVector m_param_set;
    bool m_var;
  public:
    FuncMacro (util::Loc const & loc, util::Ident const & name, util::IdentVector const & param_set, bool var, basl::TokenVector const & rep_set);
    ~ FuncMacro ();
    MacroKind getKind () const;
    bool hasVarArgs () const;
    int getNumParams () const;
    util::IdentVector const & getParamSet () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_FuncMacro.inl"
#endif
#endif
