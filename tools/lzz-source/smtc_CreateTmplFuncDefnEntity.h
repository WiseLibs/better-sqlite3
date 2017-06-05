// smtc_CreateTmplFuncDefnEntity.h
//

#ifndef LZZ_smtc_CreateTmplFuncDefnEntity_h
#define LZZ_smtc_CreateTmplFuncDefnEntity_h
// semantic
#include "smtc_EntityPtr.h"
#include "smtc_TmplFuncDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createTmplFuncDefnEntity (TmplFuncDefnPtr const & tmpl_func_defn);
}
#undef LZZ_INLINE
#endif
