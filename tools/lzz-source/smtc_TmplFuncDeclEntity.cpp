// smtc_TmplFuncDeclEntity.cpp
//

#include "smtc_TmplFuncDeclEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_TmplFuncDeclEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplFuncDeclEntity::TmplFuncDeclEntity (TmplFuncDeclPtr const & tmpl_func_decl)
    : m_tmpl_func_decl (tmpl_func_decl)
    {}
}
namespace smtc
{
  TmplFuncDeclEntity::~ TmplFuncDeclEntity ()
    {}
}
namespace smtc
{
  void TmplFuncDeclEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
