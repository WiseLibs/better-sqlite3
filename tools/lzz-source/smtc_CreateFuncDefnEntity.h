// smtc_CreateFuncDefnEntity.h
//

#ifndef LZZ_smtc_CreateFuncDefnEntity_h
#define LZZ_smtc_CreateFuncDefnEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_FuncDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFuncDefnEntity (FuncDefnPtr const & func_defn);
}
#undef LZZ_INLINE
#endif
