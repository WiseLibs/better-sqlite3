// smtc_NsEntity.cpp
//

#include "smtc_NsEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_NsEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  NsEntity::NsEntity (NsPtr const & ns)
    : m_ns (ns)
    {}
}
namespace smtc
{
  NsEntity::~ NsEntity ()
    {}
}
namespace smtc
{
  void NsEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
