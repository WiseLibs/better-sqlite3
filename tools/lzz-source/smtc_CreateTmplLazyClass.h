// smtc_CreateTmplLazyClass.h
//

#ifndef LZZ_smtc_CreateTmplLazyClass_h
#define LZZ_smtc_CreateTmplLazyClass_h
// semantic
#include "smtc_BaseSpecPtrVector.h"
#include "smtc_ClassKey.h"
#include "smtc_LazyClassPtr.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_TmplLazyClassPtr.h"
#include "smtc_TmplSpecPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplLazyClassPtr createTmplLazyClass (TmplSpecPtrVector const & tmpl_spec_set, int flags, ClassKey key, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, BaseSpecPtrVector const & base_spec_set);
}
namespace smtc
{
  TmplLazyClassPtr createTmplLazyClass (TmplSpecPtrVector const & tmpl_spec_set, LazyClassPtr const & lazy_class);
}
#undef LZZ_INLINE
#endif
