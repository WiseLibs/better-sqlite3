// gram_FuncMacro.cpp
//

#include "gram_FuncMacro.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_FuncMacro.inl"
#endif
// gram
#define LZZ_INLINE inline
namespace gram
{
  FuncMacro::FuncMacro (util::Loc const & loc, util::Ident const & name, util::IdentVector const & param_set, bool var, basl::TokenVector const & rep_set)
    : RepMacro (loc, name, rep_set), m_param_set (param_set), m_var (var)
    {}
}
namespace gram
{
  FuncMacro::~ FuncMacro ()
    {}
}
namespace gram
{
  MacroKind FuncMacro::getKind () const
    {
      return FUNC_MACRO;
    }
}
#undef LZZ_INLINE
