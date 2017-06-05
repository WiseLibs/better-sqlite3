// smtc_GetFuncType.cpp
//

#include "smtc_GetFuncType.h"
// std lib
#include <algorithm>

// semantic
#include "smtc_FuncType.h"
#include "smtc_GetNonTypeParamType.h"
#define LZZ_INLINE inline
namespace smtc
{
  CvType getFuncType (CvType const & ret_type, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec)
  {
    CvTypeVector param_type_set;
    std::transform (param_set.begin (), param_set.end (), std::back_inserter (param_type_set), GetNonTypeParamType ());
    TypePtr type = new FuncType (ret_type, param_type_set, vararg, cv, throw_spec);
    return CvType (type, Cv ());
  }
}
namespace smtc
{
  CvType getFuncType (CvType const & ret_type, CvTypeVector const & param_type_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec)
  {
    TypePtr type = new FuncType (ret_type, param_type_set, vararg, cv, throw_spec);
    return CvType (type, Cv ());
  }
}
#undef LZZ_INLINE
