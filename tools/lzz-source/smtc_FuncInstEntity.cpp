// smtc_FuncInstEntity.cpp
//

#include "smtc_FuncInstEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_FuncInstEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  FuncInstEntity::FuncInstEntity (FuncDeclPtr const & func_decl)
    : m_func_decl (func_decl)
    {}
}
namespace smtc
{
  FuncInstEntity::~ FuncInstEntity ()
    {}
}
namespace smtc
{
  void FuncInstEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
