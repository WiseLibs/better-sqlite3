// smtc_NavSubmitFuncDefnEntity.cpp
//

#include "smtc_NavSubmitFuncDefnEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_NavSubmitFuncDefnEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  NavSubmitFuncDefnEntity::NavSubmitFuncDefnEntity (NavSubmitFuncDefnPtr const & nav_submit_func_defn)
    : FuncDeclEntity (nav_submit_func_defn)
    {}
}
namespace smtc
{
  NavSubmitFuncDefnEntity::~ NavSubmitFuncDefnEntity ()
    {}
}
namespace smtc
{
  void NavSubmitFuncDefnEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
