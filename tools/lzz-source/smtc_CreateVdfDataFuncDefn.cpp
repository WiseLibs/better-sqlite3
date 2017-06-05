// smtc_CreateVdfDataFuncDefn.cpp
//

#include "smtc_CreateVdfDataFuncDefn.h"
// semantic
#include "smtc_VdfDataFuncDefn.h"
#define LZZ_INLINE inline
namespace smtc
{
  VdfDataFuncDefnPtr createVdfDataFuncDefn (int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, util::String const & cmt)
  {
    return new VdfDataFuncDefn (flags, ret_type, name, param_set, vararg, cmt);
  }
}
#undef LZZ_INLINE
