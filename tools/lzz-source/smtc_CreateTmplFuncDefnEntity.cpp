// smtc_CreateTmplFuncDefnEntity.cpp
//

#include "smtc_CreateTmplFuncDefnEntity.h"
// semantic
#include "smtc_TmplFuncDefnEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createTmplFuncDefnEntity (TmplFuncDefnPtr const & tmpl_func_defn)
  {
    return new TmplFuncDefnEntity (tmpl_func_defn);
  }
}
#undef LZZ_INLINE
