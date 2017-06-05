// smtc_LazyClassScope.cpp
//

#include "smtc_LazyClassScope.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_LazyClassScope.inl"
#endif
// semantic
#include "smtc_ScopeVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  LazyClassScope::LazyClassScope (LazyClassPtr const & lazy_class)
    : ClassScope (lazy_class)
    {}
}
namespace smtc
{
  LazyClassScope::~ LazyClassScope ()
    {}
}
namespace smtc
{
  void LazyClassScope::accept (ScopeVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
