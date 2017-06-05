// smtc_VdfClassEntity.cpp
//

#include "smtc_VdfClassEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_VdfClassEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  VdfClassEntity::~ VdfClassEntity ()
    {}
}
namespace smtc
{
  void VdfClassEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
