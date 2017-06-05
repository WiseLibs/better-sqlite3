// smtc_FuncDeclEntity.cpp
//

#include "smtc_FuncDeclEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_FuncDeclEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  FuncDeclEntity::FuncDeclEntity (FuncDeclPtr const & func_decl)
    : m_func_decl (func_decl)
    {}
}
namespace smtc
{
  FuncDeclEntity::~ FuncDeclEntity ()
    {}
}
namespace smtc
{
  void FuncDeclEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
