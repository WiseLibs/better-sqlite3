// smtc_TmplClassDeclEntity.cpp
//

#include "smtc_TmplClassDeclEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_TmplClassDeclEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplClassDeclEntity::TmplClassDeclEntity (TmplClassDeclPtr const & tmpl_class_decl)
    : m_tmpl_class_decl (tmpl_class_decl)
    {}
}
namespace smtc
{
  TmplClassDeclEntity::~ TmplClassDeclEntity ()
    {}
}
namespace smtc
{
  void TmplClassDeclEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
