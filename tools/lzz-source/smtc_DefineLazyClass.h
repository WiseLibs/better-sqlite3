// smtc_DefineLazyClass.h
//

#ifndef LZZ_smtc_DefineLazyClass_h
#define LZZ_smtc_DefineLazyClass_h
#include "smtc_BaseSpecPtrVector.h"
#include "smtc_ClassKey.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_ScopePtr.h"
#include "gram_SpecSel.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr defineLazyClass (ScopePtr const & scope, gram::SpecSel const & spec_sel, ClassKey key, NamePtr const & name, bool is_dll_api, ParamPtrVector const & param_set, bool vararg, BaseSpecPtrVector const & base_spec_set);
}
#undef LZZ_INLINE
#endif
