// smtc_NavClassEntity.cpp
//

#include "smtc_NavClassEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_NavClassEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  NavClassEntity::~ NavClassEntity ()
    {}
}
namespace smtc
{
  void NavClassEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
namespace smtc
{
  NavClassPtr NavClassEntity::getNavClass () const
    {
      return getClassDecl ();
    }
}
#undef LZZ_INLINE
