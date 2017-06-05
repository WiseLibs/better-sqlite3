// smtc_CreateLazyClass.h
//

#ifndef LZZ_smtc_CreateLazyClass_h
#define LZZ_smtc_CreateLazyClass_h
// semantic
#include "smtc_BaseSpecPtrVector.h"
#include "smtc_ClassKey.h"
#include "smtc_LazyClassPtr.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtrVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  LazyClassPtr createLazyClass (int flags, ClassKey key, NamePtr const & name, bool is_dll_api, ParamPtrVector const & param_set, bool vararg, BaseSpecPtrVector const & base_spec_set);
}
#undef LZZ_INLINE
#endif
