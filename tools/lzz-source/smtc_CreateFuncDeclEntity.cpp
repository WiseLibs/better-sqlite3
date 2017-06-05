// smtc_CreateFuncDeclEntity.cpp
//

#include "smtc_CreateFuncDeclEntity.h"
// semantic
#include "smtc_FuncDeclEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFuncDeclEntity (FuncDeclPtr const & func_decl)
  {
    return new FuncDeclEntity (func_decl);
  }
}
#undef LZZ_INLINE
