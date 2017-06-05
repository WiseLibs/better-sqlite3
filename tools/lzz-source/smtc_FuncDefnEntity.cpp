// smtc_FuncDefnEntity.cpp
//

#include "smtc_FuncDefnEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_FuncDefnEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  FuncDefnEntity::FuncDefnEntity (FuncDefnPtr const & func_defn)
    : m_func_defn (func_defn)
    {}
}
namespace smtc
{
  FuncDefnEntity::~ FuncDefnEntity ()
    {}
}
namespace smtc
{
  void FuncDefnEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
