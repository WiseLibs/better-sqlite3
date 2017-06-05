// smtc_CreateVdfScope.cpp
//

#include "smtc_CreateVdfScope.h"
// semantic
#include "smtc_VdfScope.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createVdfScope (NsPtr const & outer_ns, NamePtr const & base_type_name, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, ThrowSpecPtr const & throw_spec, NsPtr const & private_ns)
  {
    return new VdfScope (outer_ns, base_type_name, ret_type, name, param_set, vararg, throw_spec, private_ns);
  }
}
#undef LZZ_INLINE
