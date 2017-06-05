// smtc_BaseName.cpp
//

#include "smtc_BaseName.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_BaseName.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  BaseName::BaseName (util::Loc const & loc, util::Ident const & macro)
    : m_loc (loc), m_macro (macro)
    {}
}
namespace smtc
{
  BaseName::~ BaseName ()
    {}
}
#undef LZZ_INLINE
