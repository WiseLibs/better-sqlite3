// smtc_TmplClassDefnEntity.cpp
//

#include "smtc_TmplClassDefnEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_TmplClassDefnEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplClassDefnEntity::~ TmplClassDefnEntity ()
    {}
}
namespace smtc
{
  void TmplClassDefnEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
namespace smtc
{
  TmplClassDefnPtr TmplClassDefnEntity::getTmplClassDefn () const
    {
      return getTmplClassDecl ();
    }
}
#undef LZZ_INLINE
