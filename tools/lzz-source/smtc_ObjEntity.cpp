// smtc_ObjEntity.cpp
//

#include "smtc_ObjEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_ObjEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  ObjEntity::ObjEntity (ObjPtr const & obj)
    : m_obj (obj)
    {}
}
namespace smtc
{
  ObjEntity::~ ObjEntity ()
    {}
}
namespace smtc
{
  void ObjEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
