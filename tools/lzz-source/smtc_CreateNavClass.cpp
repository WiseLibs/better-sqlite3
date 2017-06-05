// smtc_CreateNavClass.cpp
//

#include "smtc_CreateNavClass.h"
// semantic
#include "smtc_NavClass.h"
#define LZZ_INLINE inline
namespace smtc
{
  NavClassPtr createNavClass (int flags, NamePtr const & name, ParamPtrVector const & ctor_param_set, BaseSpecPtrVector const & base_spec_set, CvType const & ret_type, CvType const & node_type, ParamPtrVector const & submit_param_set)
  {
    return new NavClass (flags, name, ctor_param_set, base_spec_set, ret_type, node_type, submit_param_set);
  }
}
#undef LZZ_INLINE
