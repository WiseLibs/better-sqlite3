// smtc_TmplLazyClassEntity.cpp
//

#include "smtc_TmplLazyClassEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_TmplLazyClassEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplLazyClassEntity::~ TmplLazyClassEntity ()
    {}
}
namespace smtc
{
  void TmplLazyClassEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
namespace smtc
{
  TmplLazyClassPtr TmplLazyClassEntity::getTmplLazyClass () const
    {
      return getTmplClassDecl ();
    }
}
#undef LZZ_INLINE
