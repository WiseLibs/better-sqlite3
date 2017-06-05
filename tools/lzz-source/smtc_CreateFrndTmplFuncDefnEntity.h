// smtc_CreateFrndTmplFuncDefnEntity.h
//

#ifndef LZZ_smtc_CreateFrndTmplFuncDefnEntity_h
#define LZZ_smtc_CreateFrndTmplFuncDefnEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_TmplFuncDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFrndTmplFuncDefnEntity (TmplFuncDefnPtr const & tmpl_func_defn);
}
#undef LZZ_INLINE
#endif
