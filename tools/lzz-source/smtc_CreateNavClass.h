// smtc_CreateNavClass.h
//

#ifndef LZZ_smtc_CreateNavClass_h
#define LZZ_smtc_CreateNavClass_h
// semantic
#include "smtc_BaseSpecPtrVector.h"
#include "smtc_ClassKey.h"
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"
#include "smtc_NavClassPtr.h"
#include "smtc_ParamPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  NavClassPtr createNavClass (int flags, NamePtr const & name, ParamPtrVector const & ctor_param_set, BaseSpecPtrVector const & base_spec_set, CvType const & ret_type, CvType const & node_type, ParamPtrVector const & submit_param_set);
}
#undef LZZ_INLINE
#endif
