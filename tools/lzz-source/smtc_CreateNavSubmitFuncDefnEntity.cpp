// smtc_CreateNavSubmitFuncDefnEntity.cpp
//

#include "smtc_CreateNavSubmitFuncDefnEntity.h"
// semantic
#include "smtc_NavSubmitFuncDefnEntity.h"
#define LZZ_INLINE inline
namespace smtc
{
  EntityPtr createNavSubmitFuncDefnEntity (NavSubmitFuncDefnPtr const & nav_submit_func_defn)
  {
    return new NavSubmitFuncDefnEntity (nav_submit_func_defn);
  }
}
#undef LZZ_INLINE
