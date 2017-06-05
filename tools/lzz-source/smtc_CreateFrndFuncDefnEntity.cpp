// smtc_CreateFrndFuncDefnEntity.cpp
//

#include "smtc_CreateFrndFuncDefnEntity.h"
// semantic
#include "smtc_FrndFuncDefnEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFrndFuncDefnEntity (FuncDefnPtr const & func_defn)
  {
    return new FrndFuncDefnEntity (func_defn);
  }
}
#undef LZZ_INLINE
