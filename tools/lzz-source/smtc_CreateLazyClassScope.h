// smtc_CreateLazyClassScope.h
//

#ifndef LZZ_smtc_CreateLazyClassScope_h
#define LZZ_smtc_CreateLazyClassScope_h
// semantic
#include "smtc_LazyClassPtr.h"
#include "smtc_ScopePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createLazyClassScope (LazyClassPtr const & lazy_class);
}
#undef LZZ_INLINE
#endif
