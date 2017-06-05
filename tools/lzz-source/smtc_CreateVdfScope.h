// smtc_CreateVdfScope.h
//

#ifndef LZZ_smtc_CreateVdfScope_h
#define LZZ_smtc_CreateVdfScope_h
// semantic
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_ScopePtr.h"
#include "smtc_ThrowSpecPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createVdfScope (NsPtr const & outer_ns, NamePtr const & base_type_name, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, ThrowSpecPtr const & throw_spec, NsPtr const & private_ns);
}
#undef LZZ_INLINE
#endif
