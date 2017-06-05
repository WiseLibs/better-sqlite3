// smtc_DtorBaseName.cpp
//

#include "smtc_DtorBaseName.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_DtorBaseName.inl"
#endif
#include "smtc_BaseNameVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  DtorBaseName::DtorBaseName (util::Loc const & loc, util::Ident const & macro, util::Ident const & ident)
    : BaseName (loc, macro), m_ident (ident)
    {}
}
namespace smtc
{
  DtorBaseName::~ DtorBaseName ()
    {}
}
namespace smtc
{
  void DtorBaseName::accept (BaseNameVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
