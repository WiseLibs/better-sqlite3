// smtc_LazyClassEntity.cpp
//

#include "smtc_LazyClassEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_LazyClassEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  LazyClassEntity::~ LazyClassEntity ()
    {}
}
namespace smtc
{
  void LazyClassEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
namespace smtc
{
  LazyClassPtr LazyClassEntity::getLazyClass () const
    {
      return getClassDecl ();
    }
}
#undef LZZ_INLINE
