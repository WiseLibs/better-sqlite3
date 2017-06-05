// smtc_NavClassScope.cpp
//

#include "smtc_NavClassScope.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_NavClassScope.inl"
#endif
// semantic
#include "smtc_ScopeVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  NavClassScope::NavClassScope (NavClassPtr const & nav_class)
    : ClassScope (nav_class)
    {}
}
namespace smtc
{
  NavClassScope::~ NavClassScope ()
    {}
}
namespace smtc
{
  void NavClassScope::accept (ScopeVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
