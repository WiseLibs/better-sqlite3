// smtc_CreateFrndFuncDeclEntity.cpp
//

#include "smtc_CreateFrndFuncDeclEntity.h"
// semantic
#include "smtc_FrndFuncDeclEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFrndFuncDeclEntity (FuncDeclPtr const & func_decl)
  {
    return new FrndFuncDeclEntity (func_decl);
  }
}
#undef LZZ_INLINE
