// smtc_GetFuncType.h
//

#ifndef LZZ_smtc_GetFuncType_h
#define LZZ_smtc_GetFuncType_h
// semantic
#include "smtc_CvTypeVector.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_ThrowSpecPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  CvType getFuncType (CvType const & ret_type, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec);
}
namespace smtc
{
  CvType getFuncType (CvType const & ret_type, CvTypeVector const & param_type_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec);
}
#undef LZZ_INLINE
#endif
