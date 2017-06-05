// smtc_ClassDeclEntity.cpp
//

#include "smtc_ClassDeclEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_ClassDeclEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  ClassDeclEntity::ClassDeclEntity (ClassDeclPtr const & class_decl)
    : m_class_decl (class_decl)
    {}
}
namespace smtc
{
  ClassDeclEntity::~ ClassDeclEntity ()
    {}
}
namespace smtc
{
  void ClassDeclEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
