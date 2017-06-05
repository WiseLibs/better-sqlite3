// smtc_FrndTmplFuncDeclEntity.cpp
//

#include "smtc_FrndTmplFuncDeclEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_FrndTmplFuncDeclEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  FrndTmplFuncDeclEntity::FrndTmplFuncDeclEntity (TmplFuncDeclPtr const & tmpl_func_decl)
    : m_tmpl_func_decl (tmpl_func_decl)
    {}
}
namespace smtc
{
  FrndTmplFuncDeclEntity::~ FrndTmplFuncDeclEntity ()
    {}
}
namespace smtc
{
  void FrndTmplFuncDeclEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
