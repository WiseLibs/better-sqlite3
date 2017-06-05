// smtc_AccessSpecEntity.cpp
//

#include "smtc_AccessSpecEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_AccessSpecEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  AccessSpecEntity::AccessSpecEntity (AccessSpecPtr const & access_spec)
    : m_access_spec (access_spec)
    {}
}
namespace smtc
{
  AccessSpecEntity::~ AccessSpecEntity ()
    {}
}
namespace smtc
{
  void AccessSpecEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
