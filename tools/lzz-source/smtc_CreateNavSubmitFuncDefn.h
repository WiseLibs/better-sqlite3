// smtc_CreateNavSubmitFuncDefn.h
//

#ifndef LZZ_smtc_CreateNavSubmitFuncDefn_h
#define LZZ_smtc_CreateNavSubmitFuncDefn_h
// semantic
#include "smtc_CvType.h"
#include "smtc_FuncDecl.h"
#include "smtc_NamePtr.h"
#include "smtc_NavSubmitFuncDefnPtr.h"
#include "smtc_ObjPtrVector.h"
#include "smtc_ParamPtrVector.h"

// gram
#include "gram_Block.h"
#define LZZ_INLINE inline
namespace smtc
{
  NavSubmitFuncDefnPtr createNavSubmitFuncDefn (int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, NamePtr const & nav_name, ObjPtrVector const & obj_set, gram::Block const & ret_stmt);
}
#undef LZZ_INLINE
#endif
