// smtc_CreateNsScope.h
//

#ifndef LZZ_smtc_CreateNsScope_h
#define LZZ_smtc_CreateNsScope_h
// semantic
#include "smtc_NsPtr.h"
#include "smtc_ScopePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  ScopePtr createNsScope (NsPtr const & ns);
}
#undef LZZ_INLINE
#endif
