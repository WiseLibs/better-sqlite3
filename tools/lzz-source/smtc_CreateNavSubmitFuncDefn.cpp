// smtc_CreateNavSubmitFuncDefn.cpp
//

#include "smtc_CreateNavSubmitFuncDefn.h"
// semantic
#include "smtc_NavSubmitFuncDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  NavSubmitFuncDefnPtr createNavSubmitFuncDefn (int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, NamePtr const & nav_name, ObjPtrVector const & obj_set, gram::Block const & ret_stmt)
  {
    return new NavSubmitFuncDefn (flags, ret_type, name, param_set, nav_name, obj_set, ret_stmt);
  }
}
#undef LZZ_INLINE
