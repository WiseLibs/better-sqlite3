// smtc_TmplFuncDefnEntity.cpp
//

#include "smtc_TmplFuncDefnEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_TmplFuncDefnEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplFuncDefnEntity::TmplFuncDefnEntity (TmplFuncDefnPtr const & tmpl_func_defn)
    : m_tmpl_func_defn (tmpl_func_defn)
    {}
}
namespace smtc
{
  TmplFuncDefnEntity::~ TmplFuncDefnEntity ()
    {}
}
namespace smtc
{
  void TmplFuncDefnEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
