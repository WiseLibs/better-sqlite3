// smtc_FrndTmplClassDeclEntity.cpp
//

#include "smtc_FrndTmplClassDeclEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_FrndTmplClassDeclEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  FrndTmplClassDeclEntity::FrndTmplClassDeclEntity (TmplClassDeclPtr const & tmpl_class_decl)
    : m_tmpl_class_decl (tmpl_class_decl)
    {}
}
namespace smtc
{
  FrndTmplClassDeclEntity::~ FrndTmplClassDeclEntity ()
    {}
}
namespace smtc
{
  void FrndTmplClassDeclEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
