// smtc_DeclareLazyClassObjParamSet.cpp
//

#include "smtc_DeclareLazyClassObjParamSet.h"
// std lib
#include <algorithm>

// semantic
#include "smtc_BuildLazyClassObjParamSet.h"
#include "smtc_DeclareParamAsMbrObj.h"
#include "smtc_LazyClass.h"
#define LZZ_INLINE inline
namespace smtc
{
  void declareLazyClassObjParamSet (LazyClassPtr const & lazy_class, ParamPtrVector const & param_set, BaseSpecPtrVector const & base_spec_set, bool as_ref)
  {
    ParamPtrVector obj_param_set;
    buildLazyClassObjParamSet (param_set, base_spec_set, obj_param_set);
    if (! obj_param_set.empty ())
    {
      // TBD: private or protected ... then change back to default?
      std::for_each (obj_param_set.begin (), obj_param_set.end (), DeclareParamAsMbrObj (lazy_class, as_ref));
    }
  }
}
#undef LZZ_INLINE
