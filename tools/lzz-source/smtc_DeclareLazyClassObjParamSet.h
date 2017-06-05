// smtc_DeclareLazyClassObjParamSet.h
//

#ifndef LZZ_smtc_DeclareLazyClassObjParamSet_h
#define LZZ_smtc_DeclareLazyClassObjParamSet_h
// semantic
#include "smtc_BaseSpecPtrVector.h"
#include "smtc_LazyClassPtr.h"
#include "smtc_ParamPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  void declareLazyClassObjParamSet (LazyClassPtr const & lazy_class, ParamPtrVector const & param_set, BaseSpecPtrVector const & base_spec_set, bool as_ref = false);
}
#undef LZZ_INLINE
#endif
