// smtc_NsScope.cpp
//

#include "smtc_NsScope.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_NsScope.inl"
#endif
// semantic
#include "smtc_ScopeVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  NsScope::NsScope (NsPtr const & ns)
    : m_ns (ns)
    {}
}
namespace smtc
{
  NsScope::~ NsScope ()
    {}
}
namespace smtc
{
  void NsScope::accept (ScopeVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
