// smtc_FrndTmplFuncDefnEntity.cpp
//

#include "smtc_FrndTmplFuncDefnEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_FrndTmplFuncDefnEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  FrndTmplFuncDefnEntity::FrndTmplFuncDefnEntity (TmplFuncDefnPtr const & tmpl_func_defn)
    : m_tmpl_func_defn (tmpl_func_defn)
    {}
}
namespace smtc
{
  FrndTmplFuncDefnEntity::~ FrndTmplFuncDefnEntity ()
    {}
}
namespace smtc
{
  void FrndTmplFuncDefnEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
