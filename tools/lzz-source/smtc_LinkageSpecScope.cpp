// smtc_LinkageSpecScope.cpp
//

#include "smtc_LinkageSpecScope.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_LinkageSpecScope.inl"
#endif
// semantic
#include "smtc_ScopeVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  LinkageSpecScope::~ LinkageSpecScope ()
    {}
}
namespace smtc
{
  void LinkageSpecScope::accept (ScopeVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
