// smtc_CreateTmplParam.h
//

#ifndef LZZ_smtc_CreateTmplParam_h
#define LZZ_smtc_CreateTmplParam_h
// semantic
#include "smtc_NamePtr.h"
#include "smtc_ParamPtr.h"
#include "smtc_ParamPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  ParamPtr createTmplParam (NamePtr const & name, ParamPtrVector const & param_set, NamePtr const & def_name);
}
#undef LZZ_INLINE
#endif
