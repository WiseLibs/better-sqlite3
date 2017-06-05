// smtc_UsingDirEntity.cpp
//

#include "smtc_UsingDirEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_UsingDirEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  UsingDirEntity::~ UsingDirEntity ()
    {}
}
namespace smtc
{
  void UsingDirEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
