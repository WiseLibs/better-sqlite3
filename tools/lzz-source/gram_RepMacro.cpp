// gram_RepMacro.cpp
//

#include "gram_RepMacro.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_RepMacro.inl"
#endif
// gram
#define LZZ_INLINE inline
namespace gram
{
  RepMacro::RepMacro (util::Loc const & loc, util::Ident const & name, basl::TokenVector const & rep_set)
    : Macro (loc, name), m_rep_set (rep_set)
    {}
}
#undef LZZ_INLINE
