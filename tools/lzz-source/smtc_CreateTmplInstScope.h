// smtc_CreateTmplInstScope.h
//

#ifndef LZZ_smtc_CreateTmplInstScope_h
#define LZZ_smtc_CreateTmplInstScope_h
// semantic
#include "smtc_ScopePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createTmplInstScope (ScopePtr const & parent);
}
#undef LZZ_INLINE
#endif
