// smtc_CreateLazyClassScope.cpp
//

#include "smtc_CreateLazyClassScope.h"
// semantic
#include "smtc_LazyClassScope.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createLazyClassScope (LazyClassPtr const & lazy_class)
  {
    return new LazyClassScope (lazy_class);
  }
}
#undef LZZ_INLINE
