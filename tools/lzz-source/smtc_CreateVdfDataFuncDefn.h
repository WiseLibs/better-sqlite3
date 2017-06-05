// smtc_CreateVdfDataFuncDefn.h
//

#ifndef LZZ_smtc_CreateVdfDataFuncDefn_h
#define LZZ_smtc_CreateVdfDataFuncDefn_h
// semantic
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_VdfDataFuncDefnPtr.h"

// util
#include "util_String.h"

#define LZZ_INLINE inline
namespace smtc
{
  VdfDataFuncDefnPtr createVdfDataFuncDefn (int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, util::String const & cmt);
}
#undef LZZ_INLINE
#endif
