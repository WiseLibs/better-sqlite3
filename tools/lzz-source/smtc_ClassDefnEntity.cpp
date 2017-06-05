// smtc_ClassDefnEntity.cpp
//

#include "smtc_ClassDefnEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_ClassDefnEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  ClassDefnEntity::~ ClassDefnEntity ()
    {}
}
namespace smtc
{
  void ClassDefnEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
namespace smtc
{
  ClassDefnPtr ClassDefnEntity::getClassDefn () const
    {
      return getClassDecl ();
    }
}
#undef LZZ_INLINE
