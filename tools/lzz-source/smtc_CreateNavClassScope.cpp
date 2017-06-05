// smtc_CreateNavClassScope.cpp
//

#include "smtc_CreateNavClassScope.h"
// semantic
#include "smtc_NavClassScope.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createNavClassScope (NavClassPtr const & nav_class)
  {
    return new NavClassScope (nav_class);
  }
}
#undef LZZ_INLINE
