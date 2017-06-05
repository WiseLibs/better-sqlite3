// smtc_TmplInstScope.cpp
//

#include "smtc_TmplInstScope.h"
// semantic
#include "smtc_ScopeVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplInstScope::TmplInstScope (ScopePtr const & parent)
    : m_parent (parent)
    {}
}
namespace smtc
{
  TmplInstScope::~ TmplInstScope ()
    {}
}
namespace smtc
{
  void TmplInstScope::accept (ScopeVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
namespace smtc
{
  ScopePtr const & TmplInstScope::getParent () const
    {
      return m_parent;
    }
}
#undef LZZ_INLINE
