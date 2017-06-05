// smtc_TmplSpecScope.cpp
//

#include "smtc_TmplSpecScope.h"
// semantic
#include "smtc_ScopeVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplSpecScope::TmplSpecScope (ScopePtr const & parent, TmplSpecPtr const & tmpl_spec)
    : m_parent (parent), m_tmpl_spec (tmpl_spec)
    {}
}
namespace smtc
{
  TmplSpecScope::~ TmplSpecScope ()
    {}
}
namespace smtc
{
  void TmplSpecScope::accept (ScopeVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
namespace smtc
{
  ScopePtr const & TmplSpecScope::getParent () const
    {
      return m_parent;
    }
}
namespace smtc
{
  TmplSpecPtr const & TmplSpecScope::getTmplSpec () const
    {
      return m_tmpl_spec;
    }
}
#undef LZZ_INLINE
