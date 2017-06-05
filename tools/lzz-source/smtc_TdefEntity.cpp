// smtc_TdefEntity.cpp
//

#include "smtc_TdefEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_TdefEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  TdefEntity::TdefEntity (TdefPtr const & tdef)
    : m_tdef (tdef)
    {}
}
namespace smtc
{
  TdefEntity::~ TdefEntity ()
    {}
}
namespace smtc
{
  void TdefEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
