// smtc_CreateTmplLazyClass.cpp
//

#include "smtc_CreateTmplLazyClass.h"
// semantic
#include "smtc_CreateLazyClass.h"
#include "smtc_TmplLazyClass.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplLazyClassPtr createTmplLazyClass (TmplSpecPtrVector const & tmpl_spec_set, int flags, ClassKey key, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, BaseSpecPtrVector const & base_spec_set)
  {
    bool is_dll_api = false;
    LazyClassPtr lazy_class = createLazyClass (flags, key, name, is_dll_api, param_set, vararg, base_spec_set);
    return new TmplLazyClass (tmpl_spec_set, lazy_class);
  }
}
namespace smtc
{
  TmplLazyClassPtr createTmplLazyClass (TmplSpecPtrVector const & tmpl_spec_set, LazyClassPtr const & lazy_class)
  {
    return new TmplLazyClass (tmpl_spec_set, lazy_class);
  }
}
#undef LZZ_INLINE
