// smtc_UsingDeclEntity.cpp
//

#include "smtc_UsingDeclEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_UsingDeclEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  UsingDeclEntity::~ UsingDeclEntity ()
    {}
}
namespace smtc
{
  void UsingDeclEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
