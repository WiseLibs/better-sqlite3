// smtc_FrndFuncDeclEntity.cpp
//

#include "smtc_FrndFuncDeclEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_FrndFuncDeclEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  FrndFuncDeclEntity::FrndFuncDeclEntity (FuncDeclPtr const & func_decl)
    : m_func_decl (func_decl)
    {}
}
namespace smtc
{
  FrndFuncDeclEntity::~ FrndFuncDeclEntity ()
    {}
}
namespace smtc
{
  void FrndFuncDeclEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
