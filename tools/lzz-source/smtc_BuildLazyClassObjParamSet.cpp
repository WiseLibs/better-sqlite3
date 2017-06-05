// smtc_BuildLazyClassObjParamSet.cpp
//

#include "smtc_BuildLazyClassObjParamSet.h"
// std lib
#include <algorithm>

// semantic
#include "smtc_HasLazyBaseSpecArg.h"
#include "smtc_NameToString.h"
#include "smtc_Param.h"
#define LZZ_INLINE inline
namespace smtc
{
  void buildLazyClassObjParamSet (ParamPtrVector const & param_set, BaseSpecPtrVector const & base_spec_set, ParamPtrVector & obj_param_set)
  {
    for (ParamPtrVectorConstIter beg = param_set.begin (), end = param_set.end (); beg != end; ++ beg)
    {
      ParamPtr const & param = * beg;
      util::String arg = nameToString (param->getName ());
      if (std::find_if (base_spec_set.begin (), base_spec_set.end (), HasLazyBaseSpecArg (arg)) == base_spec_set.end ())
      {
        obj_param_set.push_back (param);
      }
    }
  }
}
#undef LZZ_INLINE
