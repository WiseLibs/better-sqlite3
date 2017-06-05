// smtc_DefineNavClass.h
//

#ifndef LZZ_smtc_DefineNavClass_h
#define LZZ_smtc_DefineNavClass_h
// semantic
#include "smtc_BaseSpecPtrVector.h"
#include "smtc_CvType.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_ScopePtr.h"

// gram
#include "gram_SpecSel.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr defineNavClass (ScopePtr const & scope, gram::SpecSel const & spec_sel, CvType const & ret_type, NamePtr const & name, CvType const & node_type, ParamPtrVector const & param_set, BaseSpecPtrVector const & base_spec_set);
}
#undef LZZ_INLINE
#endif
