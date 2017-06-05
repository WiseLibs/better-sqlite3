// smtc_BuildLazyClassObjParamSet.h
//

#ifndef LZZ_smtc_BuildLazyClassObjParamSet_h
#define LZZ_smtc_BuildLazyClassObjParamSet_h
// semantic
#include "smtc_ParamPtrVector.h"
#include "smtc_BaseSpecPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  void buildLazyClassObjParamSet (ParamPtrVector const & param_set, BaseSpecPtrVector const & base_spec_set, ParamPtrVector & obj_param_set);
}
#undef LZZ_INLINE
#endif
