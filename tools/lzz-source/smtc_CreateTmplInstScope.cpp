// smtc_CreateTmplInstScope.cpp
//

#include "smtc_CreateTmplInstScope.h"
// semantic
#include "smtc_TmplInstScope.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createTmplInstScope (ScopePtr const & parent)
  {
    return new TmplInstScope (parent);
  }
}
#undef LZZ_INLINE
