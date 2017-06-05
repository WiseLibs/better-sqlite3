// smtc_OpenTmplInst.cpp
//

#include "smtc_OpenTmplInst.h"
// semantic
#include "smtc_CreateTmplInstScope.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr openTmplInst (ScopePtr const & scope)
  {
    return createTmplInstScope (scope.unref ());
  }
}
#undef LZZ_INLINE
