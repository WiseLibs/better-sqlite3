// smtc_CreateFrndFuncDefnEntity.h
//

#ifndef LZZ_smtc_CreateFrndFuncDefnEntity_h
#define LZZ_smtc_CreateFrndFuncDefnEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_FuncDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFrndFuncDefnEntity (FuncDefnPtr const & func_defn);
}
#undef LZZ_INLINE
#endif
