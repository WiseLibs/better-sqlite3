// smtc_ClassInstEntity.cpp
//

#include "smtc_ClassInstEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_ClassInstEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  ClassInstEntity::ClassInstEntity (ClassDeclPtr const & class_decl)
    : m_class_decl (class_decl)
    {}
}
namespace smtc
{
  ClassInstEntity::~ ClassInstEntity ()
    {}
}
namespace smtc
{
  void ClassInstEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
