// smtc_FrndClassDeclEntity.cpp
//

#include "smtc_FrndClassDeclEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_FrndClassDeclEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  FrndClassDeclEntity::FrndClassDeclEntity (ClassDeclPtr const & class_decl)
    : m_class_decl (class_decl)
    {}
}
namespace smtc
{
  FrndClassDeclEntity::~ FrndClassDeclEntity ()
    {}
}
namespace smtc
{
  void FrndClassDeclEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
