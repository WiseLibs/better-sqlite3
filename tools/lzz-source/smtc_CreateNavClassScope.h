// smtc_CreateNavClassScope.h
//

#ifndef LZZ_smtc_CreateNavClassScope_h
#define LZZ_smtc_CreateNavClassScope_h
// semantic
#include "smtc_NavClassPtr.h"
#include "smtc_ScopePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createNavClassScope (NavClassPtr const & nav_class);
}
#undef LZZ_INLINE
#endif
