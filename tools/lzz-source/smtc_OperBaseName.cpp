// smtc_OperBaseName.cpp
//

#include "smtc_OperBaseName.h"
#include "smtc_BaseNameVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  OperBaseName::OperBaseName (util::Loc const & loc, util::Ident const & macro, OperKind kind)
    : BaseName (loc, macro), m_kind (kind)
    {}
}
namespace smtc
{
  OperBaseName::~ OperBaseName ()
    {}
}
namespace smtc
{
  void OperBaseName::accept (BaseNameVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
namespace smtc
{
  OperKind OperBaseName::getOperKind () const
    {
      return m_kind;
    }
}
#undef LZZ_INLINE
