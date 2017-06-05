// smtc_EnumEntity.cpp
//

#include "smtc_EnumEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_EnumEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  EnumEntity::EnumEntity (EnumPtr const & en)
    : m_en (en)
    {}
}
namespace smtc
{
  EnumEntity::~ EnumEntity ()
    {}
}
namespace smtc
{
  void EnumEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
