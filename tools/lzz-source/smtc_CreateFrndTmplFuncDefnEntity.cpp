// smtc_CreateFrndTmplFuncDefnEntity.cpp
//

#include "smtc_CreateFrndTmplFuncDefnEntity.h"
// semantic
#include "smtc_FrndTmplFuncDefnEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createFrndTmplFuncDefnEntity (TmplFuncDefnPtr const & tmpl_func_defn)
  {
    return new FrndTmplFuncDefnEntity (tmpl_func_defn);
  }
}
#undef LZZ_INLINE
