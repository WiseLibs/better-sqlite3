// smtc_CreateFuncDefnEntity.cpp
//

#include "smtc_CreateFuncDefnEntity.h"
// semantic
#include "smtc_FuncDefnEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFuncDefnEntity (FuncDefnPtr const & func_defn)
  {
    return new FuncDefnEntity (func_defn);
  }
}
#undef LZZ_INLINE
