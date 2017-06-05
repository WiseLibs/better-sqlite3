// smtc_IdentBaseName.cpp
//

#include "smtc_IdentBaseName.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_IdentBaseName.inl"
#endif
#include "smtc_BaseNameVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  IdentBaseName::IdentBaseName (util::Loc const & loc, util::Ident const & macro, util::Ident const & ident)
    : BaseName (loc, macro), m_ident (ident)
    {}
}
namespace smtc
{
  IdentBaseName::~ IdentBaseName ()
    {}
}
namespace smtc
{
  void IdentBaseName::accept (BaseNameVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
