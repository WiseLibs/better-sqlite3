// smtc_FrndFuncDefnEntity.cpp
//

#include "smtc_FrndFuncDefnEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_FrndFuncDefnEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  FrndFuncDefnEntity::FrndFuncDefnEntity (FuncDefnPtr const & func_defn)
    : m_func_defn (func_defn)
    {}
}
namespace smtc
{
  FrndFuncDefnEntity::~ FrndFuncDefnEntity ()
    {}
}
namespace smtc
{
  void FrndFuncDefnEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
