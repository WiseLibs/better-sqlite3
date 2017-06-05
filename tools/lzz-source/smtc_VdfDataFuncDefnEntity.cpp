// smtc_VdfDataFuncDefnEntity.cpp
//

#include "smtc_VdfDataFuncDefnEntity.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_VdfDataFuncDefnEntity.inl"
#endif
// semantic
#include "smtc_EntityVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  VdfDataFuncDefnEntity::VdfDataFuncDefnEntity (VdfDataFuncDefnPtr const & vdf_data_func_defn)
    : FuncDeclEntity (vdf_data_func_defn)
    {}
}
namespace smtc
{
  VdfDataFuncDefnEntity::~ VdfDataFuncDefnEntity ()
    {}
}
namespace smtc
{
  void VdfDataFuncDefnEntity::accept (EntityVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
