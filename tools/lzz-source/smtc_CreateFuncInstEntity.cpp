// smtc_CreateFuncInstEntity.cpp
//

#include "smtc_CreateFuncInstEntity.h"
// semantic
#include "smtc_FuncInstEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFuncInstEntity (FuncDeclPtr const & func_decl)
  {
    return new FuncInstEntity (func_decl);
  }
}
#undef LZZ_INLINE
