// smtc_CreateLazyClass.cpp
//

#include "smtc_CreateLazyClass.h"
// semantic
#include "smtc_LazyClass.h"
#define LZZ_INLINE inline
namespace smtc
{
  LazyClassPtr createLazyClass (int flags, ClassKey key, NamePtr const & name, bool is_dll_api, ParamPtrVector const & param_set, bool vararg, BaseSpecPtrVector const & base_spec_set)
  {
    return new LazyClass (flags, key, name, is_dll_api, param_set, vararg, base_spec_set);
  }
}
#undef LZZ_INLINE
